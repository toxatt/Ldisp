/*
 * cmd.c
 *
 *  Created on: 22 мая 2019 г.
 *      Author: anton
 */

#include "FreeRTOS.h"
#include "cmd.h"
#include "strings.h"
#include "hardware.h"
#include "semphr.h"

#include "utility.h"
#include "main.h"
#include "debug.h"
#include "string.h"
#include "stdlib.h"
#include "stdio_ext.h"
#include <ctype.h>
#include "tok.h"


extern xSemaphoreHandle S_Save;

//#define MAXSETPARAM 16

uint8_t GGC_GprsSettings		(char *, const GgCommand_t *, bool);
uint8_t GGC_StartTracking		(char *, const GgCommand_t *, bool);
uint8_t GGC_StopTracking		(char *, const GgCommand_t *, bool);
uint8_t GGC_PollPosition		(char *, const GgCommand_t *, bool);
uint8_t GGC_DeviceReset			(char *, const GgCommand_t *, bool);
uint8_t GGC_FwUpdate		  	(char *, const GgCommand_t *, bool);
uint8_t GGC_InitSMS			  	(char *, const GgCommand_t *, bool);

uint8_t GGC_CPUReset			(char *,const SMS_Command_t *, bool);
uint8_t GGC_SetParamHandle		(char *,const SMS_Command_t *, bool);
uint8_t GGC_GetParamHandle		(char * cmd, const  SMS_Command_t * gg_cmd, bool exec);

uint8_t GGR_Command				(char *, int buf_size, const char *cmd);
uint8_t GGR_General				(char *, int buf_size, bool sms, const GgCommand_t * cmd);
uint8_t GGR_GprsSettings		(char *, int buf_size, bool sms, const GgCommand_t * cmd);
uint8_t GGR_FwUpdate			(char *, int buf_size, bool sms, const GgCommand_t * cmd);

uint8_t GGR_Status(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd);

uint8_t GGR_GetVer(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd);

uint8_t GGR_SetParamResp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd);
uint8_t GGR_GetParamResp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd);
uint8_t GGR_GetIOResp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd);
uint8_t GGR_GetGPSResp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd);

uint8_t GGC_TPASS_Handle(char * cmd,  const SMS_Command_t * gg_cmd, bool exec);
uint8_t GGR_TPASS_Resp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd);
uint8_t GGR_save_param_resp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd);

uint8_t GGR_SendMessage(char *, const GgCommand_t *, bool);
uint8_t GGC_ID_Handle(char * cmd,  const SMS_Command_t * gg_cmd, bool exec);
uint8_t GGC_save_param_Handle(char * cmd,  const SMS_Command_t * gg_cmd, bool exec);


uint8_t CMD_Parsing (char * SMS_ptr,char * outbuf,uint8_t src);
uint8_t * GetVer (void);

//GgCommandCounts GprsSetCounts;
//GgCommandCounts StartTrackingCounts;
//GgCommandCounts FwUpdateCounts;
GgCommandCounts InitSMSCounts;

uint32_t auth_tick;


const SMS_Command_t SMS_CMDs[] =
{
  // CMD           count          number param  Handle               Response
  {"getstatus",   &InitSMSCounts,   0,        NULL,               		GGR_Status },
  {"getweektime", &InitSMSCounts,   0,        NULL,               		NULL},
  {"getver",      &InitSMSCounts,   0,        NULL,               		GGR_GetVer},
  {"cpureset",    &InitSMSCounts,   0,        GGC_CPUReset,       		NULL},
  {"getparam",    &InitSMSCounts,   1,        GGC_GetParamHandle, 		GGR_GetParamResp},
  {"getio",       &InitSMSCounts,   0,        NULL,               		GGR_GetIOResp},
  {"setparam",    &InitSMSCounts,   2,     	  GGC_SetParamHandle,		GGR_SetParamResp},
  {"saveparam",   &InitSMSCounts,   0,        GGC_save_param_Handle,	GGR_save_param_resp},
  {"getgps",      &InitSMSCounts,   0,        NULL,               		GGR_GetGPSResp},
  {"TPASS:",      &InitSMSCounts,   0,        GGC_TPASS_Handle,   		GGR_TPASS_Resp},

//  {"$",      	  &InitSMSCounts,   0,        GGC_ID_Handle,   	  		NULL},
  {NULL}
};




 const SET_CMD_t SMS_CMD[] =
{
//PARA	   type						assert		offset
  {0,   	cmd_type_string, 		"%s",		0 },
  {200, 	cmd_type_1byte,  		"%d", 		offsetof(T_settings, MY_ADDR)  },   //
  {2,   	cmd_type_double,		"%f", 		offsetof(T_settings, cnt_ratio)},     //
  {3,   	cmd_type_double,		"%f", 		offsetof(T_settings, cnt_pulses_per_litre)}, //
  {100,   	cmd_type_4byte,			"%d", 		offsetof(T_settings, cnt_EX_trim)}, //
  {101,   	cmd_type_4byte,			"%d", 		offsetof(T_settings, cnt_start)}, //
  {110,   	cmd_type_1byte,			"%d", 		offsetof(T_settings, mode)}, //
  {120,   	cmd_type_1byte,			"%d", 		offsetof(T_settings, timezone)}, //
  {7200,   	cmd_type_1byte,			"%d", 		offsetof(T_settings, MASTER_Dispay.addr)}, //
  {7800,   	cmd_type_4byte,			"%X", 		offsetof(T_settings, MASTER_Dispay.pgn)}, //
  {7400,   	cmd_type_1byte,			"%d", 		offsetof(T_settings, MASTER_Dispay.start)}, //
  {7600,   	cmd_type_1byte,			"%d", 		offsetof(T_settings, MASTER_Dispay.bit)}, //
  {8000,   	cmd_type_1byte,			"%d", 		offsetof(T_settings, MASTER_Dispay.timeout)}, //
  {910,   	cmd_type_4byte,			"%d", 		offsetof(T_settings, TPASS)} //
//  {281,		1,						"%d", 		offsetof(T_settings, crc)},
};


 char sms_cmd_buffer_out[180];

 set_new_t set_new;

 char GG_FwFileName[32];
 int  GG_FwSmsIndex;


 /*******************************************************************************
 * Function Name	:	GGR_SendMessage
 * Description	:
 *******************************************************************************/
 uint8_t GGR_SendMessage(char * cmd, const GgCommand_t * gg_cmd, bool exec)
 {
 	return E_OK;
 }

 /*******************************************************************************
 * Function Name	:	GGC_FwUpdate
 * Description	:
 *******************************************************************************/
 uint8_t GGC_FwUpdate(char * cmd, const GgCommand_t * gg_cmd, bool exec)
 {
 	int nsize = TokenSizeComma(cmd);
 	if (nsize > 0 && nsize < sizeof(GG_FwFileName) - 1)
 	{
 		strncpy(GG_FwFileName, cmd, nsize);
 		GG_FwFileName[nsize] = 0;
 		return E_OK;
 	}
 	return E_ERROR;
 }


 /*******************************************************************************
 * Function Name	:	GGR_FwUpdate
 * Description	:
 *******************************************************************************/
 uint8_t GGR_FwUpdate(char* buffer, int buf_size, bool sms, const GgCommand_t * cmd)
 {
 	if (sms)
 	{
 		if (buffer == NULL && buf_size != 0)
 			GG_FwSmsIndex = buf_size;
 		return E_ERROR;
 	}
 	return GGR_Command(buffer, buf_size, cmd->Command);
 }

 /*******************************************************************************
 * Function Name	:	GGC_GprsSettings
 * Description	:
 *******************************************************************************/
 uint8_t GGC_GprsSettings(char * cmd, const GgCommand_t * gg_cmd, bool exec)
 {
 	int size;
 	uint8_t state = 0;
 	// apn,username,password,hostname,port
 	while (cmd != NULL && state < 99)
 	{
 		size = TokenSizeComma(cmd);
 		switch (state)
 		{
 			case 0:
 				if (size > 0 && size < (sizeof(settings.MY_ADDR) - 1))
 				{
 					if (exec)
 					{
 						//strncpy(settings.MY_ADDR, cmd, size);
 						//settings.MY_ADDR[size] = 0;
 					}
 				}
 				else
 					state = 99;
 				break;
 			case 1:
 				if (size > 0 && size < (sizeof(settings.cnt_ratio) - 1))
 				{
 					if (exec)
 					{
 					//	strncpy(settings.cnt_ratio, cmd, size);
 						//settings.cnt_ratio[size] = 0;
 					}
 				}
 				else
 					//settings.GPRS_USERNAME[0] = 0;
 				break;
 			case 2:
// 				if (size > 0 && size < (sizeof(settings.GPRS_PASSWORD) - 1))
// 				{
// 					if (exec)
// 					{
// 						strncpy(settings.GPRS_PASSWORD, cmd, size);
// 						settings.GPRS_PASSWORD[size] = 0;
// 					}
// 				}
// 				else
// 					settings.GPRS_PASSWORD[0] = 0;
 				break;
 			case 3:
// 				if (size > 0 && size < (sizeof(settings.HOST_ADDR) - 1))
// 				{
// 					if (exec)
// 					{
// 						strncpy(settings.HOST_ADDR, cmd, size);
// 						settings.HOST_ADDR[size] = 0;
// 					}
// 				}
// 				else
// 					state = 99;
 				break;
 			case 4:
// 				if (size > 0 && size < (sizeof(settings.HOST_PORT) - 1))
// 				{
// 					if (exec)
// 					{
// 						strncpy(settings.HOST_PORT, cmd, size);
// 						settings.HOST_PORT[size] = 0;
// 					}
// 					return E_OK;
// 				}
// 				else
// 					state = 99;
 				break;
 		}
 		cmd = TokenNextComma(cmd);
 		state++;
 	}
 	return E_ERROR;
 }

 /*******************************************************************************
 * Function Name	:GGC_GprsSettings
 * Description	:	Send message to host
 *******************************************************************************/
 uint8_t GGR_Command(char* buffer, int buf_size, const char *cmd)
 {
 	if (buffer != NULL && buf_size != 0)
 	{

 		return E_OK;
 	}
 	return E_ERROR;
 }

 /*******************************************************************************
 * Function Name	:	GGC_GprsSettings
 * Description	:	Send message to host
 *******************************************************************************/
 uint8_t GGR_General(char* buffer, int buf_size, bool sms, const GgCommand_t * cmd)
 {
 	if (sms)
 		return E_ERROR;
 	return GGR_Command(buffer, buf_size, cmd->Command);
 }

 /*******************************************************************************
 * Function Name	:	GGC_GprsSettings
 * Description	:	Send message to host
 *******************************************************************************/
 uint8_t GGR_GprsSettings(char* buffer, int buf_size, bool sms, const GgCommand_t * cmd)
 {
 	if (!sms && buffer != NULL && buf_size != 0)
 	{

 		return E_OK;
 	}
 	return E_ERROR;
 }

 /*******************************************************************************
 * Function Name	:	GGC_StartTracking
 * Description	:
 *******************************************************************************/
 uint8_t GGC_StartTracking(char* cmd, const GgCommand_t * ggCommand, bool exec)
 {
 	//char *token = cmd;
 //	int value;
 //	while (token != NULL)
 //	{
 //		if (TokenSizeComma(token) >= (sizeof("TimeFilter=") - 1 + 2))
 //		{
 //			if (strncmp(token, "TimeFilter=", sizeof("TimeFilter=") - 1) == 0)
 //			{
 //				value = nmea_atoi(token + sizeof("TimeFilter=") - 1, 5, 10);
 //				if (value >= 15 && value <= (60 * 60))
 //				{
 //					if (exec && GpsContext.SendInterval != value)
 //						GpsContext.SendInterval = value;
 //					return E_OK;
 //				}
 //				return E_ERROR;
 //			}
 //		}
 //		token = TokenNextComma(token);
 //	}
 	return E_ERROR;
 }

 /*******************************************************************************
 * Function Name	:	GGC_StopTracking
 * Description	:
 *******************************************************************************/
 uint8_t GGC_StopTracking(char* cmd, const GgCommand_t * ggCommand, bool exec)
 {
 	return E_OK;
 }
 /*******************************************************************************
 * Function Name	:	GGC_PollPosition
 * Description	:
 *******************************************************************************/
 uint8_t GGC_PollPosition(char* cmd, const GgCommand_t * ggCommand, bool exec)
 {
 	return E_OK;
 }
 /*******************************************************************************
 * Function Name	:	GGC_DeviceReset
 * Description	:
 *******************************************************************************/
 uint8_t GGC_DeviceReset(char* cmd, const GgCommand_t * ggCommand, bool exec)
 {
 	return E_OK;
 }

 /*******************************************************************************
 * Function Name	:	ggFindCommand
 * Description	:
 *******************************************************************************/
 const GgCommand_t * ggFindCommand(char *cmd, const GgCommand_t * cmds, int size)
 {
 	while (cmds->Command != NULL)
 	{
 		if (strncmp(cmd, cmds->Command, size) == 0)
 			return cmds;
 		cmds++;
 	}
 	return NULL;
 }

 /*******************************************************************************
 * Function Name	:	ggFindParam
 * Description	:
 *******************************************************************************/
 const SET_CMD_t * GG_SET_FindParam(uint16_t param)
 {
    //{1,   "%s8", offsetof(settings_t,SMS_login)  },
   uint16_t i=0;
 	while (SMS_CMD[i].param_ID != NULL)
 	{
 		if (param == SMS_CMD[i++].param_ID)
 			return &SMS_CMD[i];
 		i++;
 	}
 	return NULL;
 }

 /*******************************************************************************
 * Function Name	:	CheckGGCommand
 * Description	:	Compare and remove checksum from line
 *******************************************************************************/
 uint8_t GG_CheckCommand(char * cmd)
 {
 	uint8_t cs;
 	char * pos;
 	int len;

 	len = strlen(cmd);
 	if (len > 10)
 	{
 		pos = strchr(cmd, '*');
 		if (pos != NULL && ((pos - cmd) == (len - 3)))
 		{
 			cs = nmea_atoi(pos + 1, 2, 16);
 			*pos = 0;
 			if (cs == nmea_calc_crc(cmd + 1, len - 4))
 				return E_OK;
 		}
 	}
 	return E_BAD_COMMAND;
 }

 /*******************************************************************************
 * Function Name	:	ProcessGpsGateCommand
 * Description	:
 *******************************************************************************/
 const GgCommand_t * ProcessGpsGateCommand(char * text, bool exec)
 {
 //	int size;
 //	uint8_t state = 0;
 //	const GgCommand_t * gg_cmd = NULL;

 //	while (text != NULL)
 //	{
 //		size = TokenSizeComma(text);
 //		if (state == 0)
 //		{	// Check for checksum and command
 //			if (size == 6 /*&& GG_CheckCommand(text) == E_OK*/)
 //			{
 //				if (strncmp(text, "$FRRET", size) == 0)
 //					gg_cmd = &GgReplayMap[0];
 //				else if (strncmp(text, "$FRCMD", size) == 0)
 //					gg_cmd = &GgCommandMap[0];
 //			}
 //			if (gg_cmd == NULL)
 //				break;
 //		}
 //		else if (state == 1)
 //		{	// Check IMEI code from command and module
 //			if (size == 0 || strncmp(text, GsmIMEI(), size) != 0)
 //				break;
 //		}
 //		else if (state == 2)
 //		{	// Find command and execute handler
 //			if (size != 0
 //			&&	(gg_cmd = ggFindCommand(text, gg_cmd, size)) != NULL
 //				)
 //			{
 //				text = TokenNextComma(text);	// skip command name
 //				text = TokenNextComma(text);	// skip inline
 //				if ((gg_cmd->Handler)(text, gg_cmd, exec) == E_OK)
 //					return gg_cmd;
 //			}
 //			break;
 //		}

 //		text = TokenNextComma(text);
 //		++state;
 //	}

 	return NULL;
 }

 /*******************************************************************************
 * Function Name	:	ProcessGpsGateCommand
 * Description	:
 *******************************************************************************/
 const SMS_Command_t * ProcessCommand(char * text, bool exec, uint8_t * len)
 {
 	int size;
   uint16_t i;

   const SMS_Command_t * gg_cmd = NULL;
   char * token,* start;

   start = text;
   text = strpbrk(text,"abcdefghigklmnopgrstuvwxyz$T");
   //2 parse cmd
 	while (text != NULL)
 	{
     if ((token =  strpbrk(text,"; "))!=NULL)
     size = (token - text); else size = strlen(text);    //size of parametr to token

 			//Pars token, is cmd?
       i=0;
        if (size == 0) return NULL;  //End sms
       while(SMS_CMDs[i].Command != NULL)
       {
          if (strlen(SMS_CMDs[i].Command) == size
            && memcmp(text,&SMS_CMDs[i].Command[0], size) == 0)
          {
            *len = (text - start) + size; //how much of chars we was used
            gg_cmd = &SMS_CMDs[i];
            break;
          };
          i++;
       };
        if (gg_cmd != NULL)
          return gg_cmd;
        text++;
 	}

 	return NULL;
 }

  /*******************************************************************************
 * Function Name	:	GGC_Authorization_Check
 * Description	:	Parsing begin of SMS for check password if needed
  *******************************************************************************/
 uint8_t GG_Authorization_Check (char *text, char * da, uint8_t * len)
 {
   uint32_t i;
   uint8_t size;

   bool phones_sets = false;
   bool phone_ok = false;
   *len =0;

//   for (i=0;i<8;i++)
//   {
//     if (settings.Phones[i][0] != 0 )
//       {
//         phones_sets = true;
//       } else continue;
//
//     if (memcmp((da+1),&settings.Phones[i][0],strlen(&settings.Phones[i][0]))==0)
//         {
//           phone_ok = true;
//           break;
//         };
//   };
//
//   if ((phones_sets & phone_ok )|| phones_sets == false  )
//   {
//     if (settings.SMS_login[0] != 0)
//       {
//
//         size = strlen(settings.SMS_login); //login size
//         if ((TokenSize(text,' ') == size) && (memcmp(text,&settings.SMS_login[0],size)==0))
//         {
//           *len = (size+1);   //for shift buffer ptr size of login
//           DebugPutLineTASKln("SMS access granted");
//
//           return E_OK;
//         };
//         return E_SMS_ACCESS_ERROR;
//       }
//       else return E_OK; //if login
//
//    };
//
//     return E_SMS_ACCESS_ERROR;

   return 0;
 };

 /*******************************************************************************
 * Function Name	:	GGC_Status
 * Description	:	Send message to admin
 *******************************************************************************/
 uint8_t GGR_Status(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd)
 {
    char restrict_buf[32];
     //sprintf(restrict_buf,"%u", gsm
   DEBUG("SMS getstatus detected\r\n");
 	if ( (buffer != NULL ))
 	{
//     buffer = strcpyEx( strcpyEx( strcpyEx( strcpyEx( strcpyEx( strcpyEx( strcpyEx( buffer,
//     "OK "),
//     ","),
//     "Link:"),
//     GsmTCPIsConnected()? "1 ":"0 "),
//     "IP: "),
//     "GSM: "),
//     "VER: "VERSION_INFO);
//
//     DebugPutLine(buffer);
//     DEBUG("\r\n");
//     DEBUG("Send getstatus SMS\r\n");
//
//     *sms = true;
     return E_OK;
   }
 	return E_ERROR;
 }


 /*******************************************************************************
 * Function Name	:	GGR_GetVer
 * Description	:	Send message to admin
 *******************************************************************************/
 uint8_t GGR_GetVer(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd)
 {
   DEBUG("SMS getver detected\r\n");

 	if (buffer != NULL )
 	{
 		buffer = strcpyEx( strcpyEx( strcpyEx( buffer,
 			"\r\n<"),
 			GetVer()),
 		 	">\r\n");

 	   *sms = true;
     DebugPutLine(buffer);
     DEBUG("\r\n");
    // DEBUG("Send getstatus SMS\r\n");
 		return E_OK;
 	}
 	return E_ERROR;
 }






 /*******************************************************************************
 * Function Name	:	GGR_GetParamResp
 * Description	:	Send message with new param to host
 *******************************************************************************/
 uint8_t GGR_GetParamResp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd)
 {
   DEBUG("SMS get param detected\r\n");
    char restrict_buf[32];
 	if (buffer != NULL && buf_size != 0)
 	{
 //		buffer =  strcpyEx( strcpyEx( strcpyEx( strcpyEx( buffer,
 //    "Param ID "),
 //
 //			"0 "),
 //    "New val:"),
 //      "0");

 		 if (set_new.param_ID !=0)
 		    {
 		       buffer += sprintf(buffer,"\r\n\r\nParam ID: %04d Val: %s",
 		    		   SMS_CMD[set_new.param_ID].param_ID,set_new.out_string);

 		       if (set_new.source == source_configtool)
 		    	 buffer += sprintf(buffer,"\r\n<%04d %s>\r\n\r\n\r",
 		    			 SMS_CMD[set_new.param_ID].param_ID,set_new.out_string);
 		    }
        DebugPutLine(buffer);
     DEBUG("\r\n");
        *sms = true;
 		return E_OK;
 	}
 	return E_ERROR;
 }

 /*******************************************************************************
 * Function Name	:	GGR_SetParamResp
 * Description	:	Send message with new param to host
 *******************************************************************************/
 uint8_t GGR_SetParamResp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd)
 {
   DEBUG("SMS set param detected\r\n");
    char restrict_buf[32];
 	if (buffer != NULL && buf_size != 0)
 	{
 //		buffer =  strcpyEx( strcpyEx( strcpyEx( strcpyEx( buffer,
 //    "Param ID "),
 //
 //			"0 "),
 //    "New val:"),
 //      "0");

    if (set_new.param_ID !=0)
    {

       buffer += sprintf(buffer,"\r\n\r\nParam ID: %04d Val: %s",
    		   SMS_CMD[set_new.param_ID].param_ID,set_new.out_string);

       if (set_new.source == source_configtool)
    	 buffer += sprintf(buffer,"\r\n<%04d %s>\r\n\r\n\r",
    			 SMS_CMD[set_new.param_ID].param_ID,set_new.out_string);
    }
   //  else
    //   sprintf(buffer,""

 		return E_OK;
 	}
 	return E_ERROR;
 }


 uint32_t get_val(void * x)
 {
	 return (uint32_t)(x);
 }

 /*******************************************************************************
 * Function Name	:	GGC_GetParamHandle
 * Description	:	Send param
 *******************************************************************************/

 uint8_t GGC_GetParamHandle(char * cmd, const  SMS_Command_t * gg_cmd, bool exec)
 {
     uint8_t size, i;
     char *ptr,x;
     uint32_t param,xx,*pp;
     __IO double dd=0;
     __IO void *v=NULL;


     DEBUG("GetParam Handle\r\n");

     //parse param
   while(cmd!= NULL)
   {
     cmd = TokenNext(cmd,' ');
     if ((size = TokenSize(cmd,';'))==NULL) size = strlen(cmd);
     if ( (param = atoi(cmd))<=0xFFFF )
     {
       //test suppurted number param
        cmd = TokenNext(cmd,' ');
        if ((ptr = strpbrk(cmd," ;\0") )!= NULL ) size = (ptr - cmd);
        i = 0;
         do
         {
           if (param == SMS_CMD[i].param_ID )
           {
             //param if exist in list
//             sscanf(cmd,&SMS_CMD[i].cmd_assert,(void*)(uint32_t)(&settings+SMS_CMD[i].offset));
           //  if (nmea_scanf(cmd, size,SMS_CMD[i].cmd_assert,&set_new.param_val)!=NULL)
        	   if (1)
             {
               //assert  ok
               DEBUG("SMS GET PARAM ");
               set_new.param_ID  = i;

               ptr = (void*)&settings;
               ptr += SMS_CMD[i].offset;

               	  switch (SMS_CMD[i].type) {
					case cmd_type_string:
				//		sscanf(cmd,&SMS_CMD[i].cmd_assert,(void*)(uint32_t)(&settings_new+SMS_CMD[i].offset));
						sprintf((char *)&set_new.out_string,SMS_CMD[i].cmd_assert,ptr);
						break;
					case cmd_type_2byte:
					case cmd_type_4byte:
					case cmd_type_8byte:
					case cmd_type_1byte:

						 v = &settings;
						 v+= SMS_CMD[i].offset;
						 pp = v;
						 xx = *pp;
						 switch (SMS_CMD[i].type)
						 {
						 case cmd_type_1byte:
								xx &= 0xFF;
								break;
							case cmd_type_2byte:
								xx &= 0xFFFF;
								break;

							case cmd_type_4byte:
								xx &= 0xFFFFFFFF;
							default:
								break;

						 }
						sprintf((char *)&set_new.out_string,SMS_CMD[i].cmd_assert,xx);
						break;

					case cmd_type_double:
	            		   v = &settings;
	            		   v+= SMS_CMD[i].offset;
	            		   memcpy((uint8_t*)&dd,(uint8_t*)v,8);
	            		   sprintf((char*)&set_new.out_string,SMS_CMD[i].cmd_assert, dd );

						break;
					default:
						break;
				}
//               ptr = &settings + SMS_CMD[i].offset;
//               x =  (char)(*(SMS_CMD[i].cmd_assert+1));
//               if (x=='d')
//               {
//            	   sprintf(&set_new.param_val,SMS_CMD[i].cmd_assert,*ptr);
//               } else
//            	   if (x =='s')
//            	   {
//            		   sprintf(&set_new.param_val,SMS_CMD[i].cmd_assert,ptr);
//            	   }
//            	   else if (x=='f')
//            	   {
//            		   v = &settings;
//            		   v+= SMS_CMD[i].offset;
//            		  memcpy((void*)&dd,v,8);
//            		   sprintf((char*)&set_new.param_val,SMS_CMD[i].cmd_assert, dd );
//            	   }

               return E_OK;
             } else
             {
               set_new.param_ID =0;
              return E_BAD_RESPONSE;
             };
           };
           i++;
         } while (SMS_CMD[i].param_ID !=NULL);
     };
   };

 	return E_ERROR;
 }

/*******************************************************************************
 * Function Name	:	GGC_SetParamHandle
 * Description	:	Parse new param, send to flash task
 *******************************************************************************/

uint8_t GGC_SetParamHandle(char * cmd, const SMS_Command_t * gg_cmd, bool exec) {
	uint8_t size, i,byte_size;
	char *ptr;
	uint32_t param;
	//__IO double dd = 0;
	__IO void *v = NULL;

	DEBUG("SetParam Handle\r\n");

	//parse param
	while (cmd != NULL) {
		cmd = TokenNext(cmd, ' ');
		if ((size = TokenSize(cmd, ';')) == NULL)
			size = strlen(cmd);
		if ((param = atoi(cmd)) <= 0xFFFF) {
			//test supported number parameter
			cmd = TokenNext(cmd, ' ');
			if ((ptr = strpbrk(cmd, " ;\0")) != NULL)
				size = (ptr - cmd);
			i = 0;
			do {
				if (param == SMS_CMD[i].param_ID) {
					//param if exist in list

					//   	sscanf(cmd,size,"%s%d%f",&set_new.var_string,&set_new.var_uint,&set_new.var_double);
					//      if (nmea_scanf(cmd, size,SMS_CMD[i].cmd_assert,&set_new.var_string)!=NULL)
//            	nmea_scanf(cmd, size,SMS_CMD[i].cmd_assert,(&settings+SMS_CMD[i].offset));
					if (1) {
						//assert  ok
						DEBUG("SMS SET PARAM ");

						set_new.param_ID = i;
						switch (SMS_CMD[i].type) {
						case cmd_type_string:
							//		sscanf(cmd,&SMS_CMD[i].cmd_assert,(void*)(uint32_t)(&settings_new+SMS_CMD[i].offset));
							if (nmea_scanf(cmd, size, SMS_CMD[i].cmd_assert,
									&set_new.var_string) != NULL) {
								sprintf((char *) &set_new.out_string,
										SMS_CMD[i].cmd_assert,
										set_new.var_string);
							} else {
								set_new.param_ID = 0;
								return E_BAD_RESPONSE;
							}
							;
							break;
						case cmd_type_8byte:
						case cmd_type_4byte:
						case cmd_type_2byte:
						case cmd_type_1byte:

							if (nmea_scanf(cmd, size, SMS_CMD[i].cmd_assert,&set_new.var_uint) != NULL) {
								sprintf((char *) &set_new.out_string,
										SMS_CMD[i].cmd_assert,
										set_new.var_uint);
								switch (SMS_CMD[i].type)
								{
									case cmd_type_8byte:
										byte_size = 8;
										break;
									case cmd_type_4byte:
										byte_size = 4;
										break;
									case cmd_type_2byte:
										byte_size = 2;
										break;
									case cmd_type_1byte:
									default:
										byte_size = 1;
										break;
								}
								v = &settings;
								v += SMS_CMD[i].offset;
								memcpy((uint8_t*) v,(uint8_t*) &set_new.var_uint, byte_size);
								//nmea_scanf(cmd, size, SMS_CMD[i].cmd_assert, v);

								//								v = &settings;
//								v += SMS_CMD[i].offset;
//								*v = set_new.var_uint;
							} else {
								set_new.param_ID = 0;
								return E_BAD_RESPONSE;
							}
							break;

//							if (nmea_scanf(cmd, size, SMS_CMD[i].cmd_assert,
//																&set_new.var_uint) != NULL) {
//															sprintf((char *) &set_new.out_string,
//																	SMS_CMD[i].cmd_assert,
//																	set_new.var_uint);
//							} else {
//										set_new.param_ID = 0;
//										return E_BAD_RESPONSE;
//									}
//							break;
						case cmd_type_double:
							if (nmea_scanf(cmd, size, SMS_CMD[i].cmd_assert,
									&set_new.var_double) != NULL) {
								v = &settings;
								v += SMS_CMD[i].offset;
								memcpy((uint8_t*) v,
										(uint8_t*) &set_new.var_double, 8);
								sprintf((char*) &set_new.out_string,
										SMS_CMD[i].cmd_assert,
										set_new.var_double);
							} else {
								set_new.param_ID = 0;
								return E_BAD_RESPONSE;
							}

							break;
						default:
							break;
						}

						//break;//next param
						return E_OK;
					} else {
						set_new.param_ID = 0;
						return E_BAD_RESPONSE;
					};
				};
				i++;
			} while (SMS_CMD[i].param_ID != NULL);
		};
	};

	return E_ERROR;
}


 uint8_t GGR_GetIOResp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd)
 {
    DEBUG("SMS GetIO detected\r\n");

 	if (buffer != NULL )
 	{

 		buffer = strcpyEx(   buffer,
 			"OK ");

 	   *sms = true;
     DebugPutLine(buffer);
     DEBUG("\r\n");
    // DEBUG("Send getstatus SMS\r\n");
 		return E_OK;

 	}
 	return E_ERROR;
 };


  /*******************************************************************************
 * Function Name	:	 GGR_GetGPSResp
 * Description	:	Send message with GPS status to host
 *******************************************************************************/
 uint8_t GGR_GetGPSResp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd)
 {
    DEBUG("SMS GetGPS detected\r\n");

 	if (buffer != NULL )
 	{

 		buffer = strcpyEx(   buffer,
     "GPS: ");

 	   *sms = true;
     DebugPutLine(buffer);
     DEBUG("\r\n");
    // DEBUG("Send getstatus SMS\r\n");
 		return E_OK;
 	}
 	return E_ERROR;
 };

 uint8_t GGR_TPASS_Resp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd)
 {
	   DEBUG("TPASS response\r\n");

	 	if (buffer != NULL && (auth_tick + 30000 < xTaskGetTickCount() || auth_tick ==0))
	 	{
	 		auth_tick = xTaskGetTickCount();
	 		buffer = strcpyEx(   buffer,
	 			"\r\nTASK COM TERM: PASSWORD OK\r\n");

	 	   *sms = true;
	     DebugPutLine(buffer);
	     DEBUG("\r\n");
	    // DEBUG("Send getstatus SMS\r\n");
	 		return E_OK;

	 	}
	 	return E_ERROR;

 }


 uint8_t GGR_save_param_resp(char* buffer, int buf_size, bool *sms, const SMS_Command_t * cmd)
 {
	   DEBUG("save param response response\r\n");

	 	if (buffer != NULL )
	 	{
	 		buffer = strcpyEx(   buffer,
	 			"\r\n<PARAM SAVED>\r\n");
	 	   *sms = true;
	     DebugPutLine(buffer);
	     DEBUG("\r\n");
	    // DEBUG("Send getstatus SMS\r\n");
	 		return E_OK;

	 	}
	 	return E_ERROR;

 }

 /*******************************************************************************
 * Function Name	:	GGC_CPUReset
 * Description	:
 *******************************************************************************/
 uint8_t GGC_CPUReset(char * cmd,  const SMS_Command_t * gg_cmd, bool exec)
 {
 //	if (exec)
 //		GlobalStatus |= SMS_INIT_OK;
 //
	 NVIC_SystemReset();
 	return E_OK;
 }


 uint8_t * GetVer (void)
 {
	 return ((uint8_t*)VERSION_INFO);
 }

 /*******************************************************************************
 * Function Name	:	GGC_TPASS_Handle
 * Description	:
 *******************************************************************************/
 uint8_t GGC_TPASS_Handle(char * cmd,  const SMS_Command_t * gg_cmd, bool exec)
 {

		uint8_t size, i;
		char *ptr;
		uint32_t pass;

		DEBUG("TPASS Handle\r\n");

		//parse param
		while (cmd != NULL) {
			cmd = TokenNext(cmd, ' ');
			if ((size = TokenSize(cmd, ';')) == NULL)
				size = strlen(cmd);
			if ((pass = atoi(cmd)) <= 0xFFFF) {
				//test suppurted number param
				cmd = TokenNext(cmd, ' ');
				if ((ptr = strpbrk(cmd, " ;\0")) != NULL)
					size = (ptr - cmd);
				i = 0;
			}
		}
 	return E_OK;
 }
 /*******************************************************************************
  * Function Name	:	GGC_ID_Handle
  * Description	:
  *******************************************************************************/
  uint8_t GGC_ID_Handle(char * cmd,  const SMS_Command_t * gg_cmd, bool exec)
  {

 		uint8_t size, i;
 		char *ptr;
 		uint32_t pass;

 		DEBUG("ID Handle\r\n");

 		//parse param
 		while (cmd != NULL) {
 			cmd = TokenNext(cmd, ' ');
 			if ((size = TokenSize(cmd, ';')) == NULL)
 				size = strlen(cmd);
 			if ((pass = atoi(cmd)) <= 0xFFFF) {
 				//test suppurted number param
 				cmd = TokenNext(cmd, ' ');
 				if ((ptr = strpbrk(cmd, " ;\0")) != NULL)
 					size = (ptr - cmd);
 				i = 0;
 			}
 		}
  	return E_OK;
  }

  /*******************************************************************************
   * Function Name	:	GGC_save_param_Handle
   * Description	:
   *******************************************************************************/
   uint8_t GGC_save_param_Handle(char * cmd,  const SMS_Command_t * gg_cmd, bool exec)
   {

  		uint8_t size, i;
  		char *ptr;
  		uint32_t pass;

  		DEBUG("Save param Handle\r\n");
  		xSemaphoreGive(S_Save);
  		//parse param

   	return E_OK;
   }




 uint8_t CMD_Parsing (char * SMS_ptr,char * outbuf,uint8_t src)
 {

	 char * token, *SMS_ptr_send;
	 bool is_text, send, is_set = false;
	 uint8_t ntoken, flash_cmd = 0;
	 const SMS_Command_t *cmds;
	 SMS_ptr_send = outbuf;
	 if (src == 0xFE) set_new.source = source_configtool; else
		 if (src == 0xFD) set_new.source = source_tcp;

 //------------------------------------------------------------------------------------------------------------
	  do
	    {
	      cmds = NULL;
	      cmds = ProcessCommand (SMS_ptr, 0, &ntoken);
	      if (cmds == NULL)
		{    // unknown command
		     //next cmd

		}
	      else
		{
		  SMS_ptr += ntoken;
		  if (cmds->Handler != NULL)
		    {
		      //Handle comand
		      if ((cmds->Handler) (SMS_ptr, cmds, true) == E_OK)
			{	//OK

			  if (cmds->number_param != 0)
			    {
			      is_set = true;
			    };
			};
		    };
		  send = 0;

		  if (cmds->Response != NULL)
		    (cmds->Response) (SMS_ptr_send, ntoken, &send, cmds);

		  SMS_ptr_send += strlen (SMS_ptr_send);
		  set_new.param_ID = 0;
		}
	      SMS_ptr = TokenNext (SMS_ptr, ';');//strpbrk(SMS_ptr," ;");
	      if (SMS_ptr == NULL)
		{
		  //end of sms
		  if (is_set)
		    {
		      flash_cmd = 1;
		      //osSemaphoreWait(FlashSemaphoreHandle,0);
//              xQueueSend(set_qeue_handle,&flash_cmd,10);
//              xSemaphoreGive(FlashSemaphoreHandle);
		    };
		  if (strlen (sms_cmd_buffer_out))
		    {

		    //  if (E_OK == gsmSendSMS (gsmSenderDA, sms_cmd_buffer_out))
			 outbuf = sms_cmd_buffer_out;
			DEBUG("SMS send\n\r");
		    };
		};

	    }
	  while ((SMS_ptr != NULL));
 }



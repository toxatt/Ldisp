/*
 * cmd.h
 *
 *  Created on: 22 мая 2019 г.
 *      Author: anton
 */

#ifndef CMD_H_
#define CMD_H_

#include "stm32f10x.h"

#include <stdint.h>
#include <stdbool.h>
//#include "main.h"

typedef struct {
	uint32_t	DateTime;
	uint32_t	DateTimeInt;
	int			Index;
	int			Count;
} GgCommandCounts;


struct GgCommand_s {
	const char		* Command;
	GgCommandCounts * Counts;
			uint8_t	(*Handler)(char *, const struct GgCommand_s *, bool);
			uint8_t	(*Response)(char * buffer, int buf_size, bool sms, const struct GgCommand_s * cmd);
};

struct SMS_Command_s {
	const char		* Command;
	GgCommandCounts * Counts;
	uint8_t number_param;
	uint8_t	(*Handler)(char *, const struct SMS_Command_s *, bool);
	uint8_t	(*Response)(char * buffer, int buf_size, bool *sms, const struct SMS_Command_s * cmd);
};

enum
{
	cmd_type_string = 0,
	cmd_type_1byte,
	cmd_type_2byte,
	cmd_type_4byte,
	cmd_type_8byte,
	cmd_type_double

}e_cmd;

struct SET_CMD_s{
	uint16_t param_ID;
	uint8_t type;
	const char  * cmd_assert;
	uint32_t offset;
};

enum
{
	source_SMS=0,
	source_configtool,
	source_tcp
}E_SOURCE;

typedef struct {
	uint8_t source;
	uint16_t param_ID;
	char var_string[32], out_string[32];
	uint32_t var_uint;
	double var_double;
} set_new_t;

extern set_new_t set_new;


typedef struct GgCommand_s GgCommand_t;
typedef struct SMS_Command_s SMS_Command_t;
typedef struct SET_CMD_s SET_CMD_t;


typedef struct
{

} T_CMD_context;


extern const SMS_Command_t SMS_CMDs[] ;
extern set_new_t set_new;


const GgCommand_t * ProcessGpsGateCommand(char * cmd, bool);
const SMS_Command_t * ProcessCommand(char * text, bool exec,uint8_t * len);
uint8_t GG_CheckCommand(char *);
void GG_ClearAllCounts(void);
uint8_t GG_Authorization_Check (char *text, char * da, uint8_t * len);

extern  uint8_t CMD_Parsing (char * SMS_ptr,char * outbuf, uint8_t src);

#endif /* CMD_H_ */

/*
 * command.h
 *
 *  Created on: 2018Äê9ÔÂ15ÈÕ
 *      Author: Administrator
 */
#ifndef __COMMAND_H
#define __COMMAND_H

#ifndef NULL
#define NULL 0
#endif

#define CFG_CBSIZE  256    /* Console I/O Buffer Size	*/
#define CFG_MAXARGS 16     /* max number of command args	*/
#define MAX_COMMAND_LEN 30 /* command length */

/*
 * Monitor Command Table
 */
struct cmd_tbl_s
{
    char *name;     /* Command Name	*/
    int maxargs;    /* maximum number of arguments	*/
    /* Implementation function	*/
    int (*cmd)(struct cmd_tbl_s *, int, char *[]);
    char *usage; /* Usage message	(short)	*/
};


typedef struct cmd_tbl_s cmd_tbl_t;

void command_init(unsigned int BaudRate);
void sys_cmd_exe(void);


#endif

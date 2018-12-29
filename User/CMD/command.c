/*
 * command.c
 *
 *  Created on: 2018年9月15日
 *      Author: Administrator
 */
#include "main.h"

#define FLASH_LAST_PAGE 0X0807F800
#define FLASH_DATA_VAL 0x1234

unsigned char const idn[] = "Gost,Demo,BJA5.297.556,V1.30"; //”制造商“，”产品标号“，”产品序列号“，”软件版本号“
unsigned char const version[] = "V1.30";                    //版本号
unsigned char const data_str[] = __DATE__;                  //程序编译系统日期
unsigned char const time_str[] = __TIME__;                  //程序编译系统时间

int do_help(cmd_tbl_t *cmdtp, int argc, char *argv[]);
int do_upgrade(cmd_tbl_t *cmdtp, int argc, char *argv[]);
int do_reboot(cmd_tbl_t *cmdtp, int argc, char *argv[]);
int do_idn(cmd_tbl_t *cmdtp, int argc, char *argv[]);
int do_ver(cmd_tbl_t *cmdtp, int argc, char *argv[]);
int do_key(cmd_tbl_t *cmdtp, int argc, char *argv[]);
/**
  * @brief  系统命令结构体数组，添加命令添加结构体即可
  */
struct cmd_tbl_s sys_cmd_tab[] =
    {
        {"help", CFG_MAXARGS, do_help,
         "help    - Print online help\r\n"},
        {"upgrade", CFG_MAXARGS, do_upgrade,
         "upgrade - Upgrade system\r\n"},
        {"reboot", CFG_MAXARGS, do_reboot,
         "reboot  - Reboot the machine\r\n"},
        {"*idn?", CFG_MAXARGS, do_idn,
         "*idn?   - Identification query\r\n"},
        {"*key", CFG_MAXARGS, do_key,
         "*key    - Key test\r\n"},
        {"ver?", CFG_MAXARGS, do_ver,
         "ver?    - Print monitor version\r\n"}

};
#define __cmd_start (sys_cmd_tab[0])
#define __cmd_end (sys_cmd_tab[sizeof(sys_cmd_tab) / sizeof(struct cmd_tbl_s)])
/**
  * @brief  初始化串口控制器
  * @param  BaudRate:串口1波特率 
  * @retval 0,成功处理
  * 		其他,错误代码
  */
void command_init(u32 BaudRate)
{
    usart1_configuration(BaudRate); //初始化串口
}
/**
  * @brief  帮助命令help,打印出所有命令列表及简单帮助
  * @param  *cmdtp: 传入的结构体
  *           argc: 参数个数
  *          *argv: 参数二维数组
  * @retval 0,成功处理
  * 		其他,错误代码
  */
int do_help(cmd_tbl_t *cmdtp, int argc, char *argv[])
{
    cmdtp = NULL;
    if (argc == 1)
    {
        /* print short help (usage) */
        for (cmdtp = &__cmd_start; cmdtp != &__cmd_end; cmdtp++)
        {
            /* allow user abort */
            if (cmdtp->usage == NULL)
                continue;
            printf("%s", cmdtp->usage);
        }
        return 0;
    }
    else
    {
        printf("- No help available.\r\n");
        return 1;
    }
}
/**
  * @brief  hello测试用例
  * @param  *cmdtp: 传入的结构体
  *           argc: 参数个数
  *          *argv: 参数二维数组
  * @retval 0,成功处理
  * 		其他,错误代码
  */
int do_upgrade(cmd_tbl_t *cmdtp, int argc, char *argv[])
{
    __disable_irq();    
    FLASH_Unlock();
    FLASH_ProgramHalfWord(FLASH_LAST_PAGE, FLASH_DATA_VAL);
    NVIC_SystemReset();

    return 0;
}
/**
  * @brief  软件重启
  * @param  *cmdtp: 传入的结构体
  *           argc: 参数个数
  *          *argv: 参数二维数组
  * @retval 0,成功处理
  * 		其他,错误代码
  */
int do_reboot(cmd_tbl_t *cmdtp, int argc, char *argv[])
{
    __disable_irq();
    printf("reboot system!\r\n");
    NVIC_SystemReset();
    return 0;
}
/**
  * @brief  *idn? 查询机器型号命令
  * @param  *cmdtp: 传入的结构体
  *           argc: 参数个数
  *          *argv: 参数二维数组
  * @retval 0,成功处理
  * 		其他,错误代码
  */
int do_idn(cmd_tbl_t *cmdtp, int argc, char *argv[])
{
    printf("%s\r\n", idn);
    return 0;
}
/**
  * @brief  key 按键测试命令
  * @param  *cmdtp: 传入的结构体
  *           argc: 参数个数
  *          *argv: 参数二维数组
  * @retval 0,成功处理
  * 		其他,错误代码
  */
int do_key(cmd_tbl_t *cmdtp, int argc, char *argv[])
{
    uint8_t val_flg = 0;
    switch (argc)
    {
    case 2:
    {
        val_flg = key_command_test(argv);
        switch (val_flg)
        {
        case 0:
            printf("ok\r\n");
            break;
        case 1:
            printf("error\r\n");
            break;
        case 2:
            goto Parametre_error;
        }
    }
    break;
    default:
        break;
    }
    return 0;
Parametre_error:
    printf("Parametre error\r\n");
    return 0;
}
/**
  * @brief  ver?
  * @param  *cmdtp: 传入的结构体
  *           argc: 参数个数
  *          *argv: 参数二维数组
  * @retval 0,成功处理
  * 		其他,错误代码
  */
int do_ver(cmd_tbl_t *cmdtp, int argc, char *argv[])
{
    printf("%s,%s,%s\r\n", version, data_str, time_str);
    return 0;
}
/**
  * @brief  在 sys_cmd_tab[] 结构体数组中查找 name
  * @param  cmd: 传入的str
  * @retval 找到的结构体数组
  * 		NULL,无匹配
  */
cmd_tbl_t *find_cmd(const char *cmd)
{
    cmd_tbl_t *cmdtp;
    cmd_tbl_t *cmdtp_temp = &__cmd_start; /*Init value */
    const char *p;
    int len;
    int n_found = 0;

    /*
	 * Some commands allow length modifiers (like "cp.b");
	 * compare command name only until first dot.
	 */
    len = ((p = strchr(cmd, '.')) == NULL) ? strlen(cmd) : (p - cmd);

    for (cmdtp = &__cmd_start; cmdtp != &__cmd_end; cmdtp++)
    {
        if (strncmp(cmd, cmdtp->name, len) == 0)
        {
            if (len == strlen(cmdtp->name))
                return cmdtp; /* full match */

            cmdtp_temp = cmdtp; /* abbreviated command ? */
            n_found++;
        }
    }
    if (n_found == 1)
    { /* exactly one match */
        return cmdtp_temp;
    }

    return NULL; /* not found or ambiguous command */
}
/**
  * @brief  命令分割提取
  * @param  line: 传入的str
  *         argv[]:分割后的字符串
  * @retval 0,成功处理
  * 		其他,错误代码
  */
int parse_line(char *line, char *argv[])
{
    int nargs = 0;

#ifdef DEBUG_PARSER
    printf("parse_line: \"%s\"\r\n", line);
#endif
    while (nargs < CFG_MAXARGS)
    {

        /* skip any white space */
        while ((*line == ' ') || (*line == '\t'))
        {
            ++line;
        }

        if (*line == '\0')
        { /* end of line, no more args	*/
            argv[nargs] = NULL;
#ifdef DEBUG_PARSER
            printf("parse_line: nargs=%d\r\n", nargs);
#endif
            return (nargs);
        }

        argv[nargs++] = line; /* begin of argument string	*/

        /* find end of string */
        while (*line && (*line != ' ') && (*line != '\t'))
        {
            ++line;
        }

        if (*line == '\0')
        { /* end of line, no more args	*/
            argv[nargs] = NULL;
#ifdef DEBUG_PARSER
            printf("parse_line: nargs=%d\r\n", nargs);
#endif
            return (nargs);
        }

        *line++ = '\0'; /* terminate current arg	 */
    }

    printf("** Too many args (max. %d) **\r\n", CFG_MAXARGS);

#ifdef DEBUG_PARSER
    printf("parse_line: nargs=%d\r\n", nargs);
#endif
    return (nargs);
}
/**
  * @brief  命令解释函数
  * @param  cmd: 传入的字符串
  * @retval 0,成功处理
  * 		其他,错误代码
  */
int run_command(const char *cmd)
{
    cmd_tbl_t *cmdtp;
    char cmdbuf[CFG_CBSIZE]; /* working copy of cmd		*/
    char *token;             /* start of token in cmdbuf	*/
    char *sep;               /* end of token (separator) in cmdbuf */
    char *str = cmdbuf;
    char *argv[CFG_MAXARGS + 1]; /* NULL terminated	*/
    int argc, inquotes;
    int repeatable = 1;
    int rc = 0;

    if (!cmd || !*cmd)
    {
        return -1; /* empty command */
    }

    if (strlen(cmd) >= CFG_CBSIZE)
    {
        printf("## Command too long!\r\n");
        return -1;
    }

    strcpy(cmdbuf, cmd);

    /* Process separators and check for invalid
	 * repeatable commands
	 */

#ifdef DEBUG_PARSER
    printf("[PROCESS_SEPARATORS] %s\r\n", cmd);
#endif
    while (*str)
    {

        /*
		 * Find separator, or string end
		 * Allow simple escape of ';' by writing "\;"
		 */
        for (inquotes = 0, sep = str; *sep; sep++)
        {
            if ((*sep == '\'') &&
                (*(sep - 1) != '\\'))
                inquotes = !inquotes;

            if (!inquotes &&
                (*sep == ';') &&      /* separator		*/
                (sep != str) &&       /* past string start	*/
                (*(sep - 1) != '\\')) /* and NOT escaped	*/
                break;
        }

        /*
		 * Limit the token to data between separators
		 */
        token = str;
        if (*sep)
        {
            str = sep + 1; /* start of command for next pass */
            *sep = '\0';
        }
        else
            str = sep; /* no more commands for next pass */
#ifdef DEBUG_PARSER
        printf("token: \"%s\"\r\n", token);
#endif

        /* Extract arguments */
        if ((argc = parse_line(token, argv)) == 0)
        {
            rc = -1; /* no command at all */
            continue;
        }

        /* Look up command in command table */
        if ((cmdtp = find_cmd(argv[0])) == NULL)
        {
            printf("Unknown command '%s' - try 'help'\r\n", argv[0]);
            rc = -1; /* give up after bad command */
            continue;
        }

        /* found - check max args */
        if (argc > cmdtp->maxargs)
        {
            printf("Usage:\r\n%s\r\n", cmdtp->usage);
            rc = -1;
            continue;
        }

        /* OK - call function to do the command */
        if ((cmdtp->cmd)(cmdtp, argc, argv) != 0)
        {
            rc = -1;
        }
    }

    return rc ? rc : repeatable;
}
/**
  * @brief  处理系统命令
  * @param  void
  * @retval void
  */
void sys_cmd_exe(void)
{
    int len = 0;

    if (USART1_RX_STA & 0x8000) //串口接收完成
    {
        len = USART1_RX_STA & 0x3fff; //得到此次接收到的数据长度
        USART1_RX_BUF[len] = '\0';    //在末尾加入结束符.
        run_command((const char *)USART1_RX_BUF);
    }
    USART1_RX_STA = 0; //状态寄存器清空
}

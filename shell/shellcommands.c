#include "hal.h"
#include "shell.h"
#include "shellcommands.h"

char uartShellHistoryBuffer[SHELL_MAX_HIST_BUFF];

const ShellCommand commands[] =
{
#if 0
    { "status",  cmd_status },
    { "diic",    cmd_diic },
    { "piic",    cmd_piic },
    { "env",     cmd_env },
    { "gps",    cmd_gps },
    { "date",    cmd_date },
    #endif
    { "reboot",  cmd_reboot },
    { "dm",      cmd_dmb },
    { "dmb",     cmd_dmb },
    { "dmw",     cmd_dmw },
    { "out",     cmd_out },
    { "blink",   cmd_blink },
    { "am",      cmd_auxmotor },
    { "ping",    cmd_ping },
    { "send",    cmd_send },
    {NULL, NULL}
};

const ShellConfig shell_cfg_uart =
{
    (BaseSequentialStream *)&SD6,
    commands,
    uartShellHistoryBuffer,
    SHELL_MAX_HIST_BUFF
};

#include "hal.h"
#include "shell.h"
#include "shellcommands.h"

char uartShellHistoryBuffer[SHELL_MAX_HIST_BUFF];

const ShellCommand commands[] =
{
#if 0
    { "status",  cmd_status },
    { "out",     cmd_out },
    { "blink",   cmd_blink },
    { "ping",    cmd_ping },
    { "diic",    cmd_diic },
    { "piic",    cmd_piic },
    { "env",     cmd_env },
    { "gps",    cmd_gps },
    { "date",    cmd_date },
    #endif
    { "dm",      cmd_dmb },
    { "dmb",     cmd_dmb },
    { "dmw",     cmd_dmw },
    { "reboot",  cmd_reboot },
    {NULL, NULL}
};

const ShellConfig shell_cfg_uart =
{
    (BaseSequentialStream *)&SD6,
    commands,
    uartShellHistoryBuffer,
    SHELL_MAX_HIST_BUFF
};

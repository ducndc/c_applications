/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app_ctrl.h"
#include "app_cli.h"
#include "utils.h"

int g_optind = 2;

static app_ctrl_t *ctrl_conn;

static app_cli_cmd_t cli_cmds[] = {
    {"help", app_cli_cmd_help, "command usage"},
    {"dev_send_app", app_cli_send_raw_data, "send raw data to app"},
    {"termination", app_cli_send_temination, "terminate application"}
};

 static int 
 app_cli_open_connection(
    const char *ctrl_path
)
{
    ctrl_conn = app_ctrl_open(ctrl_path);

    if (!ctrl_conn)
    {
        return -1;
    }

    return 0;
}

static void 
app_cli_close_connection(
    void 
)
{
    app_ctrl_close(ctrl_conn);
    ctrl_conn = NULL;
}

static int 
app_cli_cmd_help(
    app_ctrl_t *ctrl,
    int argc,
    char *argv[]
)
{
    app_cli_cmd_t *cmd;
    int cmd_num = sizeof(cli_cmds) / sizeof(app_cli_cmd_t);
    int i;

    cmd = cli_cmds;
    
    for (i = 0; i < cmd_num; ++i, ++cmd)
    {
        printf(" %-60s %-50s \n", cmd->cmd, cmd->usage);
    }

    return 0;
}

static int 
app_cli_send_raw_data(
    app_ctrl_t *ctrl,
    int argc,
    char *argv[]
)
{
    char cmd[256];
    int i = 0;
    int ret = 0;

    sprintf(&cmd[i], "%s ", argv[0]);
    i += strlen(argv[0]) + 1;
    sprintf(&cmd[i], "%s ", argv[1]);

    ret = app_cli_command(ctrl, cmd, strlen(cmd));

    return ret;
}

static int 
app_cli_send_temination(
    app_ctrl_t *ctrl,
    int argc,
    char *argv[]
)
{
    char cmd[256];
    int i = 0;
    int ret = 0;

    sprintf(&cmd[i], "%s ", argv[0]);
    i += strlen(argv[0]) + 1;
    sprintf(&cmd[i], "%s ", argv[1]);

    ret = app_cli_command(ctrl, cmd, strlen(cmd));

    return ret;
}

static int 
app_cli_request(
    app_ctrl_t *ctrl,
    int argc,
    char *argv[]
)
{
    app_cli_cmd_t *cmd = NULL;
    app_cli_cmd_t *match = NULL;
    int ret = 0;

    cmd = cli_cmds;

    while (cmd->cmd)
    {
        if (0 == strncmp(cmd->cmd, argv[0], strlen(argv[0])))
        {
            match = cmd;
            break;
        }

        cmd++;
    }

    if (match)
    {
        ret = match->cmd_handler(ctrl, argc, &argv[0]);
    }
    else
    {
        ret = -1;
    }

    return ret;
}

int 
main(
    int argc,
    char *argv[]
)
{
    APP_LOG("application_cli start");

    int ret = 0;
    char socket_path[64] = {0};

    snprintf(socket_path, sizeof(socket_path), "/tmp/app_ctrl_%s", argv[1]);
    
    ret = app_cli_open_connection(socket_path);

    if (ret < 0)
    {
        APP_LOG("open connection failed");
        return ret;
    }

    ret = app_cli_request(ctrl_conn, argc - g_optind, &argv[g_optind]);

    app_cli_close_connection();

    APP_LOG("application_cli terminate");

    return ret;
}

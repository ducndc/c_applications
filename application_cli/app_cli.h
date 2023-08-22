/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */

#ifndef __APP_CLI_H__
#define __APP_CLI_H__

#include "app_ctrl.h"

typedef struct app_cli_cmd app_cli_cmd_t;

struct app_cli_cmd {
    const char* cmd;
    int (*cmd_handler)(app_ctrl_t *ctrl, int argc, char *argv[]);
    const char *usage;
}; 

static int app_cli_cmd_help(app_ctrl_t *ctrl, int argc, char *argv[]);
static int app_cli_send_raw_data(app_ctrl_t *ctrl, int argc, char *argv[]);

#endif /* END __APP_CLI_H__ */
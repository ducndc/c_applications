/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */

 #ifndef __APP_CTRL_H__
 #define __APP_CTRL_H__

#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct app_ctrl app_ctrl_t; 

struct app_ctrl {
    int s;
    struct sockaddr_un local;
    struct sockaddr_un dest;
};

app_ctrl_t *app_ctrl_open(const char *ctrl_path);

void app_ctrl_close(app_ctrl_t *ctrl);

int app_cli_command(app_ctrl_t *ctrl, const char *cmd, size_t cmd_len);

 #endif /* END __APP_CTRL_H__ */
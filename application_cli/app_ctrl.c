/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>

#include "app_ctrl.h"

int 
make_addr(
    const char *name, 
    struct sockaddr_un *p_addr, 
    socklen_t *p_sock_len
)
{
    int name_len = strlen(name);

    if (name_len >= ((int)sizeof(p_addr->sun_path) - 1))
    {
        return -1;
    }

    p_addr->sun_path[0] = '\0';
    strcpy(p_addr->sun_path + 1, name);
    p_addr->sun_family = AF_UNIX;
    *p_sock_len = 1 + name_len + offsetof(struct sockaddr_un, sun_path);

    return 0;
}

app_ctrl_t
*app_ctrl_open(const char *ctrl_path)
{
    app_ctrl_t *ctrl = NULL;
    socklen_t socklen;
    int status = 0;

    ctrl = malloc(sizeof(*ctrl));
    
    if (!ctrl) 
    {
        return NULL;
    }

    memset(ctrl, 0, sizeof(*ctrl));
    ctrl->s = socket(AF_UNIX, SOCK_STREAM, 0);

    if (ctrl->s < 0)
    {
        goto error;
    }

    make_addr("/tmp/app_ctrl_cli", &ctrl->local, &socklen);

    if (bind(ctrl->s, (struct sockaddr *)&ctrl->local, socklen) < 0)
    {
        close(ctrl->s);
        goto error;
    }

    make_addr(ctrl_path, &ctrl->dest, &socklen);
    status = connect(ctrl->s, (struct sockaddr *)&ctrl->dest, socklen);

    if (status < 0)
    {
        close(ctrl->s);
        goto error;
    }

    return ctrl;

error:
    free(ctrl);
    return NULL;
}

void 
app_ctrl_close(
    app_ctrl_t *ctrl
)
{
    close(ctrl->s);
    free(ctrl);
}

int 
app_cli_command(
    app_ctrl_t *ctrl,
    const char *cmd,
    size_t cmd_len
)
{
    if (send(ctrl->s, cmd, cmd_len, 0) < 0)
    {
        return -1;
    }

    return 0;
}

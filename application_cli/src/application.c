/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>

#include "utils.h"
#include "application.h"

int 
main(
    int argc,
    char *argv[]
)
{
    struct sockaddr_un addr;
    socklen_t server_len;
    int ctrl_sock;
    fd_set rset;

    FD_ZERO(&rset);

    APP_LOG("application start");

    ctrl_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    
    if (ctrl_sock < 0)
    {
        APP_LOG("open ctrl_sock fail");
        return -1;
    }

    make_addr("/tmp/app_ctrl_server", &addr, &server_len);

    if (bind(ctrl_sock, (struct sockaddr *)&addr, server_len) < 0)
    {
        APP_LOG("bind addr to ctrl_sock fail");
        unlink(addr.sun_path);
        close(ctrl_sock);

        return -1;
    }

    if (listen(ctrl_sock, 1) < 0)
    {
        unlink(addr.sun_path);
        close(ctrl_sock);
        APP_LOG("listen ctrl_sock fail");

        return -1;
    }

    FD_SET(ctrl_sock, &rset);

    for (;;) {
        if (FD_ISSET(ctrl_sock, &rset)) 
        {
            if (-1 == app_ctrl_interface_recv_and_parse(ctrl_sock))
            {
                break;
            }
        }
    }
    
    close(ctrl_sock);

    APP_LOG("application terminate");

    return 0;
}

int 
app_ctrl_interface_recv_and_parse(
    int ctrl_sock
)
{
    struct sockaddr_un from;
    int lenfrom = sizeof(from);
    int recv_fd = 0;
    char *file = NULL;
    char buf[1024] = {0};
    int len = 1023;

    fd_set rset;
    
    recv_fd = accept(ctrl_sock, (struct sockaddr *)&from, (socklen_t *)&lenfrom);

    if (recv_fd < 0)
    {
        close(recv_fd);
        return -1;
    }

    len = recv(recv_fd, buf, len, 0);
    buf[len] = '\0';

    APP_LOG(buf);

    if (0 == strncmp(buf, "dev_send_app", strlen("dev_send_app")))
    {
        file = buf + sizeof("dev_send_app") + 1;
        APP_LOG("Running command, which recived from app_ctrl");
        /* send_app_raw_data */
    } 
    else if (0 == strncmp(buf, "termination", strlen("termination")))
    {
        close(recv_fd);
        return -1;
    } 
    else
    {
        APP_LOG("no such command");
    }

    close(recv_fd);
}

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
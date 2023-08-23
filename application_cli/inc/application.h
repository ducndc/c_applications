/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

int app_ctrl_interface_recv_and_parse(int ctrl_sock);

int make_addr(const char *name, struct sockaddr_un *p_addr, socklen_t *p_sock_len);

#endif /* END __APPLICATION_H__ */
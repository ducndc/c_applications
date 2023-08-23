/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#define APP_LOG(data) printf("[%s]:[%d] %s \n", __func__, __LINE__, data)

#define SECOND_2_HOURS(time) (time / 3600)

#define SECOND_2_DAY(time) (time / 3600 / 24)

#endif /* END __UTILS_H__ */
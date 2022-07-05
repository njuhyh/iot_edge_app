//
// Created by w00381681 on 2020/1/10.
//

#ifndef MODULESDK_EDGE_ERROR_H
#define MODULESDK_EDGE_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum enum_EDGE_RETCODE
{
    EDGE_SUCCESS,
    EDGE_ERROR,
    EDGE_INIT_ERROR,

    EDGE_BUTT
} EDGE_RETCODE;

#ifdef __cplusplus
}
#endif

#endif //MODULESDK_EDGE_ERROR_H

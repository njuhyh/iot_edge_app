//
// Created on 2021/10/25.
//

#ifndef MODULESDK_EDGE_DC_DRIVER_H
#define MODULESDK_EDGE_DC_DRIVER_H
#ifdef __cplusplus
extern "C"
{
#endif

/***
 * 数采驱动模块，用于开发数采驱动接入点位数据，驱动需实现相关回调函数
 */

#include "edge.h"
#include "edge_error.h"
#include "edge_struct.h"

/****** 其他回调函数参见edge.h ******/

/** SDK will call this function, when a new points info get is send by the cloud. */
typedef EDGE_RETCODE (FN_MODULE_POINTS_GET_RECEIVED)(const char* request_id, ST_POINTS_GET* points_get);

/** SDK will call this function, when a new points info set is send by the cloud. */
typedef EDGE_RETCODE (FN_MODULE_POINTS_SET_RECEIVED)(const char* request_id, const char* points_info, unsigned int len);

/** Module callbacks struct of above, app will invoke edge_set_callbacks(ST_MODULE_CBS* module_cbs, ST_DEVICE_CBS* device_cbs) with this. */
typedef struct stru_DC_CLIENT_CBS
{
    FN_MODULE_POINTS_SET_RECEIVED* pfn_module_points_set_cb;
    FN_MODULE_POINTS_GET_RECEIVED* pfn_module_points_get_cb;
} ST_DC_CLIENT_CBS;

/** Module points data handler callbacks struct of above, app will invoke edge_dc_driver_set_callbacks(ST_DC_CLIENT_CBS* dc_client_cbs) with this. */
HW_API_FUNC  int   edge_dc_driver_set_callbacks(ST_DC_CLIENT_CBS* dc_client_cbs);

/** module report points data to hub. */
HW_API_FUNC  int   edge_dc_driver_points_report(const char* points_info, unsigned int len);

/** module will use this interface to report points data for cloud request. */
HW_API_FUNC  int   edge_dc_driver_points_get_rsp(const char* request_id, const char* points_info, unsigned int len);

/** module will use this interface to report operator result for cloud set request. */
HW_API_FUNC  int   edge_dc_driver_points_set_rsp(const char* request_id, ST_IOT_EDGE_RESULT* result);

#ifdef __cplusplus
}
#endif
#endif //MODULESDK_EDGE_DC_DRIVER_H

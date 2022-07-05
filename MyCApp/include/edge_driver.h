//
// Created by l50018076 on 2021/6/24.
//

#ifndef MODULESDK_EDGE_DRIVER_H
#define MODULESDK_EDGE_DRIVER_H

#ifdef __cplusplus
extern "C"
{
#endif

/***
 * 驱动模块，用于开发驱动接入设备，驱动需实现网关回调函数
 */

#include "edge.h"
#include "edge_error.h"
#include "edge_struct.h"

/****** 其他回调函数参见edge.h ******/

/** SDK will call this function, when a new sub device add is sent by the cloud. */
typedef EDGE_RETCODE (FN_SUB_DEVICE_ADD_ARRIVED_V1)(const char* event_id, ST_ADD_SUB_DEVICES_EVENT* add_sub_devices_event);

/** SDK will call this function, when a new sub device delete is sent by the cloud. */
typedef EDGE_RETCODE (FN_SUB_DEVICE_DELETED_ARRIVED_V1)(const char* event_id, ST_DELETE_SUB_DEVICES_EVENT* delete_sub_devices_event);

typedef struct stru_GATEWAY_CBS {
    FN_MESSAGE_ARRIVED* pfn_device_message_cb;
    FN_COMMAND_ARRIVED* pfn_device_command_cb;
    FN_DEVICE_EVENT_ARRIVED* pfn_device_event_cb;
    FN_SUB_DEVICE_ADD_ARRIVED_V1* pfn_sub_device_add_cb_1;
    FN_SUB_DEVICE_DELETED_ARRIVED_V1* pfn_sub_device_deleted_cb_1;
    FN_START_SCAN_ARRIVED* pfn_on_start_scan_cb;        // sub-device scanning request received
    FN_ON_GET_PRODUCTS_RSP* pfn_on_get_products_rsp_cb;

    FN_DEVICE_PROPERTIES_SET_ARRIVED* pfn_device_properties_set_cb;
    FN_DEVICE_PROPERTIES_GET_ARRIVED* pfn_device_properties_get_cb;
    FN_DEVICE_SHADOW_ARRIVED* pfn_device_shadow_cb;
} ST_GATEWAY_CBS;

HW_API_FUNC int  edge_driver_init(const char* workdir);
HW_API_FUNC void edge_driver_destroy();

HW_API_FUNC int  edge_driver_login();
HW_API_FUNC void edge_driver_logout();

HW_API_FUNC int edge_driver_get_shadow();
HW_API_FUNC int edge_driver_get_device_shadow(const char* request_id, ST_DEVICE_SHADOW_GET* device_shadow_get);
HW_API_FUNC int edge_driver_get_products(const char** product_ids, unsigned int product_id_size);

HW_API_FUNC int edge_driver_report_sub_device_properties(ST_SUB_DEVICES_PROPERTIES_REPORT* report);

HW_API_FUNC int edge_driver_send_device_event(ST_DEVICE_EVENT* device_event);
HW_API_FUNC int edge_driver_send_device_message(ST_DEVICE_MESSAGE* device_message);
HW_API_FUNC int edge_driver_send_service_event(const char* service_id, const char* event_type,
                                               const char* body, unsigned int body_len);

HW_API_FUNC int edge_driver_set_gateway_callback(ST_GATEWAY_CBS* gateway_cbs);

HW_API_FUNC int edge_driver_sync_sub_devices(const char* event_id, long long version);
HW_API_FUNC int edge_driver_update_sub_devices_status(const char* event_id, ST_DEVICE_STATUS* devices_status, unsigned int size);

#ifdef __cplusplus
}
#endif

#endif //MODULESDK_EDGE_DRIVER_H

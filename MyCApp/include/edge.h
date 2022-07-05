//
// Created by w00381681 on 2020/1/9.
//

#ifndef MODULESDK_EDGE_H
#define MODULESDK_EDGE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "edge_error.h"
#include "edge_struct.h"

#define  HW_API_FUNC __attribute ((visibility("default")))

/** Since SDK will automatic reconnected, So a notify will be called, when it's connected or disconnected. */
typedef  void         (FN_SDK_CONNECTED)();
typedef  void         (FN_SDK_DISCONNECTED)();

/** SDK will call this function, when a new device or module shadow is sent by the cloud. */
typedef  EDGE_RETCODE (FN_SHADOW_ARRIVED)(const char* shadow, unsigned int shadow_len);

/** SDK will call this function, when a new device or module command is sent by the cloud. */
typedef  EDGE_RETCODE (FN_COMMAND_ARRIVED)(const char* command_name, const char* device_id,
                        const char* service_id, const char* request_id, const char* body, unsigned int body_len);

/** SDK will call this function, when a new message is sent by the cloud. */
typedef  EDGE_RETCODE (FN_MESSAGE_ARRIVED)(const char* message_id, const char* message_name, const char* device_id, const char* body, unsigned int body_len);

/** SDK will call this function, when a new sub device event is sent by the cloud. */
typedef  EDGE_RETCODE (FN_DEVICE_EVENT_ARRIVED)(const char* device_id, const char* body, unsigned int body_len);

/** SDK will call this function, when a new sub device add is sent by the cloud. */
typedef  EDGE_RETCODE (FN_SUB_DEVICE_ADD_ARRIVED)(const char* addSubDeviceInfo, unsigned int body_len);

/** SDK will call this function, when a new sub device delete is sent by the cloud. */
typedef  EDGE_RETCODE (FN_SUB_DEVICE_DELETED_ARRIVED)(const char* deleteSubDeviceInfo, unsigned int body_len);

/** SDK will call this function, when a new start scan is sent by the cloud. */
typedef  EDGE_RETCODE (FN_START_SCAN_ARRIVED)(const char* protocol, const char* channel, const char* parentDeviceId,const char* scan_setting, unsigned int body_len);

/** SDK will call this function, when a response of getting products received by the cloud. */
typedef EDGE_RETCODE (FN_ON_GET_PRODUCTS_RSP)(ST_GET_PRODUCTS_RSP_EVENT* getProductsRspEvent);

/** SDK will call this function, when a new sub device property set is sent by the cloud. */
typedef  EDGE_RETCODE (FN_DEVICE_PROPERTIES_SET_ARRIVED)(ST_PROPERTY_SET* sub_device_property_set);

/** SDK will call this function, when a new sub device property get is sent by the cloud. */
typedef  EDGE_RETCODE (FN_DEVICE_PROPERTIES_GET_ARRIVED)(ST_PROPERTY_GET* sub_device_property_get);

/** SDK will call this function, when a new sub device shadow is sent by the cloud. */
typedef  EDGE_RETCODE (FN_DEVICE_SHADOW_ARRIVED)(ST_DEVICE_SHADOW* sub_device_shadow);

/** SDK will call this function, when a new customized message is sent by the cloud. */
typedef  EDGE_RETCODE (FN_CUSTOMIZED_MESSAGE_ARRIVED)(const char* topic, const char* payload, unsigned int len);

/** SDK will call this function, when a message which will be published to EdgeHub is received from a device. */
typedef EDGE_RETCODE (FN_ON_MESSAGE_RECEIVED)(const char* device_id, const char* product_id, const char* payload, unsigned int len);

/** Module callbacks struct of above, app will invoke edge_set_callbacks(ST_MODULE_CBS* module_cbs, ST_DEVICE_CBS* device_cbs) with this. */
typedef struct stru_MODULE_CBS
{
    FN_SHADOW_ARRIVED* pfn_shadow_cb;
    FN_COMMAND_ARRIVED* pfn_command_cb;
    FN_CUSTOMIZED_MESSAGE_ARRIVED* pfn_customized_message_cb;
    FN_DEVICE_PROPERTIES_SET_ARRIVED* pfn_module_properties_set_cb;
    FN_DEVICE_PROPERTIES_GET_ARRIVED* pfn_module_properties_get_cb;
    FN_SDK_CONNECTED* pfn_connected;
    FN_SDK_DISCONNECTED* pfn_disconnected;

    // bus message callback, which processes the data received by EdgeHub from device
    FN_ON_MESSAGE_RECEIVED* pfn_on_message_received_cb;
} ST_MODULE_CBS;

/** subdevice callbacks struct of above, app will invoke edge_set_callbacks(ST_MODULE_CBS* module_cbs, ST_DEVICE_CBS* device_cbs) with this. */
typedef struct stru_DEVICE_CBS
{
    FN_MESSAGE_ARRIVED* pfn_device_message_cb;
    FN_COMMAND_ARRIVED* pfn_device_command_cb;
    FN_DEVICE_EVENT_ARRIVED* pfn_device_event_cb;
    FN_SUB_DEVICE_ADD_ARRIVED* pfn_sub_device_add_cb;
    FN_SUB_DEVICE_DELETED_ARRIVED* pfn_sub_device_deleted_cb;
    FN_START_SCAN_ARRIVED* pfn_on_start_scan_cb;        // sub-device scanning request received
    FN_ON_GET_PRODUCTS_RSP* pfn_on_get_products_rsp_cb;

    FN_DEVICE_PROPERTIES_SET_ARRIVED* pfn_device_properties_set_cb;
    FN_DEVICE_PROPERTIES_GET_ARRIVED* pfn_device_properties_get_cb;
    FN_DEVICE_SHADOW_ARRIVED* pfn_device_shadow_cb;
} ST_DEVICE_CBS;

/** User Temporary Cloud Token. */
typedef struct stru_CLOUD_TOKEN {
    char* ak;
    char* sk;
    char* region;
    char* expire_time;
} ST_CLOUD_TOKEN;


HW_API_FUNC  int   edge_init(const char* workdir);
HW_API_FUNC  void  edge_destroy();

HW_API_FUNC  int   edge_login();
HW_API_FUNC  void  edge_logout();

HW_API_FUNC  int   edge_get_shadow();
HW_API_FUNC  int   edge_set_callbacks(ST_MODULE_CBS* module_cbs, ST_DEVICE_CBS* device_cbs);
HW_API_FUNC  int   edge_get_cloud_token(ST_CLOUD_TOKEN* cloud_token);
HW_API_FUNC  int   edge_send_service_event(const char* service_id, const char* event_type,
                                           const char* body, unsigned int body_len);
HW_API_FUNC  int   edge_send_add_sub_device(ST_DEVICE_INFO* device_info, unsigned int size);
HW_API_FUNC  int   edge_send_delete_sub_device(ST_DEVICE_INFO* device_info, unsigned int size);

HW_API_FUNC  int   edge_send_get_sub_device_shadow(const char* request_id, ST_DEVICE_SHADOW_GET* device_shadow_get);
HW_API_FUNC  int   edge_send_sub_device_message(ST_DEVICE_MESSAGE* device_message);
HW_API_FUNC  int   edge_send_sub_device_event(ST_DEVICE_EVENT* device_event);
HW_API_FUNC  int   edge_send_get_product(const char** product_ids, unsigned int product_id_size);
HW_API_FUNC  int   edge_send_sync_sub_device(long long version);
HW_API_FUNC  int   edge_send_sub_device_status(ST_DEVICE_STATUS* devices_status, unsigned int size);
HW_API_FUNC  int   edge_send_batch_device_data(ST_DEVICE_SERVICE* devices,unsigned int size);
HW_API_FUNC  int   edge_send_batch_device_data_v2(const char *device_id, const char *service_id, const char *service_properties, const char *event_time);
HW_API_FUNC  int   edge_send_batch_device_data_v3(const char *service_properties, unsigned int size);
HW_API_FUNC  int   edge_send_command_rsp(const char* rsp_name, const char* request_id, int result_code,
                                         const char* rsp_body, unsigned int body_lens);
HW_API_FUNC  int   edge_send_sub_device_property_get_rsp(const char* request_id, ST_DEVICE_PROPERTY_GET_RSP* device_property_get_rsp);
HW_API_FUNC  int   edge_send_sub_device_property_set_rsp(const char* request_id, ST_IOT_RESULT* iot_result);

HW_API_FUNC  int   edge_send_customized_message(const char* topic, const char* body, unsigned int body_len);
HW_API_FUNC  int   edge_set_bus_message_cb(const char* input_name);
HW_API_FUNC  int   edge_send_bus_message(const char* output_name, const char* body, unsigned int body_len);
HW_API_FUNC  int   edge_call_device_command(ST_COMMAND* command, unsigned int timeout);

#ifdef __cplusplus
}
#endif

#endif //MODULESDK_EDGE_H

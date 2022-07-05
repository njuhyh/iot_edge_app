//
// Created by l50018076 on 2021/8/4.
//

#ifndef MODULESDK_EDGE_STRUCT_H
#define MODULESDK_EDGE_STRUCT_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
* Struct for edge_daemon
*/
typedef struct stru_DAEMON_CLOUD_TOKEN {
    char* access_key;
    char* secret_key;
    char* auth_token;
    char* region;
    char* expires_at;
    char* token;
    char* obs_address;
    char* swr_api_address;
} ST_DAEMON_CLOUD_TOKEN;

typedef struct stru_DAEMON_TOKEN {
    char* token;
    long long expires_at;
} ST_DAEMON_TOKEN;

typedef struct stru_VERIFY_RESPONSE {
    char* module_id;
    long long expires_at;
} ST_VERIFY_RESPONSE;

typedef struct stru_DEVICE_SIGN {
    char* client_id;
    char* password;
} ST_DEVICE_SIGN;

typedef struct stru_MODULE_TRUST_CERTS {
    char* certificate;
    long long expires_at;
} ST_MODULE_TRUST_CERTS;

typedef struct stru_NODE_CERT {
    char* certificate;
    long long expires_at;
    char* private_key;
} ST_NODE_CERT;


/**
 * Common Struct Definition
 */
typedef struct stru_DEVICE_INFO {
    char* parent_device_id;
    char* node_id;
    char* device_id;
    char* name;
    char* description;
    char* product_id;
    char* fw_version;
    char* sw_version;
    char* status;
    //char* extension_info 扩展信息， json str
} ST_DEVICE_INFO;

typedef struct stru_DEVICE_STATUS {
    char* device_id;
    char* status;
} ST_DEVICE_STATUS;

typedef struct stru_SERVICE_DATA {
    char* service_id;
    char* properties;       // json str
    char* event_time;       // yyyyMMdd'T'HHmmss'Z'
} ST_SERVICE_DATA;

typedef struct stru_DEVICE_SERVICE {
    char* device_id;
    ST_SERVICE_DATA* services;
    unsigned int size;
} ST_DEVICE_SERVICE;

typedef struct {
    char* object_device_id;
    char* request_id;
    ST_SERVICE_DATA* services;
    unsigned int services_size;
} ST_PROPERTY_SET;

typedef struct {
    char* object_device_id;
    char* request_id;
    char* service_id;
} ST_PROPERTY_GET;

typedef struct {
    char** points;
    int size;
} ST_POINTS_GET;

typedef struct stru_SHADOW_DATA{
    char* service_id;
    char* desired_event_time;
    char* desired_properties;   // json str
    char* reported_event_time;  //  yyyyMMdd'T'HHmmss'Z'
    char* reported_properties;  // json str
    int version;
} ST_SHADOW_DATA;

typedef struct {
    char* object_device_id;
    char* request_id;
    ST_SHADOW_DATA *shadow;
    int shadow_size;
} ST_DEVICE_SHADOW;

typedef struct {
    char* object_device_id;
    char* service_id;
} ST_DEVICE_SHADOW_GET;

typedef struct stru_DEVICE_MESSAGE {
    char* object_device_id;
    char* name;
    char* id;
    char* content;      //json str
    int content_len;
} ST_DEVICE_MESSAGE;

typedef struct stru_SERVICE_EVENT {
    char* service_id;
    char* event_id;
    char* event_type;
    char* event_time;   // yyyyMMdd'T'HHmmss'Z'
    char* paras;        //json str
    int paras_len;
} ST_SERVICE_EVENT;

typedef struct {
    char* object_device_id;
    ST_SERVICE_EVENT* services;
    int services_size;
} ST_DEVICE_EVENT;

typedef struct {
    ST_SERVICE_DATA* services;
    unsigned int services_size;
} ST_DEVICE_PROPERTY_GET_RSP;

typedef struct {
    char* result_code;
    char* result_desc;
} ST_IOT_RESULT;

typedef struct {
    int result_code;
    char* result_desc;
} ST_IOT_EDGE_RESULT;

typedef struct stru_BUS_MESSAGE {
    char* device_id;
    char* product_id;
    ST_SERVICE_DATA* services;
    unsigned int service_len;
} ST_BUS_MESSAGE;

typedef struct stru_COMMAND {
    char* object_device_id;
    char* service_id;
    char* command_name;
    //char* paras;   json str
} ST_COMMAND;

// 驱动相关
typedef struct stru_SCAN_EVENT_RESULT {
    char* module_id;
    char* state;
    ST_DEVICE_INFO* device_info;
} ST_SCAN_EVENT_RESULT;

typedef struct stru_SUB_DEVICE_PROPERTIES_REPORT {
    ST_DEVICE_SERVICE* devices;
    unsigned int device_size;
} ST_SUB_DEVICES_PROPERTIES_REPORT;

typedef struct {
    char* para_name;
    int required;
    char* data_type;
    char* enum_list; // enum list
    char* min;
    char* max;
    int max_length;
    double step;
    char* unit;
    char* description;
} ST_SERVICE_COMMAND_PARA;

typedef struct {
    ST_SERVICE_COMMAND_PARA* paras;
    char* response_name;
    unsigned int service_command_para_len;
} ST_SERVICE_COMMAND_RESPONSE;

typedef struct {
    char* property_name;
    int required;
    char* data_type;
    char* enum_list; // enum list
    char* min;
    char* max;
    int max_length;
    double step;
    char* unit;
    char* method;
    char* description;
    char* default_value; // json str
} ST_SERVICE_PROPERTY;

typedef struct {
    char* command_name;
    ST_SERVICE_COMMAND_PARA* paras;
    ST_SERVICE_COMMAND_RESPONSE* responses;
    unsigned int para_len;
    unsigned int response_len;
} ST_SERVICE_COMMAND;

typedef struct {
    char* service_id;
    char* service_type;
    ST_SERVICE_PROPERTY* properties;
    ST_SERVICE_COMMAND* commands;
    char* description;
    char* option;
    unsigned int property_len;
    unsigned int command_len;
} ST_SERVICE_CAPABILITY;

typedef struct {
    char* product_id;
    char* name;
    char* device_type;
    char* protocol_type;
    char* data_format;
    char* industry;
    char* description;
    ST_SERVICE_CAPABILITY* serviceCapabilities;
    char* create_time;  // yyyyMMdd'T'HHmmss'Z'
    unsigned int service_capability_len;
} ST_PRODUCT_INFO;

typedef struct {
    ST_PRODUCT_INFO* products;
    unsigned int product_len;
} ST_GET_PRODUCTS_RSP_EVENT;

typedef struct stru_ADD_SUB_DEVICES_EVENT {
    ST_DEVICE_INFO* devices;
    unsigned int device_len;
    long long version;
} ST_ADD_SUB_DEVICES_EVENT;

typedef struct stru_DELETE_SUB_DEVICES_EVENT {
    ST_DEVICE_INFO* devices;
    unsigned int device_len;
    long long version;
} ST_DELETE_SUB_DEVICES_EVENT;

#ifdef __cplusplus
}
#endif

#endif //MODULESDK_EDGE_STRUCT_H

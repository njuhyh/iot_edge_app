#include "edge.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include <json-c/json.h>

struct json_object *match_service_by_id(
    struct json_object *services,
    char* id
)
{
    struct json_object *service;
    struct json_object *service_id;
    size_t n_services;
    n_services = json_object_array_length(services);
    size_t i;
    for (i = 0; i < n_services;++i)
    {
        service = json_object_array_get_idx(services, i);
        json_object_object_get_ex(service, "service_id", &service_id);
        if (!strcmp(json_object_get_string(service_id), id)){
            return service;
        }
    }
    return NULL;
}

struct json_object *create_post_body(
    char* image_data
)
{
    struct json_object *data_string;
    struct json_object *img_element;
    struct json_object *img_list;
    struct json_object *result;
    data_string = json_object_new_string(image_data);
    img_element = json_object_new_object();
    json_object_object_add(img_element, "img1", data_string);
    img_list = json_object_new_array();
    json_object_array_add(img_list, img_element);
    result = json_object_new_object();
    json_object_object_add(result, "img", img_list);
    return result;
}

struct memory {
    char *response;
    size_t size;
};

static size_t cb(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(ptr == NULL)
        return 0;  /* out of memory! */

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

struct json_object *judge_from_response(char* response){
    int is_host = 0;
    if(response[0] == '{'){
        struct json_object *response_json;
        response_json = json_tokener_parse(response);
        if(json_object_get_boolean(json_object_object_get(
            json_object_object_get(response_json, "pair_1"),
            "verified"
        ))==TRUE){
            is_host = 1;
        }
        }
    struct json_object *main_person_name;
    if(is_host){
        main_person_name = json_object_new_string("hyh");
    }else{
        main_person_name = json_object_new_string("stranger");
    }

    struct json_object *props;
    struct json_object *service;
    props = json_object_new_object();
    json_object_object_add(props, "main_person_name", main_person_name);
    service = json_object_new_object();
    json_object_object_add(service, "service_id", json_object_new_string("recognition"));
    json_object_object_add(service, "properties", props);
    return service;
}

char* add_recognition_to(char* input)
{   
    printf("Parsing json.");
    // Parse json
    struct json_object *parsed_json;
    parsed_json = json_tokener_parse(input);

    printf("Extracting base64 data.");
    // Extract image base64 data
    struct json_object *services;
    struct json_object *image_service;
    struct json_object *props;
    struct json_object *image_data;
    json_object_object_get_ex(parsed_json, "services", &services);
    if(!(image_service = match_service_by_id(services, "image")))
    {
        return "";
    }
    json_object_object_get_ex(image_service, "properties", &props);
    json_object_object_get_ex(props, "image_data", &image_data);
    char *data;
    data = json_object_get_string(image_data);

    // Wrap data into a new json string
    struct json_object *body;
    body = create_post_body(data);

    printf("Making curl.");
    // Call deepface for result
    CURL *curl = curl_easy_init();
    if(curl)
    {
        printf("Curl running request.");
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/verify");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_object_get_string(body));
        struct memory chunk = {0};

        // Setting header for json
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        /* send all data to this function  */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
        /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        res = curl_easy_perform(curl);
        printf("Result already got.");
        curl_easy_cleanup(curl);

        // Modify json and print it
        json_object_array_add(services, judge_from_response(chunk.response));
        char *result = json_object_get_string(parsed_json);
        printf("Modified data: \n%s\n", result);
        return result;
    }
    return NULL;
}

/*
 * 描述：设置总线消息回调，用于对设备上报的数据进行处理
 * 参数：
 *  input_name：消息总线输入点
 * */
EDGE_RETCODE set_bus_message_cb(const char* input_name)
{
    edge_set_bus_message_cb(input_name);
    printf("set bus message callback with input name: %s\n", input_name);

    return EDGE_SUCCESS;
}


/*
 * 描述：收到设备上报数据的回调处理，样例代码在马达设备状态错误时对马达进行重启
 * 参数：
 *  device_id：设备ID
 *  product_id: 产品ID
 *  body: 上报的数据
 *  body_len: 上报数据的大小
 * */
EDGE_RETCODE on_message_received_cb(const char* device_id, const char* product_id, const char* body, unsigned int body_len)
{
    // 设置发送设备数据的消息总线输出点，取值需在创建应用版本的outputs参数中定义
    char* output_name = "output";

    printf("start send message to output topic: %s\n", output_name);
    printf("body is: %s\nbody len is: %d\n", body, body_len);
    printf("product_id is: %s\n", product_id);
    printf("start processing deviceee.\n");

    // 设置摄像机id
    char* MOTOR_PRODUCT_ID = "lock_cam";

    // 如果是摄像机，调用deepface接口识别，原消息加上识别信息重新发送
    if (strcmp(product_id, MOTOR_PRODUCT_ID) == 0)
    {
        printf("---> It's lock_cam!");
        char *body_modified = add_recognition_to(body);
        body = body_modified;
        body_len = strlen(body);
    }

    edge_send_bus_message(output_name, body, body_len);

    printf("process ended.\n");

    return EDGE_SUCCESS;
}

/*
 * 监控APP，检视设备上报的数据，并对设备进行相应的控制
 */

void monitor_app()
{
    // 禁用缓冲区
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("start monitor app\n");

    //初始化sdk，工作路径设置（工作路径下需要含有 /conf  目录（该目录下包含证书等信息））
    edge_init("./");

    ST_MODULE_CBS module_cbs = {0};
    ST_DEVICE_CBS device_cbs = {0};

    module_cbs.pfn_on_message_received_cb = on_message_received_cb;

    // 设置回调函数
    edge_set_callbacks(&module_cbs, &device_cbs);

    printf("SDK start running!\n");

    sleep(1);
    edge_login();

    sleep(1);

    // 接受设备数据的消息总线输入点，取值需在创建应用版本的inputs参数中定义
    char* input_name = "input";
    set_bus_message_cb(input_name);

    // 这里是为了使应用能够长时间运行
    while(1)
    {
        sleep(1000);
    }

    edge_logout();
    sleep(1000);
    edge_destroy();
}

int main()
{
    // 监控app demo
    monitor_app();

    return 0;
}

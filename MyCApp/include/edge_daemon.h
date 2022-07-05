//
// Created by z00465566 on 2021/4/1.
//

#ifndef MODULESDK_EDGE_DAEMON_H
#define MODULESDK_EDGE_DAEMON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "edge_error.h"
#include "edge_struct.h"

#define  HW_API_FUNC __attribute ((visibility("default")))

//不提供
HW_API_FUNC  int  edge_daemon_bind(char* verify_code);

//强制刷新token  重新签名
HW_API_FUNC  int  edge_daemon_sign();

//下面这些提供
HW_API_FUNC  int  edge_daemon_get_token(ST_DAEMON_TOKEN* daemon_token);

HW_API_FUNC  int  edge_daemon_cloud_token(ST_DAEMON_CLOUD_TOKEN* cloud_token);

HW_API_FUNC  int  edge_daemon_encrypt(const char* plaintext, const char* algorithm, const char** result);

HW_API_FUNC  int  edge_daemon_decrypt(const char* ciphertext, const char* algorithm, const char** result);

HW_API_FUNC  int  edge_daemon_verify(const char* token, ST_VERIFY_RESPONSE* response);

HW_API_FUNC  int  edge_daemon_digest(const char* data, const char* algorithm, const char** result);

HW_API_FUNC  int  edge_daemon_device_sign(ST_DEVICE_SIGN* device_sign);

HW_API_FUNC  int  edge_daemon_node_certs(ST_NODE_CERT* node_cert);

HW_API_FUNC  int  edge_daemon_trust_certs(ST_MODULE_TRUST_CERTS* module_trust_certs);

#ifdef __cplusplus
}
#endif

#endif //MODULESDK_EDGE_DAEMON_H

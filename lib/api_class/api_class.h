#ifndef api_class_h
#define api_class_h
#include <Arduino.h>
#include <time.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include<sha/sha256.h>
#include <ArduinoJson.h>

class APIcall{
private:
    const char*root_ca;
    String shared_key;
    String uuid;
    String time;
    String auth_header;
    

public:
    APIcall(){}
    APIcall(const char*root_ca_char, String shared_key,String uuid);  // Constructor declaration
    void auth_header_and_time(); // defining private attributes time and signature
    void check_time();
    bool check_license(String product_short_code,String hardware_id,String license_key);
  

};
String HMAC_SHA256_To_Base64(String secretKey, String message);
String base64Encode(byte* byteArray, int len);

#endif api_class_h
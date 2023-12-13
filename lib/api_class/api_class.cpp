#include <api_class.h>

APIcall::APIcall(const char*root_ca_char, String shared_key,String uuid) {
    // constructor root_ca and shared_key
    root_ca=root_ca_char;
    this->shared_key = shared_key;
    this->uuid=uuid;}


void APIcall::auth_header_and_time(){
  const char* ntpServer = "pool.ntp.org";  
  configTime(0, 0, ntpServer);
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("FAILED TO OBTAIN TIME");
  }
  char buffer[30];
  strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", &timeinfo);
  // setting private time attribute
  time=String(buffer);
  // now making signature
  String msg= "licenseSpring\ndate: " + time;

  String signiture=HMAC_SHA256_To_Base64(shared_key, msg);// passing signature to hmac_sha256 and doing base encoding

  auth_header = "algorithm=\"hmac-sha256\", headers=\"date\", signature=\"" + signiture + "\", apiKey=\"" + uuid + "\"";
  
}
void APIcall::check_time(){
    Serial.println(time);
    
}

bool APIcall::check_license(String product_short_code,String hardware_id,String license_key){

  bool license_stat;
  WiFiClientSecure client;

  client.setCACert(root_ca);


  HTTPClient http;
  
  String url="https://api.licensespring.com/api/v4/check_license/";
  url +="?product="+product_short_code;
  url +="&hardware_id="+hardware_id;
  url +="&license_key="+license_key;
  Serial.print(url);

  http.begin(client, url);
  // Add the headers to the request.
  http.addHeader("Date",time);
  http.addHeader("Authorization",auth_header);
  http.addHeader("Content-Type", "application/json");
    
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      StaticJsonDocument<4000> doc;

  // Deserialize the JSON document
      DeserializationError error = deserializeJson(doc, payload);

  // Test if parsing succeeds.
      if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return false;
  }
      license_stat = doc["license_active"].as<bool>();
      http.end();
      return license_stat;
      
    
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    http.end();
    
  }
  
  return false;
}


String HMAC_SHA256_To_Base64(String secretKey, String message) {
    Sha256Wrapper sha256; // Declare an instance of the Sha256Wrapper class
         // Declare an instance of the Sha256Wrapper class

    // Calculate HMAC-SHA256 hash
    sha256.initHmac((const uint8_t*)secretKey.c_str(), secretKey.length());
    sha256.print(message.c_str());
    uint8_t* result = sha256.resultHmac();

    // Convert HMAC-SHA256 result to byte array
    uint8_t byteAr[32];
    for(int i = 0; i < 32; i++) {
        byteAr[i] = result[i];
    }
    String encoded=base64Encode(byteAr, 32);
    // Base64 encoding
    return encoded;}

String base64Encode(byte* byteArray, int len) {

    String encodedString = "";

    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int i = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (len--) {
        char_array_3[i++] = *(byteArray++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for(i = 0; i < 4; i++)
                encodedString += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for(int j = i; j < 3; j++)
            char_array_3[j] = '\0';
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        for (int j = 0; (j < i + 1); j++)
            encodedString += base64_chars[char_array_4[j]];
        while((i++ < 3))
            encodedString += '=';
    }

    return encodedString;}


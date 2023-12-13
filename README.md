
## IoT PoC ESP32
This project was part of my onboarding as a **student**. The goal was to establish **HTTPS communication with the LicenseSpring server** on an **ESP32 board** and perform a license check. The actual code is written in **C++** and follows the **Arduino structure**, utilizing libraries and functions suitable for microcontroller programming.

For secure communication, a **root certificate** is provided. We successfully ran code on an **ESP32 microcontroller** to simulate the changing states of a software license. By utilizing **Postman**, an **HTTPS client**, we were able to change the state of the license and allow temperature sensor readings. It's important to note that this demo, primarily for illustrative purposes, did not encompass real-world complexities such as verifying the current state of the license (i.e., checking if a license previously activated had been deactivated). The primary aim was to showcase the potential interaction between hardware (**ESP32**) and software licensing mechanisms in a simplified scenario.

**Potential Further Exploration**:
* **Add Configuration File**: Network and other credentials should be exported from a file.
* **Explore How to Wrap This Inside an SDK**: Handling the hardware ID of the IoT device, license file, etc.
* **Improve Class for Handling HTTPS Requests**: Make a wrapper around the API.
* **Explore How to Acquire Root Certificate Automatically**.


Acquire the Root certificate through **cert_script** where the certificate is added for **[LicenseSpring API](https://api.licensespring.com/)** --> `ls_prod.pem`. Navigate to the script directory with `cd cert_script` and run: `python3 main.py`.   
The program prints out the certificate, which has to be pasted inside `main.cpp`.

**WARNING**: Please check if the certificate is valid. Refer to this [blog post](https://licensespring.com/blog/other/esp32-board-license-node-locking-proof-of-concept/) for instructions.
## Configuration
Include the following LicenseSpring configuration fields in the `main.cpp`
### Define LicenseSpring Fields 

```cpp
String secretKey = "secret_key_from_licensespring";  
String uuid = "uuid";  
String product_short_code = "your_product_short_code";  
String hardware_id = "hardware_id";  
String license_key = "license_key";   
```

### Define network fields
```cpp
const char *ssid = "ssid_of_wifi";  
const char *pass = "password";
```

## Preparing  Hardware and Softwware

1. Connect Sensors: Carefully connect each sensor to the designated pins on your ESP32 board. Refer to the sensor documentation or your project's hardware schematic for the correct wiring.

2. Power the Board through USB  
3. Navigate to Project Folder `cd path/to/your/PoC_HTTPS_LS`
4. In the PlatformIO terminal, execute the following command to compile your code and upload it to the ESP32 board: `platformio run --target upload`
   
5. Open serial monitor and change state of license when ESP32 board is connected


## License

This project is licensed under the Apache 2.0 License - see the [LICENSE](LICENSE) file for details.
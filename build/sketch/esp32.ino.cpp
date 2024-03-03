#include <Arduino.h>
#line 1 "/home/ahsanu/project/2024/hardware/projekRKO/esp32/esp32.ino"
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <WiFi.h>

#define DATABASE_URL "https://dspencer-9922d-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define API_KEY "AIzaSyDEol-SCHoaGise0us8aLctZaIWcOQvQUM"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillisFirebase = 0;
bool signupOK = false;
#define RX 10;
#define TX 11;


#line 17 "/home/ahsanu/project/2024/hardware/projekRKO/esp32/esp32.ino"
void setupFirebaseRTDB();
#line 29 "/home/ahsanu/project/2024/hardware/projekRKO/esp32/esp32.ino"
void mil();
#line 35 "/home/ahsanu/project/2024/hardware/projekRKO/esp32/esp32.ino"
void setup();
#line 43 "/home/ahsanu/project/2024/hardware/projekRKO/esp32/esp32.ino"
void loop();
#line 17 "/home/ahsanu/project/2024/hardware/projekRKO/esp32/esp32.ino"
void setupFirebaseRTDB() {
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")) {
    signupOK = true;
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void mil() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillisFirebase > 5000 || sendDataPrevMillisFirebase == 0)) {
    sendDataPrevMillisFirebase = millis();
  }
}

void setup() {
  Serial.begin(9600);
  while (WiFi.status() == WL_CONNECTED) {
    setupFirebaseRTDB();
    break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}


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

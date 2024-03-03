#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <addons/RTDBHelper.h>
#include <addons/TokenHelper.h>

#define RX 10;
#define TX 11;

// Insert your network credentials
#define WIFI_SSID "REPLACE_WITH_YOUR_SSID"
#define WIFI_PASSWORD "REPLACE_WITH_YOUR_PASSWORD"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDEol-SCHoaGise0us8aLctZaIWcOQvQUM"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL                                                           \
  "https://dspencer-9922d-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define WAIT_UNTIL_NEW_DATA                                                    \
  while (Serial.available() <= 0) {                                            \
  }

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see
                                                      // addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

bool isTimeToSendData() {
  return Firebase.ready() && signupOK &&
         (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0);
}

int getDataDht11() {
  WAIT_UNTIL_NEW_DATA;
  return Serial.parseInt();
}

float getDataTempSensor() {
  WAIT_UNTIL_NEW_DATA;
  return Serial.parseFloat();
}

void loop() {
  if (isTimeToSendData()) {
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "dataSensor/dht11", getDataDht11())) {
      Serial.println("berhasil mengirimkan data ke database");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    } else {
      Serial.println("gagal mengirimkan data ke database");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "dataSensor/tempSensor",
                               getDataTempSensor())) {
      Serial.println("berhasil mengirimkan data ke database");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    } else {
      Serial.println("gagal mengirimkan data ke database");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}

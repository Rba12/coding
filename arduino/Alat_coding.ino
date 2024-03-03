#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 20, 4);

//rtc
char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
int jam, menit, detik;
int tanggal, bulan, tahun;
String hari;

//sensor
int value;
int MQ = A0;
DHT dht(12, DHT22);
int pir = 3;
int data = 0;
int flamesensor = A1;
int sensorValue = 0;

// relay
int pompa_relay = 8;
int buzzer_relay = 4;
int led_relay = 5;
int kipas_relay = 7;
#define RX 10;
#define TX 11;


void asap();
void pompa();
void pir1();

void setup() {
  
  Serial.begin(9600);
  dht.begin();
  // lcd.init();
  if(! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  lcd.backlight();
  lcd.setCursor(0, 0);
  pinMode(MQ, INPUT);
  pinMode(pir, INPUT);
  pinMode(flamesensor, INPUT);
  pinMode(kipas_relay, OUTPUT);
  pinMode(buzzer_relay, OUTPUT);
  pinMode(led_relay, OUTPUT);
  pinMode(pompa_relay, OUTPUT);
  //rtc.adjust(DateTime(2024, 2, 10, 22, 35, 0));//ngatur waktu rtc
}

void loop() {

  DateTime now = rtc.now();
  jam     = now.hour();
  menit   = now.minute();
  detik   = now.second();
  tanggal = now.day();
  bulan   = now.month();
  tahun   = now.year();
  hari    = daysOfTheWeek[now.dayOfTheWeek()];

  value = analogRead(MQ);
  sensorValue = analogRead(flamesensor);
  data = digitalRead(pir);

  // delay(3000);



  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.print("kelembapan: ");
  Serial.print(kelembaban);
  Serial.println(" % ");
  Serial.print("suhu: ");
  Serial.print(suhu);
  Serial.println(" *C ");
  // Serial.print("\n ");

  Serial.print("Sensor Mq :");
  Serial.println(value);
  // Serial.print("\n");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.setCursor(9, 0);
  lcd.print(kelembaban);
  lcd.setCursor(14, 0);
  lcd.println(" % ");


  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.setCursor(9, 1);
  lcd.print(suhu);
  lcd.setCursor(14, 1);
  lcd.println(" C ");


  Serial.print("pembacaan sensor api :");
  Serial.println(sensorValue);
  // Serial.println("\n");

  Serial.print("Pembacaan Nilai PIR: ");
  Serial.print(data);
  Serial.print("\n");
  delay(3000);

  Serial.print(hari);
  Serial.print(",");
  
  Serial.print(jam);
  Serial.print(":");

  Serial.print(menit);
  delay(1000);


  if (suhu >= 30) {
    digitalWrite(kipas_relay, HIGH);
  } else {
    digitalWrite(kipas_relay, LOW);
  }
  Serial.print("\n ");

if(jam >= 18 || jam <=6){
  pir1();
}
  pompa();
}

void pir1() {
  if (data == 1) {
    Serial.print(" Ruko Tidak Aman \n\n");
    digitalWrite(buzzer_relay, HIGH);
    digitalWrite(led_relay, HIGH);

    if (sensorValue > 1000 && value > 1000) {
      asap();
    }
  } else {
    Serial.print(" Ruko Aman \n\n");
    digitalWrite(buzzer_relay, LOW);
    digitalWrite(led_relay, LOW);
    if (sensorValue > 1000 && value > 1000) {
      asap();
    }
  }
}

void pompa() {
  // if (sensorValue < 1000 && value > 600 ){
  // asap();
  // }
  // else{
  //   digitalWrite(buzzer_relay,LOW);
  //   digitalWrite(led_relay,LOW);
  //   digitalWrite(pompa_relay,LOW);
  //   Serial.println(value);
  //   Serial.println("Aman");
  // }
}

void asap() {
  digitalWrite(buzzer_relay, HIGH);
  digitalWrite(led_relay, HIGH);
  digitalWrite(pompa_relay, HIGH);
  //Serial.print("Nilai output analog = ");
  Serial.println(value);
  Serial.println("ada api");
  delay(1000);
}
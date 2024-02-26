void mil() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillisFirebase > 5000 || sendDataPrevMillisFirebase == 0)) {
    sendDataPrevMillisFirebase = millis();
  }
}
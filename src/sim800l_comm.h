#ifndef SIM800L_COMM_H
#define SIM800L_COMM_H

#include <SoftwareSerial.h>

// Define SIM800L TX and RX pins
#define SIM800_TX 26
#define SIM800_RX 27

SoftwareSerial sim800(SIM800_RX, SIM800_TX); // RX, TX

void setupSIM800L() {
  sim800.begin(9600);
  delay(1000);
  sim800.println("AT");
  delay(1000);
  sim800.println("AT+CPIN?");
  delay(1000);
}

bool isSIMAvailable() {
  sim800.println("AT+CPIN?");
  delay(1000);
  String response = "";
  while (sim800.available()) {
    response += sim800.readString();
  }
  return response.indexOf("READY") != -1;
}

void sendSMS(const char* number, const char* message) {
  if (!isSIMAvailable()) {
    Serial.println("⚠️ SIM not available or not ready. Displaying message on Serial instead:");
    Serial.print("To: ");
    Serial.println(number);
    Serial.print("Message: ");
    Serial.println(message);
    return;
  }

  sim800.println("AT+CMGF=1");    // Set SMS mode to text
  delay(500);
  sim800.print("AT+CMGS=\"");
  sim800.print(number);
  sim800.println("\"");
  delay(500);
  sim800.print(message);
  delay(500);
  sim800.write(26); // Ctrl+Z to send SMS
  delay(2000);
  Serial.println("✅ SMS sent successfully.");
}

#endif

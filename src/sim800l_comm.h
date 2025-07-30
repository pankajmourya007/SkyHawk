#ifndef SIM800L_COMM_H
#define SIM800L_COMM_H

#include <SoftwareSerial.h>

SoftwareSerial sim800l(26, 27); // RX=26, TX=27

void setupSIM800L() {
  sim800l.begin(9600);
  delay(1000);
  sim800l.println("AT");
  delay(500);
  sim800l.println("AT+CMGF=1"); // Set SMS mode to text
  delay(500);
}

// Sends SMS with given message to the provided phone number
void sendSMS(String number, String message) {
  sim800l.println("AT+CMGF=1");
  delay(200);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(number);
  sim800l.println("\"");
  delay(200);
  sim800l.print(message);
  delay(200);
  sim800l.write(26); // Ctrl+Z to send
  delay(1000);
}

#endif

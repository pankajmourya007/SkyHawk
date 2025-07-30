#ifndef NRF_RADIO_H
#define NRF_RADIO_H

#include <SPI.h>
#include <RF24.h>

RF24 radio(5, 18);  // CE=5, CSN=18

const byte address[6] = "00001";  // Simple address for RX/TX

void setupNRF() {
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.stopListening(); // Device is transmitter
}

void sendNRFMessage(String msg) {
  radio.write(&msg, sizeof(msg));
}

#endif

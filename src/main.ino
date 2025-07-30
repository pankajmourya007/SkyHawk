#include "gps_module.h"
#include "sim800l_comm.h"
#include "nrf_radio.h"

void setup() {
  Serial.begin(115200);
  setupGPS();
  setupSIM800L();
  setupNRF();
}

void loop() {
  double lat, lon;
  if (getGPSData(lat, lon)) {
    String gpsMsg = "Location: " + String(lat, 6) + "," + String(lon, 6);
    Serial.println(gpsMsg);

    // Send via SMS
    sendSMS("+917xxxxxxxxx", gpsMsg); // Replace with your number

    // Send over RF
    sendNRFMessage(gpsMsg);

    delay(10000); // Wait 10 seconds before next update
  }
}

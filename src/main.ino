#include "gps_module.h"         
#include "sim800l_comm.h"       
#include "nrf_radio.h"          

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize all modules
  setupGPS();        // NEO-6M
  setupSIM800L();    // SIM800L
  setupNRF();        // NRF24L01

  Serial.println("SkyHawk system initialized...");
}

void loop() {
  double lat, lon;

  // Check GPS and get location
  if (getGPSData(lat, lon)) {
    // Build message
    String gpsMsg = "SkyHawk Alert: Drone detected at\nLat: ";
    gpsMsg += String(lat, 6);
    gpsMsg += "\nLon: ";
    gpsMsg += String(lon, 6);

    // Debug to Serial
    Serial.println(gpsMsg);

    // Send to target number
    sendSMS("+917248291481", gpsMsg.c_str()); 

  } else {
    Serial.println("Waiting for GPS fix...");
  }

  delay(10000); // Wait 10s before next reading
}

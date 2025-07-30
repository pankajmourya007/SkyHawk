#ifndef GPS_MODULE_H
#define GPS_MODULE_H

#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;
HardwareSerial SerialGPS(1); // Use Serial1 for GPS (RX1/TX1)

void setupGPS() {
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
}

bool getGPSData(double &lat, double &lon) {
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
    if (gps.location.isUpdated()) {
      lat = gps.location.lat();
      lon = gps.location.lng();
      return true;
    }
  }
  return false;
}

#endif

#include <Mouse.h>
#include <hiduniversal.h>
#include <SPI.h>
#include "hidmouserptparser.h"

USB Usb;
HIDUniversal Hid(&Usb);
HIDMouseEvents MouEvents;
HIDMouseReportParser Mou(&MouEvents);

void setup() {
  Serial.begin(9600);
  Mouse.begin();
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");
    delay(200);

  if (!Hid.SetReportParser(0, &Mou))
    ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    int x = data.substring(0, data.indexOf(',')).toInt();
    int y = data.substring(data.indexOf(',') + 1).toInt();
    Mouse.move(x, y);
    Usb.Task();
  }
}

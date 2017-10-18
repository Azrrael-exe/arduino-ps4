#include <Arduino.h>
#include <PS4BT.h>
#include <usbhub.h>
#include <SPI.h>

#include <llp.h> // Low level protocol
#include "controller.h" // Controller Functions

USB Usb;
BTD Btd(&Usb);
// PS4BT PS4(&Btd, PAIR);
PS4BT PS4(&Btd);

DataPack input;

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}

void loop() {
  Usb.Task();
  if (PS4.connected() && PS4.getButtonPress(R2)) {
    DataPack output;
    if(controller::checkAxis(PS4)){
      output.addData(0xA0, controller::readAxis(PS4, LeftHat));
      output.addData(0xA1, controller::readAxis(PS4, RightHat));

    }
    uint16_t buttons = controller::readButtonsClick(PS4);
    if(buttons){
      output.addData(0xB0, buttons);
    }
    output.write(Serial);
  }
  if(input.available(Serial)){
    if(input.hasKey(0xC0)){
      PS4.setLed(Red);
    }
    if(input.hasKey(0xC1)){
      PS4.setLed(Green);
    }
    if(input.hasKey(0xC2)){
      PS4.setLed(Blue);
    }
    if(input.hasKey(0xC3)){
      PS4.setLed(Yellow);
    }
  }
}

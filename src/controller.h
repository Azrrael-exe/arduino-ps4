#ifndef controller_h
#define controller_h

#define LeftHat 0x10
#define RightHat 0x11

#include <Arduino.h>

namespace controller {
  bool checkAxis(PS4BT &ctr){
    if(ctr.getAnalogHat(LeftHatX) > 137 || ctr.getAnalogHat(LeftHatX) < 117 || ctr.getAnalogHat(LeftHatY) > 137 || ctr.getAnalogHat(LeftHatY) < 117 || ctr.getAnalogHat(RightHatX) > 137 || ctr.getAnalogHat(RightHatX) < 117 || ctr.getAnalogHat(RightHatY) > 137 || ctr.getAnalogHat(RightHatY) < 117) {
      return true;
    }
    else {
      return false;
    }
  }
  uint16_t readAxis(PS4BT &ctr, uint8_t axis){
    uint16_t output = 0;
    if(axis == LeftHat){
      output = (ctr.getAnalogHat(LeftHatX) << 8 | ctr.getAnalogHat(LeftHatY));
    }
    else if(axis == RightHat){
      output = (ctr.getAnalogHat(RightHatX) << 8 | ctr.getAnalogHat(RightHatY));
    }
    return output;
  }
  uint16_t readButtonsClick(PS4BT &ctr){
    uint16_t output = 0;
    int b_list[16] = {
      UP, LEFT, DOWN, RIGHT,
      TRIANGLE, SQUARE, CROSS, CIRCLE,
      L2, L1, R1, R1,
      SHARE, L3, R3, OPTIONS
    };
    for(int i=0; i<16; i++){
      bitWrite(output, i, ctr.getButtonClick(b_list[i]));
    }
    return output;
  }
}

#endif

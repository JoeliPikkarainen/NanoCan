#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>

//Define build
#include "defines.h"

//Custom helpers
#include "oled_if.h"
#include "can_if.h"
#include "bluetooth_if.h"

#include "com_frame.h"

#include "mcp_can.h"

OLED_IF oled;
CAN_IF can;
BLUETOOTH_IF bt;

void setup() {

  //Power the periphreals
  pinMode(POWER_RAIL_PIN,OUTPUT);
  digitalWrite(POWER_RAIL_PIN,1);
  delay(200);

  //USB Serial
  Serial.begin(9600);
  Serial.println("START SERIAL\r\n");

  oled.init();
  oled.setText("OLED INITED");

  can.init();

  bt.init();
  bt.begin();

}

void loop() {


  COM_FRAME rx_frame;
  bt.receiveFrame(rx_frame);

  COM_FRAME dummy_frame;
  dummy_frame.toDummyFrame();
  bt.transmitFrame(dummy_frame);

  delay(1000);

}
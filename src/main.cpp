
//ARDUINO LIB
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>

//HW LIBS
#include <U8g2lib.h>
#include <CAN.h>

//Define build
#include "defines.h"
#include "mcp_can.h"

//Custom helpers
#include "oled_if.h"
#include "can_if.h"
#include "bluetooth_if.h"
#include "AdapterStates.h"

#include "com_frame.h"


OLED_IF oled;
CAN_IF can;
BLUETOOTH_IF bt;
AdapterStates state;

void actionsFromFrame(const COM_FRAME& frame);

void setup() {

  //Power the periphreals
  pinMode(POWER_RAIL_PIN,OUTPUT);
  digitalWrite(POWER_RAIL_PIN,1);
  
  delay(2000);

  //USB Serial
  Serial.begin(9600);

  oled.init();


  oled.setText("INIT CAN");
  while(!can.init()){
    Serial.println("Can init ERROR");
    oled.setText("CAN INIT ERROR");

    delay(100);
  }
  oled.setText("CAN INIT OK");

  Serial.println("Can init OK");


  bt.init();
  bt.begin();

}

void loop() {


  //RECEIVE VI BLUETOOTH
  COM_FRAME bt_rx_frame;
  int received_bt = bt.receiveFrame(bt_rx_frame);

  //TAKE ACTIONS FROM FRAME
  if(received_bt > 0){
      actionsFromFrame(bt_rx_frame);
  }

  CAN_FRAME can_rx_frame;
  
  bool received_can = can.receive(can_rx_frame);
  if(received_can){
    oled.setText("received can!");
    if(state.streaming){
      COM_FRAME bt_tx_frame;
      bt_tx_frame.addCanFrame(can_rx_frame);
      bt_tx_frame.m_cb = COMMAND_BYTE::CAN_FRAME;
      bt_tx_frame.m_sb = SENDER_BYTE::SENDER_CAN_MODULE_RESP;
      bt.transmitFrame(bt_tx_frame);
    }
  }

  
  can.getCan().dumpRegisters(Serial);
  //Serial.println(out.readString());
  
  
  /*
  COM_FRAME dummy_frame;
  dummy_frame.toDummyFrame();
  bt.transmitFrame(dummy_frame);
  */

  delay(1000);

}

void actionsFromFrame(const COM_FRAME& frame){

    if(frame.m_cb == COMMAND_BYTE::START_CAN_STREAM){
        oled.setText("start stream!");

        state.streaming = true;
    }
    if(frame.m_cb == COMMAND_BYTE::STOP_CAN_STREAM){
      oled.setText("stop stream!");
      state.streaming = false;
    }

}
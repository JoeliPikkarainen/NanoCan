
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

//Custom helpers
#include "oled_if.h"
#include "can_if.h"
#include "bluetooth_if.h"
#include "AdapterStates.h"
#include "eeprom_if.h"

#include "com_frame.h"

#include <string.h>

OLED_IF oled;
CAN_IF can;
BLUETOOTH_IF bt;
AdapterStates state;
AdapterSettings settings;

int blnk = 0;

void DBG(const char* str);

void actionsFromFrame(const COM_FRAME& frame);
void onCanReceived(int size);

void loadSettings(AdapterSettings& settings);
void applySettings(const AdapterSettings& settings);
void saveSettings(const AdapterSettings& settings);

void onCanRateGetRequested();
void onCanRateSetRequested(COM_FRAME rxframe);

bool hasReceived = false;

void setup() {

  //Power the periphreals
  //pinMode(POWER_RAIL_PIN,OUTPUT);
  //digitalWrite(POWER_RAIL_PIN,1);

  loadSettings(settings);

  pinMode(IS_ON_PIN,OUTPUT);
  digitalWrite(IS_ON_PIN,1);

  delay(2000);

  //USB Serial
#ifdef DBG_ON
  Serial.begin(115200);
#endif
  DBG("0");

  //oled.init();
  DBG("INITED OLED");


  //oled.setText("INIT CAN");
  DBG("INIT CAN");

  int can_retries = 0;
  while(!can.init() && can_retries < -1){
    delay(100);
    can_retries++;
    if(can_retries == 0){
      oled.setText("CAN INIT ERROR");
    }

  }

  DBG("INITED CAN");

  //can.sleepEnable(true);
  if(can.isInited()){
    oled.setText("CAN INIT OK");
  }else{
    oled.setText("CAN INIT FAIL");
  }

  DBG("1");


  bt.init();
      oled.setText("BT INIT OK");
  bt.begin();
      oled.setText("BT BEGIN OK");

 DBG("2");
      oled.setText("INIT DONE");

}

void loop() {

  //LED to check that device doesnt go to faulty reset loop, caused by USB Serial
  blnk = (blnk == 0) ? 1:0;
  digitalWrite(IS_ON_PIN,blnk);

  //RECEIVE VIA BLUETOOTH
  COM_FRAME bt_rx_frame;
  int received_bt = bt.receiveFrame(bt_rx_frame);

  //TAKE ACTIONS FROM FRAME
  if(received_bt > 0){
      actionsFromFrame(bt_rx_frame);
  }


  CAN_FRAME can_rx_frame = CAN_FRAME();
  
  bool received_can = can.receive(can_rx_frame);
  if(received_can){
    if(state.streaming){
      COM_FRAME bt_tx_frame = COM_FRAME();
      bt_tx_frame.addCanFrame(can_rx_frame);
      bt_tx_frame.m_sb = SENDER_BYTE::SENDER_CAN_MODULE_RESP;
      bt_tx_frame.m_cb = COMMAND_BYTE::CAN_FRAME;

      //char txtbf[16];
      //itoa(bt_tx_frame.m_data_len,txtbf,10);
      //oled.setText(txtbf);
      //bt.transmitFrame(bt_tx_frame);
    }
  }
  
  if(received_can && !hasReceived){

      //oled.setText("RECEIVED");
      hasReceived = received_can;
  }


  
  //can.getCan().dumpRegisters(Serial);
  
  
  /*
  COM_FRAME dummy_frame;
  dummy_frame.toDummyFrame();
  bt.transmitFrame(dummy_frame);
  */
 delay(1000);
}

void actionsFromFrame(const COM_FRAME& frame){

    char hexstr[201];

    uint8_t bf[32];
    int len;
    COM_FRAME tmp = frame;
    tmp.toByteArray(&bf[0],len);

    for(int i = 0; i < len; i++){
      sprintf(hexstr, "%02x ", bf[i]);
    }
    Serial.println(hexstr);

    if(frame.m_cb == COMMAND_BYTE::CAN_STREAM){
      if(frame.m_ctb == COMMNAD_TYPE_BYTE::SET){
        bool stream_on = (frame.m_data_buff[0] == 1) ? true : false;
        state.streaming = stream_on;
      }
    }

    else if(frame.m_cb == COMMAND_BYTE::CAN_RATE){
      if(frame.m_ctb == COMMNAD_TYPE_BYTE::GET){
        onCanRateGetRequested();
      }
      else if(frame.m_ctb == COMMNAD_TYPE_BYTE::SET){
        onCanRateSetRequested(frame);
      }
    }

}
void onCanRateGetRequested(){
        COM_FRAME resp;
        resp.m_ctb = COMMNAD_TYPE_BYTE::GET;
        resp.m_cb = COMMAND_BYTE::CAN_RATE;

        resp.m_data_len = 2;
        union kbs_u
        {
          uint16_t u16;
          uint8_t u8[2];
        }ku;

        ku.u16 = can.rateKbs;       
        resp.m_data_buff[1] = ku.u8[1];
        resp.m_data_buff[0] = ku.u8[0];
        bt.transmitFrame(resp);
}

void onCanRateSetRequested(COM_FRAME rxframe){

        union kbs_u
        {
          uint16_t u16;
          uint8_t u8[2];
        }ku;

        ku.u8[0] = rxframe.m_data_buff[0];
        ku.u8[1] = rxframe.m_data_buff[1];

        can.rateKbs = ku.u16;

        can.getCan().end();
        
        COM_FRAME f;
        f.m_data_len = 1;
        f.m_data_buff[0] = can.init();
        bt.transmitFrame(f);
        onCanRateGetRequested();

        bt.transmitInfoText("HELLO",5);
        
}

void loadSettings(AdapterSettings& settings)
{

  EEPROM_IF e;
  settings.can_rate_kbs = e.loadu16(SECTOR_CAN_RATE); 
}
void applySettings(const AdapterSettings& settings)
{
  can.rateKbs = settings.can_rate_kbs;
}

void saveSettings(const AdapterSettings& settings)
{
  EEPROM_IF e;
  e.saveValue((const void*)can.rateKbs, SECTOR_CAN_RATE, sizeof(can.rateKbs));
}



void DBG(const char* str){
#ifdef DBG_ON
  Serial.println(str);
  Serial.flush();
  Serial.clearWriteError();
#endif
}

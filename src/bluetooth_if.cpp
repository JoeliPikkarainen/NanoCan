#include "bluetooth_if.h"
#include "defines.h"

BLUETOOTH_IF::BLUETOOTH_IF() 
{
    
}

int BLUETOOTH_IF::init() 
{
    m_serial = new SoftwareSerial(BT_RX, BT_TX);
}

int BLUETOOTH_IF::begin() 
{
    m_serial->begin(9600);
    m_serial->write("START BLUETOOTH\n\r");
    return 0;
}

int BLUETOOTH_IF::getMessage(char *msg) 
{
    char bt_bf[16];

    uint8_t byte_cnt = 0;
    for(;m_serial->available() > 0;){
        //Serial.write(bt.read());
        bt_bf[byte_cnt] = m_serial->read();
        byte_cnt++;
    }

    strcpy(msg,bt_bf);
    return byte_cnt;
}

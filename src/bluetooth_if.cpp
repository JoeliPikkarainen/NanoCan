#include "bluetooth_if.h"
#include "defines.h"

#include "Arduino.h"

BLUETOOTH_IF::BLUETOOTH_IF() 
{
    
}

int BLUETOOTH_IF::init() 
{
    m_serial = new SoftwareSerial(BT_RX, BT_TX);
    pinMode(BT_STATE, INPUT);
    return 0;
}

int BLUETOOTH_IF::begin() 
{
    m_serial->begin(9600);
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

int BLUETOOTH_IF::transmitFrame(COM_FRAME frame) 
{
    uint8_t frame_bf[64];
    int len = -1;
    frame.toByteArray(&frame_bf[0],len);

    int sent = m_serial->write(frame_bf,len);
    return sent;  
}

int BLUETOOTH_IF::receiveFrame(COM_FRAME& frame) 
{
    if(m_serial->available() == 0)
        return -1;

    int frame_size = m_serial->available();
    uint8_t f_buff[frame_size];

    for (int i = 0; i < frame_size; i++)
    {
        f_buff[i] = m_serial->read();
    }
    
    frame.fromByteArray(f_buff,frame_size);
    return frame_size;
}

int BLUETOOTH_IF::transmitInfoText(const char* str, int len) 
{
    uint8_t bf[16];
    for(int i = 0; i < len; i++){
        bf[i] = str[i];
    }

    COM_FRAME f = COM_FRAME(
        SENDER_BYTE::SENDER_CAN_MODULE_RESP,
        COMMNAD_TYPE_BYTE::NULL_TYPE_BYTE,
        COMMAND_BYTE::INFO_STRING,
        len,
        bf
    );

    transmitFrame(f);
}

bool BLUETOOTH_IF::connected() 
{
    return digitalRead(BT_STATE);
}

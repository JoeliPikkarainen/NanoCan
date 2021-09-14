#ifndef BLUETOOTH_IF_H
#define BLUETOOTH_IF_H

#include <SoftwareSerial.h>
#include <com_frame.h>

class BLUETOOTH_IF{

public:
    BLUETOOTH_IF();
    
    int init();
    int begin();

    int getMessage(char *msg);
    
    int transmitFrame(COM_FRAME frame);
    int receiveFrame(COM_FRAME& frame);
    
private:
    SoftwareSerial* m_serial;
};
#endif
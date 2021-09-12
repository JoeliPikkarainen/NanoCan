#ifndef BLUETOOTH_IF_H
#define BLUETOOTH_IF_H

#include <SoftwareSerial.h>

class BLUETOOTH_IF{

public:
    BLUETOOTH_IF();
    
    int init();
    int begin();

    int getMessage(char *msg);
    
private:
    SoftwareSerial* m_serial;
};
#endif
#ifndef OLED_IF_H
#define OLED_IF_H

#include "defines.h"

#include <U8g2lib.h>
#include <Wire.h>

class OLED_IF{

public:
    OLED_IF();
    
    int init();
    int setText(const char* str);

private:

};

#endif
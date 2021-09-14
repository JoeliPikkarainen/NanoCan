#include "oled_if.h"
//0.91 128X32 OLED
U8G2_SSD1306_128X64_NONAME_2_SW_I2C u8g2 (U8G2_R0, I2C_SDA, I2C_SCL);

//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_ALT0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // same as the NONAME variant, but may solve the "every 2nd line skipped" problem
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 16, /* data=*/ 17, /* reset=*/ U8X8_PIN_NONE);   // ESP32 Thing, pure SW emulated I2C
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 16, /* data=*/ 17);   // ESP32 Thing, HW I2C with pin remapping

#define FONT_DEFAULT    u8g2_font_profont12_mr
#define FONT_H_PX       8
#define OLED_H_PX       64
#define OLED_W_PX       128
OLED_IF::OLED_IF()
{
    
}

int OLED_IF::init()
{
    u8g2.begin();
    u8g2.firstPage();
    return 0;
}

int OLED_IF::setText(const char* str)
{
    u8g2.clear();
    u8g2.clearDisplay();
    u8g2.clearBuffer();


        do{
            u8g2.setFont(FONT_DEFAULT);
            u8g2.drawStr(0, 20, str);
        } while(u8g2.nextPage());


    
    return 0;
}

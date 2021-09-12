#include "oled_if.h"
//0.91 128X32 OLED
U8G2_SSD1306_128X64_NONAME_2_SW_I2C u8g2 (U8G2_R0, I2C_SDA, I2C_SCL);

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
            u8g2.drawStr(0, 15, str);
        } while(u8g2.nextPage());
    

return 0;
}

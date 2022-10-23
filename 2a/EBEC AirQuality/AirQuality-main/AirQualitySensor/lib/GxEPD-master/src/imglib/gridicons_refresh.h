#if defined(ESP8266) || defined(ESP32)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif
// 24 x 24 gridicons_refresh
const unsigned char gridicons_refresh[] PROGMEM = { /* 0X01,0X01,0XB4,0X00,0X40,0X00, */
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 
0xFF, 0xFF, 0x1F, 0xFF, 0xFE, 0x3F, 0xFF, 0xFC, 
0x01, 0xFF, 0xFC, 0x00, 0x7F, 0xFE, 0x3C, 0x3F, 
0xFF, 0x1F, 0x1F, 0xFF, 0x8F, 0x9F, 0xFF, 0xFF, 
0x8F, 0xFF, 0xFF, 0xCF, 0xFF, 0xFF, 0xCF, 0xFF, 
0xFF, 0xCF, 0xF3, 0xFF, 0xCF, 0xF1, 0xFF, 0x8F, 
0xF9, 0xFF, 0x9F, 0xF8, 0xFF, 0x1F, 0xFC, 0x3C, 
0x3F, 0xFE, 0x00, 0x7F, 0xFF, 0x81, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

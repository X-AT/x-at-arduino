
#include "main.h"
#include "u8g.h"

static u8g_t u8g;


void Display_Task_Init(void)
{
	u8g_InitI2C(&u8g, &u8g_dev_ssd1306_128x64_i2c, U8G_I2C_OPT_NONE);

	u8g_SetFont(&u8g, u8g_font_6x10);
	u8g_DrawStr(&u8g, 0, 15, "Hello World!");
}


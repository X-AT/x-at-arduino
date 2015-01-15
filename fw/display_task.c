
#include "main.h"
#include "u8g.h"
#include "wall_time.h"

static u8g_t u8g;
static unsigned long last_redraw_ms;
static enum {
	DRAW_USB_CONNECT_MSG,
	DRAW_USB_DISCONNECT_MSG,
	DRAW_USB_DATA
} draw_state;


static void draw(void)
{
	switch (draw_state) {
		case DRAW_USB_CONNECT_MSG:
			u8g_DrawStrP(&u8g, 0, 10, PSTR("USB connected."));
			u8g_DrawStrP(&u8g, 0, 26, PSTR("Waiting X-AT trackd..."));
			break;

		case DRAW_USB_DISCONNECT_MSG:
			u8g_DrawStrP(&u8g, 0, 10, PSTR("USB disconnected!!!"));
			break;

		case DRAW_USB_DATA:
			/* XXX: need to figure out how to draw image outside of picture loop */
			break;
	}
}

void Display_Task_Init(void)
{
	u8g_InitI2C(&u8g, &u8g_dev_ssd1306_128x64_i2c, U8G_I2C_OPT_FAST);

	u8g_SetFont(&u8g, u8g_font_6x10);
	last_redraw_ms = millis();
	Display_USBDisconnect();
}

void Display_Task(void)
{
	// reduce frame rate
	unsigned long time = millis();
	if (time > last_redraw_ms && time - last_redraw_ms < 10)
		return;
	last_redraw_ms = millis();

	u8g_FirstPage(&u8g);
	do {
		wdt_reset();
		draw();
	}
	while ( u8g_NextPage(&u8g) );
}

uint8_t Display_GetWidth(void)
{
	return u8g_GetWidth(&u8g);
}

uint8_t Display_GetHeight(void)
{
	return u8g_GetHeight(&u8g);
}

void Display_USBConnect(void)
{
	draw_state = DRAW_USB_CONNECT_MSG;
}

void Display_USBDisconnect(void)
{
	draw_state = DRAW_USB_DISCONNECT_MSG;
}

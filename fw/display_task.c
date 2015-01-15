
#include "main.h"
#include "u8g.h"
#include "wall_time.h"

static u8g_t u8g;
static unsigned long last_redraw_ms;
static enum {
	DRAW_USB_CONNECT_MSG,
	DRAW_USB_DISCONNECT_MSG,
	DRAW_USB_ERROR_MSG,
	DRAW_USB_DATA
} draw_state;


#define D_WIDTH		128
#define D_HEIGHT	64

/** image buffer that stores whole image from usb host
 * Size hardcoded for SSD1306 128x64 OLED display
 */
static uint8_t frame_buffer[D_WIDTH * D_HEIGHT / 8];


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

		case DRAW_USB_ERROR_MSG:
			u8g_DrawStrP(&u8g, 0, 10, PSTR("USB report error."));
			u8g_DrawStrP(&u8g, 0, 26, PSTR("Wrong display message."));
			break;

		case DRAW_USB_DATA:
			u8g_DrawBitmap(&u8g, 0, 0, D_WIDTH/8, D_HEIGHT, frame_buffer);
			break;
	}
}

void Display_Task_Init(void)
{
	u8g_InitI2C(&u8g, &u8g_dev_ssd1306_128x64_i2c, U8G_I2C_OPT_FAST);
	u8g_SetFont(&u8g, u8g_font_6x10);

	last_redraw_ms = millis();
	Display_USBDisconnect();
	memset(frame_buffer, 0, sizeof(frame_buffer));
}

void Display_Task(void)
{
	// reduce frame rate
	unsigned long time = millis();
	if (time > last_redraw_ms && time - last_redraw_ms < 10)
		return;
	last_redraw_ms = millis();

	u8g_FirstPage(&u8g);
	do
		draw();
	while (u8g_NextPage(&u8g));
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

void Display_USBError(void)
{
	draw_state = DRAW_USB_ERROR_MSG;
}

void Display_Write(uint16_t offset, uint8_t len, uint8_t *data)
{
	// sanity check
	if (offset + len > sizeof(frame_buffer))
		draw_state = DRAW_USB_ERROR_MSG;
	else
		draw_state = DRAW_USB_DATA;

	memcpy(frame_buffer + offset, data, len);
}

/**
 * @brief Header file for main.c.
 * @file
 *
 * Based on LUFA GenericHID demo.
 */

#ifndef _MAIN_H_
#define _MAIN_H_

/* Includes: */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>

#include "Descriptors.h"
#include "wall_time.h"

#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

/* Macros: */
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

/* Function Prototypes: */
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
void EVENT_USB_Device_StartOfFrame(void);

bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		uint8_t* const ReportID,
		const uint8_t ReportType,
		void* ReportData,
		uint16_t* const ReportSize);
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		const uint8_t ReportID,
		const uint8_t ReportType,
		const void* ReportData,
		const uint16_t ReportSize);


/* adc_task module */
void ADC_Task_Init(void);
void ADC_Task(void);
uint16_t BAT_GetVoltageRaw(void);
uint16_t QTR_GetAzValueRaw(void);
uint16_t QTR_GetElValueRaw(void);
uint8_t QTR_GetStatusButtons(void);
void QTR_SetAzElLevel(uint16_t az, uint16_t el);

/* stepper_task module */
void Stepper_Task_Init(void);
void Stepper_Task(void);
int32_t Stepper_GetAzPosition(void);
int32_t Stepper_GetElPosition(void);
uint8_t Stepper_GetFlags(void);
void Stepper_GetSettings(struct XAT_Report_Stepper_Settings *settings);
void Stepper_SetSettings(const struct XAT_Report_Stepper_Settings *settings);
void Stepper_SetAzEl(const struct XAT_Report_Az_El *az_el);
void Stepper_SetCurPosition(const struct XAT_Report_Cur_Position *cur_position);
void Stepper_Stop(bool az, bool el);

/* display_task module */
void Display_Task_Init(void);
void Display_Task(void);
uint8_t Display_GetWidth(void);
uint8_t Display_GetHeight(void);
void Display_USBConnect(void);
void Display_USBDisconnect(void);
void Display_USBError(void);
void Display_Write(uint16_t offset, uint8_t len, uint8_t *data);

#endif /* _MAIN_H_ */

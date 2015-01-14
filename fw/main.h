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

#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

/* Macros: */

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

#endif /* _MAIN_H_ */

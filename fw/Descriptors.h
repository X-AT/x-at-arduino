/**
 * @brief Header file for Descriptors.c.
 * @file
 *
 * Based on LUFA GenericHID demo.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

/* Includes: */
#include <avr/pgmspace.h>
#include <LUFA/Drivers/USB/USB.h>

/* Type Defines: */
typedef struct {
	USB_Descriptor_Configuration_Header_t Config;

	// Generic HID Interface
	USB_Descriptor_Interface_t            HID_Interface;
	USB_HID_Descriptor_HID_t              HID_GenericHID;
	USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
} USB_Descriptor_Configuration_t;

enum InterfaceDescriptors_t {
	INTERFACE_ID_XAT_HID = 0, /**< HID interface descriptor ID */
};

enum StringDescriptors_t {
	STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
	STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
	STRING_ID_Product      = 2, /**< Product string ID */
};

/* HID report types */
enum XAT_ReportID_t {
	REPORT_ID_F_INFO = 1,
	REPORT_ID_G_STATUS = 2,
	REPORT_ID_G_BAT_VOLTAGE = 3,
	REPORT_ID_F_STEPPER_SETTINGS = 4,
	REPORT_ID_S_AZ_EL = 5,
	REPORT_ID_F_QTR = 6,
};

struct XAT_Report_Info {
	uint8_t display_rows;
	uint8_t display_columns;
	/* TODO */
} ATTR_PACKED;

struct XAT_Report_Status {
	/* TODO flags bits */
	uint8_t flags;
#define STATUS_BUTTON1	(1<<0)
#define STTAUS_BUTTON2	(1<<1)
	uint8_t buttons;
	int32_t azimuth_position;
	int32_t elevation_position; /* (altitude) */
} ATTR_PACKED;

struct XAT_Report_Bat_Voltage {
	uint16_t raw_adc;
} ATTR_PACKED;

struct XAT_Report_Stepper_Settings {
	uint16_t azimuth_acceleration;
	uint16_t elevation_acceleration;
	uint16_t azimuth_velocity;
	uint16_t elevation_velocity;
} ATTR_PACKED;

struct XAT_Report_Az_El {
	int32_t azimuth_position;
	int32_t elevation_position;
} ATTR_PACKED;

struct XAT_Report_QTR {
	uint16_t azimuth_qtr_raw;
	uint16_t elevation_qtr_raw;
} ATTR_PACKED;

typedef union {
	uint8_t data[64];
	struct XAT_Report_Info info;
	struct XAT_Report_Status status;
	struct XAT_Report_Bat_Voltage bat_voltage;
	struct XAT_Report_Stepper_Settings stepper_settings;
	struct XAT_Report_Az_El az_el;
	struct XAT_Report_QTR qtr;
} XAT_ReportBuffer_t;

/* Macros: */
/** Endpoint address of the HID reporting IN endpoint. */
#define HID_IN_EPADDR         (ENDPOINT_DIR_IN | 1)

/** Size in bytes of the Generic HID reporting endpoint. */
#define HID_EPSIZE            64

/* Function Prototypes: */
uint16_t CALLBACK_USB_GetDescriptor(
		const uint16_t wValue,
		const uint8_t wIndex,
		const void** const DescriptorAddress)
	ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

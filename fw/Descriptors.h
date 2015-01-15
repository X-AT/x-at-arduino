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
	STRING_ID_SerialNumber = 3, /**< Serial number (git describe) string ID */
};

/* HID report types */
enum XAT_ReportID_t {
	REPORT_ID_F_INFO             = 1,	/**< Get device info */
	REPORT_ID_G_STATUS           = 2,	/**< Get status: endstops and positions */
	REPORT_ID_G_BAT_VOLTAGE      = 3,	/**< Get raw analog value of Vbat (see logical/phys min/max desc) */
	REPORT_ID_F_STEPPER_SETTINGS = 4,	/**< Get/set acceleration and velocity settings */
	REPORT_ID_S_AZ_EL            = 5,	/**< Set target position for steppers */
	REPORT_ID_F_QTR              = 6,	/**< Get raw analog value / Set threshold level */
	REPORT_ID_F_CUR_POSITION     = 7,	/**< Set current position of steppers (cuse with caution) */
	REPORT_ID_S_STOP             = 8,	/**< Require stop of motors */
	REPORT_ID_S_DISP_WRITE_8     = 16,	/**< Write bitmap to display (max 8-byte) */
	REPORT_ID_S_DISP_WRITE_16    = 17,	/**< Write bitmap to display (max 16-byte) */
	REPORT_ID_S_DISP_WRITE_32    = 18,	/**< Write bitmap to display (max 32-byte) */
	REPORT_ID_S_DISP_WRITE_60    = 19,	/**< Write bitmap to display (max 60-byte) */
};

struct XAT_Report_Info {
	uint8_t display_name[32];
	uint8_t display_rows;
	uint8_t display_columns;
	/* TODO */
} ATTR_PACKED;

struct XAT_Report_Status {
#define FLAGS_AZ_IN_MOTION	(1<<0)
#define FLAGS_EL_IN_MOTION	(1<<1)
	uint8_t flags;
#define STATUS_BUTTON1	(1<<0)	// azimuth endstop
#define STATUS_BUTTON2	(1<<1)
	uint8_t buttons;
	int32_t azimuth_position;
	int32_t elevation_position; /* aka USAGE(altitude) */
} ATTR_PACKED;

struct XAT_Report_Bat_Voltage {
	uint16_t raw_adc;
} ATTR_PACKED;

struct XAT_Report_Stepper_Settings {
	uint16_t azimuth_acceleration;
	uint16_t elevation_acceleration;
	uint16_t azimuth_max_speed;
	uint16_t elevation_max_speed;
} ATTR_PACKED;

struct XAT_Report_Az_El {
	int32_t azimuth_position;
	int32_t elevation_position;
} ATTR_PACKED;

struct XAT_Report_QTR {
	uint16_t azimuth_qtr_raw;
	uint16_t elevation_qtr_raw;
} ATTR_PACKED;

struct XAT_Report_Cur_Position {
	int32_t azimuth_position;
	int32_t elevation_position;
} ATTR_PACKED;

struct XAT_Report_Stop {
#define STOP_MOTOR_AZ	(1<<0)
#define STOP_MOTOR_EL	(1<<1)
	uint8_t motor;
} ATTR_PACKED;

struct XAT_Report_Disp_Write_n {
	uint16_t offset;
	uint8_t len;
	uint8_t data[];
} ATTR_PACKED;

typedef union {
	uint8_t data[64];
	struct XAT_Report_Info info;
	struct XAT_Report_Status status;
	struct XAT_Report_Bat_Voltage bat_voltage;
	struct XAT_Report_Stepper_Settings stepper_settings;
	struct XAT_Report_Az_El az_el;
	struct XAT_Report_QTR qtr;
	struct XAT_Report_Cur_Position cur_position;
	struct XAT_Report_Stop stop;
	struct XAT_Report_Disp_Write_n disp_write;
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


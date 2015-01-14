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


/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "Descriptors.h"

/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */
static const USB_Descriptor_HIDReport_Datatype_t PROGMEM xat_report[] = {
#include "xat_desc.hid.h"
};

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
static const USB_Descriptor_Device_t PROGMEM device_descriptor = {
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(2,0,0),
	.Class                  = USB_CSCP_NoDeviceClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,

	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

	.VendorID               = 0x03EB,	// GenericHID VID/PID for now
	.ProductID              = 0x204F,
	.ReleaseNumber          = VERSION_BCD(0,0,0),

	.ManufacturerStrIndex   = STRING_ID_Manufacturer,
	.ProductStrIndex        = STRING_ID_Product,
	.SerialNumStrIndex      = NO_DESCRIPTOR,

	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
static const USB_Descriptor_Configuration_t PROGMEM configuration_descriptor = {
	.Config = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

		.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
		.TotalInterfaces        = 1,

		.ConfigurationNumber    = 1,
		.ConfigurationStrIndex  = NO_DESCRIPTOR,

		.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),

		.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
	},

	.HID_Interface = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

		.InterfaceNumber        = INTERFACE_ID_XAT_HID,
		.AlternateSetting       = 0x00,

		.TotalEndpoints         = 1,

		.Class                  = HID_CSCP_HIDClass,
		.SubClass               = HID_CSCP_NonBootSubclass,
		.Protocol               = HID_CSCP_NonBootProtocol,

		.InterfaceStrIndex      = NO_DESCRIPTOR
	},

	.HID_GenericHID = {
		.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

		.HIDSpec                = VERSION_BCD(1,1,1),
		.CountryCode            = 0x00,
		.TotalReportDescriptors = 1,
		.HIDReportType          = HID_DTYPE_Report,
		.HIDReportLength        = sizeof(xat_report)
	},

	.HID_ReportINEndpoint = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

		.EndpointAddress        = HID_IN_EPADDR,
		.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize           = HID_EPSIZE,
		.PollingIntervalMS      = 0x20
	},
};

const USB_Descriptor_String_t PROGMEM language_string = USB_STRING_DESCRIPTOR_ARRAY(LANGUAGE_ID_ENG);
const USB_Descriptor_String_t PROGMEM manufacturer_string = USB_STRING_DESCRIPTOR(L"X-AT project");
const USB_Descriptor_String_t PROGMEM product_string = USB_STRING_DESCRIPTOR(L"X-AT stepper controller");

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	switch (DescriptorType) {
	case DTYPE_Device:
		Address = &device_descriptor;
		Size    = sizeof(USB_Descriptor_Device_t);
		break;

	case DTYPE_Configuration:
		Address = &configuration_descriptor;
		Size    = sizeof(USB_Descriptor_Configuration_t);
		break;

	case DTYPE_String:
		switch (DescriptorNumber) {
		case STRING_ID_Language:
			Address = &language_string;
			Size    = pgm_read_byte(&language_string.Header.Size);
			break;

		case STRING_ID_Manufacturer:
			Address = &manufacturer_string;
			Size    = pgm_read_byte(&manufacturer_string.Header.Size);
			break;

		case STRING_ID_Product:
			Address = &product_string;
			Size    = pgm_read_byte(&product_string.Header.Size);
			break;
		}
		break;

	case HID_DTYPE_HID:
		Address = &configuration_descriptor.HID_GenericHID;
		Size    = sizeof(USB_HID_Descriptor_HID_t);
		break;

	case HID_DTYPE_Report:
		Address = &xat_report;
		Size    = sizeof(xat_report);
			break;
	}

	*DescriptorAddress = Address;
	return Size;
}


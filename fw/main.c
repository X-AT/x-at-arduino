/* @brief X-AT Arduino main
 * @file
 *
 * Based on LUFA GenericHID demo.
 */


#include "main.h"

static uint8_t prev_hid_report_buffer[64];
USB_ClassInfo_HID_Device_t xat_hid_interface = {
	.Config = {
		.InterfaceNumber              = INTERFACE_ID_XAT_HID,
		.ReportINEndpoint             = {
			.Address              = HID_IN_EPADDR,
			.Size                 = HID_EPSIZE,
			.Banks                = 1,
		},
		.PrevReportINBuffer           = prev_hid_report_buffer,
		.PrevReportINBufferSize       = sizeof(prev_hid_report_buffer),
	},
};


static void setup_hardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	LEDs_Init();
	USB_Init();
}

int main(void)
{
	setup_hardware();

	GlobalInterruptEnable();

	for (;;)
	{
		HID_Device_USBTask(&xat_hid_interface);
		USB_USBTask();
	}
}

void EVENT_USB_Device_Connect(void)
{
}

void EVENT_USB_Device_Disconnect(void)
{
}

void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&xat_hid_interface);

	USB_Device_EnableSOFEvents();
}

void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&xat_hid_interface);
}

void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&xat_hid_interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	*ReportSize = 0;
	return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
}


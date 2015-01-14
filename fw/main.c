/* @brief X-AT Arduino main
 * @file
 *
 * Based on LUFA GenericHID demo.
 */


#include "main.h"
#include "Descriptors.h"

static XAT_ReportBuffer_t prev_hid_report_buffer;
USB_ClassInfo_HID_Device_t xat_hid_interface = {
	.Config = {
		.InterfaceNumber              = INTERFACE_ID_XAT_HID,
		.ReportINEndpoint             = {
			.Address              = HID_IN_EPADDR,
			.Size                 = HID_EPSIZE,
			.Banks                = 1,
		},
		.PrevReportINBuffer           = prev_hid_report_buffer.data,
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
	ADC_Task_Init();
}

static uint16_t report_fill_info(XAT_ReportBuffer_t *data)
{
	/* XXX TODO */
	data->info.display_rows = 64;
	data->info.display_columns = 128;
	return sizeof(data->info);
}

static uint16_t report_fill_status(XAT_ReportBuffer_t *data)
{
	/* XXX TODO */
	data->status.flags = 0x5a;
	data->status.buttons = QTR_GetStatusButtons();
	data->status.azimuth_position = -100;
	data->status.elevation_position = 100;
	return sizeof(data->status);
}

static uint16_t report_fill_bat_voltage(XAT_ReportBuffer_t *data)
{
	data->bat_voltage.raw_adc = BAT_GetVoltageRaw();
	return sizeof(data->bat_voltage);
}

static uint16_t report_fill_stepper_settings(XAT_ReportBuffer_t *data)
{
	return sizeof(data->stepper_settings);
}

static uint16_t report_fill_qtr(XAT_ReportBuffer_t *data)
{
	data->qtr.azimuth_qtr_raw = QTR_GetAzValueRaw();
	data->qtr.elevation_qtr_raw = QTR_GetElValueRaw();
	return sizeof(data->qtr);
}

static void report_apply_stepper_settings(const XAT_ReportBuffer_t *data, uint16_t size)
{
	if (size != sizeof(data->stepper_settings))
		return;

}

static void report_apply_az_el(const XAT_ReportBuffer_t *data, uint16_t size)
{
	if (size != sizeof(data->az_el))
		return;

}

static void report_apply_qtr(const XAT_ReportBuffer_t *data, uint16_t size)
{
	if (size != sizeof(data->qtr))
		return;

	QTR_SetAzElLevel(data->qtr.azimuth_qtr_raw, data->qtr.elevation_qtr_raw);
}

int main(void)
{
	setup_hardware();

	LEDs_TurnOnLEDs(LEDS_LED1 | LEDS_LED2);
	GlobalInterruptEnable();

	for (;;)
	{
		HID_Device_USBTask(&xat_hid_interface);
		USB_USBTask();
		ADC_Task();
	}
}

void EVENT_USB_Device_Connect(void)
{
	LEDs_TurnOffLEDs(LEDS_LED2);
}

void EVENT_USB_Device_Disconnect(void)
{
	// XXX: leds inverted on PRO MICRO
	LEDs_TurnOnLEDs(LEDS_LED2);
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
	switch (*ReportID) {
	case REPORT_ID_F_INFO:
		*ReportSize = report_fill_info(ReportData);
		break;

	case REPORT_ID_G_STATUS:
		*ReportSize = report_fill_status(ReportData);
		break;

	case REPORT_ID_G_BAT_VOLTAGE:
		*ReportSize = report_fill_bat_voltage(ReportData);
		break;

	case REPORT_ID_F_STEPPER_SETTINGS:
		*ReportSize = report_fill_stepper_settings(ReportData);
		break;

	case REPORT_ID_F_QTR:
		*ReportSize = report_fill_qtr(ReportData);
		break;

	default:
		/* TODO signal error */
		*ReportSize = 0;
	}

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
	switch (ReportID) {
	case REPORT_ID_F_STEPPER_SETTINGS:
		report_apply_stepper_settings(ReportData, ReportSize);
		break;

	case REPORT_ID_S_AZ_EL:
		report_apply_az_el(ReportData, ReportSize);
		break;

	case REPORT_ID_F_QTR:
		report_apply_qtr(ReportData, ReportSize);
		break;

	default:
		/* TODO signal error */
		break;
	}
}


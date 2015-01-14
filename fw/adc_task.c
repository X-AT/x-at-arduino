
#include "main.h"
#include "LUFA/Drivers/Peripheral/ADC.h"

static uint16_t bat_voltage_raw;
static uint16_t az_qtr_value_raw;
static uint16_t el_qtr_value_raw;

#define QTR_DEFAULT_LEVEL	255
static uint16_t az_level = QTR_DEFAULT_LEVEL;
static uint16_t el_level = QTR_DEFAULT_LEVEL;

static enum {
	DO_VBAT,
	DO_EL_QTR,
	DO_AZ_QTR,
} task_state;


void ADC_Task_Init(void)
{
	ADC_Init(ADC_SINGLE_CONVERSION | ADC_PRESCALE_32);
	ADC_SetupChannel(7);		// A0-PF7 Vbat
	ADC_SetupChannel(6);		// A1-PF6 EL endstop
	ADC_SetupChannel(5);		// A2-PF5 AZ endstop

	task_state = DO_VBAT;
	ADC_StartReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | ADC_CHANNEL7);
}

/**
 * This task continiusly conv three ADC channels:
 * - Vbat
 * - QTR-1A on azimuth endstop
 * - QTR-1A on elevation endstop
 */
void ADC_Task(void)
{
	if (!ADC_IsReadingComplete())
		return;

	switch (task_state) {
	case DO_VBAT:
		bat_voltage_raw = ADC_GetResult();
		task_state = DO_EL_QTR;
		ADC_StartReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | ADC_CHANNEL6);
		break;

	case DO_EL_QTR:
		el_qtr_value_raw = ADC_GetResult();
		task_state = DO_AZ_QTR;
		ADC_StartReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | ADC_CHANNEL5);
		break;

	case DO_AZ_QTR:
		az_qtr_value_raw = ADC_GetResult();
		task_state = DO_VBAT;
		ADC_StartReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | ADC_CHANNEL7);
		break;
	};
}

uint16_t BAT_GetVoltageRaw(void)
{
	return bat_voltage_raw;
}

uint16_t QTR_GetAzValueRaw(void)
{
	return az_qtr_value_raw;
}

uint16_t QTR_GetElValueRaw(void)
{
	return el_qtr_value_raw;
}

/**
 * Return bitmask of endstop values.
 * Threshold level ar set by @a QTR_SetAzElLevel()
 */
uint8_t QTR_GetStatusButtons(void)
{
	uint8_t mask = 0;

	if (az_qtr_value_raw < az_level)
		mask |= STATUS_BUTTON1;

	if (el_qtr_value_raw < el_level)
		mask |= STATUS_BUTTON2;

	return mask;
}

void QTR_SetAzElLevel(uint16_t az, uint16_t el)
{
	az_level = az;
	el_level = el;
}

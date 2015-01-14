
#include "main.h"
#include "LUFA/Drivers/Peripheral/ADC.h"

static uint16_t bat_voltage_raw;


void BAT_Init(void)
{
	ADC_Init(ADC_FREE_RUNNING | ADC_PRESCALE_32);
	ADC_SetupChannel(7);		// A0-PF7
	ADC_StartReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | ADC_CHANNEL7);
}

void BAT_Task(void)
{
	if (!ADC_IsReadingComplete())
		return;

	bat_voltage_raw = ADC_GetResult();
}

uint16_t BAT_GetVoltageRaw(void)
{
	return bat_voltage_raw;
}

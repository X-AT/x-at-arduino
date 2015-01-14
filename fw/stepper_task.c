
#include "main.h"
#include "accelstepper.h"

#define EL_STEP		PB5
#define EL_DIR		PB4
#define AZ_STEP		PD7
#define AZ_DIR		PE6
#define step_pulse_delay()	_delay_us(10)

static AccelStepper_t azimuth_stepper,
		      elevation_stepper;

static void azimuth_step(AccelStepper_t *self)
{
	cbi(PORTD, AZ_STEP);

	if (self->direction == DIRECTION_CW)
		sbi(PORTE, AZ_DIR);
	else
		cbi(PORTE, AZ_DIR);

	sbi(PORTD, AZ_STEP);
	step_pulse_delay();
	cbi(PORTD, AZ_STEP);
}

static void elevation_step(AccelStepper_t *self)
{
	cbi(PORTB, EL_STEP);

	if (self->direction == DIRECTION_CW)
		sbi(PORTB, EL_DIR);
	else
		cbi(PORTB, EL_DIR);

	sbi(PORTB, EL_STEP);
	step_pulse_delay();
	cbi(PORTB, EL_STEP);
}

void Stepper_Task_Init(void)
{
	// GPIO setup
	cbi(PORTB, EL_STEP);
	cbi(PORTB, EL_DIR);
	sbi(DDRB, EL_STEP);
	sbi(DDRB, EL_DIR);

	cbi(PORTD, AZ_STEP);
	cbi(PORTE, AZ_DIR);
	sbi(DDRD, AZ_STEP);
	sbi(DDRE, AZ_DIR);

	AS_ObjectInit(&azimuth_stepper, azimuth_step);
	AS_ObjectInit(&elevation_stepper, elevation_step);
}

void Stepper_Task(void)
{
	AS_Run(&azimuth_stepper);
	AS_Run(&elevation_stepper);
}

int32_t Stepper_GetAzPosition(void)
{
	return AS_CurrentPosition(&azimuth_stepper);
}

int32_t Stepper_GetElPosition(void)
{
	return AS_CurrentPosition(&elevation_stepper);
}

uint8_t Stepper_GetFlags(void)
{
	uint8_t flags = 0;

	if (AS_DistanceToGo(&azimuth_stepper) > 0)
		flags |= FLAGS_AZ_IN_MOTION;

	if (AS_DistanceToGo(&elevation_stepper) > 0)
		flags |= FLAGS_EL_IN_MOTION;

	return flags;
}

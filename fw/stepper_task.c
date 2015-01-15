
#include "main.h"
#include "accelstepper.h"

#define EL_STEP		PB5
#define EL_DIR		PB4
#define AZ_STEP		PD7
#define AZ_DIR		PE6
#define step_pulse_delay()	_delay_us(1)

#define INIT_ACCEL	50
#define INIT_MSPEED	200

static AccelStepper_t azimuth_stepper,
		      elevation_stepper;

static void azimuth_step(AccelStepper_t *self)
{
	cbi(PORTD, AZ_STEP);

	if (self->direction == DIRECTION_CCW)
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

	if (self->direction == DIRECTION_CCW)
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

	AS_SetAcceleration(&azimuth_stepper, INIT_ACCEL);
	AS_SetAcceleration(&elevation_stepper, INIT_ACCEL);
	AS_SetMaxSpeed(&azimuth_stepper, INIT_MSPEED);
	AS_SetMaxSpeed(&elevation_stepper, INIT_MSPEED);
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

void Stepper_GetSettings(struct XAT_Report_Stepper_Settings *settings)
{
	// Should i add accesor wrapper?
	settings->azimuth_acceleration = azimuth_stepper.acceleration;
	settings->elevation_acceleration = elevation_stepper.acceleration;
	settings->azimuth_max_speed = azimuth_stepper.max_speed;
	settings->elevation_max_speed = elevation_stepper.max_speed;
}

void Stepper_SetSettings(const struct XAT_Report_Stepper_Settings *settings)
{
	AS_SetAcceleration(&azimuth_stepper, settings->azimuth_acceleration);
	AS_SetMaxSpeed(&azimuth_stepper, settings->azimuth_max_speed);
	AS_SetAcceleration(&elevation_stepper, settings->elevation_acceleration);
	AS_SetMaxSpeed(&elevation_stepper, settings->elevation_max_speed);
}

void Stepper_SetAzEl(const struct XAT_Report_Az_El *az_el)
{
	AS_MoveTo(&azimuth_stepper, az_el->azimuth_position);
	AS_MoveTo(&elevation_stepper, az_el->elevation_position);
}

void Stepper_SetCurPosition(const struct XAT_Report_Cur_Position *cur_position)
{
	AS_SetCurrentPosition(&azimuth_stepper, cur_position->azimuth_position);
	AS_SetCurrentPosition(&elevation_stepper, cur_position->elevation_position);
}

void Stepper_Stop(bool az, bool el)
{
	if (az)
		AS_Stop(&azimuth_stepper);

	if (el)
		AS_Stop(&elevation_stepper);
}

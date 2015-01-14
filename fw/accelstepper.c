/**
 * @brief AccelStepper in C
 *
 * This is a port from Arduino C++ to C.
 * Ported only minimal subset of original library.
 */

#include "accelstepper.h"
#include <math.h>
#include <string.h>


static void _AS_ComputeNewSpeed(AccelStepper_t *self)
{
	// + -> ve clockwise from current position
	int32_t distance = AS_DistanceToGo(self);

	// Equation 16
	int32_t steps_to_stop = (int32_t)((self->speed * self->speed) / (2.0 * self->acceleration));

	if (distance == 0 && steps_to_stop <= 1) {
		// We are at target and its time to stop
		self->step_interval_us = 0;
		self->speed = 0.0;
		self->n = 0;
		return;
	}

	if (distance > 0) {
		// We are anticlockwise from the target
		// Need to go clockwise from here, maybe decelerate now
		if (self->n > 0) {
			// Currently accelerating, need to decel now? Or maybe going the wrong way?
			if ((steps_to_stop >= distance) || self->direction == DIRECTION_CCW)
				self->n = -steps_to_stop;	// Start deceleration
		}
		else if (self->n < 0) {
			// Currently decelerating, need to accel again?
			if ((steps_to_stop < distance) && self->direction == DIRECTION_CW)
				self->n = -self->n;		// Start accceleration
		}
	}
	else if (distance < 0) {
		// We are clockwise from the target
		// Need to go anticlockwise from here, maybe decelerate
		if (self->n > 0) {
			// Currently accelerating, need to decel now? Or maybe going the wrong way?
			if ((steps_to_stop >= -distance) || self->direction == DIRECTION_CW)
				self->n = -steps_to_stop;	// Start deceleration
		}
		else if (self->n < 0) {
			// Currently decelerating, need to accel again?
			if ((steps_to_stop < -distance) && self->direction == DIRECTION_CCW)
				self->n = -self->n;		// Start accceleration
		}
	}

    // Need to accelerate or decelerate
    if (self->n == 0) {
	// First step from stopped
	self->cn = self->c0;
	self->direction = (distance > 0) ? DIRECTION_CW : DIRECTION_CCW;
    }
    else {
	// Subsequent step. Works for accel (n is +_ve) and decel (n is -ve).
	// Equation 13
	self->cn = self->cn - ((2.0 * self->cn) / ((4.0 * self->n) + 1));
	self->cn = fmaxf(self->cn, self->cmin);
    }

    self->n++;
    self->step_interval_us = self->cn;
    self->speed = 1e6 / self->cn;

    if (self->direction == DIRECTION_CCW)
	self->speed = -self->speed;
}

/**
 * Object constructor
 */
void AS_ObjectInit(AccelStepper_t *self, AS_step_cb_t step_cb)
{
	memset(self, 0, sizeof(*self));
	self->step_cb = step_cb;
	self->max_speed = 1.0;
	self->acceleration = 0.0;
	//self->sqrt_twoa = 1.0;
	self->min_pulse_width_us = 1;
	self->cmin = 1.0;
	self->direction = DIRECTION_CCW;

	AS_SetAcceleration(self, 1);
}

void AS_MoveTo(AccelStepper_t *self, int32_t abs)
{
	if (abs == self->target_pos)
		return;

	self->target_pos = abs;
	_AS_ComputeNewSpeed(self);
}

bool AS_Run(AccelStepper_t *self)
{
	if (AS_RunSpeed(self))
		_AS_ComputeNewSpeed(self);
	return self->speed != 0.0 || AS_DistanceToGo(self) != 0;
}

bool AS_RunSpeed(AccelStepper_t *self)
{
	if (!self->step_interval_us)
		return false;

	uint32_t time = micros(); // XXX: TODO

	// Gymnastics to detect wrapping of either the nextStepTime and/or the current time
	unsigned long next_step_time = self->last_step_time_us + self->step_interval_us;
	if (   ((next_step_time >= self->last_step_time_us) && ((time >= next_step_time) || (time < self->last_step_time_us)))
	    || ((next_step_time <  self->last_step_time_us) && ((time >= next_step_time) && (time < self->last_step_time_us)))
	    ) {

		self->current_pos += (self->direction == DIRECTION_CW)? 1 : -1;
		self->step_cb(self);

		self->last_step_time_us = time;
		return true;
	}

	return false;
}

void AS_SetMaxSpeed(AccelStepper_t *self, float speed)
{
	if (speed == self->max_speed)
		return;

	self->max_speed = speed;
	self->cmin = 1e6 / speed;
	if (self->n > 0) {
		// Equation 16
		self->n = (int32_t)((self->speed * self->speed) / (2 * self->acceleration));
		_AS_ComputeNewSpeed(self);
	};
}

void AS_SetAcceleration(AccelStepper_t *self, float acceleration)
{
	if (acceleration == 0.0 || acceleration == self->acceleration)
		return;

	// Equation 17
	self->n = self->n * (self->acceleration / acceleration);
	// Equation 7 (new variant)
	self->c0 = sqrt(1.0 / acceleration) * 1e6;
	self->acceleration = acceleration;
	_AS_ComputeNewSpeed(self);
}

void AS_SetCurrentPosition(AccelStepper_t *self, int32_t position)
{
	self->target_pos = self->current_pos = position;
	self->n = 0;
	self->step_interval_us = 0;
}

void AS_Stop(AccelStepper_t *self)
{
	if (self->speed == 0.0)
		return;

	// Equation 16 (+integer rounding)
	int32_t steps_to_stop = (long)((self->speed * self->speed) / (2.0 * self->acceleration)) + 1;
	AS_Move(self, (self->speed > 0)? steps_to_stop : -steps_to_stop);
}

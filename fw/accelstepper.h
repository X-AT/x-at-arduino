/**
 * @brief AccelStepper in C
 *
 * This is a port from Arduino C++ to C.
 * Ported only minimal subset of original library.
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef _ACCELSTEPPER_H_
#define _ACCELSTEPPER_H_

enum AS_Direction {
	DIRECTION_CCW = 0,	//!< Counter-Clocwise
	DIRECTION_CW  = 1,	//!< Clockwise
};

struct AccelStepper;
typedef void (*AS_step_cb_t)(struct AccelStepper *self);

/**
 * AccelStepper Object (class)
 */
typedef struct AccelStepper {
	AS_step_cb_t step_cb;
	int32_t current_pos;		//!< Current absolute position [Steps]
	int32_t target_pos;		//!< Target absolute position [Steps]
	float speed;			//!< Current motor speed [Steps/Second]
	float max_speed;		//!< Maximum permitted speed [Steps/Second]
	float acceleration;		//!< Accleration [Step/Second**2]
	uint32_t step_interval_us;	//!< Current interval between steps
	uint32_t last_step_time_us;	//!< Last step time
	//uint32_t min_pulse_width_us;	//!< Minimum allowed pulse width
	int32_t n;			//!< step counter for speed calc
	float c0;			//!< Initial step size in [us]
	float cn;			//!< Last step size [us]
	float cmin;			//!< Minimum step size by max_speed
	enum AS_Direction direction;	//!< Current direction
} AccelStepper_t;


/* Object Functions */
void AS_ObjectInit(AccelStepper_t *self, AS_step_cb_t step_cb);
static inline void AS_Move(AccelStepper_t *self, int32_t rel);
void AS_MoveTo(AccelStepper_t *self, int32_t abs);
bool AS_Run(AccelStepper_t *self);
bool AS_RunSpeed(AccelStepper_t *self);
void AS_SetMaxSpeed(AccelStepper_t *self, float speed);
void AS_SetAcceleration(AccelStepper_t *self, float acceleration);
static inline int32_t AS_DistanceToGo(AccelStepper_t *self);
static inline int32_t AS_TargetPosition(AccelStepper_t *self);
static inline int32_t AS_CurrentPosition(AccelStepper_t *self);
void AS_SetCurrentPosition(AccelStepper_t *self, int32_t position);
void AS_Stop(AccelStepper_t *self);


/* Inlined functions */
static inline void AS_Move(AccelStepper_t *self, int32_t rel)
{
	AS_MoveTo(self, self->current_pos + rel);
}

static inline int32_t AS_DistanceToGo(AccelStepper_t *self)
{
	return self->target_pos - self->current_pos;
}

static inline int32_t AS_TargetPosition(AccelStepper_t *self)
{
	return self->target_pos;
}

static inline int32_t AS_CurrentPosition(AccelStepper_t *self)
{
	return self->current_pos;
}

#endif /* _ACCELSTEPPER_H_ */

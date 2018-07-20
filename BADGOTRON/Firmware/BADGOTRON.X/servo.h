/* 
 * File:   servo.h
 * Author: bocal
 *
 * Created on May 24, 2018, 3:01 PM
 */

#ifndef SERVO_H
#define	SERVO_H

#define PIN_SERVO_MODE TRISDbits.TRISD0
#define PIN_SERVO_WRITE LATDbits.LATD0

#define PWM_MIN_CYCLE 1500
#define PWM_MAX_PERCENT_CYCLE 44

#endif	/* SERVO_H */


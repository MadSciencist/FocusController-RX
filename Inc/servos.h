#ifndef SERVOS_H_
#define SERVOS_H_

#include "stm32f0xx.h"
#include "nrf24l01.h"
#include "tim.h"
#include "servos_abstract.h"
#include <string.h> // memcpy

#define SERVO_US_MIN 525
#define SERVO_US_MAX 2475
#define GIMBAL_US_MIN 900
#define GIMBAL_US_MAX 2100

#define NUM_OF_GIMBAL_OUTPUTS 4
#define NUM_OF_SERVOS 3

uint8_t startServoPWM();
uint8_t startGimbalPWM();

void setGimbalOutputs(uint8_t gimbalOutput, uint8_t raw);

void setServoMicros(uint8_t servo, uint16_t value);
void setGimbalMicros(uint8_t gimbalOutput, uint16_t value);

uint16_t map_u16(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);
uint16_t constrain_u16(uint16_t x, uint16_t min, uint16_t max);

#endif
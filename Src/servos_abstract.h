#ifndef SERVOS_ABSTRACT_H_
#define SERVOS_ABSTRACT_H_

#include "stm32f0xx.h"
#include "nrf24l01.h"
#include "tim.h"
#include "servos.h"
#include "stm32f0xx_it.h"
#include "wireless_receive.h"

typedef struct{
  uint16_t setPos;
  uint16_t previousPos;
  volatile uint8_t setSpeed;
} servos_t;


void s_init(servos_t* servo);
void servoWriteToServoObject(uint8_t servoNum, servos_t* servo, uint16_t position, uint8_t speed);

#endif
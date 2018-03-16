#include "servos_abstract.h"

extern servos_t s[NUM_OF_SERVOS];
user_parameters_t user;

uint16_t servo_ticks[] = {1500, 1500, 1500}; //dac na center po init

void s_init(servos_t* servo)
{
  servo->setPos = 1500;
  servo->previousPos = 1500; //is this needed?
  servo->setSpeed = 0;
}

void servoWriteToServoObject(uint8_t servoNum, servos_t* servo, uint16_t position, uint8_t speed)
{
  uint16_t tmp_pos = constrain_u16(position, user.limitLeft[servoNum] , user.limitRight[servoNum]);
  
  servo->setPos =  tmp_pos;
  servo->setSpeed = speed; 
  servo->previousPos = servo->setPos;
}

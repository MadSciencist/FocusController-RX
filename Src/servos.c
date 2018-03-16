#include "servos.h"

extern servos_t s;

void setGimbalOutputs(uint8_t gimbalOutput, uint8_t raw)
{
  setGimbalMicros(gimbalOutput, map_u16(raw, 0, 255, GIMBAL_US_MIN, GIMBAL_US_MAX));
}

uint8_t startServoPWM()
{
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  
  return 1;
}

uint8_t startGimbalPWM()
{
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
  
  return 1;
}

void setServoMicros(uint8_t servo, uint16_t value)
{
  switch(servo)
  {
  case 0:
    if(value >= SERVO_US_MIN && value <= SERVO_US_MAX)
      TIM1->CCR1 = value;
    break;
    
  case 1:
    if(value >= SERVO_US_MIN && value <= SERVO_US_MAX)
      TIM1->CCR2 = value;
    break;
    
  case 2:
    if(value >= SERVO_US_MIN && value <= SERVO_US_MAX)
      TIM1->CCR3 = value;
    break;
    
  default:
    break;   
  }
}

void setGimbalMicros(uint8_t gimbalOutput, uint16_t value)
{ 
  switch(gimbalOutput)
  {
  case 0:
    if(value >= GIMBAL_US_MIN && value <= GIMBAL_US_MAX)
      TIM3->CCR1 = value;
    break;
    
  case 1:
    if(value >= GIMBAL_US_MIN && value <= GIMBAL_US_MAX)
      TIM3->CCR2 = value;
    break;
    
  case 2:
    if(value >= GIMBAL_US_MIN && value <= GIMBAL_US_MAX)
      TIM3->CCR3 = value;
    
  case 3:
    if(value >= GIMBAL_US_MIN && value <= GIMBAL_US_MAX)
      TIM3->CCR4 = value;
    break;
    
  default:
    break;
  }
}

uint16_t map_u16(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
{
  uint16_t tmp;
  if((x - in_min) < 0)
    tmp = 0;
  else tmp = x - in_min;
  return (tmp * (out_max - out_min) / (in_max - in_min) + out_min);
}

uint16_t constrain_u16(uint16_t x, uint16_t min, uint16_t max)
{
  if(x>max) return max;
  if(x<min) return min;
  return x;
}
#include "wireless_receive.h"

extern uint16_t ADC_RAW;
extern user_parameters_t user;
extern uint8_t receivedNewCalibration;

void generateFeedbackMsg(uint8_t* _toSend, uint8_t* buff, uint8_t len)
{
  _toSend[0] = '<';
  _toSend[1] = 1;
  
  for(uint8_t i = 0; i < len; i++)
  {
    _toSend[i+2] = buff[i];
  }
  
  _toSend[16] = '>';
}

void generateReceivedOkMsg(uint8_t* _toSend)
{
  _toSend[0] = '<';
  _toSend[1] = 2;
  _toSend[2] = 'o';
  _toSend[3] = 'k';
  _toSend[16] = '>';
}

void parseIncomingData(uint8_t* data, uint16_t* pos, uint8_t* speed, uint8_t* joy, user_parameters_t* usr)
{
  //static uint8_t cntr = 0;
  uint8_t ID = data[2];
  
  if(data[0] == '<' && data[16] == '>')
  {
    switch(ID)
    {
    case 1: //new data to write to outputs
      {
        //cntr = data[1]; //message counter from 0 to 255
        
        pos[0] = (data[4] << 8) | data[3];
        pos[1] = (data[6] << 8) | data[5];
        pos[2] = (data[8] << 8) | data[7];
        
        speed[0] = data[9];
        speed[1] = data[10];
        speed[2] = data[11]; 
        
        joy[0] = data[12];
        joy[1] = data[13];
        joy[2] = data[14];
        
        //uint8_t bitBooleans = data[15];
        
        break;
      }
      
    case 2:
      usr->limitLeft[0] = (data[4] << 8) | data[3];
      usr->limitLeft[1] = (data[6] << 8) | data[5];
      usr->limitLeft[2] = (data[8] << 8) | data[7];
      
      usr->limitRight[0] = (data[10] << 8) | data[9];
      usr->limitRight[1] = (data[12] << 8) | data[11];
      usr->limitRight[2] = (data[14] << 8) | data[13];
      
      WriteToFlash(&user, sizeof(user), SECTOR31_FLASH_BEGINING);
      
      receivedNewCalibration = 1; //flag used to respond with OK
      break;
      
    default:
      break;
    }
  }
}

void userParmetersInit(user_parameters_t* usr)
{
  for(uint8_t i = 0; i < 3; i++)
  {
    usr->limitLeft[i] = SERVO_US_MIN;
    usr->limitRight[i] = SERVO_US_MAX;
  }
}

void getCapacityInAscii(char* capacity)
{
  float v = get_voltage(ADC_RAW);
  float c = GetCapacity(v);
  sprintf((char *)capacity, "%3d%", (int)c);
}

float get_voltage(uint16_t bit_voltage) //adc0
{
  return ((bit_voltage * (V_REFERENCE / CONV_RESOLUTION)) * V_CALIB_RATIO);
}

float GetCapacity(float _v)
{
  float cap = (_v - BATTERY_EMPTY) * (100.0) / (BATTERY_FULL - BATTERY_EMPTY);
  if(cap > 100.0f)
    return 100.0f;
  else if(cap < 0.0f)
    return 0;
  else return cap;
}
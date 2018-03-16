#ifndef WIRELESS_RECEIVE_H_
#define WIRELESS_RECEIVE_H_

#include "stm32f0xx.h"
#include "nrf24l01.h"
#include <string.h> // memcpy
#include "servos.h"
#include "eeprom_emulator.h"

#define V_CALIB_RATIO 5.9023f
#define V_REFERENCE  3.3f
#define CONV_RESOLUTION 4095.0f
#define BATTERY_EMPTY 3.185f * 2.0f //* 2 cells
#define BATTERY_FULL  4.185f * 2.0f

typedef struct{
  uint16_t limitLeft[3];
  uint16_t limitRight[3];
} user_parameters_t;

void parseIncomingData(uint8_t* data, uint16_t* pos, uint8_t* speed, uint8_t* joy, user_parameters_t* usr);
void generateFeedbackMsg(uint8_t* _toSend, uint8_t* buff, uint8_t len);
void generateReceivedOkMsg(uint8_t* _toSend);
void userParmetersInit(user_parameters_t* usr);
void getCapacityInAscii(char* capacity);
float GetCapacity(float _v);
float get_voltage(uint16_t bit_voltage);

#endif
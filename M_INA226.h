#ifndef __M_INA_H__
#define __M_INA_H__

/*
Library based on Nich1con edition

INA226 MAX INPUTS:
U=36V
Ush=0.8V

HOW TO USE:
-change required settings in .h file
-INA_MAX_CURRENT - max current for your shunt (0.01R, 0.08mV max, 0.08/0.01=max current)
-INA_R_SHUNT - your shunt resistance
-INA_USE_RECALIBRATION in Nich1con library he push calibration value to INA register
at every current, power request. I left this feature
-set alert limits (if you need it), INA alert pin toggles if value is bigger than a threshold
-set conversion time, averaging (optimal values for display refresh rate are (332us, x64)
-"tiny" functions are required if you don't want to use float when flushing out converted data
-don't forget to calibrate INA current by means of a calibration value
*/



///////////////////////////////////////////////////////
#include "main.h"
#include <stdbool.h>
///////////////////////////////////////////////////////

//Address
///////////////////////////////////////////////////////
#define INA_I2C_ADDRESS 0x40
#define INA_HAL_I2C_ADDRESS INA_I2C_ADDRESS<<1
///////////////////////////////////////////////////////

//Settings
///////////////////////////////////////////////////////
#define INA_MAX_CURRENT 8
#define INA_R_SHUNT 0.01F
///////////////////////////////////////////////////////

//define if you want to use recalibration in 
//current and power reading functions
///////////////////////////////////////////////////////
//#define INA_USE_RECALIBRATION
///////////////////////////////////////////////////////

//Delay
///////////////////////////////////////////////////////
#define INA_DELAY(ms) HAL_Delay(ms)
///////////////////////////////////////////////////////

//I2C HAL
///////////////////////////////////////////////////////
#define INA_I2C_HAL_TIMEOUT 0x01
///////////////////////////////////////////////////////

//HAL i2c handler
///////////////////////////////////////////////////////
extern I2C_HandleTypeDef hi2c1;
///////////////////////////////////////////////////////

//Functions
///////////////////////////////////////////////////////
#define INA_I2C_TX(buf,buf_size) \
	HAL_I2C_Master_Transmit(&hi2c1,INA_HAL_I2C_ADDRESS,buf,buf_size,INA_I2C_HAL_TIMEOUT)
#define INA_I2C_RX(buf,buf_size) \
	HAL_I2C_Master_Receive(&hi2c1,INA_HAL_I2C_ADDRESS,buf,buf_size,INA_I2C_HAL_TIMEOUT);
///////////////////////////////////////////////////////

//Grade of current/wattage per 1 bit in int16_t
///////////////////////////////////////////////////////
#define INA_CURRENT_LSB INA_MAX_CURRENT/32768.0F //current LSB
#define INA_POWER_LSB INA_CURRENT_LSB * 25.0F //wattage LSB
///////////////////////////////////////////////////////

//Choose alert limits
///////////////////////////////////////////////////////
//#define INA_ALERT_SHUNT_V
//#define INA_ALERT_BUS_V 30U
///////////////////////////////////////////////////////

//Choose conversion time for BUS VOLTAGE (measuring time)
///////////////////////////////////////////////////////
//#define INA_CONV_BUS_V 0b000 //140 us
//#define INA_CONV_BUS_V 0b001 //204 us
#define INA_CONV_BUS_V 0b010 //332 us
//#define INA_CONV_BUS_V 0b011 //588 us
//#define INA_CONV_BUS_V 0b100 //1100 us
//#define INA_CONV_BUS_V 0b101 //2116 us
//#define INA_CONV_BUS_V 0b110 //4156 us
//#define INA_CONV_BUS_V 0b111 //8244 us
///////////////////////////////////////////////////////

//Choose conversion time for SHUNT VOLTAGE (measuring time)
///////////////////////////////////////////////////////
//#define INA_CONV_SHUNT_V 0b000 //140 us
//#define INA_CONV_SHUNT_V 0b001 //204 us
#define INA_CONV_SHUNT_V 0b010 //332 us
//#define INA_CONV_SHUNT_V 0b011 //588 us
//#define INA_CONV_SHUNT_V 0b100 //1100 us
//#define INA_CONV_SHUNT_V 0b101 //2116 us
//#define INA_CONV_SHUNT_V 0b110 //4156 us
//#define INA_CONV_SHUNT_V 0b111 //8244 us
///////////////////////////////////////////////////////

//Choose average grade (increases conversion time)
///////////////////////////////////////////////////////
//#define INA_AVG 0b000 //X1
//#define INA_AVG 0b001 //X4
//#define INA_AVG 0b010 //X16
#define INA_AVG 0b011 //X64
//#define INA_AVG 0b100 //X128
//#define INA_AVG 0b101 //X256
//#define INA_AVG 0b110 //X512
//#define INA_AVG 0b111 //X1024
///////////////////////////////////////////////////////

//Registers
///////////////////////////////////////////////////////
#define INA_CFG_REG_ADDR 0x00
#define INA_SHUNT_REG_ADDR 0x01
#define INA_VBUS_REG_ADDR 0x02
#define INA_POWER_REG_ADDR 0x03
#define INA_CUR_REG_ADDR 0x04
#define INA_CAL_REG_ADDR 0x05
#define INA_MASK_ENABLE_REG_ADDR 0x06
#define INA_ALERT_LIMIT_REG_ADDR 0x07
#define INA_ID_REG_ADDR 0xFE
///////////////////////////////////////////////////////












//Functions prototypes
///////////////////////////////////////////////////////
void INA_Init(void);

uint16_t INA_GetID(void);
void INA_SleepMode(uint8_t state);
void INA_SetCalVal(uint16_t cal);
uint16_t INA_GetCalVal(void);
void INA_ChangeCalVal(int16_t adj);
void INA_SetAver(uint8_t avg);
void INA_SetSampleTime(uint8_t ch, uint8_t samp_t);

float INA_GetBusVoltage(void);
float INA_GetCurrent(void);
float INA_GetPower(void);
float INA_GetShuntVoltage(void);

uint16_t INA_GetBusVoltageTiny(void);
uint16_t INA_GetCurrentTiny(void);
uint32_t INA_GetShuntVoltageTiny(void);
uint16_t INA_GetPowerTiny(void);
///////////////////////////////////////////////////////

#endif

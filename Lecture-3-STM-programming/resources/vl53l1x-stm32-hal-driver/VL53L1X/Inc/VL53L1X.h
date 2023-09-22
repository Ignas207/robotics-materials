#ifndef VL53L1X_H_
#define VL53L1X_H_

#include "i2c.h"
#include "gpio.h"

typedef struct vl53l1x {
	// I2C information
	I2C_HandleTypeDef* hi2c;
	uint8_t address;

	// XSHUT pin
	GPIO_TypeDef* xshut_port;
	uint16_t xshut_pin;
} VL53L1X;

void TOF_BootMultipleSensors(VL53L1X** const sensors, uint8_t count);

void TOF_InitStruct(VL53L1X* const sensor, I2C_HandleTypeDef* hi2c, uint8_t address, GPIO_TypeDef* xshut_port, uint16_t xshut_pin);
void TOF_BootSensor(VL53L1X* const sensor);

void TOF_TurnOn(VL53L1X* const sensor);
void TOF_TurnOff(VL53L1X* const sensor);

void TOF_StartRanging(VL53L1X* const sensor);
void TOF_StopRanging(VL53L1X* const sensor);

uint16_t TOF_GetDistance(VL53L1X* const sensor);

#endif // VL53L1X_H_

# VL53L1X Wrapper API
A wrapper API for the VL53L1X sensor ST drivers, written in C.

## Why?
The default API provided by ST for the VL53L1X is very cumbersome when dealing with multiple sensors on the same I2C peripheral. In addition, it provides no way to control the shutdown and interrupt pins.

## Goal
The goal of this API is ease of use, at the cost of features, while still keeping as much portability as possible.

This wrapper API is designed to sit on top of the STM32 HAL driver. Managing multiple sensors is simplified by a C structure, which specifies the communication peripherals and IO pins.

A lot of the advanced features, while nice to have, are not needed for basic usage, which is why the wrapper API doesn't currently implement them.

## Usage
For a more in-depth example, look at the provided CubeIDE example project.

### Setting up for CubeIDE
1. Copy the VL53L1X folder into the CubeIDE project folder.
2. Add an include path to the VL53L1X and VL53L1X/Inc folders.
	This can be done by right-clicking the folders and clicking on "Add/remove include path..."
3. Sometimes, CubeIDE excludes copy-pasted files from the project. Right click on the VL53L1X folder, go to Properties -> "C/C++ Build" and untick "Exclude resource from build".

Now you should be able to include the main header file inside your project.

### Wrapper API functions
##### TOF_InitStruct()
This function is used to give initial values to the VL53L1X structure. That includes the I2C peripheral used, I2C address and the port and pin of XSHUT pin. This function doesn't actually communicate with the sensor and just configures values store in the MCU.

##### TOF_BootSensor()
This function confiugres the target sensor. The configuration is left as default, the only thing actually changed is the I2C address, which by default is 0x52. 
In order to use this function, all the other unconfigured sensors must be turned off. Otherwise there will be a conflict on the I2C lines, with multiple sensors responding to the same address.

##### TOF_GetDistance()
This function gets the most recent measurement from the sensor and returns it. The return value is an unsigned 16-bit integer, which shows the distance in millimeters.

##### Other functions
Other functions are for internal API usage only and are not covered in this README. Additinal information can be gotten from the source code, which includes

### Using code for a single sensor
Let's look at an example of setting up a single sensor. All the API functions begin with TOF (which stands for Time of Flight).

```c
#include "VL53L1X.h"
VL53L1X sensor1;

int main(void) {
// MCU peripheral setup

// Setup
TOF_InitStruct(&sensor1, &hi2c1, 0x32, XSHUT_GPIO_Port, XSHUT_GPIO_Pin);
TOF_BootSensor(&sensor1);

// Getting a measurement
uint16_t distance = TOF_GetDistance(&sensor1);
printf("%d\n\r", distance);
}
```

### Using code for multiple sensors
As mentioned before, the default ST driver makes it really annoying to setup multiple sensors. The default address of the sensor is 0x52, which is stored in volatile memory. Because of this, when having multiple sensors on a single I2C peripheral, communication is impossible. This is solved by using the XSHUT pins, to disable the sensors and configure them one by one. 

However, as mentioned before, the ST driver doesn't provide any functions to simplify this process and your main() function will include dozens of lines of setup code
for turning off every sensor and initializing them one by one. To make this process look more elegant in the main code, there is a function to initialize any amount of sensors at once.

```c
VL53L1X sensor1;
VL53L1X sensor2;
VL53L1X sensor3;

// Booting all the sensors
TOF_InitStruct(&sensor1, &hi2c1, 0x32, XSHUT1_GPIO_Port, XSHUT1_Pin);
TOF_InitStruct(&sensor2, &hi2c1, 0x34, XSHUT2_GPIO_Port, XSHUT2_Pin);
TOF_InitStruct(&sensor3, &hi2c1, 0x36, XSHUT3_GPIO_Port, XSHUT3_Pin);

VL53L1X* sensors[] = {&sensor1, &sensor2, &sensor3};
TOF_BootMultipleSensors(sensors, 3); // Array of sensors and how many sensors it contains

// Getting measurements
uint16_t distance1 = TOF_GetDistance(&sensor1);
uint16_t distance2 = TOF_GetDistance(&sensor2);
uint16_t distance3 = TOF_GetDistance(&sensor3);
```

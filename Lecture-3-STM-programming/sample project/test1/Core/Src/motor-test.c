#include "motor-test.h"

void WriteMotor(uint8_t motorDirection, uint8_t motorSpeed)
{

    uint32_t prevSpeed = TIM1->CCR1;
    HAL_GPIO_WritePin(MOTOR_DIRECTION_GPIO_Port, MOTOR_DIRECTION_Pin, motorDirection);
    HAL_Delay(1);

    if(prevSpeed < motorSpeed)
    {
        for (size_t i = prevSpeed; i < motorSpeed; i++)
        {
            TIM1->CCR1 = i;
            HAL_Delay(1);
        }

    }
    


    return;
}
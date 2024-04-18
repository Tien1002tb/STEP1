#include "stm32f10x.h"

#define MOTOR_PIN1 GPIO_Pin_12
#define MOTOR_PIN2 GPIO_Pin_13
#define MOTOR_PIN3 GPIO_Pin_14
#define MOTOR_PIN4 GPIO_Pin_15
#define MOTOR_PORT GPIOB
 GPIO_InitTypeDef GPIO_InitStructure;
void delay_ms(uint32_t ms);
void stepMotor(uint8_t step);

int main(void) {
    // Enable GPIOA clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = MOTOR_PIN1 | MOTOR_PIN2 | MOTOR_PIN3 | MOTOR_PIN4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MOTOR_PORT, &GPIO_InitStructure);

    while (1) {
			int i;
        // Step the motor forward
        for ( i = 0; i < 4; i++) {
            stepMotor(i);
            delay_ms(10); 
        }
        delay_ms(1000);

        // Step the motor backward
        for ( i = 3; i >= 0; i--) {
            stepMotor(i);
            delay_ms(10); 
        }

        delay_ms(1000);
    }
}
void delay_ms(uint32_t ms) {
    uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 7200; j++) {
        }
    }
}

void stepMotor(uint8_t step) {
    switch(step) {
        case 0:
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN1);
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN2);
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN3);
            GPIO_SetBits(MOTOR_PORT, MOTOR_PIN4);
            break;
        case 1:
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN1);
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN2);
            GPIO_SetBits(MOTOR_PORT, MOTOR_PIN3);
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN4);
            break;
        case 2:
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN1);
            GPIO_SetBits(MOTOR_PORT, MOTOR_PIN2);
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN3);
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN4);
            break;
        case 3:
            GPIO_SetBits(MOTOR_PORT, MOTOR_PIN1);
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN2);
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN3);
            GPIO_ResetBits(MOTOR_PORT, MOTOR_PIN4);
            break;
        default:
            break;
    }
}

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "systick_time.h"
#include "step.h"
// IN4: PB15
// IN3: PB14
// IN2: PB13
// IN1: PB12
int main(void){
    Step_Motor_GPIO_Init();  	
    while (1){
			motor_circle(32, 0, 10);  
    }
}


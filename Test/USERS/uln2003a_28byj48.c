#include "uln2003a_28byj48.h"
#include "stm32f10x.h"   
#include "stm32f10x_gpio.h" 
#include "systick_time.h"

void Step_Motor_GPIO_Init(void)
{  GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void half_step(uint8_t step_count){

	if(step_count<9 && step_count>0){
		switch(step_count){
		case 1:
			/*
			IN1->1
			IN2->0
			IN3->0
			IN4->0
			*/
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_13);
		GPIO_ResetBits(GPIOB , GPIO_Pin_14);
			GPIO_ResetBits(GPIOB , GPIO_Pin_15);
			DelayMs(1);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			break;
		case 2:
			/*
			IN1->1
			IN2->1
			IN3->0
			IN4->0
			*/
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			DelayMs(1);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			break;
		case 3:
			/*
			IN1->0
			IN2->1
			IN3->0
			IN4->0
			*/
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
		DelayMs(1);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			break;
		case 4:
			/*
			IN1->0
			IN2->1
			IN3->1
			IN4->0
			*/
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			DelayMs(1);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			break;
		case 5:
			/*
			IN1->0
			IN2->0
			IN3->1
			IN4->0
			*/
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			DelayMs(1);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			break;
		case 6:
			/*
			IN1->0
			IN2->0
			IN3->1
			IN4->1
			*/
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			DelayMs(1);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			break;

		case 7:
			/*
			IN1->0
			IN2->0
			IN3->0
			IN4->1
			*/
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			DelayMs(1);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			break;

		case 8:
			/*
			IN1->1
			IN2->0
			IN3->0
			IN4->1
			*/
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			DelayMs(1);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			break;

		}
	}


}

void CCW_Drive_HalfStep_Number(uint16_t step_number){
	if(step_number<=4096){
	uint16_t second_loop_vounter=step_number/8,j;
	uint8_t last_count=step_number%8;
		int i;
for( j=0;j<second_loop_vounter;j++)
  {
	for( i=1;i<=8;i++){
		half_step(i);

	}
   }

if(last_count){


	for(i=1;i<last_count;i++){
		half_step(i);

	}
   }
  }
}
void CW_Drive_HalfStep_Number(uint16_t step_number){
	if(step_number<=4096){
	uint16_t second_loop_vounter=step_number/8,j;
	uint8_t last_count=step_number%8;
	int i;	
for( j=0;j<second_loop_vounter;j++)
  {
	for( i=8;i>0;i--){
		half_step(i);

	}
   }

if(last_count){
	for( i=8;i>8-last_count;i--){
		half_step(i);

	}
   }
  }
}
void CCW_angluar_drive(uint16_t angle){
	uint16_t mangle=angle%360;
    uint16_t step_angle=(mangle*4096)/360;
    CCW_Drive_HalfStep_Number(step_angle);
}

void CW_angluar_drive(uint16_t angle){
	uint16_t mangle=angle%360;
    uint16_t step_angle=(mangle*4096)/360;
    CW_Drive_HalfStep_Number(step_angle);
}

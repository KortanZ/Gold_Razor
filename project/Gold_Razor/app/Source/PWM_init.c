#include "PWM_init.h"
#include "Encoder_init.h"

FTM_InitTypeDef motor_init_struct;
FTM_InitTypeDef Steer_init_struct;
uint32 Steer;
uint32 Speed_Now,Speed_Old;
float32 Speed_Error[3],Desired_SpeedValue;
uint32 angle_to_period(int8);
uint32 PWM_Expect = 3000;

/*-------------------------------------------���-------------------------------------------*/
void Motor_init(void)
{
    motor_init_struct.FTM_Ftmx = FTM0;
    motor_init_struct.FTM_Mode = FTM_MODE_PWM;
    motor_init_struct.FTM_PwmFreq = Motor_Fre;

    LPLD_FTM_Init(motor_init_struct);
/*----------������ɫͨ����ʼ��--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch1,
                        0,
                        LeftMotor_Negative,  //PTA4
                        ALIGN_LEFT
                        );
/*----------�ҵ����ɫͨ����ʼ��--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch2,
                        PWM_Expect,
                        LeftMotor_Forward,  //PTA5
                        ALIGN_LEFT
                        );
/*----------������ɫͨ����ʼ��--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch3,
                        0,
                        RightMotor_Negative,  //PTA6
                        ALIGN_LEFT
                        );
/*----------�ҵ����ɫͨ����ʼ��--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch4,
                        PWM_Expect,
                        RightMotor_Forward,  //PTA7
                        ALIGN_LEFT
                        );
}

/*-------------------------------------------���-------------------------------------------*/

void Steer_init(void)
{

	//Steer = angle_to_period(0);

    Steer_init_struct.FTM_Ftmx = FTM2;
    Steer_init_struct.FTM_Mode = FTM_MODE_PWM;
    Steer_init_struct.FTM_PwmFreq = 100;

    LPLD_FTM_Init(Steer_init_struct);

    LPLD_FTM_PWM_Enable(FTM2, //ʹ��FTM2
                        FTM_Ch0, //ʹ��Ch0ͨ��
                        1432, //��ʼ���Ƕ�0��  100HZΪ1432  MAX=1570,Min=1250
                        PTA10, //ʹ��Ch0ͨ����PTD0����
                        ALIGN_LEFT        //���������
                        );
}

uint32 angle_to_period(int8 deg)
{
  uint32 pulse_width = 500+2000*(90+deg)/180;
  return (uint32)(10000*pulse_width/20000 - 25);
}

void MotorDuty_Change(uint32 Duty1,uint32 Duty2,uint32 Duty3,uint32 Duty4)
{
	LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch1,Duty1);
	LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch2,Duty2);
	LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch3,Duty3);
	LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch4,Duty4);
}



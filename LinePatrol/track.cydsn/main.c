
//头文件，不加更改
#include <project.h>
#include<stdio.h>
#include<stdlib.h>

extern uint8 const CYCODE LCD_Char_1_customFonts[];

float angle = -90.0;
int Angle = 0;
char tmp[20];
char outputStr[30];
char Rotate_Dir[20];
int PWM_1 = 4300;
int PWM_2 = 4950;
uint16 ADCresult1;
uint16 ADCresult2;
uint16 ADCresult3;
char outputStr1[50];

void LCD_Display(); //LED显示
void Rotate_Verification();//旋转确认
void Servo_PWM_1(int m1);
void Servo_PWM_2(int m2);
void RotateDirectionVerify();
void IntToString(char *str, int number)
{
    sprintf(str,"%d",number);
}


int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Clock_1_Enable();
    Clock_2_Enable();
    PWM_1_Start();
    PWM_2_Start();
    LCD_Char_1_Start();
    LCD_Char_1_LoadCustomFonts(LCD_Char_1_customFonts);
    ADC_SAR_Seq_1_Start();
    LCD_Char_1_ClearDisplay();
    ADC_SAR_Seq_1_StartConvert();
    for(;;)
    {
        /* Place your application code here. */
        ADC_SAR_Seq_1_IsEndConversion(ADC_SAR_Seq_1_WAIT_FOR_RESULT);
        ADCresult1 = ADC_SAR_Seq_1_GetResult16(0); //得到1号色彩传感器测量数值
        ADCresult2 = ADC_SAR_Seq_1_GetResult16(1); //得到2号色彩传感器测量数值
        ADCresult3 = ADC_SAR_Seq_1_GetResult16(2); //得到3号色彩传感器测量数值

        //输出1号色彩传感器的测量数值到屏幕
        LCD_Char_1_Position(0,0);
        LCD_Char_1_PrintString(" "); //输入前清屏
        LCD_Char_1_Position(0,0);
        sprintf(outputStr, "%d ",ADCresult1);
        LCD_Char_1_PrintString(outputStr);

        //输出2号色彩传感器的测量数值到屏幕
        LCD_Char_1_Position(1,0);
        LCD_Char_1_PrintString(" "); //输入前清屏
        LCD_Char_1_Position(1,0);
        sprintf(outputStr, "%d ",ADCresult2);
        LCD_Char_1_PrintString(outputStr);

        //输出3号色彩传感器的测量数值到屏幕
        LCD_Char_1_Position(1,7);
        LCD_Char_1_PrintString(" "); //输入前清屏
        LCD_Char_1_Position(1,7);
        sprintf(outputStr, "%d ",ADCresult3); //显示转的角度
        LCD_Char_1_PrintString(outputStr);

        int th =1050; //定义黑白分界阈值
       if((ADCresult1 < th)&&(ADCresult2 < th)&&(ADCresult3 < th))
        {//三个色彩传感器全为黑，此时应该直行前进
            //设置电机转速，此时两轮速度应该大致相同
            Servo_PWM_1(4120); //4250
            Servo_PWM_2(5070);  //4950
            //将1输出到输出屏幕，表示此时小车应该直行前进
            LCD_Char_1_PrintString("      ");
            LCD_Char_1_Position(1,13);
            LCD_Char_1_PrintString("1");
            CyDelay(50);//延迟
        }

        // 左边探头检测出白色，车子偏左，此时小车应该右转
        if(((ADCresult1>th)&&(ADCresult2<th)&&(ADCresult3 < ADCresult2 + 300 && ADCresult3 < th - 100))||
             ((ADCresult1>th)&&(ADCresult2>th)&&(ADCresult3<ADCresult2 + 300 && ADCresult3 < th- 100)))
        {
            //设置电机转速，此时左轮速度应该大于右轮速度
            Servo_PWM_1(3900);
            Servo_PWM_2(4500);
            //将2输出到输出屏幕，表示此时小车应该右转
            LCD_Char_1_PrintString(" ");
            LCD_Char_1_Position(1,13);
            LCD_Char_1_PrintString("2");
            CyDelay(20);//转弯时延迟减小，测量更加灵敏
         }
        //右边探头检测出白色，车子偏右，此时小车应该左转
        else if((ADCresult1<th + 150)&&(ADCresult2>th-500)&&(ADCresult3>th-50))
        {
            //设置电机转速，此时右轮速度应该大于左轮速度
            Servo_PWM_1(4300);
            Servo_PWM_2(5830);
            //将3输出到输出屏幕，表示此时小车应该左转
            LCD_Char_1_PrintString(" ");
            LCD_Char_1_Position(1,13);
            LCD_Char_1_PrintString("3");
            CyDelay(20);//转弯时延迟减小，测量更加灵敏
        }

        if((ADCresult1>th)&&(ADCresult2>th)&&(ADCresult3>th))
        { //此时小车三个色彩传感器检测到全白，小车应该后退
            //设置电机转速，此时两轮应该反转
            Servo_PWM_1(5000);
            Servo_PWM_2(4300);
            //将4输出到输出屏幕，表示此时小车应该后退
            LCD_Char_1_PrintString(" "); //输入前清屏
            LCD_Char_1_Position(1,13);
            LCD_Char_1_PrintString("4");
            CyDelay(20);//后退时延迟减小，测量更加灵敏
         }
        else{
            //其余情况，小车正常直线前行
            //设置电机转速，此时两轮速度应该大致相同
             Servo_PWM_1(4120);
             Servo_PWM_2(5070);
             //将5输出到输出屏幕，表示此时小车应该直线前行
            LCD_Char_1_PrintString(" ");
            LCD_Char_1_Position(1,13);
            LCD_Char_1_PrintString("5");
          }
    }
     return 0;
}


void Servo_PWM_1(int m1)
{
    PWM_1_WriteCompare(m1); //改变占空比的值
    angle = (90.0*(PWM_1-4500))/2500; //换算成实际转过的角度, 正负值表示逆顺时针转动
    Angle=(int)angle;
}
void Servo_PWM_2(int m2)
{
    PWM_2_WriteCompare(m2);//改变占空比的值
    angle = (90.0*(PWM_1-4500))/2500;  //换算成实际转过的角度, 正负值表示逆顺时针转动
    Angle=(int)angle;
}


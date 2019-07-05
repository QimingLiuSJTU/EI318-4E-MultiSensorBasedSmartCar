
#include <project.h>
#include <stdio.h>
#include <stdlib.h>

extern uint8 const CYCODE LCD_Char_1_customFonts[];

//函数声明
char *IntToString(char *str, const int num);
void LCDDisplay(const char *str1, const char *str2, const char *str3, const char *str4);
void ServoPWM(int left, int right);
void InitializeComponents();
int constrain(int x);

//PID控制参数
const float P1 = 7;   //4
const float I1 = 0;   //0.02
const float D1 = 3;   //0.005

//与墙的距离的参考值, reference input, 用于与红外传感器的返回值进行比较
const int16 I_dist = 18*5; //18

//用于记录数据的参数
int16 dist = 0;
uint16 dFIFO[100];
int16 rR_Adjust = 0;  //右轮的PWM值调整量
int16 derror = 0;        //比例项
int16 derror1 = 0;       //上一次比例项
int16 derror_error = 0;  //微分项
int16 dSum_error = 0;    //积分项
int16 All_dist = 0;
int16 dnum = 0;
int8 dn = 1;

int8 i = 0;
int dis = 0;

//中断程序, 用于产生计时中断
CY_ISR(InterruptHandler)
{
    Timer_1_ReadStatusRegister();
    
    if(i < 100)
    {
        dFIFO[i] = dis;
        All_dist = All_dist + dis;              
        ++i;
    }
    else
    {
        i = 0;
        //当前的距离取100个检测值的平均值，可以减小传感器返回数值跳变的影响
        dist = All_dist / 100;
        All_dist=0;
        //获取PID中的比例、积分、微分项
        derror=I_dist - dist;
        derror_error=derror-derror1;    
        derror1=derror;     
        dSum_error=dSum_error+derror;
        //通过PID公式得到右轮PWM值的调整量
        rR_Adjust=P1*derror / 5 + I1*dSum_error / 5 + D1*derror_error;  
        rR_Adjust = -rR_Adjust;
    }
}

//主程序
//小车共有3种state, state = 1: 直行； state = 2: 沿墙左转; state = 3: 碰撞后右转
int main()
{
    //初始化器件
    InitializeComponents();
    uint32 adc_result = 0;
    //用于存贮显示在数码版上的字符
    char string1[15],string2[15], string3[15], string4[15];
    //初始化小车状态为直行
    uint8 state = 1;
    
    for(;;)
    {               
        //获取红外传感器返回的与墙距离值
        ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_WAIT_FOR_RESULT);         
        adc_result = ADC_SAR_Seq_GetResult16(0);   
        if(adc_result > 0x7FFF)
           adc_result = 0;                
        if(adc_result > 0)
            //担心由于数字变化范围小，调节量变化不大，调节效果不好，进行*5操作
            dis = (0.5/(0.00002*adc_result -0.00045)-2) * 5;  
        
        //小车3种状态的转化
        if (state == 1)
        {   
            //如果距离突然变得很大，从直行状态转化成沿墙左转状态
            if(dis > 38 * 5)
            {   
                //先保持一段直行状态
                ServoPWM(4150, 5178 + rR_Adjust);
                CyDelay(315);
                state = 2;
            }
        }
        else if (state == 2)
        {   
            //如果与墙距离回复到正常范围，从沿墙左转状态恢复到直行状态，并将积分项效果减弱
            if (dis < 20 * 5)
            { 
                dSum_error *= 0.3;
                state = 1;
            }
        }
        else if (state == 3) 
        {   
            //碰撞后如果与墙距离很大，则进入沿墙左转状态，否则进入直行状态
            if(dis > 38 * 5)
            {
                ServoPWM(4150, 5178 + rR_Adjust);
                state = 2;
            }
            else
            state = 1;
        }
                               
        //获取碰撞传感器的返回值
        if(Button_Read() > 0)
        {
            state = 3;
            LCDDisplay(IntToString(string1, state), IntToString(string2, derror), IntToString(string3, dis), IntToString(string4, rR_Adjust));
        }
        
        //根据小车的当前状态进行电机的控制
        switch(state)
        {   
            //直行state 1
            case 1:
                if(rR_Adjust < 0)
                    rR_Adjust *= 2; //需要向外拐，但是调整的不够快，所以进行了*2处理
                else
                    rR_Adjust *= 1.5; //向内拐，调整不够快，所以进行了*1.5处理               
                rR_Adjust = constrain(rR_Adjust); //对调整量数值进行限制
                ServoPWM(4100, 5178 + rR_Adjust); //控制电机PWM参数
                break;
            case 2: 
                ServoPWM(4278, 5300 + rR_Adjust); //控制小车进行左转
                break;
            case 3: 
                ServoPWM(5700, 4000); //先向右后方退
                CyDelay(450);
                ServoPWM(3850, 4250); //再向右转
                CyDelay(800);
                break;
            default: 
                break;
        }
    
        //通过LCD显示一些观察信息
        LCDDisplay(IntToString(string1, state), IntToString(string2, derror), IntToString(string3, dis), IntToString(string4, rR_Adjust));      
        
        CyDelay(100); //程序延时, 避免刷新太快
    }
    
    return 0;
}

//将数字转化成字符串函数
char *IntToString(char *str, const int num)
{
    sprintf(str, "%d", num);
    return str;
}

//将字符显示在数码板上的函数
void LCDDisplay(const char *str1, const char *str2, const char *str3, const char *str4)
{
    LCD_Char_ClearDisplay();
    LCD_Char_Position(0, 0);
    LCD_Char_PrintString(str1);
    LCD_Char_Position(0, 10);
    LCD_Char_PrintString(str2);
    LCD_Char_Position(1, 0);
    LCD_Char_PrintString(str3);
    LCD_Char_Position(1,10);
    LCD_Char_PrintString(str4);
}

//控制电机转速的函数
void ServoPWM(int left, int right)
{
    PWM_1_WriteCompare(left);
    PWM_2_WriteCompare(right);
}

//初始化器件函数
void InitializeComponents()
{
    CyGlobalIntEnable;
    
    ADC_SAR_Seq_Start();
    ADC_SAR_Seq_StartConvert();
    
    LCD_Char_Start();
    LCD_Char_LoadCustomFonts(LCD_Char_customFonts);
    
    PWM_1_Start();
    PWM_2_Start();
    
    isr_1_StartEx(InterruptHandler); 
    Timer_1_Enable(); 
    Timer_1_Start();
}

//限制数值的保护函数
int constrain(int x)
{
    if(x > 250)
        x = 250;
    else if(x < -250)
        x = -250;
    return x;
}


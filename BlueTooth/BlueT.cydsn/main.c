
#include <project.h>
#include <stdio.h>
#include <stdlib.h>

//功能函数声明
void ServoPWM(int left, int right);
void InitializeComponents();

//主函数
int main()
{
    /* Place your initialization/startup code here  */
    uint8 ch;  
    //初始化器件
    InitializeComponents();
    //用于检测通信是否正常
    UART_UartPutString("CY8CKIT-042 USB-UART\r\n");
    UART_UartPutString("Now,let's begin the travel of PSoc4\r\n");
    //用于存贮接收到的指令
    ch=0xcc;  
    //使得小车静止的PWM参数
    ServoPWM(4500, 4800);
    
    for(;;)
    {
        //得到指令字符
        ch = UART_UartGetChar();
        if(0u != ch)
        {

            UART_UartPutChar(ch);
            
            //前后左右的控制，Q\H\Z\Y分别代表前后左右, 当按下控制键为大写，当松开控制键为小写
            if (ch == 'Q')
            {
                ServoPWM(4000, 5278);
            }
            if(ch == 'q')
            {
                ServoPWM(4500, 4800);
            }
            if (ch == 'H')
            {
                ServoPWM(5150, 4000);
            }
            if(ch == 'h')
            {
                ServoPWM(4500, 4800);
            }
            if (ch == 'Z')
            {
                ServoPWM(4180, 5278);
            }
            if(ch == 'z')
            {
                ServoPWM(4500, 4800);
            }
            if (ch == 'Y')
            {
                ServoPWM(3900, 5100);
            }
            if(ch == 'y')
            {
                ServoPWM(4500, 4800);
            }
            
            //控制小车走出J形字母, 先向前再向右
            if (ch == 'J') 
            {
                ServoPWM(4000, 5278);
                CyDelay(2000);
                ServoPWM(3500, 5100);
                CyDelay(3000);
                ServoPWM(4500, 4800);
            }
            
            //控制小车走出U形字母, 先向前再向右再向前
            if (ch == 'U') //
            {
                ServoPWM(4000, 5278);
                CyDelay(2000);
                ServoPWM(3500, 5100);
                CyDelay(3500);
                ServoPWM(4000, 5278);
                CyDelay(2000);
                ServoPWM(4500, 4800);
            }
            
            //控制小车走出S形字母, 先向左再向右
            if (ch == 'S') 
            {
                ServoPWM(4180, 5278);
                CyDelay(5200);
                ServoPWM(3900, 5000);
                CyDelay(4100);
                ServoPWM(4500, 4800);
            }
            
        }

    }
    return 0;
}

//初始化器件
void InitializeComponents()
{
    CyGlobalIntEnable;
    PWM_1_Start();
    PWM_2_Start();
    UART_Start();
}

//控制电机函数,传入左/右轮电机PWM参数值
void ServoPWM(int left, int right)
{
    PWM_1_WriteCompare(left);
    PWM_2_WriteCompare(right);
}

#include <REGX52.H>
#include <RTX51TNY.H>        //Su dung thu vien RTX51 Tiny Real-Time
#define INIT 0               //Dinh nghia INIT = 0
#define DO 1                 //Dinh nghia DO = 1
#define BUTT 2               //Dinh nghia BUTTTON = 2
sbit LED_DO = P1^2;          //Dinh nghia chan LED_DO
sbit BUTTON = P1^3;          //Dinh nghia chan BUTTON
void USART(void) interrupt 4 //Ngat nhan USART
{
 if(RI)                      //Flag nhan duoc ki tu
 { //Clear flag
 RI=0; //Nhan ki tu 
 isr_send_signal(DO);        //Gui signal cho task DO
 }
}
//=========Ham Start up==========
void Startup(void) _task_ INIT
{ 
 SCON=0x52;                  //USART che do 1
 TMOD=0x21;                  //Timer 1 mode 2
 TH1=TL1=-3;                 //baudrate 9600
 TR1=1;
 IE=0x90;                    //Ngat USART 
 os_create_task (DO);        //Tao Task_Led_Do 
 os_create_task (BUTT);      //Tao Task BUTTON
 os_delete_task (INIT);      //Xoa Task hien tai (Task 0)
}
void Task_Led_Do(void) _task_ DO 
{
 while(1)
 { 
 os_wait2(K_SIG ,50);        //Cho signal voi time out 50 ticks 
 LED_DO ^= 1;                //Dao trang thai Led Do
 }
}
void Task_BUTTON(void) _task_ BUTT
{
 while(1)
 {
 if(BUTTON == 0)             //Nhan nut nhan = 0
 {
 os_send_signal(DO);         //Gui signal cho task DO
 while(BUTTON==0);           //Cho nut nhan = 1(Chong nhieu)
 }
 os_wait2(K_TMO, 10);        //Cho 10 ticks = 100ms
 }
}

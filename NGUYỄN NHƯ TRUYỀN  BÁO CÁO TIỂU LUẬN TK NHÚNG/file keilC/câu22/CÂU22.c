#include <REGX52.H>
#define led1 P3_0
#define led2 P3_1
#define sang 0
#define tat 1
sbit up=P3^2;
char so[ ]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
char count;
unsigned char chuc,donvi; 
 
void delay_ms(int time){
       while(time--){
	   TMOD=0x01;
	   TH0=0xfc;
	   TL0=0x18;
	   TR0=1;
	   while(!TF0);
	   TF0=0;
	   TR0=0;
	   }
 }

void tang()interrupt 0{
        count++;
         if(count>30) count=0;
}

void main (){
            EA=1;
	  EX0=1;
	  IT0=1;
	  EX1=1;
	  IT1=1;
	  while(1){
	         chuc=count/10;
	         donvi=count%10;
	         led1 =sang;    P2=so[chuc];   delay_ms(10);   led1 =tat;
	         led2 =sang;    P2=so[donvi];  delay_ms(10);   led2 =tat;
	   }
}

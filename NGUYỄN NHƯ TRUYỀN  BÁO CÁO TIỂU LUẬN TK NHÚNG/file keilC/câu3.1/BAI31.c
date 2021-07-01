#include <REGX52.H>

#define LCD_RS P1_0
#define LCD_RW P1_1
#define LCD_EN P1_2
#define LCD_D4 P0_4
#define LCD_D5 P0_5
#define LCD_D6 P0_6
#define LCD_D7 P0_7

void delay_us(unsigned int t){
       unsigned int i;
	   for(i=0;i<t;i++);
}

void delay_ms(unsigned int t){
       unsigned int i,j;
	   for(i=0;i<t;i++)
	   for(j=0;j<125;j++);
}

void delay(long time)
{
    while (time--);
}

void LCD_Enable(void){
        LCD_EN =1;
		delay_us(3);
		LCD_EN =0;
		delay_us(50);
}

void LCD_Send4Bit(unsigned char Data){
        LCD_D4=Data & 0x01;
		LCD_D5=(Data>>1)&1;
		LCD_D6=(Data>>2)&1;
		LCD_D7=(Data>>3)&1;
}

void LCD_SendCommand(unsigned char command){
        LCD_Send4Bit(command >>4);
		LCD_Enable();
		LCD_Send4Bit(command);
		LCD_Enable();
}

void LCD_Clear(){
        LCD_SendCommand(0x01);
		delay_us(10);
}

void LCD_Init(){
        LCD_Send4Bit(0x00);
		delay_ms(20);
		LCD_RS=0;
		LCD_RW=0;
		LCD_Send4Bit(0x03);
		LCD_Enable();
		delay_ms(5);
		LCD_Enable();
		delay_us(100);
		LCD_Enable();
		LCD_Send4Bit(0x02);
		LCD_Enable();
		LCD_SendCommand(0x28);
		LCD_SendCommand(0x0c);
		LCD_SendCommand(0x06);
		LCD_SendCommand(0x01);
}

void LCD_Gotoxy(unsigned char x, unsigned char y){
        unsigned char address;
		if(!y)address=(0x80+x);
		else address= (0xc0+x);
		delay_us(1000);
		LCD_SendCommand(address);
		delay_us(50);
}

void LCD_PutChar(unsigned char Data){
        LCD_RS=1;
		LCD_SendCommand(Data);
		LCD_RS=0;
}

void LCD_Puts(char*s){
        while (*s){
		        LCD_PutChar(*s);
				s++;
		}
}

void main(){
    LCD_Init();
	LCD_Puts(" hello");
	delay_ms(1000);
	LCD_Clear();
	LCD_Gotoxy(0,0);
	LCD_Puts("trinh van khanh");
	delay_ms(1000);
	LCD_Gotoxy(0,1);
	LCD_Puts("1755252021600019");
	while(1);
}

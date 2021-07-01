#include <REGX51.H>
char so[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10, 0x89,0x06,0xC7,0x40};
//
#define led1 P2_0
#define led2 P2_1
#define sang 0
#define tat 1
char i;
void delay(int time){
	while(time--);
}
void main(){
	led1 = led2 = tat;
	while(1){
		led1 = sang;
		P0   = so[0];
		delay(300000);
		led1 = tat;
		led2 = tat;
               P0 = so[0];
		delay(300000);
		led2 = sang;
	}
}

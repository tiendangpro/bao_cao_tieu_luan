#include <REGX52.H>

void delay_ms(int ms){
      while(ms--){
             TH0 = 0Xfc;
	   TL0 = 0x18;
	   TR0 = 1;
	   while(!TF0);
	   TF0 = 0;
	   TR0 = 0;
      }
}

void main(){
       EX0 = 1; //cho phep ngat ngoai 0
       IT0 = 1; //chon kieu ngat theo suon
       EA  = 1; //cho phep ngat ngoai cuc
       while(1){
	    P2 = 0;
	    delay_ms(1000);
	    P2 = 0xff;
	    delay_ms(1000);
        }
}

void ngat() interrupt 0{
       long a = 50000;
       P1_3 = 0;
       while(a--){};
       P1_3 = 1;
}

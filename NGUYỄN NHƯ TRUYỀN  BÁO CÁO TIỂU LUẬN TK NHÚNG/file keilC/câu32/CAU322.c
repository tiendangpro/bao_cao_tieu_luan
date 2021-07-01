#include <REGX52.H>

sbit rs = P2^0;
sbit rw = P2^1;
sbit e = P2^2;

void delay(unsigned int t)
{
	unsigned int i, j;
	e = 1;
	for(i = 0; i < t; i++)
	for(j = 0; j < 1275; j++);
	e = 0;
}

void cmd1(unsigned char ch)
{
	P2 = ch;
	rs = 0;
	rw = 0;
	delay(10);
}

void dat1(unsigned char ch)
{
	P2 = ch;
	rs = 1;
	rw = 0;
	delay(10);
}

void cmd(unsigned char a)
{
	unsigned char x;
	x = a & 0xF0;
	cmd1(x);
	x = (a << 4) & 0xF0;
	cmd1(x);
}

void dat(unsigned char a)
{
	unsigned char x;
	x = a & 0xF0;
	dat1(x);
	x = (a << 4) & 0xF0;
	dat1(x);
}

void main(void)
{
	unsigned char mybyte;
	cmd(0x28);
	cmd(0x01);
	cmd(0x0C);
	cmd(0x80);
	cmd(0x06);
	TMOD = 0x20;
	TH1 = 0xFD;
	SCON = 0x50;
	TR1 = 1;
	while(1)
	{
		while(RI == 0);
		mybyte = SBUF;
		dat(mybyte);
		RI = 0;
		if(mybyte == 0x08)
			cmd(0x01); 
		if(mybyte == 0x0D)
			cmd(0xC0);
	}
}
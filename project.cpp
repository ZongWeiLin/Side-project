#include<regx51.h>
#include<LCM.h>
#define PWM P2
char num,duty,num2;
bit flag;	    // �ŧibit���줸(1 bit) 
char volt;
char dip_duty;
char flag_display;//�ˬdUART�����Ϊ�
code char string1[]={ "Buck converter" };
code char string2[]={ "duty:" };
code char string3[]={ "0%" };
code char parameter='V';


void main(void)
{	
	init();//��l��LCD
    SCON=0x50;	// �]�w��mode 1  
	TH1=0xF9; //�]�wBaud rate��9600(SMOD�]��1�A��2�᪺���G)
    PCON=0x80;	// �NSMOD�]�w��1
	TMOD=0x21;//timer 1��mode2(8bit)�Ψӭp��uart,timer0��mode1�ΨӤ�PWM
	num=0;
	num2=0;
	duty=3;//buck��duty,3�N��30%
	flag=0;
    IT0=1;//�]�w���t�tĲ�o
	TR0=1;//�Ұ�timer 0
	TR1=1;//�Ұ�timer 1
	ET0=1;//�Ұ�timer 0���_
    EX0=1;//�}�ҥ~�����_0
	ES=1;//�}�Ҧ�C�q�T���_
	EA=1;//�}�Ҥ��_

	disp_p(1,3); //�]�w��ܦ�m 
	disp_s(string1);//��ܦr��1
	disp_p(2,4);//�]�w��ܦ�m 
	disp_char(&parameter);//��ܹq�����

	disp_p(2,6);
	disp_s(string2);//���duty�Ϊ�
	disp_p(2,12);
	disp_s(string3);//���duty�Ϊ�
	while(1){
	   SBUF='1';//�����}�����A���J�ǰe��SBUF�� 
	   flag=0;	 // �M���^���X�� 
	   while(flag==0); // ���ݸ�ƶǰe���� 
	   }
}
	
//timer 0���_
void timer0 (void) interrupt 1
{
	TH0=(65536-75)/256;//�e��8bit��Ӽ�
	TL0=(65536-75)%256;//�᭱8bit��l��
	num++;
	if(num>duty){
	num2++;
	if(num2>(10-duty)){num=0;num2=0;}
	else if(num2!=0)PWM=0xff;
	}
	else
	PWM=0x7f;
}

//�~�����_�Ψӧ���duty�Ϊ�
void ext0 (void) interrupt 0
{   if(duty>=10)duty=1;
    else duty++;
	disp_p(2,11);
	disp_char(&dip_duty);
	disp_p(2,16);//��ܬ�RX���S������F��Ϊ�
	disp_char(&flag_display);
}

void uart(void) interrupt 4	   
 { if (TI==1)	// ��ƶǰe������  
      { TI=0;	// �M���ǰe(�o�g)���_�X��  
	  	flag=1;	// �]�w�^���X����1  
	  }
   else		  	// ��Ʊ�������(RI=1)�� 
	  { flag_display='1';//������F��flag�N�ߦ�1
		volt=SBUF-128; //�N������ƿ�X��P0��� 
	  	dip_duty=duty+'0';
	    RI=0;	// �M���������_�X��  
        disp_p(2,3);//��ܥثe�q��
        disp_char(&volt);
		disp_p(2,11);//��ܥثeduty cycle
		disp_char(&dip_duty);
	  }
 }
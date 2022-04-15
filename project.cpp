#include<regx51.h>
#include<LCM.h>
#define PWM P2
char num,duty,num2;
bit flag;	    // 宣告bit為位元(1 bit) 
char volt;
char dip_duty;
char flag_display;//檢查UART接收用的
code char string1[]={ "Buck converter" };
code char string2[]={ "duty:" };
code char string3[]={ "0%" };
code char parameter='V';


void main(void)
{	
	init();//初始化LCD
    SCON=0x50;	// 設定為mode 1  
	TH1=0xF9; //設定Baud rate為9600(SMOD設為1，乘2後的結果)
    PCON=0x80;	// 將SMOD設定為1
	TMOD=0x21;//timer 1為mode2(8bit)用來計時uart,timer0為mode1用來切PWM
	num=0;
	num2=0;
	duty=3;//buck的duty,3代表30%
	flag=0;
    IT0=1;//設定為負緣觸發
	TR0=1;//啟動timer 0
	TR1=1;//啟動timer 1
	ET0=1;//啟動timer 0中斷
    EX0=1;//開啟外部中斷0
	ES=1;//開啟串列通訊中斷
	EA=1;//開啟中斷

	disp_p(1,3); //設定顯示位置 
	disp_s(string1);//顯示字串1
	disp_p(2,4);//設定顯示位置 
	disp_char(&parameter);//顯示電壓單位

	disp_p(2,6);
	disp_s(string2);//顯示duty用的
	disp_p(2,12);
	disp_s(string3);//顯示duty用的
	while(1){
	   SBUF='1';//指撥開關狀態載入傳送的SBUF中 
	   flag=0;	 // 清除回應旗號 
	   while(flag==0); // 等待資料傳送完畢 
	   }
}
	
//timer 0中斷
void timer0 (void) interrupt 1
{
	TH0=(65536-75)/256;//前面8bit放商數
	TL0=(65536-75)%256;//後面8bit方餘數
	num++;
	if(num>duty){
	num2++;
	if(num2>(10-duty)){num=0;num2=0;}
	else if(num2!=0)PWM=0xff;
	}
	else
	PWM=0x7f;
}

//外部中斷用來改變duty用的
void ext0 (void) interrupt 0
{   if(duty>=10)duty=1;
    else duty++;
	disp_p(2,11);
	disp_char(&dip_duty);
	disp_p(2,16);//顯示看RX有沒有收到東西用的
	disp_char(&flag_display);
}

void uart(void) interrupt 4	   
 { if (TI==1)	// 資料傳送完畢時  
      { TI=0;	// 清除傳送(發射)中斷旗號  
	  	flag=1;	// 設定回應旗號為1  
	  }
   else		  	// 資料接收完畢(RI=1)時 
	  { flag_display='1';//有收到東西flag就立成1
		volt=SBUF-128; //將接收資料輸出至P0顯示 
	  	dip_duty=duty+'0';
	    RI=0;	// 清除接收中斷旗號  
        disp_p(2,3);//顯示目前電壓
        disp_char(&volt);
		disp_p(2,11);//顯示目前duty cycle
		disp_char(&dip_duty);
	  }
 }
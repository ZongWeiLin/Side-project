#include<regx51.h> 
#include<LCM.h>
#define led    P0 // 定義led的輸出位置  
bit flag;	    // 宣告bit為位元(1 bit) 
/****      主程式       ****/ 
char volt;
void main(void)	 
 { init();//初始化LCD
   SCON=0x50;	// 設定為mode 1  
   TMOD=0x20;//設timer 1為mode2
   TH1=0xF9; //設定Baud rate為9600(SMOD設為1，乘2後的結果)
   PCON=0x80;	// 將SMOD設定為1
   TR1=1;//啟動timer 1
   ES=EA=1;    //  設定UART中斷致能
   while(1)	
     { SBUF='1';//指撥開關狀態載入傳送的SBUF中 
	   flag=0;	 // 清除回應旗號 
	   while(flag==0); // 等待資料傳送完畢 
	 }		
 }
/****     串列埠中斷副程式        ****/ 			
void uart(void) interrupt 4	   
 { if (TI==1)	// 資料傳送完畢時  
      { TI=0;	// 清除傳送(發射)中斷旗號  
	  	flag=1;	// 設定回應旗號為1  
	  }
   else		  	// 資料接收完畢(RI=1)時 
	  { volt=SBUF-128; //將接收資料輸出至P0顯示 
	    RI=0;	// 清除接收中斷旗號  
        disp_p(1,1);
        disp_char(&volt);
	  }
 }
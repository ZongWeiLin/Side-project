#include<regx51.h> 
#define led    P0 // 定義led的輸出位置 
#define dip_sw P2// 定義指撥開關輸入位置 
bit flag;	    // 宣告bit為位元(1 bit) 
/****      主程式       ****/ 
void main(void)	 
 { dip_sw=0xff; // 規劃指撥開關為輸入埠 
   SCON=0x90;	// 設定為mode 2  
   PCON=0x80;	// 將SMOD設定為1 
   ES=EA=1;    //  設定UART中斷致能 
   while(1)	
     { SBUF=dip_sw;//指撥開關狀態載入傳送的SBUF中 
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
	  { led=SBUF; //將接收資料輸出至P0顯示 
	    RI=0;	// 清除接收中斷旗號  
	  }
 }


#include<regx51.h> 
#define led    P0 // �w�qled����X��m 
#define dip_sw P2// �w�q�����}����J��m 
bit flag;	    // �ŧibit���줸(1 bit) 
/****      �D�{��       ****/ 
void main(void)	 
 { dip_sw=0xff; // �W�������}������J�� 
   SCON=0x90;	// �]�w��mode 2  
   PCON=0x80;	// �NSMOD�]�w��1 
   ES=EA=1;    //  �]�wUART���_�P�� 
   while(1)	
     { SBUF=dip_sw;//�����}�����A���J�ǰe��SBUF�� 
	   flag=0;	 // �M���^���X�� 
	   while(flag==0); // ���ݸ�ƶǰe���� 
	 }		
 }
/****     ��C���_�Ƶ{��        ****/ 			
void uart(void) interrupt 4	   
 { if (TI==1)	// ��ƶǰe������  
      { TI=0;	// �M���ǰe(�o�g)���_�X��  
	  	flag=1;	// �]�w�^���X����1  
	  }
   else		  	// ��Ʊ�������(RI=1)�� 
	  { led=SBUF; //�N������ƿ�X��P0��� 
	    RI=0;	// �M���������_�X��  
	  }
 }


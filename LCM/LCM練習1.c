#include <regx51.h>
#include<LCM.h>

/**** ??? ****/
void main(void)
  { char lcd_data1='A';// ??????'A' 
    char lcd_data2='a';// ???'a'??  
   init();
   disp_p(1,1);
   disp_char(lcd_data1);
   disp_p(2,6);
   disp_char(lcd_data2);
    while(1);  //???? 
  }


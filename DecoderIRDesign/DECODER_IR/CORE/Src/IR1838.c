/**
  ******************************************************************************
  * @file		IR1838.c
  * @author	www.hocdientu123.vn
  * @date		25/06/2019
  ******************************************************************************
  */
#include "IR1838.h"
/*******************************************************************************
Noi Dung    :   Kiem tra xung Start cua tin hieu infr.
Tham Bien   :   Khong.
Tra Ve      :   1     :   Co tin hieu hong ngoai.
                0     :   Khong co tin hieu hong ngoai.
********************************************************************************/
uint8_t INFR_CheckStart()
{
     uint8_t i;
     if(GPIO_ReadInputDataBit(DATA_PORT,DATA_IR1838)==0)                             // Neu co canh xuong cua tin hieu
     {
          Delay_us(10);                           // Delay de chong nhieu
          if(GPIO_ReadInputDataBit(DATA_PORT,DATA_IR1838)==0)                        // Neu dung la co canh xuong cua tin hieu
          {       
               for(i=0;i<35;i++)                   // Chia nho xung START thanh 35 doan, moi doan dai 200us
               {
                    Delay_us(200);
                    if(GPIO_ReadInputDataBit(DATA_PORT,DATA_IR1838)==1) 
											return 0;    // Neu tin hieu len muc cao (1) --> khong phai xung START
               } 
               while(GPIO_ReadInputDataBit(DATA_PORT,DATA_IR1838)==0);
								return 1;                          // Dung la xung start
          }
          
     }
     return 0;
}  
/*******************************************************************************
Noi Dung    :   Lay ma infr.
Tham Bien   :   Khong.
Tra Ve      :   0     :   Khong co tin hieu hong ngoai.
                Khac  :   Gia tri cua tin hieu hong ngoai.
********************************************************************************/
uint8_t INFR_GetKey(void)
{
     uint8_t i;
     uint8_t Data_Infr;
     Data_Infr=0;
     if(INFR_CheckStart())              // Neu dung xung START
     {
          while(GPIO_ReadInputDataBit(DATA_PORT,DATA_IR1838)==0);          // Cho het bit 1 tiep theo
          for(i=0;i<24;i++)             // Lay 24 bit du lieu (bao gom 8 bit 0 va 8 bit 1 dau tien sau xung start)
          {    
               Delay_us(1000);           // Delay 750us de kiem tra bit  
               Data_Infr=Data_Infr>>1;
               if(GPIO_ReadInputDataBit(DATA_PORT,DATA_IR1838)==1)
								 Data_Infr|=0x80;          
               while(GPIO_ReadInputDataBit(DATA_PORT,DATA_IR1838)==1);     // cho canh xuong
               while(GPIO_ReadInputDataBit(DATA_PORT,DATA_IR1838)==0);     // cho canh len
          }
          Delay_ms(400);                // Cho het tin hieu (chong nhieu) 
     }
     return Data_Infr;                  // Gia tri ma kenh tra ve
}
/******************************KET THUC FILE******************************/

/**
  ******************************************************************************
  * @file		main.c
  * @author	www.hocdientu123.vn
  * @date		25/06/2019
  ******************************************************************************
  */
#include "main.h"
//---------------------------KHAI BAO CAC BIEN VA HANG-------------------------//
uint8_t Key=0;
//---------------------------KHAI BAO CAC HAM----------------------------------//
//---------------------------HAM MAIN------------------------------------------//
int main()
	{
	  DelayInit();	// goi ham khoi tao du lieu cho cac ham delay
		GPIO_Configuration();	// goi ham cau hinh ngo vao ra cho cac PORT
		GPIO_PinRemapConfig (GPIO_Remap_SWJ_JTAGDisable, ENABLE);//bo che do nap JTAGD
		LCD16X2_Init();		//goi ham thiet lap LCD
		LCD16X2_Clear();	//xoa man hinh LCD
		LCD16X2_Gotoxy(0,0);//hien thi tai toa do x,y=(0,0)
		LCD16X2_PutString("GIAO TIEP IR1838");//hien thi chuoi ky tu
		while(1)
		{
                Key=INFR_GetKey();
                if(Key!=0)
                {
                   LCD16X2_Gotoxy(0,1);//vi tri cot va hang hien thi
									 LCD16X2_PutString("Ma Phim:");//gan chuoi cho st0r
                   LCD16X2_Gotoxy(8,1);//vi tri cot va hang hien thi
                   LCD16X2_NumBer(Key,3);//hien thi chuoi so ra LCD
                }
		}
	}


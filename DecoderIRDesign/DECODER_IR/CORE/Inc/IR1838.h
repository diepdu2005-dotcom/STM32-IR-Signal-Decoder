/**
  ******************************************************************************
  * @file		IR1838.c
  * @author	www.hocdientu123.vn
  * @date		25/06/2019
  ******************************************************************************
  */
#ifndef __IR1838_H
#define __IR1838_H

#include "main.h"
#define DATA_PORT	GPIOB
#define DATA_IR1838	GPIO_Pin_9

uint8_t  INFR_CheckStart(void);
uint8_t INFR_GetKey(void);

#endif 
/******************************KET THUC FILE******************************
______________________________NGUYEN QUY NHAT______________________________*/

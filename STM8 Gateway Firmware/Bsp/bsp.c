#include "bsp.h"

void Delay(uint16_t n)
{
  while(n--);
}
void EIGHT(void)
{
   
  uint8_t i=0;
  GPIO_ResetBits(GPIOB,GPIO_Pin_0);

  for(i=0;i<4;i++)
  {
   
   GPIO_ResetBits(GPIOD,GPIO_Pin_0);
   GPIO_SetBits(GPIOB,GPIO_Pin_0);
   
   Delay(22);
   
   GPIO_SetBits(GPIOD,GPIO_Pin_0);
   GPIO_ResetBits(GPIOB,GPIO_Pin_0);
   Delay(22);
   }
  
  for(i=0;i<4;i++)
  {
   
   GPIO_ResetBits(GPIOD,GPIO_Pin_0);
   GPIO_SetBits(GPIOB,GPIO_Pin_0);
   
   Delay(22);
   
   GPIO_SetBits(GPIOD,GPIO_Pin_0);
   GPIO_ResetBits(GPIOB,GPIO_Pin_0);
   Delay(22);
   }
  GPIO_SetBits(GPIOB,GPIO_Pin_2);
  TIM2_SetCounter(0);
  TIM2_Cmd(ENABLE);
}

void I2C_DeInit_Config(uint8_t SLAVE_ADDR)
{
      I2C_DeInit(I2C1);

    /* Set I2C registers for 7Bits Address */

    I2C1->CR1 |= 0x01;
    // Enable I2C peripheral

    I2C1->CR2 |= 0x04;
    // Enable I2C acknowledgement

    I2C1->FREQR = 16; 
    // Set I2C Freq value (16MHz)

    I2C1->OARL |= (SLAVE_ADDR << 1) ;
    // set slave address to 0xA5(put 0x4A for the register dues to7bit address) 

    I2C1->OARH |= 0x40;
    // Set 7bit address mode
           

    I2C1->ITR|= 0x07;

    // all I2C interrupt enable
    /* Enable Error Interrupt*/
    I2C_ITConfig(I2C1, (I2C_IT_TypeDef)(I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF), ENABLE);
    I2C_Cmd(I2C1,ENABLE);
}

/******************************************************************************************************

*NAME:       void EEPROM_WriteByte(uint16_t Addr,uint8_t Data)

*FUNCTION£º  To specify an address to write a byte of data to EEPROM

*PARAMETER£º Addr:The offset address where data is stored

*           Data:Data to be written

*RETURN:    NONE
******************************************************************************************************/
void EEPROM_WriteByte(uint16_t Addr,uint8_t Data)

{

   uint8_t  *Ptr_SegAddr; //Segment pointer

   Ptr_SegAddr = (uint8_t *)(FLASH_DATA_EEPROM_START_PHYSICAL_ADDRESS+Addr);  //Initialize  pointer

   FLASH_Unlock(FLASH_MemType_Data);

   while(!FLASH_IAPSR_DUL);

   disableInterrupts();

   *Ptr_SegAddr=Data; 

   while(!FLASH_IAPSR_EOP);

   enableInterrupts();

   FLASH_Lock(FLASH_MemType_Data);


}

/******************************************************************************************************

*NAME£º           uint8_t EEPROM_ReadByte(uint8_t Addr)

*FUNCTION£º       To read a byte of data from EEPROM

*PARAMETER£ºAddr:The offset address where data is stored

*RETURN£ºData£º  Read back data 


******************************************************************************************************/

uint8_t EEPROM_ReadByte(uint16_t Addr)

{

   uint16_t Data=0;

   uint8_t *Ptr_SegAddr;

   Ptr_SegAddr = (uint8_t *)(FLASH_DATA_EEPROM_START_PHYSICAL_ADDRESS+Addr);  //Initialize  pointer

   Data=*Ptr_SegAddr;

   return Data;

}

/************************************************
NAME £º BSP_Initializes
FUNCTION £º Plate-level support package initialization
PARAMETER £º NONE
RETURN £º NONE
*************************************************/
void BSP_Initializes(void)
{
  EIGHT();
}


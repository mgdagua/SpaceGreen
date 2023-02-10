
/*
 * DHT11 Interfacing with PIC18F4550
 * http://www.electronicwings.com
 */

/**
 * @file humidity_Temp
 * @version 1.0
 * @date 09/02/23
 * @brief Funciones para el funcionamiento del sensor digital DHT-11
 * @tittle Control de temperatura y humedad 
 */


#include <pic18f4550.h>
#include <xc.h>
#include <stdio.h>
#include "Configuration_Header_File.h"
#include "LCD_16x2_8-bit_Header_File.h"
#include "string.h"
#include "USART_Header_File.h"

#define Data_Out LATA0              /* assign Port pin for data*/
#define Data_In PORTAbits.RA0       /* read data from Port pin*/
#define Data_Dir TRISAbits.RA0      /* Port direction */
#define _XTAL_FREQ 8000000          /* define _XTAL_FREQ for using internal delay */

void DHT11_Start();
void DHT11_CheckResponse();
char DHT11_ReadData();
char stringbt[50];

void main() 
{
    char RH_Decimal,RH_Integral,T_Decimal,T_Integral;
    unsigned char temp_val;
    unsigned char Hum_val;
    char Checksum;
    char value[10];
    
    OSCCON = 0x72;      /* set internal oscillator with frequency 8 MHz*/
    TRISE0 = 0;
    TRISE1 = 0;
    
    LCD_Init();         /* initialize LCD16x2 */
    ADCON1=0x0F; /* this makes all pins as a digital I/O pins */
    USART_Init(9600); //CONFIGURACINION SERIAL
   
    temp_val = 35;
    Hum_val=10;
    
    
    while(1)
{   
    DHT11_Start();                  /* send start pulse to DHT11 module */
    DHT11_CheckResponse();          /* wait for response from DHT11 module */
    
    /* read 40-bit data from DHT11 module */
    RH_Integral = DHT11_ReadData(); /* read Relative Humidity's integral value */
    RH_Decimal = DHT11_ReadData();  /* read Relative Humidity's decimal value */
    T_Integral = DHT11_ReadData();  /* read Temperature's integral value */
    T_Decimal = DHT11_ReadData();   /* read Relative Temperature's decimal value */
    Checksum = DHT11_ReadData();    /* read 8-bit checksum value */
    
    temp_val = (unsigned char) T_Integral; 

    if(temp_val > 30){
        LATE0 = 1;   //si la temperatura es mayor a 30 se activa el ventilador 
        __delay_ms(2000);
    } 
    else {
        LATE0 = 0; //si no se mantiene apagado 
    }
    __delay_ms(2000);
    
    Hum_val= (unsigned char) RH_Integral;
    
    if(Hum_val < 50){  
        LATE1 = 1;  //si la humedad es menor a 50 por ciento se activa el sistema de riego 
        __delay_ms(2000);
    } 
    else {
        LATE1 = 0; //si no se mantiene apagado 
    }
    
    __delay_ms(2000);
 
    
    /* convert humidity value to ascii and send it to display*/    
    sprintf(value,"%d",RH_Integral);
    strcpy(stringbt,value); //toma el valor de la variable value y lo guarda en stringbt
    LCD_String_xy(0,0,value);
    sprintf(value,".%d ",RH_Decimal);
    strcat(stringbt,value); //concatenando agregando el valor decimal al entero
    strcat(stringbt,"% , \r\n");
    LCD_String(value);
    LCD_Char('%');
    USART_SendString(stringbt);  //enviando el valor de la humedad al purto serial

    

    /* convert temperature value to ascii and send it to display*/
    sprintf(value,"%d",T_Integral);
    strcpy(stringbt,value);
    LCD_String_xy(1,0,value);
    sprintf(value,".%d",T_Decimal);
    strcat(stringbt,value);
    strcat(stringbt," C, \r\n");
    LCD_String(value);
    LCD_Char(0xdf);
    LCD_Char('C');
    USART_SendString(stringbt);
    
    sprintf(value,"%d  ",Checksum);
    LCD_String_xy(1,8,value);
    
    
}   
    
}

/**
 * @brief Lee los datos de humedad y temperatura captados por el sensor
 * @return data alamcena los datos leidos 
 */
char DHT11_ReadData()
{
  char i,data = 0;  
    for(i=0;i<8;i++)
    {
        while(!(Data_In & 1));      /* wait till 0 pulse, this is start of data pulse */
        __delay_us(30);         
        if(Data_In & 1)             /* check whether data is 1 or 0 */    
          data = ((data<<1) | 1); 
        else
          data = (data<<1);  
        while(Data_In & 1);
    }
  return data;
}

/**
 * @brief DHT11_Start inicializa el sensor y configura los puertos 
 */
void DHT11_Start()
{    
    Data_Dir = 0;       /* set as output port */
    Data_Out = 0;       /* send low pulse of min. 18 ms width */ /*Mantiene la linea de datos en un estado bajo de 18 */
    __delay_ms(18);
    Data_Out = 1;       /* pull data bus high */
    __delay_us(20);
    Data_Dir = 1;       /* set as input port */    
}

/**
 * @brief Recibe los bits que envia el sensor digital para revisar si el bus de datos esta en alto o en bajo
 */
void DHT11_CheckResponse()
{
    while(Data_In & 1);     /* wait till bus is High */     
    while(!(Data_In & 1));  /* wait till bus is Low */
    while(Data_In & 1);     /* wait till bus is High */
}
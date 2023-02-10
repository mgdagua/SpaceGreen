/*
 * Header File For 16x2 LCD 
 * www.electronicwings.com  
 */

/**
 * @file LCD_Header_File
 * @version 1.0
 * @date 09/02/23
 * @brief funciones y asignacion de pines del LCD
 * @tittle Configuracion del LCD
 */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic18f4550.h>

#define RS LATD0                    /*PORT 0 pin is used for Register Select*/
#define EN LATD1                    /*PORT 1 pin is used for Enable*/
#define ldata LATB                  /*PORT is used for transmitting data to LCD*/
#define LCD_Dir1 TRISD
#define LCD_Dir2 TRISB

/**
 * @brief LCD_Init para incializar el LCD
 */
void LCD_Init();
/**
 * @brief LCD_Command Envia datos a los puertos del pic como comando para el LCD
 * @param y Recibe un dato de tipo char
 */
void LCD_Command(char y);
/**
 * @brief LCD_Char Enviar y registrar datos en el LCD
 * @param x Recibe un dato de tipo char
 */
void LCD_Char(char x);
/**
 * @brief LCD_String para imprimir en el LCD
 * @param recibe el mensaje de tipo char
 */
void LCD_String(const char *);
/**
 * @brief MSdelay genera un retraso en la respuesta del LCD
 * @param recibe el retraso de tipo entero sin signo
 */
void MSdelay(unsigned int );
/**
 * @brief LCD_String_xy imprime el mensaje en la 1er y 2da linea
 * @param Recibe la ubicacion y el valor de tipo char
 */
void LCD_String_xy(char ,char ,const char*);

#endif	/* XC_HEADER_TEMPLATE_H */


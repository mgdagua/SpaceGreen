/* 
 * File:   USART_Source_File.h
 * Author: Logicos
 *
 * Created on 8 de febrero de 2023, 05:39 PM
 */

/* PIC18F4550 USART Header File 
 * http://www.electronicwings.com
 */


/**
 * @file USART_Header_File
 * @version 1.0
 * @date 09/02/23
 * @brief funciones que permiten la comunicacion entre transmisor y receptor  
 * @tittle Configuracion del puerto serial 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef USART_HEADER_FILE_H
#define	USART_HEADER_FILE_H

#include <pic18f4550.h>
#include <xc.h>

/**
 * @brief USART_Init asignacion de puertos para inicializar la comunicacion serial
 */
void USART_Init(long);
/**
 * @brief USART_TxChar Permite la transmision de datos al receptor 
 * @param recibe el parametro que permite la comuncacion con el receptor
 */
void USART_TxChar(char);
/**
 * @brief USART_SendString Realiza el envio del mensaje entre el RX y Tx
 * @param Recibe la variable que se va a transmitir
 */
void USART_SendString(const char *);
/**
 * @brief USART_RxChar Permite al receptor guardar el registro enviado por el transmisor
 * @return Retorna una variable que recibe los datos y los almacena en el registro 
 */
char USART_RxChar();

#define F_CPU 8000000/64
//#define Baud_value(baud_rate) (((float)(F_CPU)/(float)baud_rate)-1)
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)

#endif	/* USART_HEADER_FILE_H */
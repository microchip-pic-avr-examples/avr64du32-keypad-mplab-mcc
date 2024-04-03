/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.1.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"

static void (*IO_PD7_InterruptHandler)(void);
static void (*IO_PD6_InterruptHandler)(void);
static void (*VBUS_DETECT_InterruptHandler)(void);
static void (*BUTTON_3_InterruptHandler)(void);
static void (*BUTTON_4_InterruptHandler)(void);
static void (*BUTTON_1_InterruptHandler)(void);
static void (*BUTTON_2_InterruptHandler)(void);
static void (*INT_BUTTON_InterruptHandler)(void);
static void (*SW0_InterruptHandler)(void);
static void (*LED0_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{

  /* OUT Registers Initialization */
    PORTA.OUT = 0x0;
    PORTC.OUT = 0x0;
    PORTD.OUT = 0x40;
    PORTF.OUT = 0x0;

  /* DIR Registers Initialization */
    PORTA.DIR = 0x0;
    PORTC.DIR = 0x0;
    PORTD.DIR = 0x40;
    PORTF.DIR = 0x4;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x0;
    PORTA.PIN1CTRL = 0x0;
    PORTA.PIN2CTRL = 0x0;
    PORTA.PIN3CTRL = 0x0;
    PORTA.PIN4CTRL = 0x0;
    PORTA.PIN5CTRL = 0x0;
    PORTA.PIN6CTRL = 0x0;
    PORTA.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x0;
    PORTC.PIN1CTRL = 0x0;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x4;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;
    PORTD.PIN0CTRL = 0x0;
    PORTD.PIN1CTRL = 0x0;
    PORTD.PIN2CTRL = 0x0;
    PORTD.PIN3CTRL = 0x0;
    PORTD.PIN4CTRL = 0x0;
    PORTD.PIN5CTRL = 0x0;
    PORTD.PIN6CTRL = 0x0;
    PORTD.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x0;
    PORTF.PIN1CTRL = 0x0;
    PORTF.PIN2CTRL = 0x80;
    PORTF.PIN3CTRL = 0x0;
    PORTF.PIN4CTRL = 0x0;
    PORTF.PIN5CTRL = 0x0;
    PORTF.PIN6CTRL = 0x88;
    PORTF.PIN7CTRL = 0x0;

  /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x0;
    PORTMUX.EVSYSROUTEA = 0x0;
    PORTMUX.SPIROUTEA = 0x0;
    PORTMUX.TCAROUTEA = 0x0;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.TWIROUTEA = 0x0;
    PORTMUX.USARTROUTEA = 0x10;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    IO_PD7_SetInterruptHandler(IO_PD7_DefaultInterruptHandler);
    IO_PD6_SetInterruptHandler(IO_PD6_DefaultInterruptHandler);
    VBUS_DETECT_SetInterruptHandler(VBUS_DETECT_DefaultInterruptHandler);
    BUTTON_3_SetInterruptHandler(BUTTON_3_DefaultInterruptHandler);
    BUTTON_4_SetInterruptHandler(BUTTON_4_DefaultInterruptHandler);
    BUTTON_1_SetInterruptHandler(BUTTON_1_DefaultInterruptHandler);
    BUTTON_2_SetInterruptHandler(BUTTON_2_DefaultInterruptHandler);
    INT_BUTTON_SetInterruptHandler(INT_BUTTON_DefaultInterruptHandler);
    SW0_SetInterruptHandler(SW0_DefaultInterruptHandler);
    LED0_SetInterruptHandler(LED0_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for IO_PD7 at application runtime
*/
void IO_PD7_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD7_InterruptHandler = interruptHandler;
}

void IO_PD7_DefaultInterruptHandler(void)
{
    // add your IO_PD7 interrupt custom code
    // or set custom function using IO_PD7_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD6 at application runtime
*/
void IO_PD6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD6_InterruptHandler = interruptHandler;
}

void IO_PD6_DefaultInterruptHandler(void)
{
    // add your IO_PD6 interrupt custom code
    // or set custom function using IO_PD6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for VBUS_DETECT at application runtime
*/
void VBUS_DETECT_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    VBUS_DETECT_InterruptHandler = interruptHandler;
}

void VBUS_DETECT_DefaultInterruptHandler(void)
{
    // add your VBUS_DETECT interrupt custom code
    // or set custom function using VBUS_DETECT_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BUTTON_3 at application runtime
*/
void BUTTON_3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BUTTON_3_InterruptHandler = interruptHandler;
}

void BUTTON_3_DefaultInterruptHandler(void)
{
    // add your BUTTON_3 interrupt custom code
    // or set custom function using BUTTON_3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BUTTON_4 at application runtime
*/
void BUTTON_4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BUTTON_4_InterruptHandler = interruptHandler;
}

void BUTTON_4_DefaultInterruptHandler(void)
{
    // add your BUTTON_4 interrupt custom code
    // or set custom function using BUTTON_4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BUTTON_1 at application runtime
*/
void BUTTON_1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BUTTON_1_InterruptHandler = interruptHandler;
}

void BUTTON_1_DefaultInterruptHandler(void)
{
    // add your BUTTON_1 interrupt custom code
    // or set custom function using BUTTON_1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BUTTON_2 at application runtime
*/
void BUTTON_2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BUTTON_2_InterruptHandler = interruptHandler;
}

void BUTTON_2_DefaultInterruptHandler(void)
{
    // add your BUTTON_2 interrupt custom code
    // or set custom function using BUTTON_2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for INT_BUTTON at application runtime
*/
void INT_BUTTON_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    INT_BUTTON_InterruptHandler = interruptHandler;
}

void INT_BUTTON_DefaultInterruptHandler(void)
{
    // add your INT_BUTTON interrupt custom code
    // or set custom function using INT_BUTTON_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for SW0 at application runtime
*/
void SW0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    SW0_InterruptHandler = interruptHandler;
}

void SW0_DefaultInterruptHandler(void)
{
    // add your SW0 interrupt custom code
    // or set custom function using SW0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for LED0 at application runtime
*/
void LED0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    LED0_InterruptHandler = interruptHandler;
}

void LED0_DefaultInterruptHandler(void)
{
    // add your LED0 interrupt custom code
    // or set custom function using LED0_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT7_bm)
    {
       BUTTON_3_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT3_bm)
    {
       VBUS_DETECT_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTD.INTFLAGS & PORT_INT7_bm)
    {
       IO_PD7_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT6_bm)
    {
       IO_PD6_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT2_bm)
    {
       BUTTON_4_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT5_bm)
    {
       BUTTON_1_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTF.INTFLAGS & PORT_INT4_bm)
    {
       BUTTON_2_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT5_bm)
    {
       INT_BUTTON_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT6_bm)
    {
       SW0_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT2_bm)
    {
       LED0_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/
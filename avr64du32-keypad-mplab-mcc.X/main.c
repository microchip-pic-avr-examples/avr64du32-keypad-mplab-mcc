 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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
#include "mcc_generated_files/system/system.h"
#include "usb_core_transfer.h"
#include "mcc_generated_files/timer/delay.h"
#include "usb_core.h"
#include "mcc_generated_files/usb/usb_hid/usb_hid_keycodes.h"
#include "mcc_generated_files/usb/usb_hid/usb_protocol_hid.h"
#include "mcc_generated_files/usb/usb_hid/usb_hid_keyboard.h"
#include "usb_hid_transfer.h"
#include "KeyReporting.h"

typedef enum {
    APPLICATION_USB_ERROR = -1, APPLICATION_USB_NOT_INIT,
            APPLICATION_USB_INIT
} APPLICATION_USB_STATE;

typedef enum {
    NOT_PRESSED = 0, PRESSED, HELD_WAIT
} APPLICATION_KEY_STATE;

//Number of tries to re-init the USB
#define USB_INIT_RETRIES 10

//Where are the buttons in the array
#define SW0_INDEX 0
#define BUTTON1_INDEX 1
#define BUTTON2_INDEX 2
#define BUTTON3_INDEX 3
#define BUTTON4_INDEX 4

#define COPY_BUTTON_INDEX BUTTON1_INDEX
#define PASTE_BUTTON_INDEX BUTTON2_INDEX
#define UNDO_BUTTON_INDEX BUTTON3_INDEX
#define CUT_BUTTON_INDEX BUTTON4_INDEX

//Should a key packet be sent?
static volatile bool shouldSendKeyEvent = false;

//Current State of the keys
static volatile APPLICATION_KEY_STATE keyStates[USB_HID_KEYBOARD_REPORT_KEYNUM] = 
{ NOT_PRESSED, NOT_PRESSED, NOT_PRESSED, NOT_PRESSED, NOT_PRESSED, NOT_PRESSED};

//USB Keyboard Report
static volatile USB_KEYBOARD_REPORT_DATA_t keyReport;

void onRTC_Overflow(void)
{
    //SW0 on Nano
    if ((keyStates[SW0_INDEX] == NOT_PRESSED) && (SW0_GetValue()))
    {
        //Key has been pressed since last time
        keyStates[SW0_INDEX] = PRESSED;
        
        //Print Text
        KeyReport_registerKeyDown(&keyReport, 'A');
        KeyReport_registerKeyDown(&keyReport, 'V');
        KeyReport_registerKeyDown(&keyReport, 'R');
        KeyReport_registerKeyDown(&keyReport, ' ');
        KeyReport_registerKeyDown(&keyReport, 'D');
        KeyReport_registerKeyDown(&keyReport, 'U');
        
        shouldSendKeyEvent = true;
    } 
    else if ((keyStates[SW0_INDEX] == PRESSED) && (!SW0_GetValue()))
    {
        //Key was released
        keyStates[SW0_INDEX] = NOT_PRESSED;
        
        //Print Text
        KeyReport_registerKeyUp(&keyReport, 'A');
        KeyReport_registerKeyUp(&keyReport, 'V');
        KeyReport_registerKeyUp(&keyReport, 'R');
        KeyReport_registerKeyUp(&keyReport, ' ');
        KeyReport_registerKeyUp(&keyReport, 'D');
        KeyReport_registerKeyUp(&keyReport, 'U');
        
        keyReport.Modifier = HID_MODIFIER_NONE;
        keyReport.KeyCode[0] = HID_KEY_NONE;

        shouldSendKeyEvent = true;
    }
    else
    {
        //Other keys
        
        if (keyStates[1] == NOT_PRESSED)
        {
            if (BUTTON_1_GetValue())
            {
                //CTRL+C
                keyStates[1] = PRESSED;
                
                keyReport.Modifier = HID_MODIFIER_LEFT_CTRL;
                keyReport.KeyCode[1] = HID_C;

                shouldSendKeyEvent = true;
            }
            else if (BUTTON_2_GetValue())
            {
                //CTRL+V
                keyStates[1] = PRESSED;
                
                keyReport.Modifier = HID_MODIFIER_LEFT_CTRL;
                keyReport.KeyCode[1] = HID_V;

                shouldSendKeyEvent = true;
            }
            else if (BUTTON_3_GetValue())
            {
                //CTRL+Z
                keyStates[1] = PRESSED;
                
                keyReport.Modifier = HID_MODIFIER_LEFT_CTRL;
                keyReport.KeyCode[1] = HID_Z;

                shouldSendKeyEvent = true;
            }
            else if (BUTTON_4_GetValue())
            {
                //CTRL+X
                keyStates[1] = PRESSED;
                
                keyReport.Modifier = HID_MODIFIER_LEFT_CTRL;
                keyReport.KeyCode[1] = HID_X;    

                shouldSendKeyEvent = true;
            }
        }
        else if (keyStates[1] == PRESSED)
        {
            keyStates[1] = HELD_WAIT;
                
            keyReport.Modifier = HID_MODIFIER_NONE;
            keyReport.KeyCode[1] = HID_KEY_NONE;    

            shouldSendKeyEvent = true;
        }
        else
        {
            if ((!BUTTON_1_GetValue()) && (!BUTTON_2_GetValue())
                    && (!BUTTON_3_GetValue()) && (!BUTTON_4_GetValue()))
            {
                keyStates[1] = NOT_PRESSED;
            }
        }

//        //CTRL+C
//        if ((BUTTON_1_GetValue()) && (keyStates[COPY_BUTTON_INDEX] == NOT_PRESSED))
//        {
//            keyStates[COPY_BUTTON_INDEX] = PRESSED;
//
//            keyReport.Modifier = HID_MODIFIER_LEFT_CTRL;
//            keyReport.KeyCode[COPY_BUTTON_INDEX] = HID_C;
//
//            shouldSendKeyEvent = true;
//        }
//        else if ((!BUTTON_1_GetValue()) && (keyStates[COPY_BUTTON_INDEX] == PRESSED))
//        {
//            keyStates[COPY_BUTTON_INDEX] = NOT_PRESSED;
//
//            keyReport.Modifier = HID_MODIFIER_NONE;
//            keyReport.KeyCode[COPY_BUTTON_INDEX] = HID_KEY_NONE;
//
//            shouldSendKeyEvent = true;
//        }
//
//        //CTRL+V
//        if ((BUTTON_2_GetValue()) && (keyStates[PASTE_BUTTON_INDEX] == NOT_PRESSED))
//        {
//            keyStates[PASTE_BUTTON_INDEX] = PRESSED;
//
//            keyReport.Modifier = HID_MODIFIER_LEFT_CTRL;
//            keyReport.KeyCode[PASTE_BUTTON_INDEX] = HID_V;
//
//            shouldSendKeyEvent = true;
//        }
//        else if ((!BUTTON_2_GetValue()) && (keyStates[PASTE_BUTTON_INDEX] == PRESSED))
//        {
//            keyStates[PASTE_BUTTON_INDEX] = NOT_PRESSED;
//
//            keyReport.Modifier = HID_MODIFIER_NONE;
//            keyReport.KeyCode[PASTE_BUTTON_INDEX] = HID_KEY_NONE;
//
//            shouldSendKeyEvent = true;
//        }
    }
    
}

int main(void)
{
    SYSTEM_Initialize();
        
    //USB Bus State
    APPLICATION_USB_STATE usbState = APPLICATION_USB_NOT_INIT;
    
    //Period Callback
    RTC_SetOVFIsrCallback(&onRTC_Overflow);
        
    //Enable Interrupts
    sei();
    
    //Keep track of the number of USB_Retries
    uint8_t retryCount = 0;
    
    while(1)
    {
        //If VUSB is present and no errors have occurred
        if ((AC0_Read()) && (usbState != APPLICATION_USB_ERROR))
        {    
            //Has the USB been initialized?
            if (usbState == APPLICATION_USB_NOT_INIT)
            {
                //Need to start USB
                if (USB_Start() == SUCCESS)
                {
                    usbState = APPLICATION_USB_INIT;
                    printf("USB Started\r\n");
                }
                else if (retryCount < USB_INIT_RETRIES)
                {
                    //Failed to init, STOP USB peripheral, increment count
                    retryCount++;
                    USB_Stop();
                }
                else
                {
                    //Failed to init
                    usbState = APPLICATION_USB_ERROR;
                    printf("Failed to start USB\r\n");
                }
            }
            else
            {
                //USB has been initialized
                
                //Has a key changed state?
                if (shouldSendKeyEvent)
                {
                    shouldSendKeyEvent = false;
                    USB_HIDKeyboardReportInSend(&keyReport); 
                }

                //Handle USB Events
                if (USBDevice_Handle() != SUCCESS)
                {
                    //Unable to handle USB Events

                    //Try to reset USB
                    if (USB_Reset() != SUCCESS)
                    {
                        printf("An error has occurred\r\n");
                        usbState = APPLICATION_USB_ERROR;
                    }
                }
            }
        }
        else
        {
            //VUSB is not present
            
            USB_Stop();
            usbState = APPLICATION_USB_NOT_INIT;
            retryCount = 0;

            printf("No USB Voltage\r\n");
            DELAY_milliseconds(500);
        }
    }    
}
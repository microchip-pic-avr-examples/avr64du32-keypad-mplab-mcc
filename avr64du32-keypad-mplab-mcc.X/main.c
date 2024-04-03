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

static volatile APPLICATION_KEY_STATE state = NOT_PRESSED;

//USB Keyboard Report
static volatile USB_KEYBOARD_REPORT_DATA_t keyReport;

void onRTC_Overflow(void)
{
    switch (state)
    {
        case NOT_PRESSED:
        {
            //Assume a key was pressed (variable cleared if not pressed)
            shouldSendKeyEvent = true;
            
            if (SW0_GetValue())
            {
                //SW0 - Print "AVR DU"
                KeyReport_addKeyDownEventFromChar(&keyReport, 'A');
                KeyReport_addKeyDownEventFromChar(&keyReport, 'V');
                KeyReport_addKeyDownEventFromChar(&keyReport, 'R');
                KeyReport_addKeyDownEventFromChar(&keyReport, ' ');
                KeyReport_addKeyDownEventFromChar(&keyReport, 'D');
                KeyReport_addKeyDownEventFromChar(&keyReport, 'U');
            }
            else if (BUTTON_1_GetValue())
            {
                //BUTTON1 - CTRL + C
                KeyReport_addKeyDownEvent(&keyReport, HID_MODIFIER_LEFT_CTRL, HID_C);
            }
            else if (BUTTON_2_GetValue())
            {
                //BUTTON2 - CTRL + V
                KeyReport_addKeyDownEvent(&keyReport, HID_MODIFIER_LEFT_CTRL, HID_V);
            }
            else if (BUTTON_3_GetValue())
            {
                //BUTTON3 - CTRL + Z
                KeyReport_addKeyDownEvent(&keyReport, HID_MODIFIER_LEFT_CTRL, HID_Z);
            }
            else if (BUTTON_4_GetValue())
            {
                //BUTTON4 - CTRL + X
                KeyReport_addKeyDownEvent(&keyReport, HID_MODIFIER_LEFT_CTRL, HID_X);
            }
            else
            {
                //No key was pressed
                shouldSendKeyEvent = false;
            }
            
            //Transition to the PRESSED event
            if (shouldSendKeyEvent)
                state = PRESSED;
            
            break;
        }
        case PRESSED:
        {
            //Remove the key down events
            KeyReport_clearReport(&keyReport);
            shouldSendKeyEvent = true;
            
            //Move to the wait state
            state = HELD_WAIT;
            break;
        }
        case HELD_WAIT:
        {
            //If all buttons are released, reset to NOT_PRESSED
            if ((!BUTTON_1_GetValue()) && (!BUTTON_2_GetValue())
                    && (!BUTTON_3_GetValue()) && (!BUTTON_4_GetValue())
                    && (!SW0_GetValue()))
            {
                state = NOT_PRESSED;
            }
            break;
        }
        default:
        {
            //We shouldn't get here
        }
    }
}

//Bitmask of USB Report
#define USB_NUM_LOCK_bm (0b1 << 0)
#define USB_CAPS_LOCK_bm (0b1 << 1)
#define USB_SCROLL_LOCK_bm (0b1 << 2)
#define USB_COMPOSE_bm (0b1 << 3)
#define USB_KANA_bm (0b1 << 4)

//Handle USB Reports
void handleUSBReport(uint16_t report)
{
    printf("%x\r\n", report);
    uint8_t reportType = (report >> 8);
    
    switch (reportType)
    {
        case 0:
        {
            //Report ID not set
            //If there is no output endpoint, CAPS LOCK/SCROLL LOCK/NUM LOCK/COMPOSE/KANA are reported here
            
            //[7:5] Constants
            //[4] Kana
            //[3] Compose
            //[2] Scroll Lock
            //[1] Caps Lock
            //[0] Num Lock
            
            LED0_SetLow();
            
            uint8_t keyMap = report & 0xFF;
            
            if (keyMap & USB_NUM_LOCK_bm)
            {
                //Num Lock
            }
            
            if (keyMap & USB_CAPS_LOCK_bm)
            {
                //Caps Lock
                LED0_SetHigh();
            }
            
            if (keyMap & USB_SCROLL_LOCK_bm)
            {
                //Scroll Lock
            }
            
            if (keyMap & USB_COMPOSE_bm)
            {
                //Compose
            }
            
            if (keyMap & USB_KANA_bm)
            {
                //Kana
            }
            
            break;
        }
        case 1:
        {
            //Input
            break;
        }
        case 2:
        {
            //Output
            break;
        }
        case 3:
        {
            //Feature
            break;
        }
        default:
        {
            
        }
    }

}

int main(void)
{
    //Setup USB Callback
    HID_SetReportCallbackRegister(&handleUSBReport);
    
    //Init HW Peripherals
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
                    //Failed to init, stop the USB peripheral, increment count
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
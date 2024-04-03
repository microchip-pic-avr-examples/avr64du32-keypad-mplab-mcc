/**
 * USB_DEVICE_STACK Generated Driver File
 * 
 * @file usb_device.c
 * 
 * @ingroup usb_device_stack
 * 
 * @brief Driver implementation file for the USB device setup.
 *
 * @version USB_DEVICE_STACK Driver Version 1.0.0
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

#include <usb_core.h>
#include <usb_hid_keyboard.h>
#include <usb_hid_keycodes.h>
#include "usb_device.h"
#include "usb0.h"

static RETURN_CODE_t usbStatus;
static void USBDevice_TransferHandler(void);
static void USBDevice_EventHandler(void);

static void HID_DefaultSetReportCallback(uint16_t report);
static USB_HID_REPORT_CALLBACK_t HID_SetReport_cb = &HID_DefaultSetReportCallback;

void USBDevice_Initialize(void)
{
    USB_DescriptorPointersSet(&descriptorPointers);
    
    USB_HIDKeyboardInitialize(&USB_HIDKeyboardReportDescriptor, HID_SetReport_cb);

    USB0_TrnComplCallbackRegister(USBDevice_TransferHandler);
    USB0_BusEventCallbackRegister(USBDevice_EventHandler);

    usbStatus = USB_Start();
}

RETURN_CODE_t USBDevice_Handle(void)
{
    if (usbStatus == SUCCESS)
    {
        usbStatus = USB_TransferHandler();
    }
    if (usbStatus == SUCCESS)
    {
        usbStatus = USB_EventHandler();
    }
    return usbStatus;
}

RETURN_CODE_t USBDevice_StatusGet(void)
{
    return usbStatus;
}

static void USBDevice_TransferHandler(void)
{
    usbStatus = USB_TransferHandler();
}

static void USBDevice_EventHandler(void)
{
    usbStatus = USB_EventHandler();
}
    
void HID_SetReportCallbackRegister(USB_HID_REPORT_CALLBACK_t cb)
{
    HID_SetReport_cb = cb;
}

#include "../system/system.h"

static void HID_DefaultSetReportCallback(uint16_t report)
{
    printf("%x\r\n", report);
    uint8_t reportType = (report >> 8);
    
    switch (reportType)
    {
        case 0:
        {
            //Report ID not set
            //If there is no output endpoint, CAPS LOCK/SCROLL LOCK/NUM LOCK/KANA are reported here
            
            //[7:5] Constants
            //[4] Kana
            //[3] Compose
            //[2] Scroll Lock
            //[1] Caps Lock
            //[0] Num Lock
            
            LED0_SetLow();
            
            uint8_t keyMap = report & 0xFF;
            
            if ((keyMap & 0x01) != 0x00)
            {
                //Num lock is active
            }
            
            if ((keyMap & 0x02) != 0x00)
            {
                //Caps lock is active
                LED0_SetHigh();
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

/**
 End of File
*/

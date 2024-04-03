/**
 *  USBHIDKEYBOARD HID Keyboard Source File
 *  @file usb_hid_keyboard.c
 *  @ingroup usb_hid_keyboard
 *  @brief Contains the implementation for the USB Keyboard drivers.
 *  @version USB Device Stack HID Driver Version 1.0.0
 */

/*
    (c) 2023 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
 */

#include <usb_hid_keyboard.h>
#include <usb_hid_keycodes.h>
#include <stddef.h>
#include <string.h>
#include <usb_common_elements.h>
#include <usb_hid.h>
#include <usb_hid_transfer.h>
#include <usb_core.h>
#include <usb_config.h>
#include <usb_protocol_hid.h>

STATIC uint8_t usbHIDKeyboardRate;
STATIC uint8_t usbHIDKeyboardProtocol;
STATIC USB_KEYBOARD_REPORT_DATA_t keyboardInputReport;

void USB_HIDKeyboardInitialize(USB_HID_REPORT_DESCRIPTOR_t *reportPtr, USB_HID_REPORT_CALLBACK_t callback)
{
    // Initialize idle rate and protocol
    usbHIDKeyboardRate = 0;
    usbHIDKeyboardProtocol = 0;

    // Clear input report
    for (uint8_t i = 0; i < USB_HID_KEYBOARD_REPORT_KEYNUM; i++)
    {
        keyboardInputReport.KeyCode[i] = 0;
    }
    keyboardInputReport.Modifier = 0;
    // Register Rate, Protocol and Report Descriptor pointers
    USB_HIDInitialize(&usbHIDKeyboardRate, &usbHIDKeyboardProtocol, reportPtr);
    USB_HIDReportUpdatedCallbackRegister(callback);
}

// Functions for handling press and release of switches

RETURN_CODE_t USB_HIDKeyModifierDown(uint8_t modifierID)
{
    RETURN_CODE_t status = UNINITIALIZED;
    keyboardInputReport.Modifier |= modifierID;
    status = USB_HIDKeyboardReportInSend(&keyboardInputReport);
    return status;
}

RETURN_CODE_t USB_HIDKeyModifierUp(uint8_t modifierID)
{
    RETURN_CODE_t status = UNINITIALIZED;
    keyboardInputReport.Modifier &= ~modifierID;
    status = USB_HIDKeyboardReportInSend(&keyboardInputReport);
    return status;
}

int8_t USB_HIDKeyCodeIndexGet(uint8_t keyID)
{
    int8_t keyIndex = HID_KEYID_NOT_FOUND;
    for (int8_t i = 0; i < (int8_t)USB_HID_KEYBOARD_REPORT_KEYNUM; i++)
    {
        if (keyID == keyboardInputReport.KeyCode[i])
        {
            // keyID already in array
            keyIndex = i;
            break;
        }
    }
    return keyIndex;
}

RETURN_CODE_t USB_HIDKeyPressDown(uint8_t keyID)
{
    uint8_t status = UNINITIALIZED;

    if (HID_KEYID_NOT_FOUND == USB_HIDKeyCodeIndexGet(keyID))
    {
        int8_t newKeyIndex = USB_HIDKeyCodeIndexGet(HID_KEY_NONE);
        if ((int8_t)HID_KEYID_NOT_FOUND != newKeyIndex)
        {
            keyboardInputReport.KeyCode[newKeyIndex] = keyID;
            status = USB_HIDKeyboardReportInSend(&keyboardInputReport);
        }
        else
        {
            // Array full, so do not send anything
            // Increase USB_HID_KEYBOARD_REPORT_KEYNUM and relevant descriptor configuration to handle more keys
            status = SUCCESS;
        }
    }
    else
    {
        // keyID already in array
        status = SUCCESS;
    }

    return status;
}

RETURN_CODE_t USB_HIDKeyPressUp(uint8_t keyID)
{
    RETURN_CODE_t status = UNINITIALIZED;

    int8_t clearKeyIndex = USB_HIDKeyCodeIndexGet(keyID);
    if ((int8_t)HID_KEYID_NOT_FOUND != clearKeyIndex)
    {
        keyboardInputReport.KeyCode[clearKeyIndex] = HID_KEY_NONE;

        while (clearKeyIndex < ((int8_t)USB_HID_KEYBOARD_REPORT_KEYNUM - 1))
        {
            keyboardInputReport.KeyCode[clearKeyIndex] = keyboardInputReport.KeyCode[clearKeyIndex + 1];
            clearKeyIndex++;
        }
        // Making sure last byte in KeyCode array is cleared.
        keyboardInputReport.KeyCode[(uint8_t)USB_HID_KEYBOARD_REPORT_KEYNUM - 1u] = HID_KEY_NONE;
    }

    status = USB_HIDKeyboardReportInSend(&keyboardInputReport);

    return status;
}

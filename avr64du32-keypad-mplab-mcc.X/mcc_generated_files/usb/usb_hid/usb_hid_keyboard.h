/**
 * USBHIDKEYBOARD HID Keyboard Header File
 * @file usb_hid_keyboard.h
 * @ingroup usb_hid
 * @defgroup usb_hid_keyboard USB Human Interface Device (HID) Keyboard
 * @brief Contains the prototypes and data types for the USB Keyboard application drivers.
 * @version USB Device Stack HID Driver Version 1.0.0
 * @{
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

#ifndef USB_HID_KEYBOARD_H
#define USB_HID_KEYBOARD_H

#include <usb_protocol_hid.h>
#include <usb_common_elements.h>

/**
 * @ingroup usb_hid_keyboard
 * @name Keyboard input report sizes
 * Macros for the input report for a standard HID keyboard.
 */
#define USB_HID_KEYBOARD_REPORT_KEYNUM 6u
#define USB_HID_KEYBOARD_REPORT_SIZE (USB_HID_KEYBOARD_REPORT_KEYNUM + 2u)

/**
 * @ingroup usb_hid_keyboard
 * @brief Sets up the keyboard application for use with the HID class.
 * @param reportPtr - Pointer to report descriptor
 * @param callback - Callback for registering the Set Report function
 * @return None.
 */
void USB_HIDKeyboardInitialize(USB_HID_REPORT_DESCRIPTOR_t *reportPtr, USB_HID_REPORT_CALLBACK_t callback);

/**
 * @ingroup usb_hid_keyboard
 * @brief Updates the keyboard report by adding the pressed modifier key in the modifier byte in the report array.
 * @param modifierID - ID of modifier key being pressed
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_HIDKeyModifierDown(uint8_t modifierID);

/**
 * @ingroup usb_hid_keyboard
 * @brief Updates the keyboard report by removing the released modifier key in the modifier byte in the report array.
 * @param modifierID - ID of modifier key being released
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_HIDKeyModifierUp(uint8_t modifierID);

/**
 * @ingroup usb_hid_keyboard
 * @brief Checks the report array to see that the key is already present.
 * @param keyID - ID of the key being pressed
 * @return HID_KEYID_NOT_FOUND or location in array where the key is already present
 */
int8_t USB_HIDKeyCodeIndexGet(uint8_t keyID);

/**
 * @ingroup usb_hid_keyboard
 * @brief Updates the keyboard report by adding the pressed key at the first available byte in the report array.
 * @param keyID - ID of key being pressed
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_HIDKeyPressDown(uint8_t keyID);

/**
 * @ingroup usb_hid_keyboard
 * @brief Updates the keyboard report by removing the released key and shifts the registered keys towards the beginning of the report array.
 * @param keyID - ID of key being released
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_HIDKeyPressUp(uint8_t keyID);

/**
 * @}
 */

#endif /* USB_HID_KEYBOARD_H */
/**
 * USBHIDKTRANSFER HID Transfer Header File
 * @file usb_hid_transfer.h
 * @ingroup usb_hid
 * @defgroup usb_hid_transfer USB Human Interface Device (HID) Transfer
 * @brief Contains the prototypes and data types for the USB HID transfer application drivers.
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

#ifndef USB_HID_TRANSFER_H
#define USB_HID_TRANSFER_H

#include <usb_common_elements.h>
#include <usb_protocol_hid.h>
#include <stdbool.h>

/**
 * @ingroup usb_hid_transfer
 * @brief Sends a HID keyboard input report to the interrupt IN endpoint.
 * @param data - Keyboard input report data
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_HIDKeyboardReportInSend(USB_KEYBOARD_REPORT_DATA_t *data);

/**
 * @ingroup usb_hid_transfer
 * @brief Verifies if a transfer was completed.
 * @param pipe - The pipe that data is being sent on
 * @param status - Status of the transfer
 * @param bytesTransferred - Number of bytes transferred
 * @return None.
 */
void USB_HIDKeyboardInputReportSentCallback(USB_PIPE_t pipe, USB_TRANSFER_STATUS_t status, uint16_t bytesTransferred);

/**
 * @ingroup usb_hid_transfer
 * @brief Sends a HID mouse input report to the interrupt IN endpoint.
 * @param data - Mouse input report data
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_HIDMouseReportInSend(USB_MOUSE_REPORT_DATA_t *data);

/**
 * @}
 */

#endif /* USB_HID_TRANSFER_H */
/**
 * USBHID HID Header File
 * @file usb_hid.h
 * @defgroup usb_hid USB Human Interface Device (HID)
 * @brief Contains the prototypes and data types for the generic HID application drivers.
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

#ifndef USB_HID_H
#define USB_HID_H

#include <usb_common_elements.h>
#include <usb_protocol_headers.h>
#include <usb_protocol_hid.h>

/**
 * @ingroup usb_hid
 * @brief Registers a callback to the HID report.
 * @param callback - Callback to the report updated function
 * @return None.
 */
void USB_HIDReportUpdatedCallbackRegister(USB_HID_REPORT_CALLBACK_t callback);

/**
 * @ingroup usb_hid
 * @brief Checks if a callback is registered and calls the End Of Request function.
 * @param None.
 * @return None.
 */
void USB_HIDReportUpdatedCallback(void);

/**
 * @ingroup usb_hid
 * @brief Registers the rate, protocol and report descriptor for HID.
 * @param ratePtr - Pointer to rate
 * @param protocolPtr - Pointer to protocol
 * @param reportPtr - Pointer to report descriptor
 * @return None.
 */
void USB_HIDInitialize(uint8_t *ratePtr, uint8_t *protocolPtr, USB_HID_REPORT_DESCRIPTOR_t *reportPtr);

/**
 * @ingroup usb_hid
 * @brief Initializes the HID class and performs control transfers.
 * @param setupRequestPtr - Pointer to the Setup Request struct
 * @return SUCCESS or an Error code according to RETURN_CODE_t
 */
RETURN_CODE_t USB_HIDRequestHandler(USB_SETUP_REQUEST_t *setupRequestPtr);

/**
 * @}
 */

#endif /* USB_HID_H */
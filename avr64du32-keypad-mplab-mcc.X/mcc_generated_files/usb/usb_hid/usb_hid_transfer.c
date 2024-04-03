/**
 *  USBHIDTRANSFER HID Transfer Source File
 *  @file usb_hid_transfer.c
 *  @ingroup usb_hid_transfer
 *  @brief Contains the implementation for the USB HID Transfer drivers.
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

#include <usb_hid_transfer.h>
#include <stddef.h>
#include <string.h>
#include <usb_common_elements.h>
#include <usb_hid.h>
#include <usb_core.h>
#include <usb_core_events.h>
#include <usb_core_transfer.h>
#include <usb_peripheral_read_write.h>
#include <usb_protocol_hid.h>
#include <usb_config.h>

STATIC USB_PIPE_t keyboardPipe = {.address = USB_HID_INTERRUPT_EP, .direction = USB_EP_DIR_IN};
STATIC USB_KEYBOARD_REPORT_DATA_t *nextKeyboardReport = NULL;
STATIC USB_KEYBOARD_REPORT_DATA_t keyboardReportBuffer;

STATIC USB_PIPE_t mousePipe = {.address = USB_HID_INTERRUPT_EP, .direction = USB_EP_DIR_IN};
STATIC USB_MOUSE_REPORT_DATA_t mouseReportBuffer;

RETURN_CODE_t USB_HIDKeyboardReportInSend(USB_KEYBOARD_REPORT_DATA_t *data)
{
    RETURN_CODE_t status = UNINITIALIZED;

    if (USB_PipeStatusIsBusy(keyboardPipe) == true)
    {
        nextKeyboardReport = data;
        status = SUCCESS;
    }
    else
    {
        (void)memcpy(&keyboardReportBuffer, data, sizeof(USB_KEYBOARD_REPORT_DATA_t));
        status = USB_TransferWriteStart(keyboardPipe, (uint8_t *)&keyboardReportBuffer, sizeof(USB_KEYBOARD_REPORT_DATA_t), false, USB_HIDKeyboardInputReportSentCallback);
    }
    return status;
}

void USB_HIDKeyboardInputReportSentCallback(USB_PIPE_t pipe, USB_TRANSFER_STATUS_t status, uint16_t bytesTransferred)
{
    (void)(pipe);
    (void)(status);
    (void)(bytesTransferred);

    if (nextKeyboardReport != NULL)
    {
        USB_HIDKeyboardReportInSend(nextKeyboardReport);
        nextKeyboardReport = NULL;
    }
}

RETURN_CODE_t USB_HIDMouseReportInSend(USB_MOUSE_REPORT_DATA_t *data)
{
    RETURN_CODE_t status = UNINITIALIZED;
    if (USB_PipeStatusIsBusy(mousePipe) == true)
    {
        status = SUCCESS;
    }
    else
    {
        (void)memcpy(&mouseReportBuffer, data, sizeof(USB_MOUSE_REPORT_DATA_t));
        status = USB_TransferWriteStart(mousePipe, (uint8_t *)&mouseReportBuffer, sizeof(USB_MOUSE_REPORT_DATA_t), false, NULL);
    }
    return status;
}
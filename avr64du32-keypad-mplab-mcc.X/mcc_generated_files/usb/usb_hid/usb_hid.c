/**
 * USBHID HID Source File
 * @file usb_hid.c
 * @ingroup usb_hid
 * @brief Contains the implementation for the HID generic drivers.
 * @version USB Device Stack HID Driver Version 1.0.0
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

#include <usb_hid.h>
#include <stddef.h>
#include <usb_common_elements.h>
#include <usb_protocol_hid.h>
#include <usb_core.h>
#include <usb_config.h>

STATIC uint8_t *reportDescriptor = NULL;
STATIC uint8_t *rate = NULL;
STATIC uint8_t *protocol = NULL;

STATIC uint16_t reportData __attribute__((aligned(2))) = 0;
STATIC uint8_t *descriptorPtr = NULL;
STATIC uint16_t descriptorLength = 0;
STATIC USB_DESCRIPTOR_TYPE_HID_t descriptorType;
STATIC USB_HID_REPORT_CALLBACK_t reportCallback = NULL;

void USB_HIDReportUpdatedCallbackRegister(USB_HID_REPORT_CALLBACK_t callback)
{
    reportCallback = callback;
}

void USB_HIDReportUpdatedCallback(void)
{
    if (reportCallback != NULL)
    {
        reportCallback(reportData);
    }
    USB_ControlEndOfRequestCallbackRegister(NULL);
}

void USB_HIDInitialize(uint8_t *ratePtr, uint8_t *protocolPtr, USB_HID_REPORT_DESCRIPTOR_t *reportPtr)
{
    rate = ratePtr;
    protocol = protocolPtr;
    reportDescriptor = (uint8_t *)reportPtr;
    USB_ClassRequestCallbackRegister(&USB_HIDRequestHandler);
}

RETURN_CODE_t USB_HIDRequestHandler(USB_SETUP_REQUEST_t *setupRequestPtr)
{
    RETURN_CODE_t status = UNSUPPORTED;
    if (USB_REQUEST_DIR_IN == setupRequestPtr->bmRequestType.dataPhaseTransferDirection)
    {
        if (USB_REQUEST_TYPE_STANDARD == (USB_REQUEST_TYPE_t)setupRequestPtr->bmRequestType.type)
        {
            if (USB_REQUEST_GET_DESCRIPTOR == setupRequestPtr->bRequest)
            {
                descriptorType = setupRequestPtr->wValue >> 8;
                switch (descriptorType)
                {
                case USB_DT_HID:
                    status = USB_DescriptorPointerGet(descriptorType, 0u, &descriptorPtr, &descriptorLength);
                    break;

                case USB_DT_HID_REPORT:
                    descriptorPtr = (uint8_t *)reportDescriptor;
                    descriptorLength = USB_HID_REPORT_DESCRIPTOR_SIZE;
                    status = SUCCESS;
                    break;

                default:
                    status = UNSUPPORTED;
                    break;
                }

                if (SUCCESS == status)
                {
                    if (descriptorLength > setupRequestPtr->wLength)
                    {
                        descriptorLength = setupRequestPtr->wLength;
                    }
                    status = USB_TransferControlDataSet(descriptorPtr, descriptorLength, NULL);
                }
            }
            else
            {
                status = UNSUPPORTED;
            }
        }
        if (USB_REQUEST_TYPE_CLASS == (USB_REQUEST_TYPE_t)setupRequestPtr->bmRequestType.type)
        {
            uint8_t reportType = (setupRequestPtr->wValue >> 8) - 1;
            // Requests Class Interface Get
            switch (setupRequestPtr->bRequest)
            {
            case USB_REQ_HID_GET_REPORT:
                if (USB_HID_REPORT_TYPE_INPUT == (USB_HID_REPORT_TYPE_t)reportType)
                {
                    // Answers with a stall condition on control endpoint as input reports are transferred on interrupt endpoint.
                    status = UNSUPPORTED;
                }
                else
                {
                    status = UNSUPPORTED;
                }
                break;
            case USB_REQ_HID_GET_IDLE:
                if (rate != NULL)
                {
                    status = USB_ControlTransferDataWriteBuffer(rate, sizeof(uint8_t));
                }
                else
                {
                    // No pointer to rate, so assume not supported and return 0
                    uint8_t empty_byte = 0;
                    status = USB_ControlTransferDataWriteBuffer(&empty_byte, sizeof(uint8_t));
                }
                break;
            case USB_REQ_HID_GET_PROTOCOL:
                if (protocol != NULL)
                {
                    status = USB_ControlTransferDataWriteBuffer(protocol, sizeof(uint8_t));
                }
                else
                {
                    // No pointer to protocol, so assume not supported and return 0
                    uint8_t empty_byte = 0;
                    status = USB_ControlTransferDataWriteBuffer(&empty_byte, sizeof(uint8_t));
                }
                break;
            default:
                status = UNSUPPORTED;
                break;
            }
        }
    }
    else // USB_REQUEST_DIR_OUT
    {
        if (USB_REQUEST_TYPE_CLASS == (USB_REQUEST_TYPE_t)setupRequestPtr->bmRequestType.type)
        {
            switch (setupRequestPtr->bRequest)
            {
            case USB_REQ_HID_SET_REPORT:
                status = USB_TransferControlDataSet((uint8_t *)&reportData, setupRequestPtr->wLength, NULL);
                if (SUCCESS == status)
                {
                    USB_ControlEndOfRequestCallbackRegister(USB_HIDReportUpdatedCallback);
                }
                else
                {
                    status = UNSUPPORTED;
                }
                break;
            case USB_REQ_HID_SET_IDLE:
                *rate = setupRequestPtr->wValue >> 8;
                status = SUCCESS;
                break;
            case USB_REQ_HID_SET_PROTOCOL:
                if (0 != setupRequestPtr->wLength)
                {
                    status = UNSUPPORTED;
                }
                else
                {
                    *protocol = setupRequestPtr->wValue;
                    status = SUCCESS;
                }
                break;
            default:
                status = UNSUPPORTED;
                break;
            }
        }
    }
    return status;
}

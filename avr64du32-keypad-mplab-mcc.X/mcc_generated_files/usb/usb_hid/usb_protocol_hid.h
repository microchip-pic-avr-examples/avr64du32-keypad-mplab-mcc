/**
 * USBPROTOCOLHID HID Protocols Header File
 * @file usb_protocol_hid.h
 * @ingroup usb_hid
 * @brief USB Human Interface Device (HID) protocol definitions
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

#ifndef USB_PROTOCOL_HID_H
#define USB_PROTOCOL_HID_H

#include <usb_common_elements.h>
#include <usb_config.h>
#include <usb_protocol_headers.h>

/**
 * @ingroup usb_hid
 * @name HID Class Boot type
 * Macros for standard HID subclass types.
 */
///@{
#define HID_SUB_CLASS_NOBOOT 0x00
#define HID_SUB_CLASS_BOOT 0x01
///@}

/**
 * @ingroup usb_hid
 * @name HID Protocol types
 * Macros for standard HID protocol types
 */
///@{
#define HID_PROTOCOL_GENERIC 0x00
#define HID_PROTOCOL_KEYBOARD 0x01
#define HID_PROTOCOL_MOUSE 0x02
///@}

/**
 * @ingroup usb_hid
 * @enum USB_REQUEST_ID_HID_t
 * @brief Type defines for standard HID request types.
 */
typedef enum USB_REQUEST_ID_HID_enum
{
    USB_REQ_HID_GET_REPORT = 0x01,          /**< Request to get the current report from the HID device*/
    USB_REQ_HID_GET_IDLE = 0x02,            /**< Request to get the current idle rate for a particular HID report*/
    USB_REQ_HID_GET_PROTOCOL = 0x03,        /**< Request to get the current protocol in use by the HID device*/
    USB_REQ_HID_SET_REPORT = 0x09,          /**< Request to send a report to the HID device*/
    USB_REQ_HID_SET_IDLE = 0x0A,            /**< Request to set the idle rate for a particular HID report*/
    USB_REQ_HID_SET_PROTOCOL = 0x0B,        /**< Request to set the protocol to be used by the HID device*/
} USB_REQUEST_ID_HID_t;

/**
 * @ingroup usb_hid
 * @enum USB_DESCRIPTOR_TYPE_HID_t
 * @brief Type defines for standard HID descriptor types.
 */
typedef enum USB_DESCRIPTOR_TYPE_HID_enum
{
    USB_DT_HID = 0x21,               /**< Descriptor type for HID class. Used to describe HID device information such as country code and HID class specification release.*/
    USB_DT_HID_REPORT = 0x22,        /**< Descriptor type for HID report. Used to define the data format and the controls used by the HID device. */
    USB_DT_HID_PHYSICAL = 0x23,      /**< Descriptor type for HID physical descriptors (optional). Used to describe the physical characteristics of a device.*/
} USB_DESCRIPTOR_TYPE_HID_t;

/**
 * @ingroup usb_hid
 * @enum USB_HID_ITEM_REPORT_TYPE_t
 * @brief Type defines for standard HID item report types.
 */
typedef enum USB_HID_ITEM_REPORT_TYPE_enum
{
    USB_HID_ITEM_REPORT_TYPE_MAIN = 0,   /**< Main items are used to define the data fields in HID reports, such as Input, Output and Feature reports*/
    USB_HID_ITEM_REPORT_TYPE_GLOBAL = 1, /**< Global items apply to all the subsequent items in the report descriptor and define characteristics such as usage page, logical minimum, logical maximum, etc*/
    USB_HID_ITEM_REPORT_TYPE_LOCAL = 2,  /**< Local items define characteristics that are specific to a particular item, such as usage or designator index*/
    USB_HID_ITEM_REPORT_TYPE_LONG = 3,   /**< Long items are not commonly used but are available for future expansion and allow for extended data fields that are not defined by the standard HID item types*/
} USB_HID_ITEM_REPORT_TYPE_t;

/**
 * @ingroup usb_hid
 * @enum USB_HID_REPORT_TYPE_t
 * @brief Type defines for standard HID report types.
 */
typedef enum USB_HID_REPORT_TYPE_enum
{
    USB_HID_REPORT_TYPE_INPUT = 1,   /**< Input reports are sent by the HID device to the host to report the state of the input controls*/
    USB_HID_REPORT_TYPE_OUTPUT = 2,  /**< Output reports are sent by the host to the HID device to control the state of the output controls*/
    USB_HID_REPORT_TYPE_FEATURE = 3, /**< Feature reports are used to exchange feature data between the host and the HID device that may not be directly tied to input or output, such as configuration data*/
} USB_HID_REPORT_TYPE_t;

/**
 * @ingroup usb_hid
 * @enum USB_HID_PROTOCOL_t
 * @brief Type defines for standard HID protocols.
 */
typedef enum USB_HID_PROTOCOL_enum
{
    USB_HID_PROTOCOL_BOOT = 0,    /**< Boot protocol is a simplified protocol that supports a limited set of HID devices*/
    USB_HID_PROTOCOL_REPORT = 1,  /**< Report protocol provides a more complex and feature-rich means of communication between the HID device and the host*/
} USB_HID_PROTOCOL_t;

/**
 * @ingroup usb_hid
 * @struct USB_HID_DESCRIPTOR_t
 * @brief Type defines for a standard HID descriptor.
 */
typedef struct
{
    USB_DESCRIPTOR_HEADER_t header; /**< Descriptor type and size*/
    uint16_t bcdHID;                /**< Binary Coded Decimal Spec. release*/
    uint8_t bCountryCode;           /**< Hardware target country*/
    uint8_t bNumDescriptors;        /**< Number of HID class descriptors to follow*/
    uint8_t bRDescriptorType;       /**< Report descriptor type*/
    uint16_t wDescriptorLength;     /**< Total length of the Report descriptor*/
} USB_HID_DESCRIPTOR_t;

/**
 * @ingroup usb_hid
 * @struct USB_HID_REPORT_DESCRIPTOR_t
 * @brief Report descriptor for a HID application.
 */
typedef struct
{
    uint8_t array[USB_HID_REPORT_DESCRIPTOR_SIZE];
} USB_HID_REPORT_DESCRIPTOR_t;

/**
 * @ingroup usb_hid
 * @struct USB_MOUSE_REPORT_DATA_t
 * @brief Type defines for a standard mouse input report.
 */
typedef struct
{
    uint8_t Button; /**< Button mask for currently pressed buttons in the mouse*/
    int8_t X;       /**< Current delta X movement of the mouse*/
    int8_t Y;       /**< Current delta Y movement of the mouse*/
} USB_MOUSE_REPORT_DATA_t;

/**
 * @ingroup usb_hid
 * @struct USB_KEYBOARD_REPORT_DATA_t
 * @brief Type defines for a standard keyboard input report.
 */
typedef struct
{
    uint8_t Modifier;   /**< Keyboard modifier byte*/
    uint8_t Reserved;   /**< Reserved for OEM use, always set to 0*/
    uint8_t KeyCode[6]; /**< Key codes of the currently pressed keys*/
} USB_KEYBOARD_REPORT_DATA_t;

/**
 * @ingroup usb_hid
 * @brief Defines a type for registering a callback for the HID report.
 */
typedef void (*USB_HID_REPORT_CALLBACK_t)(uint16_t report);

/**
 * @ingroup usb_hid
 * @name USB descriptor codes
 * Macros used for USB descriptors.
 */
///@{
#define USB_HID_BCD_V1_11 0x0111
#define USB_HID_NUM_DESC 0x01
///@}

/**
 * @ingroup usb_hid
 * @name HID Country codes
 * Macros for country codes.
 */
///@{
#define USB_HID_NO_COUNTRY_CODE 0            // Not Supported
#define USB_HID_COUNTRY_ARABIC 1             // Arabic
#define USB_HID_COUNTRY_BELGIAN 2            // Belgian
#define USB_HID_COUNTRY_CANADIAN_BILINGUAL 3 // Canadian-Bilingual
#define USB_HID_COUNTRY_CANADIAN_FRENCH 4    // Canadian-French
#define USB_HID_COUNTRY_CZECH_REPUBLIC 5     // Czech Republic
#define USB_HID_COUNTRY_DANISH 6             // Danish
#define USB_HID_COUNTRY_FINNISH 7            // Finnish
#define USB_HID_COUNTRY_FRENCH 8             // French
#define USB_HID_COUNTRY_GERMAN 9             // German
#define USB_HID_COUNTRY_GREEK 10             // Greek
#define USB_HID_COUNTRY_HEBREW 11            // Hebrew
#define USB_HID_COUNTRY_HUNGARY 12           // Hungary
#define USB_HID_COUNTRY_INTERNATIONAL_ISO 13 // International (ISO)
#define USB_HID_COUNTRY_ITALIAN 14           // Italian
#define USB_HID_COUNTRY_JAPAN_KATAKANA 15    // Japan (Katakana)
#define USB_HID_COUNTRY_KOREAN 16            // Korean
#define USB_HID_COUNTRY_LATIN_AMERICAN 17    // Latin American
#define USB_HID_COUNTRY_NETHERLANDS_DUTCH 18 // Netherlands/Dutch
#define USB_HID_COUNTRY_NORWEGIAN 19         // Norwegian
#define USB_HID_COUNTRY_PERSIAN_FARSI 20     // Persian (Farsi)
#define USB_HID_COUNTRY_POLAND 21            // Poland
#define USB_HID_COUNTRY_PORTUGUESE 22        // Portuguese
#define USB_HID_COUNTRY_RUSSIA 23            // Russia
#define USB_HID_COUNTRY_SLOVAKIA 24          // Slovakia
#define USB_HID_COUNTRY_SPANISH 25           // Spanish
#define USB_HID_COUNTRY_SWEDISH 26           // Swedish
#define USB_HID_COUNTRY_SWISS_FRENCH 27      // Swiss/French
#define USB_HID_COUNTRY_SWISS_GERMAN 28      // Swiss/German
#define USB_HID_COUNTRY_SWITZERLAND 29       // Switzerland
#define USB_HID_COUNTRY_TAIWAN 30            // Taiwan
#define USB_HID_COUNTRY_TURKISH_Q 31         // Turkish-Q
#define USB_HID_COUNTRY_UK 32                // UK
#define USB_HID_COUNTRY_US 33                // US
#define USB_HID_COUNTRY_YUGOSLAVIA 34        // Yugoslavia
#define USB_HID_COUNTRY_TURKISH_F 35         // Turkish-F
///@}

/**
 * @}
 */

#endif // _USB_PROTOCOL_HID_H_

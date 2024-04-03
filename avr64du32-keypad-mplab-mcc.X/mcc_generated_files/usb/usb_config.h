/**
 * USB_CONFIG Generated Config Header File
 * 
 * @file usb_config.h
 * 
 * @defgroup usb_device_stack USB_DEVICE_STACK
 * 
 * @brief This is a device-specific USB static configuration file that will be editable 
 * through a code composer tool, build script or manual entry by a user.  
 * 
 * The file encompasses static settings like number of endpoints, features to be enabled, etc.
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

#ifndef USB_CONFIG_H
#define USB_CONFIG_H

#include <stdint.h>
#include <usb_common_elements.h>

/**
 * @ingroup usb_device_stack
 * @def USB_EP_NUM
 * @brief Limits the size of the endpoint table and transfer array in the RAM 
 * to 1 + the highest endpoint address used by the application.
 */
#define USB_EP_NUM 2U 

/**
 * @ingroup usb_device_stack
 * @def USB_EP0_SIZE
 * @brief Controls the packet size of endpoint 0 and must correspond to bMaxPacketSize0 in the device descriptor.
 */
#define USB_EP0_SIZE 64U

/**
 * @ingroup usb_device_stack
 * @def LANG_ID_NUM
 * @brief Controls the number of language IDs supported by the application.
 */
#define LANG_ID_NUM 1U

/**
 * @ingroup usb_device_stack
 * @name USB Endpoint Addresses
 * Macros for the endpoint addresses.
 */
///@{
#define INTERFACE0ALTERNATE0_INTERRUPT_EP1_IN 1U
///@}

/**
 * @ingroup usb_device_stack
 * @name USB Endpoint Packet Sizes
 * Macros for the endpoint packet sizes.
 */
///@{
#define INTERFACE0ALTERNATE0_INTERRUPT_EP1_IN_SIZE 64U
///@}

/**
 * @ingroup usb_device_stack
 * @def USB_HID_INTERRUPT_EP
 * @brief Macro for the interrupt endpoint
 */
#define USB_HID_INTERRUPT_EP INTERFACE0ALTERNATE0_INTERRUPT_EP1_IN

/**
 * @ingroup usb_device_stack
 * @def USB_HID_REPORT_DESCRIPTOR_SIZE
 * @brief Macro for the Human Interface Devices (HID) report descriptor size
 */
#define USB_HID_REPORT_DESCRIPTOR_SIZE 59U

/**
 * @ingroup usb_device_stack
 * @def USB_INTERFACE_NUM
 * @brief The number of interfaces used by a configuration, excluding alternate interfaces.
 */
#define USB_INTERFACE_NUM 1U

/**
 * @ingroup usb_device_stack
 * @struct USB_EP_STATIC_CONFIG_BITS_struct
 * @brief Static endpoint settings.
 */
typedef struct USB_EP_STATIC_CONFIG_BITS_struct
{
    uint8_t InMultipktEnable : 1;
    uint8_t InAzlpEnable : 1;
    uint8_t InTrncInterruptEnable : 1;
    uint8_t OutMultipktEnable : 1;
    uint8_t OutAzlpEnable : 1;
    uint8_t OutTrncInterruptEnable : 1;
    uint8_t reserved : 2;
} USB_EP_STATIC_CONFIG_BITS_t;

/**
 * @ingroup usb_device_stack
 * @struct endpointStaticConfig
 * @brief Configuration of static endpoint settings.
 */
static const USB_EP_STATIC_CONFIG_BITS_t endpointStaticConfig [USB_EP_NUM] = {
    [0] = {.InTrncInterruptEnable = 1, .OutTrncInterruptEnable = 1, .InMultipktEnable = 1, .InAzlpEnable = 0, .OutMultipktEnable = 1, .OutAzlpEnable = 0},
    [1] = {.InTrncInterruptEnable = 1, .OutTrncInterruptEnable = 1, .InMultipktEnable = 0, .InAzlpEnable = 0},
};

#endif // USB_CONFIG_H
/**
 End of File
*/

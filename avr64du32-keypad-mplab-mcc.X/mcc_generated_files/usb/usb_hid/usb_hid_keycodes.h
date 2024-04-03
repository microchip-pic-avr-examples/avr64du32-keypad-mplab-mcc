/**
 * USBHIDKEYCODES HID Keycodes Header File
 * @file usb_hid_keycodes.h
 * @ingroup usb_hid
 * @brief USB Human Interface Device (HID) keycode definitions
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

#ifndef USB_HID_KEYCODES_H
#define USB_HID_KEYCODES_H

/**
 * @ingroup usb_hid
 * @name HID keyboard key codes
 * Macros for the key codes used in HID applications
 */
///@{
#define HID_KEYID_NOT_FOUND (-1)
#define HID_KEY_NONE 0x00
#define HID_ERROR_ROLLOVER 0x01
#define HID_POST_FAIL 0x02
#define HID_ERROR_UNDEFINED 0x03

#define HID_A 0x04
#define HID_B 0x05
#define HID_C 0x06
#define HID_D 0x07
#define HID_E 0x08
#define HID_F 0x09
#define HID_G 0x0A
#define HID_H 0x0B
#define HID_I 0x0C
#define HID_J 0x0D
#define HID_K 0x0E
#define HID_L 0x0F
#define HID_M 0x10
#define HID_N 0x11
#define HID_O 0x12
#define HID_P 0x13
#define HID_Q 0x14
#define HID_R 0x15
#define HID_S 0x16
#define HID_T 0x17
#define HID_U 0x18
#define HID_V 0x19
#define HID_W 0x1A
#define HID_X 0x1B
#define HID_Y 0x1C
#define HID_Z 0x1D

#define HID_1 0x1E
#define HID_2 0x1F
#define HID_3 0x20
#define HID_4 0x21
#define HID_5 0x22
#define HID_6 0x23
#define HID_7 0x24
#define HID_8 0x25
#define HID_9 0x26
#define HID_0 0x27

#define HID_RETURN 0x28
#define HID_ESCAPE 0x29
#define HID_BACKSPACE 0x2A
#define HID_TAB 0x2B
#define HID_SPACEBAR 0x2C
#define HID_UNDERSCORE 0x2D
#define HID_EQUAL 0x2E
#define HID_OPEN_BRACE 0x2F  // [ and {
#define HID_CLOSE_BRACE 0x30 // ] and }
#define HID_BACKSLASH 0x31
#define HID_HASH_TILDE 0x32 // # and ~
#define HID_SEMICOLON 0x33  // ; and :
#define HID_APOSTROPHE 0x34 // ' and "
#define HID_GRAVE_TILDE 0x35
#define HID_COMMA 0x36
#define HID_DOT 0x37
#define HID_SLASH 0x38
#define HID_CAPS_LOCK 0x39

#define HID_F1 0x3A
#define HID_F2 0x3B
#define HID_F3 0x3C
#define HID_F4 0x3D
#define HID_F5 0x3E
#define HID_F6 0x3F
#define HID_F7 0x40
#define HID_F8 0x41
#define HID_F9 0x42
#define HID_F10 0x43
#define HID_F11 0x44
#define HID_F12 0x45
#define HID_F13 0x68
#define HID_F14 0x69
#define HID_F15 0x6A
#define HID_F16 0x6B
#define HID_F17 0x6C
#define HID_F18 0x6D
#define HID_F19 0x6E
#define HID_F20 0x6F
#define HID_F21 0x70
#define HID_F22 0x71
#define HID_F23 0x72
#define HID_F24 0x73

#define HID_PRINTSCREEN 0x46
#define HID_SCROLL_LOCK 0x47
#define HID_PAUSE 0x48
#define HID_INSERT 0x49
#define HID_HOME 0x4A
#define HID_PAGEUP 0x4B
#define HID_DELETE 0x4C
#define HID_END 0x4D
#define HID_PAGEDOWN 0x4E
#define HID_RIGHT 0x4F
#define HID_LEFT 0x50
#define HID_DOWN 0x51
#define HID_UP 0x52

#define HID_KEYPAD_NUM_LOCK 0x53
#define HID_KEYPAD_SLASH 0x54
#define HID_KEYPAD_ASTERISK 0x55
#define HID_KEYPAD_MINUS 0x56
#define HID_KEYPAD_PLUS 0x57
#define HID_KEYPAD_ENTER 0x58
#define HID_KEYPAD_1 0x59
#define HID_KEYPAD_2 0x5A
#define HID_KEYPAD_3 0x5B
#define HID_KEYPAD_4 0x5C
#define HID_KEYPAD_5 0x5D
#define HID_KEYPAD_6 0x5E
#define HID_KEYPAD_7 0x5F
#define HID_KEYPAD_8 0x60
#define HID_KEYPAD_9 0x61
#define HID_KEYPAD_0 0x62
#define HID_KEYPAD_DOT 0x63
#define HID_KEYPAD_EQUAL 0x67
#define HID_KEYPAD_COMMA 0x85
#define HID_KEYPAD_EQUALSIGN 0x86
#define HID_KEYPAD_00 0xB0
#define HID_KEYPAD_000 0xB1
#define HID_KEYPAD_LEFT_PARENTHESIS 0xB6
#define HID_KEYPAD_RIGHT_PARENTHESIS 0xB7
#define HID_KEYPAD_OPEN_BRACE 0xB8
#define HID_KEYPAD_CLOSE_BRACE 0xB9
#define HID_KEYPAD_TAB 0xBA
#define HID_KEYPAD_BACKSPACE 0xBB
#define HID_KEYPAD_A 0xBC
#define HID_KEYPAD_B 0xBD
#define HID_KEYPAD_C 0xBE
#define HID_KEYPAD_D 0xBF
#define HID_KEYPAD_E 0xC0
#define HID_KEYPAD_F 0xC1
#define HID_KEYPAD_XOR 0xC2
#define HID_KEYPAD_POWER_TO 0xC3
#define HID_KEYPAD_PERCENT 0xC4
#define HID_KEYPAD_LEFT_ANGLE_BRACE 0xC5
#define HID_KEYPAD_RIGHT_ANGLE_BRACE 0xC6
#define HID_KEYPAD_AND 0xC7
#define HID_KEYPAD_AND_AND 0xC8
#define HID_KEYPAD_OR 0xC9
#define HID_KEYPAD_OR_OR 0xCA
#define HID_KEYPAD_COLON 0xCB
#define HID_KEYPAD_HASH 0xCC
#define HID_KEYPAD_SPACE 0xCD
#define HID_KEYPAD_AT 0xCE
#define HID_KEYPAD_EXCLAMATION 0xCF
#define HID_KEYPAD_MEM_STORE 0xD0
#define HID_KEYPAD_MEM_RECALL 0xD1
#define HID_KEYPAD_MEM_CLEAR 0xD2
#define HID_KEYPAD_MEM_ADD 0xD3
#define HID_KEYPAD_MEM_SUBTRACT 0xD4
#define HID_KEYPAD_MEM_MULTIPLY 0xD5
#define HID_KEYPAD_MEM_DIVIDE 0xD6
#define HID_KEYPAD_PLUS_MINUS 0xD7
#define HID_KEYPAD_CLEAR 0xD8
#define HID_KEYPAD_CLEAR_ENTRY 0xD9
#define HID_KEYPAD_BINARY 0xDA
#define HID_KEYPAD_OCTAL 0xDB
#define HID_KEYPAD_DECIMAL 0xDC
#define HID_KEYPAD_HEXADECIMAL 0xDD

#define HID_AT102 0x64 // Keyboard Non-US \ and | or < and >
#define HID_APPLICATION 0x65
#define HID_POWER 0x66

#define HID_EXECUTE 0x74
#define HID_HELP 0x75
#define HID_MENU 0x76
#define HID_SELECT 0x77
#define HID_STOP 0x78
#define HID_AGAIN 0x79
#define HID_UNDO 0x7A
#define HID_CUT 0x7B
#define HID_COPY 0x7C
#define HID_PASTE 0x7D
#define HID_FIND 0x7E
#define HID_MUTE 0x7F
#define HID_VOLUME_UP 0x80
#define HID_VOLUME_DOWN 0x81

#define HID_LOCK_CAPS_LOCK 0x82
#define HID_LOCK_NUM_LOCK 0x83
#define HID_LOCK_SCROLL_LOCK 0x84

#define HID_INTERNATIONAL_1 0x87
#define HID_INTERNATIONAL_2 0x88
#define HID_INTERNATIONAL_3 0x89
#define HID_INTERNATIONAL_4 0x8A
#define HID_INTERNATIONAL_5 0x8B
#define HID_INTERNATIONAL_6 0x8C
#define HID_INTERNATIONAL_7 0x8D
#define HID_INTERNATIONAL_8 0x8E
#define HID_INTERNATIONAL_9 0x8F

#define HID_LANG_1 0x90
#define HID_LANG_2 0x91
#define HID_LANG_3 0x92
#define HID_LANG_4 0x93
#define HID_LANG_5 0x94
#define HID_LANG_6 0x95
#define HID_LANG_7 0x96
#define HID_LANG_8 0x97
#define HID_LANG_9 0x98

#define HID_KB_ALT_ERASE 0x99
#define HID_KB_SYSREQ 0x9A
#define HID_KB_CANCEL 0x9B
#define HID_KB_CLEAR 0x9C
#define HID_KB_PRIOR 0x9D
#define HID_KB_RETURN 0x9E
#define HID_KB_SEPARATOR 0x9F
#define HID_KB_OUT 0xA0
#define HID_KB_OPER 0xA1
#define HID_KB_CLEAR_AGAIN 0xA2
#define HID_KB_CRSEL 0xA3
#define HID_KB_EXSEL 0xA4

#define HID_1K_SEPARATOR 0xB2
#define HID_DECIMAL_SEPARATOR 0xB3
#define HID_CURRENCY_UNIT 0xB4
#define HID_CURRENCY_SUB_UNIT 0xB5

#define HID_LEFT_CTRL 0xE0
#define HID_LEFT_SHIFT 0xE1
#define HID_LEFT_ALT 0xE2
#define HID_LEFT_GUI 0xE3
#define HID_RIGHT_CTRL 0xE4
#define HID_RIGHT_SHIFT 0xE5
#define HID_RIGHT_ALT 0xE6
#define HID_RIGHT_GUI 0xE7

#define HID_MEDIA_PLAYPAUSE 0xE8
#define HID_MEDIA_STOPCD 0xE9
#define HID_MEDIA_PREVIOUSSONG 0xEA
#define HID_MEDIA_NEXTSONG 0xEB
#define HID_MEDIA_EJECTCD 0xEC
#define HID_MEDIA_VOLUMEUP 0xED
#define HID_MEDIA_VOLUMEDOWN 0xEE
#define HID_MEDIA_MUTE 0xEF
#define HID_MEDIA_WWW 0xF0
#define HID_MEDIA_BACK 0xF1
#define HID_MEDIA_FORWARD 0xF2
#define HID_MEDIA_STOP 0xF3
#define HID_MEDIA_FIND 0xF4
#define HID_MEDIA_SCROLLUP 0xF5
#define HID_MEDIA_SCROLLDOWN 0xF6
#define HID_MEDIA_EDIT 0xF7
#define HID_MEDIA_SLEEP 0xF8
#define HID_MEDIA_COFFEE 0xF9
#define HID_MEDIA_REFRESH 0xFA
#define HID_MEDIA_CALC 0xFB

///@}

/**
 * @ingroup usb_hid
 * @name HID modifier key codes
 * Macros for the modifier keys
 */
///@{
#define HID_MODIFIER_NONE 0x00
#define HID_MODIFIER_LEFT_CTRL 0x01
#define HID_MODIFIER_LEFT_SHIFT 0x02
#define HID_MODIFIER_LEFT_ALT 0x04
#define HID_MODIFIER_LEFT_UI 0x08
#define HID_MODIFIER_RIGHT_CTRL 0x10
#define HID_MODIFIER_RIGHT_SHIFT 0x20
#define HID_MODIFIER_RIGHT_ALT 0x40
#define HID_MODIFIER_RIGHT_UI 0x80
///@}

/**
 * @ingroup usb_hid
 * @name HID LED codes
 * Macros for the LEDs
 */
///@{
#define HID_LED_NUM_LOCK (1 << 0)
#define HID_LED_CAPS_LOCK (1 << 1)
#define HID_LED_SCROLL_LOCK (1 << 2)
#define HID_LED_COMPOSE (1 << 3)
#define HID_LED_KANA (1 << 4)
///@}

/**
 * @}
 */

#endif // USB_HID_KEYCODES_H
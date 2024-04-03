#include "KeyReporting.h"


#include "mcc_generated_files/usb/usb_hid/usb_hid_keyboard.h"
#include "usb_hid_keycodes.h"

//Clear / Initialize a keyReport
void KeyReport_clearReport(USB_KEYBOARD_REPORT_DATA_t* keyReport)
{
    //Init key report
    for (uint8_t i = 0; i < USB_HID_KEYBOARD_REPORT_KEYNUM; i++)
    {
        (*keyReport).KeyCode[i] = HID_KEY_NONE;
    }
    (*keyReport).Modifier = HID_MODIFIER_NONE;
}

//Converts an alphanumeric letter into the appropriate HID code
void KeyReport_convertCharToCode(char c, uint8_t* code, uint8_t* mod)
{    
    //Capital Letter - convert to lowercase
    if ((c >= 'A') && (c <= 'Z'))
    {
        c = (c - 'A') + 'a';
        *mod = HID_MODIFIER_LEFT_SHIFT;
    }
    else
    {
        *mod = HID_MODIFIER_NONE;
    }
    
    if ((c >= 'a') && (c <= 'z'))
    {
        //A-Z
        *code = HID_A + (c - 'a');
    }
    else if ((c >= '0') && (c <= '9'))
    {
        //0-9
        if (c == '0')
        {
            //'0' breaks pattern
            *code = HID_0;
        }
        else
        {
            *code = HID_1 + (c - '1');
        }
    }
    else
    {
        switch (c)
        {
            case ' ':
                *code = HID_SPACEBAR;
                break;
            case '_': //SHIFT +
                *mod = HID_MODIFIER_LEFT_SHIFT;
            case '-':
                *code = HID_UNDERSCORE;
                break;
            case '+': //SHIFT + 
                *mod = HID_MODIFIER_LEFT_SHIFT;
            case '=':
                *code = HID_EQUAL;
                break;
            case '{': //SHIFT + 
                *mod = HID_MODIFIER_LEFT_SHIFT;
            case '[':
                *code = HID_OPEN_BRACE;
                break;
            case '}': //SHIFT + 
                *mod = HID_MODIFIER_LEFT_SHIFT;
            case ']':
                *code = HID_CLOSE_BRACE;
                break;
            case '|': //SHIFT +
                    *mod = HID_MODIFIER_LEFT_SHIFT;
            case '\\':
                *code = HID_BACKSLASH;
                break;
            case ':': //SHIFT +
                *mod = HID_MODIFIER_LEFT_SHIFT;
            case ';':
                *code = HID_SEMICOLON;
                break;
            case '"': //SHIFT +
                *mod = HID_MODIFIER_LEFT_SHIFT;
            case '\'':
                *code = HID_APOSTROPHE;
                break;
            case '~': //SHIFT + 
                *mod = HID_MODIFIER_LEFT_SHIFT;
            case '`':
                *code = HID_GRAVE_TILDE;
                break;
            case '<': //SHIFT +
                *mod = HID_MODIFIER_LEFT_SHIFT;
            case ',':
                *code = HID_COMMA;
                break;
            case '>': //SHIFT +
                *mod = HID_MODIFIER_LEFT_SHIFT;
            case '.':
                *code = HID_DOT;
                break;
            case '?': //SHIFT +
                *mod = HID_MODIFIER_LEFT_SHIFT;
                break;
            case '/':
                *code = HID_SLASH;
                break;
                
            //Start Number Row
            case '!': 
                *mod = HID_MODIFIER_LEFT_SHIFT;
                *code = HID_1;
                break;
            case '@': 
                *mod = HID_MODIFIER_LEFT_SHIFT;
                *code = HID_2;
                break;
            case '#': 
                *mod = HID_MODIFIER_LEFT_SHIFT;
                *code = HID_3;
                break;
            case '$': 
                *mod = HID_MODIFIER_LEFT_SHIFT;
                *code = HID_4;
                break;
            case '%':
                *mod = HID_MODIFIER_LEFT_SHIFT;
                *code = HID_5;
                break;
            case '^': 
                *mod = HID_MODIFIER_LEFT_SHIFT;
                *code = HID_6;
                break;
            case '&': 
                *mod = HID_MODIFIER_LEFT_SHIFT;
                *code = HID_7;
                break;
            case '*': 
                *mod = HID_MODIFIER_LEFT_SHIFT;
                *code = HID_8;
                break;
            case '(': 
                *mod = HID_MODIFIER_LEFT_SHIFT;
                *code = HID_9;
                break;
            case ')': 
                *mod = HID_MODIFIER_LEFT_SHIFT;
                *code = HID_0;
                break;
                
            //Unknown Key
            default:
                *code = HID_KEYID_NOT_FOUND;
        }
    }
}

//Search the keyReport for an entry of hid, and returns the index in the array
//If not found, returns UINT8_MAX
uint8_t KeyReport_getKeyIndex(USB_KEYBOARD_REPORT_DATA_t* keyReport, uint8_t hid)
{
    for (uint8_t i = 0; i < USB_HID_KEYBOARD_REPORT_KEYNUM; i++)
    {
        if ((*keyReport).KeyCode[i] == hid)
        {
            return i;
        }
    }
    
    return UINT8_MAX;
}

//Register a "key down" event for c
void KeyReport_registerKeyDown(USB_KEYBOARD_REPORT_DATA_t* keyReport, char c)
{
    uint8_t key, mod;
    KeyReport_convertCharToCode(c, &key, &mod);
    
    uint8_t index = KeyReport_getKeyIndex(keyReport, key);
    
    if (index == UINT8_MAX)
    {
        //Not in array - do we have space?
        
        index = KeyReport_getKeyIndex(keyReport, HID_KEY_NONE);
        if (index == UINT8_MAX)
        {
            //No space in array!
            return;
        }
    }
    
    (*keyReport).Modifier = mod;
    (*keyReport).KeyCode[index] = key;
    
}

//Register a "key up" event for c
void KeyReport_registerKeyUp(USB_KEYBOARD_REPORT_DATA_t* keyReport, char c)
{
    uint8_t key, mod;
    KeyReport_convertCharToCode(c, &key, &mod);
    
    uint8_t index = KeyReport_getKeyIndex(keyReport, key);
    
    //Not in array
    if (index == UINT8_MAX)
    {
        return;
    }
    
    if (mod != HID_MODIFIER_NONE)
    {
        (*keyReport).Modifier = HID_MODIFIER_NONE;
    }
    (*keyReport).KeyCode[index] = HID_KEY_NONE;
}

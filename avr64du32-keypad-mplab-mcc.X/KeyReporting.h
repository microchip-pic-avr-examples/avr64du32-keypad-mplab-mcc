#ifndef KEYREPORTING_H
#define	KEYREPORTING_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
#include "mcc_generated_files/usb/usb_hid/usb_protocol_hid.h"
    
    //Clear / Initialize a keyReport
    void KeyReport_clearReport(USB_KEYBOARD_REPORT_DATA_t* keyReport);

    //Converts an alphanumeric letter into the appropriate HID code
    void KeyReport_convertCharToCode(char c, uint8_t* code, uint8_t* mod);
    
    //Search the keyReport for an entry of hid, and returns the index in the array
    //If not found, returns UINT8_MAX
    uint8_t KeyReport_getKeyIndex(USB_KEYBOARD_REPORT_DATA_t* keyReport, uint8_t hid);
    
    //Register a "key down" event for c
    void KeyReport_addKeyDownEventFromChar(USB_KEYBOARD_REPORT_DATA_t* keyReport, char c);
    
    //Register a "key down" event
    void KeyReport_addKeyDownEvent(USB_KEYBOARD_REPORT_DATA_t* keyReport, uint8_t mod, uint8_t key);
    
    //Clear a "key down" event
    void KeyReport_clearKeyDownEventFromChar(USB_KEYBOARD_REPORT_DATA_t* keyReport, char c);
    
    //Clear the "key down" event
    void KeyReport_clearKeyDownEvent(USB_KEYBOARD_REPORT_DATA_t* keyReport, uint8_t mod, uint8_t key);
    
#ifdef	__cplusplus
}
#endif

#endif	/* KEYREPORTING_H */


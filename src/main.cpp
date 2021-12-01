#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "Communication/IRCommunication.h"

int main()
{
    initIRCommunication(38);

    while(true) {

    }

    return(0);
    // Super loop to check button state and display counter
}

#include <p32xxxx.h>
#include <xc.h>

// **** CHANGE NOTIFICATION INTERRUPTIONS ****
/* CN3 pin 15*/
    /*TRISDbits.TRISD4 = 1; // input mode
    CNENbits.CNEN13 = 1;    // Enable CN3 pin for Change Notice functionality

    CNCONbits.ON = 1; // Activer les interruptions CN globalement

    IPC6bits.CNIP = 7; // priorite interruptions CN
    IPC6bits.CNIS = 5; // sub-prio inter. CN
    IFS1bits.CNIF = 0; // Flag inter. CN
    IEC1bits.CNIE = 1; // Enable CN*/

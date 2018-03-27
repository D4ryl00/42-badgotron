/*
** main.c
**
** Project: 	interrupt-example
**
** Date:    	04/06/2015
** Revision:
** Author:  	DC
**
** Comments:    Timer 2-driven ISR used to toggle LED LD6 every 100mS
**
** Hardware Design Reference:
**  "chipKIT WF32 Rev B.0"
**
** Dependencies:
** 
**
** User Guide:
**
**
*/

/************************************************************************

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP TECHNOLOGY INC OR ITS LICENSORS BE LIABLE OR OBLIGATED
UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY,
OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

**************************************************************************/

/** INCLUDES ******************************************************************/

#include <xc.h>             /* contains Vector Name/Number Macros */
#include <sys/attribs.h>    /* contains __ISR() Macros */

/** CONFIGURATION *************************************************************/

// Key Settings:
// OSCILLATOR: 8MHz XT Oscillator w. PLL
// SYSCLK = 80 MHz (set in config bits), PBCLK = 10 MHz (= SYSCLK/8 - set in config bits))
// JTAG PORT: Disabled
// WATCHDOG TIMER: Disabled
// DEBUG/PGM PINS: PGEC2/PGED2

// DEVCFG3
// USERID = No Setting
#pragma config FSRSSEL = PRIORITY_7     // SRS Select (SRS Priority 7)
#pragma config FMIIEN = ON              // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config FUSBIDIO = ON            // USB USID Selection (Controlled by the USB Module)
#pragma config FVBUSONIO = ON           // USB VBUS ON Selection (Controlled by USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config UPLLIDIV = DIV_12        // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc (XT,HS,EC) w. PLL)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = XT             // Primary Oscillator Configuration (XT osc mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)


/** VARIABLES *****************************************************************/


/** LOCAL MACROS **************************************************************/

#define SYS_CLK_FREQUENCY  (80000000ull)       // Fsys = 80 MHz
#define PB3_CLK_FREQUENCY SYS_CLK_FREQUENCY/8   // Fpb = 10 MHz

// LED_LD6 (RG6)
#define LED_LD6       	LATFbits.LATF1
#define TRIS_LED_LD6  	TRISFbits.TRISF1
#define LED_LD6_SET()   LATGSET = _LATF_LATF1_MASK;
#define LED_LD6_CLR()   LATGCLR = _LATF_LATF1_MASK;
#define LED_LD6_INV()   LATGINV = _LATF_LATF1_MASK;

/** LOCAL PROTOTYPES ********************************************************/

void InitializeSystem(void);            // Initialize hardware and global variables

/** main() ********************************************************************/

int main(void)
{
    InitializeSystem();

    while(1);
    
} // main()

/******************************************************************************
 * Function:        void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine takes care of all of the system
 *                  initialization that is required.
 *
 * Note:
 *
 *****************************************************************************/
void InitializeSystem(void)
{
    // PIC32MX CPU Speed Optimizations (Cache/Wait States/Peripheral Bus Clks)
    // On reset, and after c-startup:
    // - Prefetch Buffer is disabled,
    // - I Cache is disabled,
    // - PFM wait States set to max setting (7 = too slow!!!)
    // - Data Memory SRAM wait states set to max setting (1 = too slow!!!)
    
    // PBCLK - already set to SYSCLK/8 via config settings
    
    // Data Memory SRAM wait states: Default Setting = 1; set it to 0
    BMXCONbits.BMXWSDRM = 0;

    // Flash PM Wait States: MX Flash runs at 2 wait states @ 80 MHz
    CHECONbits.PFMWS = 2;

    // Prefetch-cache: Enable prefetch for cacheable PFM instructions
    CHECONbits.PREFEN = 1;

    // PIC32MX695-Specific
    // JTAG: Disable on PORTA
    DDPCONbits.JTAGEN = 0;
    
    /* Initialize LED LD6 */
    LED_LD6 = 0;
    TRIS_LED_LD6 = 0;

    /* Initialize Timer 2 Peripheral Settings */
    // Turn off the timer
    T2CONbits.TON = 0;
    // Pre-Scale = 1:256 (T2Clk: 39062.5Hz)
    T2CONbits.TCKPS = 7;
    // Set T2 period ~ 100mS
    PR2 = 39062;
    // Clear counter
    TMR2 = 0;

    /* Initialize Timer 2 Interrupt Controller Settings */
    // Set the interrupt priority to 4
    IPC2bits.T2IP = 7;
    // Reset the Timer 2 interrupt flag
    IFS0bits.T2IF = 0;
    // Enable interrupts from Timer 2
    IEC0bits.T2IE = 1;
  
    /* Set Interrupt Controller for multi-vector mode */
    INTCONSET = _INTCON_MVEC_MASK;

    /* Enable Interrupt Exceptions */
    // set the CP0 status IE bit high to turn on interrupts globally
    __builtin_enable_interrupts();

    /* Enable the peripheral */
    T2CONbits.TON = 1;

} // InitializeSystem()

/*****************************************************************************
  Function:
	void __ISR(_TIMER_2_VECTOR, IPL4SRS) T2Interrupt(void);

  Description:
	Toggles LED LD1 when the Timer 2 interrupt occurs.

  Precondition:
        Peripheral interrupt config must set to matching ISR's IPL 

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/

void __ISR (_TIMER_2_VECTOR, IPL7SRS) T2Interrupt(void)
{
	// Toggle LED LD1
	LED_LD6_INV();

	// Reset interrupt flag
	IFS0bits.T2IF = 0;
}

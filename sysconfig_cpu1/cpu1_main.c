//
// Included Files
//
// Make sure to include "board.h" to use SysConfig
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

uint16_t CPU1HB;
//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Boot CPU2 core
    //
    Device_bootCPU2(BOOT_MODE_CPU2);

    //
    // ASR v0.1 architecture keeps CM disabled.
    //

    //
    // Initialize GPIO
    //
    Device_initGPIO();

    //
    // Initialize settings from SysConfig
    //
    Board_init();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop Forever
    //
    for(;;)
    {
        //
        // Add CPU1 application code here
        //
        CPU1HB++;

    }
}

//
// End of File
//

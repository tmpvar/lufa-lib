

#include "tbase8.h"


int main(void) {
  SetupHardware();
  sei();

  for (;;)
  {
    MIDI_EventPacket_t ReceivedMIDIEvent;
    /*while (MIDI_Device_ReceiveEventPacket(&Keyboard_MIDI_Interface, &ReceivedMIDIEvent)) {

    }*/

    MIDI_Device_USBTask(&tbase8_MIDI_Interface);
    USB_USBTask();
  }

  return 0;
}


/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
  /* Disable watchdog if enabled by bootloader/fuses */
  MCUSR &= ~(1 << WDRF);
  wdt_disable();

  /* Disable clock division */
  clock_prescale_set(clock_div_1);

  /* Hardware Initialization */
  USB_Init();
}

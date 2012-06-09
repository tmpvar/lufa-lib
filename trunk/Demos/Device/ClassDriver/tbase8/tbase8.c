

#include "tbase8.h"


/** LUFA MIDI Class driver interface configuration and state information. This structure is
 *  passed to all MIDI Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_MIDI_Device_t Keyboard_MIDI_Interface =
  {
    .Config =
      {
        .StreamingInterfaceNumber = 1,
        .DataINEndpoint           =
          {
            .Address          = MIDI_STREAM_IN_EPADDR,
            .Size             = MIDI_STREAM_EPSIZE,
            .Banks            = 1,
          },
        .DataOUTEndpoint          =
          {
            .Address          = MIDI_STREAM_OUT_EPADDR,
            .Size             = MIDI_STREAM_EPSIZE,
            .Banks            = 1,
          },
      },
  };

int main(void) {
  SetupHardware();
  sei();

  for (;;)
  {
    MIDI_EventPacket_t ReceivedMIDIEvent;
    while (MIDI_Device_ReceiveEventPacket(&Keyboard_MIDI_Interface, &ReceivedMIDIEvent))
    {
/*      if ((ReceivedMIDIEvent.Event == MIDI_EVENT(0, MIDI_COMMAND_NOTE_ON)) && (ReceivedMIDIEvent.Data3 > 0))
        LEDs_SetAllLEDs(ReceivedMIDIEvent.Data2 > 64 ? LEDS_LED1 : LEDS_LED2);
      else
        LEDs_SetAllLEDs(LEDS_NO_LEDS);
*/
    }

    MIDI_Device_USBTask(&Keyboard_MIDI_Interface);
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



#include "tbase8.h"

/** LUFA MIDI Class driver interface configuration and state information. This structure is
 *  passed to all MIDI Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_MIDI_Device_t tbase8_MIDI_Interface = {
  .Config = {
    .StreamingInterfaceNumber = 1,
    .DataINEndpoint           = {
      .Address          = MIDI_STREAM_IN_EPADDR,
      .Size             = MIDI_STREAM_EPSIZE,
      .Banks            = 1,
    },
    .DataOUTEndpoint = {
      .Address          = MIDI_STREAM_OUT_EPADDR,
      .Size             = MIDI_STREAM_EPSIZE,
      .Banks            = 1,
    },
  },
};

struct {
  bool pressed;
  bool on;
  unsigned long lastOn;
} inputs[8];

int main(void) {
  SetupHardware();

  TCCR1B |= (1 << CS10);


  sei();

  memset(inputs, 0, sizeof(inputs));
  unsigned long tick = 0;
  for (;;)
  {

    if (TCNT1 >= 1000) {
      tick++;
    }
    //MIDI_EventPacket_t ReceivedMIDIEvent;
    /*while (MIDI_Device_ReceiveEventPacket(&Keyboard_MIDI_Interface, &ReceivedMIDIEvent)) {

    }*/

    int inputPins[4] = { 0b00000010, 0b00001000, 0b00100000, 0b10000000 };
    int port;
    int current;
    unsigned long currentTime;
    for (int i=0; i<8; i++) {

      port = (i<4) ? PIND : PINB;
      current = i%4;
      if (port & inputPins[current]) {
        if (!inputs[i].pressed && tick > inputs[i].lastOn) {
          inputs[i].pressed = true;
          inputs[i].on = !inputs[i].on;
          inputs[i].lastOn = tick;
          // Send midi stuff
          sendMidiNote(i, inputs[i].on);
        }
      } else {
        inputs[i].pressed = false;
        //sendMidiNote(i, false);
      }
    }


    MIDI_Device_USBTask(&tbase8_MIDI_Interface);
    USB_USBTask();
  }

  return 0;
}


void sendMidiNote(int button, bool on) {
  int command = (on) ? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF;

  MIDI_EventPacket_t MIDIEvent = (MIDI_EventPacket_t) {
    .Event       = MIDI_EVENT(0, command),
    .Data1       = command | MIDI_CHANNEL(1),
    .Data2       = 60 + button,
    .Data3       = MIDI_STANDARD_VELOCITY,
  };

  MIDI_Device_SendEventPacket(&tbase8_MIDI_Interface, &MIDIEvent);
  MIDI_Device_Flush(&tbase8_MIDI_Interface);
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
  /* Disable watchdog if enabled by bootloader/fuses */
  MCUSR &= ~(1 << WDRF);
  wdt_disable();


  /* Disable clock division */
  clock_prescale_set(clock_div_1);

  /* Set the port directions for port b and d */
  DDRD  = 0xFF;
  DDRB  = 0xFF;
  PORTD = 0b01010101;
  PORTB = 0b01010101;

  /* Hardware Initialization */
  USB_Init();
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
  bool ConfigSuccess = true;

  ConfigSuccess &= MIDI_Device_ConfigureEndpoints(&tbase8_MIDI_Interface);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
  MIDI_Device_ProcessControlRequest(&tbase8_MIDI_Interface);
}

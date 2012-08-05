/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the VirtualSerial demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "tpad.h"

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t tpad_CDC_Interface =
  {
    .Config =
      {
        .ControlInterfaceNumber   = 0,
        .DataINEndpoint           =
          {
            .Address          = CDC_TX_EPADDR,
            .Size             = CDC_TXRX_EPSIZE,
            .Banks            = 1,
          },
        .DataOUTEndpoint =
          {
            .Address          = CDC_RX_EPADDR,
            .Size             = CDC_TXRX_EPSIZE,
            .Banks            = 1,
          },
        .NotificationEndpoint =
          {
            .Address          = CDC_NOTIFICATION_EPADDR,
            .Size             = CDC_NOTIFICATION_EPSIZE,
            .Banks            = 1,
          },
      },
  };

/** Standard file stream for the CDC interface when set up, so that the virtual CDC COM port can be
 *  used like any regular character stream in the C APIs
 */
static FILE USBSerialStream;


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
  SetupHardware();
  uint16_t bytesAvailable, currentByte;

  CDC_Device_CreateStream(&tpad_CDC_Interface, &USBSerialStream);
  sei();

  for (;;)
  {

    //
    // Read pressures from 16 buttons
    //
    ButtonStates();

    //
    // Handle incoming bytes
    //
    bytesAvailable = CDC_Device_BytesReceived(&tpad_CDC_Interface);
    while (bytesAvailable--) {
      currentByte = CDC_Device_ReceiveByte(&tpad_CDC_Interface);
      // TODO: implement led updates from host
    }

    CDC_Device_USBTask(&tpad_CDC_Interface);
    USB_USBTask();
  }
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
  /* Disable watchdog if enabled by bootloader/fuses */
  MCUSR &= ~(1 << WDRF);
  wdt_disable();

  /* Disable clock division */
  clock_prescale_set(clock_div_1);
  USB_Init();


  //
  // Setup sensor power pins
  //
  DDRD = 0;
  PORTD = 0;

  // Configure ADC
  ADC_Init(ADC_PRESCALE_32 | ADC_FREE_RUNNING);

  // Setup sensor read pins
  ADC_SetupChannel(0);
  ADC_SetupChannel(1);
  ADC_SetupChannel(4);
  ADC_SetupChannel(5);
  ADC_SetupChannel(6);
  ADC_SetupChannel(7);
  ADC_SetupChannel(12);
  ADC_SetupChannel(13);
}

void ButtonStates(void) {

  uint16_t port, result;
  char buffer[64];

  PORTD = 0b11111111;
  /*for (int i=0; i<4; i++) {
    if (i > 1) {
      PORTC = (i%1 == 0) ? 0b01000000 : 0b10000000;
    } else {
      PORTB = (i%1 == 0) ? 0b01000000 : 0b10000000;
    }
*/
    // TODO: dry this up
    ADC_StartReading(ADC_REFERENCE_AVCC | ADC_LEFT_ADJUSTED | ADC_CHANNEL0);
    while(!(ADC_IsReadingComplete())) {}
    sprintf(buffer, "4,%d\n", ADC_GetResult());
    fputs(buffer, &USBSerialStream);

    ADC_StartReading(ADC_REFERENCE_AVCC | ADC_LEFT_ADJUSTED | ADC_CHANNEL1);
    while(!(ADC_IsReadingComplete())) {}
    sprintf(buffer, "0,%d\n", ADC_GetResult());
    fputs(buffer, &USBSerialStream);

    ADC_StartReading(ADC_REFERENCE_AVCC | ADC_LEFT_ADJUSTED | ADC_CHANNEL4);
    while(!(ADC_IsReadingComplete())) {}
    sprintf(buffer, "1,%d\n", ADC_GetResult());
    fputs(buffer, &USBSerialStream);

    ADC_StartReading(ADC_REFERENCE_AVCC | ADC_LEFT_ADJUSTED | ADC_CHANNEL5);
    while(!(ADC_IsReadingComplete())) {}
    sprintf(buffer, "2,%d\n", ADC_GetResult());
    fputs(buffer, &USBSerialStream);

    ADC_StartReading(ADC_REFERENCE_AVCC | ADC_LEFT_ADJUSTED | ADC_CHANNEL6);
    while(!(ADC_IsReadingComplete())) {}
    sprintf(buffer, "3,%d\n", ADC_GetResult());
    fputs(buffer, &USBSerialStream);

    ADC_StartReading(ADC_REFERENCE_AVCC | ADC_LEFT_ADJUSTED | ADC_CHANNEL12);
    while(!(ADC_IsReadingComplete())) {}
    sprintf(buffer, "7,%d\n", ADC_GetResult());
    fputs(buffer, &USBSerialStream);

    ADC_StartReading(ADC_REFERENCE_AVCC | ADC_LEFT_ADJUSTED | ADC_CHANNEL13);
    while(!(ADC_IsReadingComplete())) {}
    sprintf(buffer, "6,%d\n", ADC_GetResult());
    fputs(buffer, &USBSerialStream);

    ADC_StartReading(ADC_REFERENCE_AVCC | ADC_LEFT_ADJUSTED | ADC_CHANNEL7);
    while(!(ADC_IsReadingComplete())) {}
    sprintf(buffer, "5,%d\n", ADC_GetResult());
    fputs(buffer, &USBSerialStream);

/*
    ADC_StartReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | ADC_CHANNEL5);
    while(!(ADC_IsReadingComplete())) {}
    sprintf(buffer, "  %d", ADC_GetResult());
    fputs(buffer, &USBSerialStream);

    ADC_StartReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | ADC_CHANNEL6);
    while(!(ADC_IsReadingComplete())) {}
    sprintf(buffer, "  %d", ADC_GetResult());
    fputs(buffer, &USBSerialStream);

    ADC_StartReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | ADC_CHANNEL7);
    while(!(ADC_IsReadingComplete())) {}
    sprintf(buffer, "  %d", ADC_GetResult());
    fputs(buffer, &USBSerialStream);


    PORTB = 0;
    PORTC = 0;
  //}
  */
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
  bool ConfigSuccess = true;

  ConfigSuccess &= CDC_Device_ConfigureEndpoints(&tpad_CDC_Interface);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
  CDC_Device_ProcessControlRequest(&tpad_CDC_Interface);
}


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
 *  Header file for MIDI.c.
 */

#ifndef _TBASE8_H_
#define _TBASE8_H_

  /** LUFA MIDI Class driver interface configuration and state information. This structure is
   *  passed to all MIDI Class driver functions, so that multiple instances of the same class
   *  within a device can be differentiated from one another.
   */
  USB_ClassInfo_MIDI_Device_t tbase8_MIDI_Interface =
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


  /* Includes: */
    #include <avr/io.h>
    #include <avr/wdt.h>
    #include <avr/power.h>
    #include <avr/interrupt.h>
    #include <stdbool.h>
    #include <string.h>

    #include "Descriptors.h"

    #include <LUFA/Drivers/USB/USB.h>

  /* Function Prototypes: */
    void SetupHardware(void);

    void EVENT_USB_Device_Connect(void);
    void EVENT_USB_Device_Disconnect(void);
    void EVENT_USB_Device_ConfigurationChanged(void);
    void EVENT_USB_Device_ControlRequest(void);

#endif


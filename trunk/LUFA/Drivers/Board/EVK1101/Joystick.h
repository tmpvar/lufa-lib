/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Board specific joystick driver header for the EVK1101.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the joystick driver
 *        dispatch header located in LUFA/Drivers/Board/Joystick.h.
 */

/** \ingroup Group_Joystick
 *  @defgroup Group_Joystick_EVK1101 EVK1101
 *
 *  Board specific joystick driver header for the EVK1101.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the joystick driver
 *        dispatch header located in LUFA/Drivers/Board/Joystick.h.
 *
 *  @{
 */

#ifndef __JOYSTICK_EVK1101_H__
#define __JOYSTICK_EVK1101_H__

	/* Includes: */
		#include <avr32/io.h>

		#include "../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_JOYSTICK_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Joystick.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define JOY_MASK_PA              (1 << 13)
			#define JOY_MASK_PB              ((1 << 6) | (1 << 7) | (1 << 8) | (1 << 9))
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Mask for the joystick being pushed in the left direction. */
			#define JOY_LEFT                  (1UL << 6)

			/** Mask for the joystick being pushed in the upward direction. */
			#define JOY_UP                    (1UL << 7)

			/** Mask for the joystick being pushed in the right direction. */
			#define JOY_RIGHT                 (1UL << 8)

			/** Mask for the joystick being pushed in the downward direction. */
			#define JOY_DOWN                  (1UL << 9)

			/** Mask for the joystick being pushed inward. */
			#define JOY_PRESS                 (1UL << 13)
			
		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void Joystick_Init(void)
			{
				AVR32_GPIO.port[0].gpers = JOY_MASK_PA;
				AVR32_GPIO.port[0].puers = JOY_MASK_PA;
				AVR32_GPIO.port[1].gpers = JOY_MASK_PB;
				AVR32_GPIO.port[1].puers = JOY_MASK_PB;
			}
			
			static inline uint32_t Joystick_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint32_t Joystick_GetStatus(void)
			{
				return ((~AVR32_GPIO.port[1].pvr & JOY_MASK_PB) |
				        (~AVR32_GPIO.port[0].pvr & JOY_MASK_PA));
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
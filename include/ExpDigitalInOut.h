/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_EXPDIGITALINOUT_H
#define MBED_EXPDIGITALINOUT_H

#include "mbed.h"
#include "DigitalInOutInterface.h"
#include "GPIOExpansionInterface.h"

#if DEVICE_EXPANSION || defined(DOXYGEN_ONLY)

/** An external digital input, used for reading the state of a pin
 *
 * @note Synchronization level: Interrupt safe
 *
 */

class ExpDigitalInOut : public DigitalInOutInterface{

public:
    /** Create an ExpDigitalIn connected to the specified pin
     *
     *  @param exp 	ExpansionInterface which controls the external pin
     *  @param port ExpDigitalIn port to connect to
     *  @param pin 	ExpDigitalIn pin to connect to
     */
	ExpDigitalInOut(GPIOExpansionInterface *exp, ExpPortName port, ExpPinName pin);

    /** Create an ExpDigitalIn connected to the specified pin
     *
     *  @param exp 	ExpansionInterface which controls the external pin
     *  @param port ExpDigitalIn port to connect to
     *  @param pin 	ExpDigitalIn pin to connect to
     *  @param mode the initial mode of the pin
     */
	ExpDigitalInOut(GPIOExpansionInterface *exp, ExpPortName port, ExpPinName pin, PinMode mode);

	~ExpDigitalInOut();
    /** Read the input, represented as 0 or 1 (int)
     *
     *  @returns
     *    An integer representing the state of the input pin,
     *    0 for logical 0, 1 for logical 1
     */
    int read();

    /** Set the output, specified as 0 or 1 (int)
     *
     *  @param value An integer specifying the pin output value,
     *      0 for logical 0, 1 (or any other non-zero value) for logical 1
     */
    void write(int value);

    /** Set as an output
     */
    void output();

    /** Set as an input
     */
    void input();

    /** Set the input pin mode
     *
     *  @param pull PullUp, PullDown, PullNone, OpenDrain
     */
    void mode(PinMode pull);

    /** Return the output setting, represented as 0 or 1 (int)
     *
     *  @returns
     *    Non zero value if pin is connected to uc GPIO
     *    0 if gpio object was initialized with NC
     */
    int is_connected();

    /** A shorthand for write()
     * \sa ExpDigitalOut::write()
     * @code
     *      ExpDigitalIn  button(BUTTON1);
     *      ExpDigitalOut led(LED1);
     *      led = button;   // Equivalent to led.write(button.read())
     * @endcode
     */
    ExpDigitalInOut &operator= (int value);

    /** A shorthand for write() using the assignment operator which copies the
     * state from the ExpDigitalOut argument.
     * \sa ExpDigitalOut::write()
     */
    ExpDigitalInOut &operator= (ExpDigitalInOut &rhs);

    /** An operator shorthand for read()
     * \sa ExpDigitalIn::read()
     * @code
     *      ExpDigitalIn  button(BUTTON1);
     *      ExpDigitalOut led(LED1);
     *      led = button;   // Equivalent to led.write(button.read())
     * @endcode
     */
    operator int();

protected:

#if !defined(DOXYGEN_ONLY)
    bool _checkAttachment(void);
    bool _setAttachment(void);
    bool _resetAttachment(void);
    bool _setDirection(ExpDigitalDirection direction);
    bool _setMode(PinMode mode);
    bool _isConnected;
    GPIOExpansionInterface *_exp;
	ExpPortName _port;
	ExpPinName _pin;
#endif
};

#endif

#endif
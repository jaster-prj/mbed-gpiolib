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
#ifndef MBED_INTDIGITALINOUT_H
#define MBED_INTDIGITALINOUT_H

#include "mbed.h"
#include "DigitalInOutInterface.h"

/** An external digital input, used for reading the state of a pin
 *
 * @note Synchronization level: Interrupt safe
 *
 */

class IntDigitalInOut : public DigitalInOutInterface{

public:
    /** Create an IntDigitalInOut connected to the specified pin
     *
     *  @param name	PinName of the internal pin
     */
	IntDigitalInOut(PinName name);

    /** Create an IntDigitalInOut connected to the specified pin
     *
     *  @param name	PinName of the internal pin
     *  @param mode the initial mode of the pin
     */
	IntDigitalInOut(PinName pin, PinDirection direction, PinMode mode, int value);

    /** Create an IntDigitalInOut connected to the specified pin
     *
     *  @param pin	Pin-Object of the internal pin
     */
	IntDigitalInOut(DigitalInOut *pin);

	~IntDigitalInOut();
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
     * \sa IntDigitalInOut::write()
     * @code
     *      IntDigitalInOut  button(BUTTON1);
     *      IntDigitalInOut led(LED1);
     *      led = button;   // Equivalent to led.write(button.read())
     * @endcode
     */
    IntDigitalInOut &operator= (int value);

    /** A shorthand for write() using the assignment operator which copies the
     * state from the IntDigitalInOut argument.
     * \sa IntDigitalInOut::write()
     */
    IntDigitalInOut &operator= (IntDigitalInOut &rhs);

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
    DigitalInOut *_pin;
    bool _created;
#endif
};

#endif
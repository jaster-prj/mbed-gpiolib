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
#ifndef INTDIGITALOUT_H
#define INTDIGITALOUT_H

#include "mbed.h"
#include "DigitalOutInterface.h"

/** An internal digital output, used for setting the state of a pin
 *
 * @note Synchronization level: Interrupt safe
 *
 */
class IntDigitalOut : public DigitalOutInterface{

public:
 
     /** Create an IntDigitalOut connected to the specified pin
     *
     *  @param name	PinName of the internal pin
     */
	IntDigitalOut(PinName name);

    /** Create an IntDigitalOut connected to the specified pin
     *
     *  @param name	PinName of the internal pin
     *  @param mode the initial mode of the pin
     */
	IntDigitalOut(PinName name, PinMode mode);

    /** Create an IntDigitalOut connected to the specified pin
     *
     *  @param pin	Pin-Object of the internal pin
     */
	IntDigitalOut(DigitalOut *pin);

	~IntDigitalOut();
    /** Set the output, specified as 0 or 1 (int)
     *
     *  @param value An integer specifying the pin output value,
     *      0 for logical 0, 1 (or any other non-zero value) for logical 1
     */
    void write(int value);

    /** Return the output setting, represented as 0 or 1 (int)
     *
     *  @returns
     *    an integer representing the output setting of the pin,
     *    0 for logical 0, 1 for logical 1
     */
    int read();

    /** Return the output setting, represented as 0 or 1 (int)
     *
     *  @returns
     *    Non zero value if pin is connected to uc GPIO
     *    0 if gpio object was initialized with NC
     */
    int is_connected();

    /** A shorthand for write()
     * \sa IntDigitalOut::write()
     * @code
     *      IntDigitalOut  button(BUTTON1);
     *      IntDigitalOut led(LED1);
     *      led = button;   // Equivalent to led.write(button.read())
     * @endcode
     */
    IntDigitalOut &operator= (int value);

    /** A shorthand for write() using the assignment operator which copies the
     * state from the IntDigitalOut argument.
     * \sa ExpDigitalOut::write()
     */
    IntDigitalOut &operator= (IntDigitalOut &rhs);

    /** A shorthand for read()
     * \sa IntDigitalOut::read()
     * @code
     *      IntDigitalOut  button(BUTTON1);
     *      IntDigitalOut led(LED1);
     *      led = button;   // Equivalent to led.write(button.read())
     * @endcode
     */
    operator int();

#if !defined(DOXYGEN_ONLY)
protected:
    DigitalOut *_pin;
    bool _created;
#endif
};

#endif
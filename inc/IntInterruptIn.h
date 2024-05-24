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
#ifndef INTINTERRUPTIN_H
#define INTINTERRUPTIN_H

#include "mbed.h"
#include "InterruptInInterface.h"

namespace mbed {

/** An external digital interrupt input, used to call a function on a rising or falling edge
 *
 * @note Synchronization level: Interrupt safe
 */
class IntInterruptIn : InterruptInInterface {

public:

    /** Create an IntDigitalInOut connected to the specified pin
     *
     *  @param name	PinName of the internal pin
     */
	IntInterruptIn(PinName name);

    /** Create an IntDigitalInOut connected to the specified pin
     *
     *  @param name	PinName of the internal pin
     *  @param mode the initial mode of the pin
     */
	IntInterruptIn(PinName name, PinMode mode);

    /** Create an IntDigitalInOut connected to the specified pin
     *
     *  @param pin	Pin-Object of the internal pin
     */
	IntInterruptIn(InterruptIn *pin);

    virtual ~IntInterruptIn();

    /** Read the input, represented as 0 or 1 (int)
     *
     *  @returns
     *    An integer representing the state of the input pin,
     *    0 for logical 0, 1 for logical 1
     */
    int read();

    /** An operator shorthand for read()
     */
    operator int();


    /** Attach a function to call when a rising edge occurs on the input
     *
     *  @param func A pointer to a void function, or 0 to set as none
     */
    void rise(Callback<void()> func);

    /** Attach a function to call when a falling edge occurs on the input
     *
     *  @param func A pointer to a void function, or 0 to set as none
     */
    void fall(Callback<void()> func);

    /** Set the input pin mode
     *
     *  @param pull PullUp, PullDown, PullNone, PullDefault
     *  See PinNames.h for your target for definitions)
     */
    void mode(PinMode pull);

    /** Enable IRQ. Set the GPIOExpander Interrupt Register
     */
    void enable_irq();

    /** Disable IRQ. Reset the GPIOExpander Interrupt Register
     */
    void disable_irq();
#if !defined(DOXYGEN_ONLY)
protected:
    InterruptIn *_pin;
    bool _created;

    Callback<void()> _rise;
    Callback<void()> _fall;
#endif
};

} // namespace mbed

#endif
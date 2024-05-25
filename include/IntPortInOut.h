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
#ifndef INTPORTINOUT_H
#define INTPORTINOUT_H

#include "mbed.h"
#include "PortInOutInterface.h"
#include "GPIOExpansionInterface.h"

/** An internal port in and out
 *
 * @note Synchronization level: Interrupt safe
 */
class IntPortInOut : public PortInOutInterface{
public:

    /** Create an IntPortInOut connected to the specified port
     *
     *  @param port PortInOut port to connect to
     */
    IntPortInOut(PortInOut *port);
    /** Create an IntPortInOut connected to the specified port
     *
     *  @param name IntPortInOut port to connect to
     *  @param mask Bitmask defines which port pins should be an input (0 - ignore, 1 - include)
     */
    IntPortInOut(PortName name, int mask = 0xFFFFFFFF);

	~IntPortInOut();
    /** Read the value input to the port
     *
     *  @returns
     *    An integer with each bit corresponding to the associated pin value
     */
    int read();

    /** Write the value to the output port
     *
     *  @param value An integer specifying a bit to write for every corresponding ExpPortOut pin
     */
    void write(int value);

    /** Set as an output
     */
    void output();

    /** Set as an input
     */
    void input();

    /** A shorthand for write()
     * \sa ExpPortOut::write()
     */
    IntPortInOut &operator= (int value);

    /** A shorthand for read()
     * \sa ExpPortOut::read()
     */
    IntPortInOut &operator= (IntPortInOut &rhs);

    /** Set the input pin mode
     *
     *  @param mode PullUp, PullDown, PullNone, OpenDrain
     */
    void mode(PinMode mode);

    /** A shorthand for read()
     */
    operator int();

#if !defined(DOXYGEN_ONLY)
protected:
    PortInOut *_port;
    bool _created;
#endif
};

#endif
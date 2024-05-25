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
#ifndef INTPORTOUT_H
#define INTPORTOUT_H

#include "mbed.h"
#include "PortOutInterface.h"
#include "GPIOExpansionInterface.h"

/** A multiple pin digital output
 *
 * @note Synchronization level: Interrupt safe
 */
class IntPortOut : public PortOutInterface{
public:

    /** Create an IntPortInOut connected to the specified port
     *
     *  @param port PortInOut port to connect to
     */
    IntPortOut(PortOut *port);
    /** Create an IntPortInOut connected to the specified port
     *
     *  @param name IntPortInOut port to connect to
     *  @param mask Bitmask defines which port pins should be an input (0 - ignore, 1 - include)
     */
    IntPortOut(PortName name, int mask = 0xFFFFFFFF);

    ~IntPortOut();
    /** Write the value to the output port
     *
     *  @param value An integer specifying a bit to write for every corresponding ExpPortOut pin
     */
    void write(int value);

    /** Read the value currently output on the port
     *
     *  @returns
     *    An integer with each bit corresponding to associated pin value
     */
    int read();

    /** A shorthand for write()
     * \sa IntPortOut::write()
     */
    IntPortOut &operator= (int value);

    /** A shorthand for read()
     * \sa IntPortOut::read()
     */
    IntPortOut &operator= (IntPortOut &rhs);

    /** A shorthand for read()
     * \sa IntPortOut::read()
     */
    operator int();

#if !defined(DOXYGEN_ONLY)
protected:
    PortOut *_port;
    bool _created;
#endif
};

#endif
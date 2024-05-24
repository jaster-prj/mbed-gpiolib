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
#ifndef INTPORTIN_H
#define INTPORTIN_H

#include "mbed.h"
#include "PortInInterface.h"
#include "GPIOExpansionInterface.h"

/** An external multiple pin digital input
 *
 * @note Synchronization level: Interrupt safe
 */
class IntPortIn : public PortInInterface{
public:

    /** Create an IntPortIn connected to the specified port
     *
     *  @param port PortIn port to connect to
     */
    IntPortIn(PortIn *port);
    /** Create an IntPortIn connected to the specified port
     *
     *  @param name IntPortIn port to connect to
     *  @param mask Bitmask defines which port pins should be an input (0 - ignore, 1 - include)
     */
    IntPortIn(PortName name, int mask = 0xFFFFFFFF);

	~IntPortIn();
    /** Read the value input to the port
     *
     *  @returns
     *    An integer with each bit corresponding to the associated pin value
     */
    int read();

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
    PortIn *_port;
    bool _created;
#endif
};

#endif
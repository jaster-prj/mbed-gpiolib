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
#ifndef EXPPORTINOUT_H
#define EXPPORTINOUT_H

#include "mbed.h"
#include "PortInOutInterface.h"
#include "GPIOExpansionInterface.h"

#if DEVICE_EXPANSION || defined(DOXYGEN_ONLY)

/** An external multiple pin digital input
 *
 * @note Synchronization level: Interrupt safe
 */
class ExpPortInOut : public PortInOutInterface{
public:

	  /** Create an ExpPortIn connected to the specified pin
		 *
		 *  @param exp 	ExpansionInterface which controls the external pin
		 *  @param port ExpPortIn port to connect to
     *  @param mask Bitmask defines which port pins should be an input (0 - ignore, 1 - include)
		 */
	ExpPortInOut(GPIOExpansionInterface *exp, ExpPortName port, int mask = 0xFFFFFFFF);

	~ExpPortInOut();
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
    ExpPortInOut &operator= (int value);

    /** A shorthand for read()
     * \sa ExpPortOut::read()
     */
    ExpPortInOut &operator= (ExpPortInOut &rhs);

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
    bool _checkAttachment(void);
    bool _setAttachment(void);
    bool _resetAttachment(void);
    bool _setDirection(ExpDigitalDirection direction);
    bool _setMode(PinMode mode);
    GPIOExpansionInterface *_exp;
    ExpPortName _port;
    int _mask;
    bool _isConnected;
#endif
};

#endif

#endif
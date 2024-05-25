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
#include "../include/IntDigitalOut.h"

IntDigitalOut::IntDigitalOut(PinName name) {
	_pin = new DigitalOut(name);
	_created = true;
}
IntDigitalOut::IntDigitalOut(PinName name, PinMode mode) {
	_pin = new DigitalOut(name, mode);
	_created = true;
}
IntDigitalOut::IntDigitalOut(DigitalOut *pin) {
	_pin = pin;
	_created = false;
}

IntDigitalOut::~IntDigitalOut() {
	if (_created) {
		delete _pin;
	}
}

void IntDigitalOut::write(int value) {
	_pin->write(value);
}

int IntDigitalOut::read(void) {
	return _pin->read();
}

int IntDigitalOut::is_connected() {
	return (int)(_pin!=nullptr);
}

IntDigitalOut &IntDigitalOut::operator= (int value) {
    write(value);
    return *this;
}

IntDigitalOut &IntDigitalOut::operator= (IntDigitalOut &rhs) {
    write(rhs.read());
    return *this;
}

IntDigitalOut::operator int()
{
    // Underlying call is atomic
    return read();
}

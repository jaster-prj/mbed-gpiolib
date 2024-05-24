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
#include "../inc/IntDigitalInOut.h"

IntDigitalInOut::IntDigitalInOut(PinName name) {
	_pin = new DigitalInOut(name);
	_created = true;
}
IntDigitalInOut::IntDigitalInOut(PinName name, PinDirection direction, PinMode mode, int value) {
	_pin = new DigitalInOut(name, direction, mode, value);
	_created = true;
}
IntDigitalInOut::IntDigitalInOut(DigitalInOut *pin) {
	_pin = pin;
	_created = false;
}

IntDigitalInOut::~IntDigitalInOut() {
	if (_created) {
		delete _pin;
	}
}

void IntDigitalInOut::write(int value) {
	_pin->write(value);
}

int IntDigitalInOut::read(void) {
	return _pin->read();
}

void IntDigitalInOut::output() {
	_pin->output();
}

void IntDigitalInOut::input() {
	_pin->input();
}

int IntDigitalInOut::is_connected() {
	return (int)(_pin!=nullptr);
}

IntDigitalInOut &IntDigitalInOut::operator= (int value) {
    write(value);
    return *this;
}

IntDigitalInOut &IntDigitalInOut::operator= (IntDigitalInOut &rhs) {
    write(rhs.read());
    return *this;
}

IntDigitalInOut::operator int()
{
    // Underlying call is atomic
    return read();
}
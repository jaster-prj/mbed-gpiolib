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
#include "../inc/IntDigitalIn.h"

IntDigitalIn::IntDigitalIn(PinName name) {
	_pin = new DigitalIn(name);
	_created = true;
}
IntDigitalIn::IntDigitalIn(PinName name, PinMode mode) {
	_pin = new DigitalIn(name, mode);
	_created = true;
}
IntDigitalIn::IntDigitalIn(DigitalIn *pin) {
	_pin = pin;
	_created = false;
}

IntDigitalIn::~IntDigitalIn(){
	if (_created) {
		delete _pin;
	}
}
int IntDigitalIn::read(void) {
	return _pin->read();
}

void IntDigitalIn::mode(PinMode pull) {
	_pin->mode(pull);
}

int IntDigitalIn::is_connected() {
	return (int)(_pin!=nullptr);
}


IntDigitalIn::operator int()
{
    // Underlying call is atomic
    return read();
}
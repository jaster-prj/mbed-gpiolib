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
#include "../include/IntInterruptIn.h"

IntInterruptIn::IntInterruptIn(PinName name) {
	_pin = new InterruptIn(name);
	_created = true;
}

IntInterruptIn::IntInterruptIn(PinName name, PinMode mode) {
	_pin = new InterruptIn(name, mode);
	_created = true;
}

IntInterruptIn::IntInterruptIn(InterruptIn *pin) {
	_pin = pin;
}

IntInterruptIn::~IntInterruptIn() {
	if (_created) {
		delete _pin;
	}
}

int IntInterruptIn::read(void) {
	return _pin->read();
}

// int IntInterruptIn::is_connected() {
// 	return (int)_pin->is_connected();
// }

IntInterruptIn::operator int()
{
    // Underlying call is atomic
    return read();
}

void IntInterruptIn::rise(Callback<void()> func) {
    _pin->rise(func);
}

void IntInterruptIn::fall(Callback<void()> func) {
    _pin->fall(func);
}

void IntInterruptIn::mode(PinMode pull) {
	_pin->mode(pull);
}

void IntInterruptIn::enable_irq(void) {
	_pin->enable_irq();
}

void IntInterruptIn::disable_irq(void) {
	_pin->disable_irq();
}

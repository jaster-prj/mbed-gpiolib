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
#include "../include/IntPortIn.h"

IntPortIn::IntPortIn(PortName name, int mask) {
	_port = new PortIn(name, mask);
	_created = true;
}

IntPortIn::IntPortIn(PortIn *port) {
	_port = port;
	_created = false;
}

IntPortIn::~IntPortIn(){
	if (_created) {
		delete _port;
	}
}
int IntPortIn::read(void) {
	return _port->read();
}

void IntPortIn::mode(PinMode mode) {
	_port->mode(mode);
}

//int IntPortIn::is_connected() {
//	return (int)_port->is_connected();
//}

IntPortIn::operator int()
{
    // Underlying call is atomic
    return read();
}

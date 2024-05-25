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
#include "../include/IntPortInOut.h"

IntPortInOut::IntPortInOut(PortName name, int mask) {
	_port = new PortInOut(name, mask);
	_created = true;
	_port->input();
}

IntPortInOut::IntPortInOut(PortInOut *port) {
	_port = port;
	_created = false;
	_port->input();
}

IntPortInOut::~IntPortInOut(){
	_port->input();
	if (_created) {
		delete _port;
	}
}

int IntPortInOut::read(void) {
	return _port->read();
}

void IntPortInOut::write(int value) {
	_port->write(value);
}

void IntPortInOut::output() {
	_port->output();
}

void IntPortInOut::input() {
	_port->input();
}

//int IntPortInOut::is_connected() {
//	return (int)_port->is_connected();
//}

IntPortInOut &IntPortInOut::operator= (int value){
    write(value);
    return *this;
}

IntPortInOut &IntPortInOut::operator= (IntPortInOut &rhs){
    write(rhs.read());
    return *this;
}

void IntPortInOut::mode(PinMode mode) {
	_port->mode(mode);
}

IntPortInOut::operator int()
{
    // Underlying call is atomic
    return read();
}

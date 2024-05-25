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
#include "../include/IntPortOut.h"

IntPortOut::IntPortOut(PortName name, int mask) {
	_port = new PortOut(name, mask);
	_created = true;
}

IntPortOut::IntPortOut(PortOut *port) {
	_port = port;
	_created = false;
}

IntPortOut::~IntPortOut(){
	if (_created) {
		delete _port;
	}
}

void IntPortOut::write(int value) {
	_port->write(value);
}

int IntPortOut::read(void) {
	return _port->read();
}

//int IntPortOut::is_connected() {
//	return (int)_port->is_connected();
//}

IntPortOut &IntPortOut::operator= (int value){
    write(value);
    return *this;
}

IntPortOut &IntPortOut::operator= (IntPortOut &rhs){
    write(rhs.read());
    return *this;
}

IntPortOut::operator int()
{
    // Underlying call is atomic
    return read();
}

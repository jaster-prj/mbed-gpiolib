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
#include "../include/ExpPortInOut.h"

#if DEVICE_EXPANSION

ExpPortInOut::ExpPortInOut(GPIOExpansionInterface *exp, ExpPortName port, int mask) {
	_exp = exp;
	_port = port;
	_mask = mask;
	_isConnected = false;
	if (_checkAttachment() == false && _setDirection(INPUT)) {
		_isConnected = _setAttachment();
	}
}

ExpPortInOut::~ExpPortInOut(){
	_setDirection(INPUT);
	if (_isConnected && _resetAttachment()){
		_isConnected = false;
	}
}

int ExpPortInOut::read(void) {
	int value;
	_exp->read(_port, &value);
	return (value&_mask);
}

void ExpPortInOut::write(int value) {
	int value_old;
	_exp->read(_port, &value_old);
	if ((value&_mask) != (value_old&_mask)){
		_exp->write(_port, (value_old & ~_mask) | (value & _mask));
	}
}

void ExpPortInOut::output() {
	_setDirection(OUTPUT);
}

void ExpPortInOut::input() {
	_setDirection(INPUT);
}

//int ExpPortIn::is_connected() {
//	return (int)_isConnected;
//}

ExpPortInOut &ExpPortInOut::operator= (int value){
    write(value);
    return *this;
}

ExpPortInOut &ExpPortInOut::operator= (ExpPortInOut &rhs){
    write(rhs.read());
    return *this;
}

void ExpPortInOut::mode(PinMode mode) {
	_setMode(mode);
}

ExpPortInOut::operator int()
{
    // Underlying call is atomic
    return read();
}

bool ExpPortInOut::_checkAttachment(void) {
//	ExpPinName pin;
	if (_mask >= (1 << _exp->getPortWidth())){
		_mask = _mask | ((1 << _exp->getPortWidth())-1);
	}
	for (int i = 0; i < _exp->getPortWidth(); i++) {
		if ((_mask & (1 << i)) != 0) {
//			pin = (ExpPinName)(((char)_port << 4) | i);
			if (_exp->isAttached(_port, (ExpPinName)(i)) == true) {
				return true;
			}
		}
	}
	return false;
}

bool ExpPortInOut::_setAttachment(void){
	for (int i = 0; i < _exp->getPortWidth(); i++) {
		if ((_mask & (1 << i)) != 0) {
			_exp->attach(_port, (ExpPinName)(i), NULL, 0);
		}
		return true;
	}
	return false;
}

bool ExpPortInOut::_resetAttachment(void){
	for (int i = 0; i < _exp->getPortWidth(); i++) {
		if ((_mask & (1 << i)) != 0) {
			_exp->detach(_port, (ExpPinName)(i));
		}
		return true;
	}
	return false;
}

bool ExpPortInOut::_setDirection(ExpDigitalDirection direction){
	int direction_new;
	int direction_old;
	_exp->getDirection(_port, &direction_old);
	if (direction == INPUT){
		direction_new = direction_old & ~_mask;
	}
	else{
		direction_new = direction_old | _mask;
	}
	if (direction_new == direction_old){
		return true;
	}
	_exp->setDirection(_port, direction_new);
	_exp->getDirection(_port, &direction_old);
	return (direction_new != direction_old) ? false : true;
}

bool ExpPortInOut::_setMode(PinMode mode){
	if (mode != PullNone && mode !=PullUp){
		return false;
	}
	int pinmode_old;
	int pinmode_new;
	_exp->getConfigureMode(_port, mode, &pinmode_old);
	pinmode_new = (mode == PullNone) ? (pinmode_old & ~_mask) : (pinmode_old | _mask);
	if (pinmode_new != pinmode_old) {
		_exp->setConfigureMode(_port, mode, pinmode_new);
	}
	_exp->getConfigureMode(_port, mode, &pinmode_old);
	if (pinmode_new != pinmode_old) {
		return false;
	}
	return true;
}

#endif

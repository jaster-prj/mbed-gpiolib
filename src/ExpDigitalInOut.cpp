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
#include "../include/ExpDigitalInOut.h"

#if DEVICE_EXPANSION

ExpDigitalInOut::ExpDigitalInOut(GPIOExpansionInterface *exp, ExpPortName port, ExpPinName pin) {
	_exp = exp;
	_port = port;
	_pin = pin;
	_isConnected = false;
	if (_checkAttachment() == false && _setDirection(INPUT)) {
		_isConnected = _setAttachment();
		_setMode(PullNone);
	}
}

ExpDigitalInOut::ExpDigitalInOut(GPIOExpansionInterface *exp, ExpPortName port, ExpPinName pin, PinMode mode) {
	_exp = exp;
	_port = port;
	_pin = pin;
	_isConnected = false;
	if (_checkAttachment() == false && _setDirection(INPUT)) {
		_isConnected = _setAttachment();
		_setMode(mode);
	}
}

ExpDigitalInOut::~ExpDigitalInOut(){
	_setDirection(INPUT);
	if (_isConnected && _resetAttachment()){
		_setMode(PullNone);
	}
}
int ExpDigitalInOut::read(void) {
	int value;
	int pinposition = 1 << (char)_pin;
	_exp->read(_port, &value);
	return (int)((value&pinposition) >> (char)_pin);
}

void ExpDigitalInOut::write(int value) {
	int value_new;
	int value_old;
	int pinposition = 1 << (char)_pin;
	int pinvalue = value << (char)_pin;
	_exp->read(_port, &value_old);
	value_new = (value_old & ~pinposition) | pinvalue;
	if (value_new != value_old){
		_exp->write(_port, value_new);
	}
}

void ExpDigitalInOut::output() {
	_setDirection(OUTPUT);
}

void ExpDigitalInOut::input() {
	_setDirection(INPUT);
}

void ExpDigitalInOut::mode(PinMode pull) {
	if (_isConnected) {
		_setMode(pull);
	}
}

int ExpDigitalInOut::is_connected() {
	return (int)_isConnected;
}

ExpDigitalInOut &ExpDigitalInOut::operator= (int value) {
    write(value);
    return *this;
}

ExpDigitalInOut &ExpDigitalInOut::operator= (ExpDigitalInOut &rhs) {
    write(rhs.read());
    return *this;
}


ExpDigitalInOut::operator int()
{
    // Underlying call is atomic
    return read();
}

bool ExpDigitalInOut::_checkAttachment(void) {
	return _exp->isAttached(_port, _pin);
}

bool ExpDigitalInOut::_setAttachment(void){
	_exp->attach(_port, _pin, NULL, 0);
	return true;
}

bool ExpDigitalInOut::_resetAttachment(void){
	_exp->detach(_port, _pin);
	return true;
}

bool ExpDigitalInOut::_setDirection(ExpDigitalDirection direction){
	int direction_new;
	int direction_old;
	int pinposition = 1 << (char)_pin;
	_exp->getDirection(_port, &direction_old);
	if (direction == INPUT){
		direction_new = direction_old & ~pinposition;
	}
	else{
		direction_new = direction_old | pinposition;
	}
	if (direction_new == direction_old){
		return true;
	}
	_exp->setDirection(_port, direction_new);
	_exp->getDirection(_port, &direction_old);
	return (direction_new != direction_old) ? false : true;
}

bool ExpDigitalInOut::_setMode(PinMode mode){
//	if (mode != PullNone && mode !=PullUp){
//		return false;
//	}
	int pinmode_old;
	int pinmode_new;
	int pinposition = 0x01 << (char)_pin;
	int mask;
	_exp->getConfigureMode(_port, mode, &pinmode_old);
	mask = (mode != PullNone) ? 0xFFFFFFFF : 0;
	pinmode_new = (pinmode_old & ~pinposition) | (mask | pinposition);
	if (pinmode_new != pinmode_old) {
		_exp->setConfigureMode(_port, mode, pinmode_new);
	}
	_exp->getConfigureMode(_port, mode, &pinmode_old);
	return (pinmode_new != pinmode_old) ? false: true;
}

#endif

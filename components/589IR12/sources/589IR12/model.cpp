// Copyright 2022 ICS8-64 and ICS8-65
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

#include <589IR12/model.hpp>

INT I3000_589IR12_Model::isdigital(CHAR* pinname) {
    return 1;
}

VOID I3000_589IR12_Model::setup(IINSTANCE* instance, IDSIMCKT* dsim) {
    this->_instance = instance;

    _pin_D1 = instance->getdsimpin("D1", true);
    _pin_D2 = instance->getdsimpin("D2", true);
    _pin_D3 = instance->getdsimpin("D3", true);
    _pin_D4 = instance->getdsimpin("D4", true);
    _pin_D5 = instance->getdsimpin("D5", true);
    _pin_D6 = instance->getdsimpin("D6", true);
    _pin_D7 = instance->getdsimpin("D7", true);
    _pin_D8 = instance->getdsimpin("D8", true);
    _pin_CLR= instance->getdsimpin("CLR", true);
    _pin_CS1 = instance->getdsimpin("CS1", true);
    _pin_CS2 = instance->getdsimpin("CS2", true);
    _pin_MD = instance->getdsimpin("MD", true);
    _pin_EV = instance->getdsimpin("EV", true);
    _pin_GND = instance->getdsimpin("GND", true);

    _pin_INR = instance->getdsimpin("INR", true);
    _pin_Q1 = instance->getdsimpin("Q1", true);
    _pin_Q2 = instance->getdsimpin("Q2", true);
    _pin_Q3 = instance->getdsimpin("Q3", true);
    _pin_Q4 = instance->getdsimpin("Q4", true);
    _pin_Q5 = instance->getdsimpin("Q5", true);
    _pin_Q6= instance->getdsimpin("Q6", true);
    _pin_Q7= instance->getdsimpin("Q7", true);
    _pin_Q8 = instance->getdsimpin("Q8", true);
    _pin_UCC = instance->getdsimpin("UCC", true);
}

VOID I3000_589IR12_Model::runctrl(RUNMODES mode) {}

VOID I3000_589IR12_Model::actuate(REALTIME time, ACTIVESTATE newstate) {}

BOOL I3000_589IR12_Model::indicate(REALTIME time, ACTIVEDATA* newstate) {
    return FALSE;
}

VOID I3000_589IR12_Model::simulate(ABSTIME time, DSIMMODES mode) {}

VOID I3000_589IR12_Model::callback(ABSTIME time, EVENTID eventid) {}
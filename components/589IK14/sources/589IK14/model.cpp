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

#include <589IK14/model.hpp>

INT I3000_589IK14_Model::isdigital(CHAR* pinname) {
    return 1;
}

VOID I3000_589IK14_Model::setup(IINSTANCE* instance, IDSIMCKT* dsim) {
    this->_instance = instance;

    _pin_INE = instance->getdsimpin("INE", true);
    _pin_CLK = instance->getdsimpin("CLK", true);
    _pin_P2 = instance->getdsimpin("P2", true);
    _pin_P1 = instance->getdsimpin("P1", true);
    _pin_P0 = instance->getdsimpin("P0", true);
    _pin_GS = instance->getdsimpin("GS", true);
    _pin_EW = instance->getdsimpin("EW", true);
    _pin_ERC = instance->getdsimpin("ERC", true);
    _pin_EG = instance->getdsimpin("EG", true);
    _pin_IR7 = instance->getdsimpin("IR7", true);
    _pin_IR6 = instance->getdsimpin("IR6", true);
    _pin_IR5 = instance->getdsimpin("IR5", true);
    _pin_IR4 = instance->getdsimpin("IR4", true);
    _pin_IR3 = instance->getdsimpin("IR3", true);
    _pin_IR2 = instance->getdsimpin("IR2", true);
    _pin_IR1 = instance->getdsimpin("IR1", true);
    _pin_IR0 = instance->getdsimpin("IR0", true);
    _pin_IC2 = instance->getdsimpin("IC2", true);
    _pin_IC1 = instance->getdsimpin("IC1", true);
    _pin_IC0 = instance->getdsimpin("IC0", true);
    _pin_GE = instance->getdsimpin("GE", true);
    _pin_IA = instance->getdsimpin("IA", true);
}
//External model DLL "i3000-components-589IK14.DLL" not found. GLE=0x000000C1.
//                    i3000-components-589IK14.dll

VOID I3000_589IK14_Model::runctrl(RUNMODES mode) {}

VOID I3000_589IK14_Model::actuate(REALTIME time, ACTIVESTATE newstate) {}

BOOL I3000_589IK14_Model::indicate(REALTIME time, ACTIVEDATA* newstate) {
    return FALSE;
}

VOID I3000_589IK14_Model::simulate(ABSTIME time, DSIMMODES mode) {}

VOID I3000_589IK14_Model::callback(ABSTIME time, EVENTID eventid) {}

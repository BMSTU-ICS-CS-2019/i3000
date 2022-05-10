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

#include <589IK03/model.hpp>

INT I3000_589IK03_Model::isdigital(CHAR* pinname) {
    return 1;
}

VOID I3000_589IK03_Model::setup(IINSTANCE* instance, IDSIMCKT* dsim) {
    _instance = instance;

    _pin_EC8 = instance->getdsimpin("EC8", true);
    _pin_Y7 = instance->getdsimpin("Y7", true);
    _pin_X7 = instance->getdsimpin("X7", true);
    _pin_Y6 = instance->getdsimpin("Y6", true);
    _pin_X6 = instance->getdsimpin("X6", true);
    _pin_Y5 = instance->getdsimpin("Y5", true);
    _pin_X5 = instance->getdsimpin("X5", true);
    _pin_Y4 = instance->getdsimpin("Y4", true);
    _pin_X4 = instance->getdsimpin("X4", true);
    _pin_Y3 = instance->getdsimpin("Y3", true);
    _pin_X3 = instance->getdsimpin("X3", true);
    _pin_Y2 = instance->getdsimpin("Y2", true);
    _pin_X2 = instance->getdsimpin("X2", true);
    _pin_Y1 = instance->getdsimpin("Y1", true);
    _pin_X1 = instance->getdsimpin("X1", true);
    _pin_Y0 = instance->getdsimpin("Y0", true);
    _pin_X0 = instance->getdsimpin("X0", true);
    _pin_CN = instance->getdsimpin("Cn", true);

    _pin_CN8 = instance->getdsimpin("Cn+8", true);
    _pin_CN7 = instance->getdsimpin("Cn+7", true);
    _pin_CN6 = instance->getdsimpin("Cn+6", true);
    _pin_CN5 = instance->getdsimpin("Cn+5", true);
    _pin_CN4 = instance->getdsimpin("Cn+4", true);
    _pin_CN3 = instance->getdsimpin("Cn+3", true);
    _pin_CN2 = instance->getdsimpin("Cn+2", true);
    _pin_CN1 = instance->getdsimpin("Cn+1", true);

    _pin_UCC = instance->getdsimpin("Ucc", true);
    _pin_GND = instance->getdsimpin("GND", true);
}


VOID I3000_589IK03_Model::runctrl(RUNMODES mode) {}

VOID I3000_589IK03_Model::actuate(REALTIME time, ACTIVESTATE newstate) {}

BOOL I3000_589IK03_Model::indicate(REALTIME time, ACTIVEDATA* newstate) {
    return FALSE;
}

VOID I3000_589IK03_Model::simulate(ABSTIME time, DSIMMODES mode) {}

VOID I3000_589IK03_Model::callback(ABSTIME time, EVENTID eventid) {}


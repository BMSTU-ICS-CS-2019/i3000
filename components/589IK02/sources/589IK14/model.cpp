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

#include <589IK02/model.hpp>

INT I3000_589IK02_Model::isdigital(CHAR* pinname) {
    return 1;
}

VOID I3000_589IK02_Model::setup(IINSTANCE* instance, IDSIMCKT* dsim) {
    // INSTANCE
    _instance = instance;

    // INPUT PINS
    _pin_CI = instance->getdsimpin("CI", false);
    _pin_RI = instance->getdsimpin("RI", false);
    _pin_M0 = instance->getdsimpin("M0", false);
    _pin_M1 = instance->getdsimpin("M1", false);
    _pin_I0 = instance->getdsimpin("I0", false);
    _pin_I1 = instance->getdsimpin("I1", false);
    _pin_K0 = instance->getdsimpin("K0", false);
    _pin_F0 = instance->getdsimpin("F0", false);
    _pin_F1 = instance->getdsimpin("F1", false);
    _pin_F2 = instance->getdsimpin("F2", false);
    _pin_F3 = instance->getdsimpin("F3", false);
    _pin_F4 = instance->getdsimpin("F4", false);
    _pin_F5 = instance->getdsimpin("F5", false);
    _pin_F6 = instance->getdsimpin("F6", false);
    _pin_CLK = instance->getdsimpin("CLK", false);
    _pin_EA = instance->getdsimpin("EA", false);
    _pin_ED = instance->getdsimpin("ED", false);

    // OUTPUT PINS
    _pin_R0 = instance->getdsimpin("R0", false);
    _pin_C0 = instance->getdsimpin("C0", false);
    _pin_X = instance->getdsimpin("X", false);
    _pin_Y = instance->getdsimpin("Y", false);
    _pin_A0 = instance->getdsimpin("A0", false);
    _pin_A1 = instance->getdsimpin("A1", false);
    _pin_D0 = instance->getdsimpin("D0", false);
    _pin_D1 = instance->getdsimpin("D1", false);

    _pin_GND = instance->getdsimpin("GND", false);
    _pin_UCC = instance->getdsimpin("Ucc", false);
}

VOID I3000_589IK02_Model::runctrl(RUNMODES mode) {}

VOID I3000_589IK02_Model::actuate(REALTIME time, ACTIVESTATE newstate) {}

BOOL I3000_589IK02_Model::indicate(REALTIME time, ACTIVEDATA* newstate) {
    return FALSE;
}

VOID I3000_589IK02_Model::simulate(ABSTIME time, DSIMMODES mode) {}

VOID I3000_589IK02_Model::callback(ABSTIME time, EVENTID eventid) {}
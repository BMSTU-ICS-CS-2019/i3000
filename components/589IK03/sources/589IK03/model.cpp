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

void SET_STATE(bool condition, IDSIMPIN2* pin, ABSTIME time);
INT I3000_589IK03_Model::isdigital(CHAR* pinname) {
    return 1;
}

VOID I3000_589IK03_Model::setup(IINSTANCE* instance, IDSIMCKT* dsimckt) {
    _instance = instance;
    _ckt = dsimckt;

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

    // SET 'SLO' STATE TO OUTPUT PINS
    _pin_CN8->setstate(SLO);
    _pin_CN7->setstate(SLO);
    _pin_CN6->setstate(SLO);
    _pin_CN5->setstate(SLO);
    _pin_CN4->setstate(SLO);
    _pin_CN3->setstate(SLO);
    _pin_CN2->setstate(SLO);
    _pin_CN1->setstate(SLO);
}


VOID I3000_589IK03_Model::runctrl(RUNMODES mode) {}

VOID I3000_589IK03_Model::actuate(REALTIME time, ACTIVESTATE newstate) {}

BOOL I3000_589IK03_Model::indicate(REALTIME time, ACTIVEDATA* newstate) {
    return FALSE;
}

VOID I3000_589IK03_Model::simulate(ABSTIME time, DSIMMODES mode) {
        BOOL CN = islow(_pin_CN->getstate());

        BOOL Y7 = ishigh(_pin_Y7->getstate());
        BOOL X7 = ishigh(_pin_X7->getstate());
        BOOL Y6 = ishigh(_pin_Y6->getstate());
        BOOL X6 = ishigh(_pin_X6->getstate());
        BOOL Y5 = ishigh(_pin_Y5->getstate());
        BOOL X5 = ishigh(_pin_X5->getstate());
        BOOL Y4 = ishigh(_pin_Y4->getstate());
        BOOL X4 = ishigh(_pin_X4->getstate());
        BOOL Y3 = ishigh(_pin_Y3->getstate());
        BOOL X3 = ishigh(_pin_X3->getstate());
        BOOL Y2 = ishigh(_pin_Y2->getstate());
        BOOL X2 = ishigh(_pin_X2->getstate());
        BOOL Y1 = ishigh(_pin_Y1->getstate());
        BOOL X1 = ishigh(_pin_X1->getstate());
        BOOL Y0 = ishigh(_pin_Y0->getstate());
        BOOL X0 = ishigh(_pin_X0->getstate());
        BOOL EC8 = ishigh(_pin_EC8->getstate());

        BOOL CN1 = X0 & Y0 | Y0 & CN;
        BOOL CN2 = X1 & Y1 | Y1 & CN1;
        BOOL CN3 = X2 & Y2 | Y2 & CN2;
        BOOL CN4 = X3 & Y3 | Y3 & CN3;
        BOOL CN5 = X4 & Y4 | Y4 & CN4;
        BOOL CN6 = X5 & Y5 | Y5 & CN5;
        BOOL CN7 = X6 & Y6 | Y6 & CN6;
        BOOL CN8 = X7 & Y7 | Y7 & CN7;

        /// Setting the states to outputs.
        SET_INVERSE_STATE(CN1, _pin_CN1, time);
        SET_INVERSE_STATE(CN2, _pin_CN2, time);
        SET_INVERSE_STATE(CN3, _pin_CN3, time);
        SET_INVERSE_STATE(CN4, _pin_CN4, time);
        SET_INVERSE_STATE(CN5, _pin_CN5, time);
        SET_INVERSE_STATE(CN6, _pin_CN6, time);
        SET_INVERSE_STATE(CN7, _pin_CN7, time);

        if (FALSE == EC8) {
            // to FALSE actually =)
            SET_INVERSE_STATE(TRUE, _pin_CN8, time);
        } else {
            SET_INVERSE_STATE(CN8, _pin_CN8, time);
        }
}

VOID I3000_589IK03_Model::callback(ABSTIME time, EVENTID eventid) {}


VOID I3000_589IK03_Model::SET_INVERSE_STATE(BOOL condition, IDSIMPIN2 *pin, ABSTIME time) {
    FALSE != condition ? pin->setstate(time, details::DELAY, SLO) : pin->setstate(time, details::DELAY, SHI);
}


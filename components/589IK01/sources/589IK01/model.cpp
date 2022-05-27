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

#include <589IK01/model.hpp>

void SET_STATE(bool condition, IDSIMPIN2* pin, ABSTIME time);
INT I3000_589IK01_Model::isdigital(CHAR* pinname) {
    return 1;
}

VOID I3000_589IK01_Model::setup(IINSTANCE* instance, IDSIMCKT* dsimckt) {
    _instance = instance;
    _ckt = dsimckt;
    //
    //    _pin_A = instance->getdsimpin("A", true);
    //    _pin_B = instance->getdsimpin("B", true);
    _pin_EWA = instance->getdsimpin("EWA", true);
    _pin_FI = instance->getdsimpin("FI", true);
    _pin_AC6 = instance->getdsimpin("AC6", true);
    _pin_AC5 = instance->getdsimpin("AC5", true);
    _pin_AC4 = instance->getdsimpin("AC4", true);
    _pin_AC3 = instance->getdsimpin("AC3", true);
    _pin_AC2 = instance->getdsimpin("AC2", true);
    _pin_AC1 = instance->getdsimpin("AC1", true);
    _pin_AC0 = instance->getdsimpin("AC0", true);
    _pin_FC3 = instance->getdsimpin("FC3", true);
    _pin_FC2 = instance->getdsimpin("FC2", true);
    _pin_FC1 = instance->getdsimpin("FC1", true);
    _pin_FC0 = instance->getdsimpin("FC0", true);
    _pin_K7 = instance->getdsimpin("K7", true);
    _pin_K6 = instance->getdsimpin("K6", true);
    _pin_K5 = instance->getdsimpin("K5", true);
    _pin_K4 = instance->getdsimpin("K4", true);
    _pin_K3 = instance->getdsimpin("K3", true);
    _pin_K2 = instance->getdsimpin("K2", true);
    _pin_K1 = instance->getdsimpin("K1", true);
    _pin_K0 = instance->getdsimpin("K0", true);
    _pin_CLK = instance->getdsimpin("CLK", true);
    _pin_ERA = instance->getdsimpin("ERA", true);
    _pin_EN = instance->getdsimpin("EN", true);
    _pin_A8 = instance->getdsimpin("A8", true);
    _pin_A7 = instance->getdsimpin("A7", true);
    _pin_A6 = instance->getdsimpin("A6", true);
    _pin_A5 = instance->getdsimpin("A5", true);
    _pin_A4 = instance->getdsimpin("A4", true);
    _pin_A3 = instance->getdsimpin("A3", true);
    _pin_A2 = instance->getdsimpin("A2", true);
    _pin_A1 = instance->getdsimpin("A1", true);
    _pin_A0 = instance->getdsimpin("A0", true);
    _pin_PK2 = instance->getdsimpin("PK2", true);
    _pin_PK1 = instance->getdsimpin("PK1", true);
    _pin_PK0 = instance->getdsimpin("PK0", true);
    _pin_INE = instance->getdsimpin("INE", true);
    _pin_FO = instance->getdsimpin("FO", true);

    _pin_A8->setstate(SLO);
    _pin_A7->setstate(SLO);
    _pin_A6->setstate(SLO);
    _pin_A5->setstate(SLO);
    _pin_A4->setstate(SLO);
    _pin_A3->setstate(SLO);
    _pin_A2->setstate(SLO);
    _pin_A1->setstate(SLO);
    _pin_A0->setstate(SLO);
    _pin_PK2->setstate(SLO);
    _pin_PK1->setstate(SLO);
    _pin_PK0->setstate(SLO);
    _pin_INE->setstate(SLO);
    _pin_FO->setstate(SLO);
    //    _pin_B->setstate(SLO);
}


VOID I3000_589IK01_Model::runctrl(RUNMODES mode) {}

VOID I3000_589IK01_Model::actuate(REALTIME time, ACTIVESTATE newstate) {}

BOOL I3000_589IK01_Model::indicate(REALTIME time, ACTIVEDATA* newstate) {
    return FALSE;
}

VOID I3000_589IK01_Model::simulate(ABSTIME time, DSIMMODES mode) {
    if (IS_HIGH(_pin_CLK)) {
        if (_previous_CLK_state == false){
            // Фронт
            auto state = get_micro_operation();
            switch (state) {
                case JCC:
                    RUN_JCC();
                    break;
                case JZR:
                    RUN_JZR();
                    break;
                case JCR:
                    RUN_JCR();
                    break;
                case JFL:
                    RUN_JFL();
                    break;
                case JCF:
                    RUN_JCF();
                    break;
                case JZF:
                    RUN_JZF();
                    break;
                case JPR:
                    RUN_JPR();
                    break;
                case JLL:
                    RUN_JLL();
                    break;
                case JCE:
                    RUN_JCE();
                    break;
                case JPX:
                    RUN_JPX();
                    break;
                case JRL:
                    RUN_JRL();
                    break;
            }
            _previous_CLK_state = true;
        }
    }
    else{
        if (_previous_CLK_state == true){
            // Спад
        }
    }
}

VOID I3000_589IK01_Model::callback(ABSTIME time, EVENTID eventid) {}


VOID I3000_589IK01_Model::SET_STATE(bool condition, IDSIMPIN2* pin, ABSTIME time) {
    condition ? pin->setstate(time, details::DELAY, SHI) : pin->setstate(time, details::DELAY, SLO);
}

BOOL I3000_589IK01_Model::IS_HIGH(IDSIMPIN * pin){
    return pin->isposedge();
}
BOOL I3000_589IK01_Model::IS_LOW(IDSIMPIN * pin){
    return pin->isposedge();
}
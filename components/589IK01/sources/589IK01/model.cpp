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
#include <string>

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
    if (_pin_CLK->isposedge()) {
        //        if (_previous_CLK_state == false) {
        // Фронт
        if (IS_HIGH(_pin_EWA)) {
            output_K_A();
        } else {
            output_logic_A();
        }
        output_flags();
        set_PR_latch();
        //            _previous_CLK_state = true;
        //        }
    } else if (_pin_CLK->isnegedge()) {
        set_flags();
    } else if (IS_LOW(_pin_CLK)) {
        _F = IS_LOW(_pin_FI);
    }
}

VOID I3000_589IK01_Model::callback(ABSTIME time, EVENTID eventid) {}


VOID I3000_589IK01_Model::SET_STATE(bool condition, IDSIMPIN2* pin, ABSTIME time) {
    if (IS_HIGH(_pin_EN)) {
        condition ? pin->setstate(time, details::DELAY, SHI) : pin->setstate(time, details::DELAY, SLO);
        save_state(condition, pin);
    }
}

BOOL I3000_589IK01_Model::IS_HIGH(IDSIMPIN* pin) {
    return pin->isactive();
}
BOOL I3000_589IK01_Model::IS_LOW(IDSIMPIN* pin) {
    return 1 - IS_HIGH(pin);
}
void I3000_589IK01_Model::set_flags() {
    auto flag_mnemonic = get_flag_input_mnemonic();
    switch (flag_mnemonic) {
        case SCZ:
            _C = _F;
            _Z = _F;
            break;
        case STZ:
            _Z = _F;
            break;
        case STC:
            _C = _F;
            break;
        case HCZ:
            break;
    }
}

void I3000_589IK01_Model::output_flags() {
    auto flag_mnemonic = get_flag_output_mnemonic();
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>(("output_logic_A" + std::to_string(flag_mnemonic)).c_str()),
               reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif
    switch (flag_mnemonic) {
        case FF0:
            SET_STATE(true, _pin_FO);
            break;
        case FFC:
            SET_STATE(1-_C, _pin_FO);
            break;
        case FFZ:
            SET_STATE(1-_Z, _pin_FO);
            break;
        case FF1:
            SET_STATE(false, _pin_FO);
            break;
    }
}
void I3000_589IK01_Model::output_logic_A() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("output_logic_A"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif

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
    if (_A_values[0] == TRUE && _A_values[1] == TRUE && _A_values[2] == TRUE && _A_values[3] == TRUE
        && _A_values[4] == FALSE && _A_values[5] == FALSE && _A_values[6] == FALSE && _A_values[7] == FALSE
        && _A_values[8] == FALSE) {
        SET_STATE(true, _pin_INE);
    }
    else{
        SET_STATE(false, _pin_INE);
    }
}
void I3000_589IK01_Model::set_PR_latch() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("set_PR_latch"), reinterpret_cast<LPCSTR>("Hel!"), MB_ICONERROR);
#endif

    _PR_latch[0] = IS_LOW(_pin_K0);
    _PR_latch[1] = IS_LOW(_pin_K1);
    _PR_latch[2] = IS_LOW(_pin_K2);
    _PR_latch[3] = IS_LOW(_pin_K3);
}
I3000_589IK01_Model::FlagOutputMnemonic I3000_589IK01_Model::get_flag_output_mnemonic() const {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("get_flag_output_mnemonic"), reinterpret_cast<LPCSTR>("Hello!"),
               MB_ICONERROR);
#endif

    if (IS_LOW(_pin_FC3) && IS_LOW(_pin_FC2)) {
        return FF0;
    }
    if (IS_LOW(_pin_FC3) && IS_HIGH(_pin_FC2)) {
        return FFC;
    }
    if (IS_HIGH(_pin_FC3) && IS_LOW(_pin_FC2)) {
        return FFZ;
    }
    if (IS_HIGH(_pin_FC3) && IS_HIGH(_pin_FC2)) {
        return FF1;
    }
    throw 42;
}
I3000_589IK01_Model::FlagInputMnemonic I3000_589IK01_Model::get_flag_input_mnemonic() const {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("get_flag_input_mnemonic"), reinterpret_cast<LPCSTR>("Hello!"),
               MB_ICONERROR);
#endif

    if (IS_LOW(_pin_FC1) && IS_LOW(_pin_FC0)) {
        return SCZ;
    }
    if (IS_LOW(_pin_FC1) && IS_HIGH(_pin_FC0)) {
        return STZ;
    }
    if (IS_HIGH(_pin_FC1) && IS_LOW(_pin_FC0)) {
        return STC;
    }
    if (IS_HIGH(_pin_FC1) && IS_HIGH(_pin_FC0)) {
        return HCZ;
    }
    throw 42;
}
void I3000_589IK01_Model::output_K_A() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("output_K_A"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif

    SET_STATE(IS_LOW(_pin_K4), _pin_A0);
    SET_STATE(IS_LOW(_pin_K5), _pin_A1);
    SET_STATE(IS_LOW(_pin_K6), _pin_A2);
    SET_STATE(IS_LOW(_pin_K7), _pin_A3);
    if (IS_HIGH(_pin_ERA)) {
        SET_STATE(IS_LOW(_pin_K0), _pin_A4);
        SET_STATE(IS_LOW(_pin_K1), _pin_A5);
        SET_STATE(IS_LOW(_pin_K2), _pin_A6);
        SET_STATE(IS_LOW(_pin_K3), _pin_A7);
        SET_STATE(false, _pin_A8);
    }
    SET_STATE(false, _pin_INE);

}
VOID I3000_589IK01_Model::RUN_JCC() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("JCC"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif
    if (IS_HIGH(_pin_ERA)) {
        SET_STATE(IS_HIGH(_pin_AC0), _pin_A4);
        SET_STATE(IS_HIGH(_pin_AC1), _pin_A5);
        SET_STATE(IS_HIGH(_pin_AC2), _pin_A6);
        SET_STATE(IS_HIGH(_pin_AC3), _pin_A7);
        SET_STATE(IS_HIGH(_pin_AC4), _pin_A8);
    }
}
VOID I3000_589IK01_Model::RUN_JCR() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("JCR"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif

    SET_STATE(IS_HIGH(_pin_AC0), _pin_A0);
    SET_STATE(IS_HIGH(_pin_AC1), _pin_A1);
    SET_STATE(IS_HIGH(_pin_AC2), _pin_A2);
    SET_STATE(IS_HIGH(_pin_AC3), _pin_A3);
}
VOID I3000_589IK01_Model::RUN_JZR() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("JZR"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif

    SET_STATE(IS_HIGH(_pin_AC0), _pin_A0);
    SET_STATE(IS_HIGH(_pin_AC1), _pin_A1);
    SET_STATE(IS_HIGH(_pin_AC2), _pin_A2);
    SET_STATE(IS_HIGH(_pin_AC3), _pin_A3);
    if (IS_HIGH(_pin_ERA)) {
        SET_STATE(false, _pin_A4);
        SET_STATE(false, _pin_A5);
        SET_STATE(false, _pin_A6);
        SET_STATE(false, _pin_A7);
        SET_STATE(false, _pin_A8);
    }
}
VOID I3000_589IK01_Model::RUN_JFL() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("JFL"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif

    SET_STATE(_F, _pin_A0);
    SET_STATE(true, _pin_A1);
    SET_STATE(false, _pin_A2);
    if (IS_HIGH(_pin_ERA)) {
        SET_STATE(IS_HIGH(_pin_AC0), _pin_A4);
        SET_STATE(IS_HIGH(_pin_AC1), _pin_A5);
        SET_STATE(IS_HIGH(_pin_AC2), _pin_A6);
        SET_STATE(IS_HIGH(_pin_AC3), _pin_A7);
    }
}
VOID I3000_589IK01_Model::RUN_JCF() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("JCF"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif

    SET_STATE(_C, _pin_A0);
    SET_STATE(true, _pin_A1);
    SET_STATE(false, _pin_A2);
    if (IS_HIGH(_pin_ERA)) {
        SET_STATE(IS_HIGH(_pin_AC0), _pin_A4);
        SET_STATE(IS_HIGH(_pin_AC1), _pin_A5);
        SET_STATE(IS_HIGH(_pin_AC2), _pin_A6);
    }
}
VOID I3000_589IK01_Model::RUN_JZF() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("JZF"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif

    SET_STATE(_Z, _pin_A0);
    SET_STATE(true, _pin_A1);
    SET_STATE(false, _pin_A2);
    if (IS_HIGH(_pin_ERA)) {
        SET_STATE(IS_HIGH(_pin_AC0), _pin_A4);
        SET_STATE(IS_HIGH(_pin_AC1), _pin_A5);
        SET_STATE(IS_HIGH(_pin_AC2), _pin_A6);
    }
}
VOID I3000_589IK01_Model::RUN_JPR() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("JPR"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif

    SET_STATE(_PR_latch[0], _pin_A0);
    SET_STATE(_PR_latch[1], _pin_A1);
    SET_STATE(_PR_latch[2], _pin_A2);
    SET_STATE(_PR_latch[3], _pin_A3);
    if (IS_HIGH(_pin_ERA)) {
        SET_STATE(IS_HIGH(_pin_AC0), _pin_A4);
        SET_STATE(IS_HIGH(_pin_AC1), _pin_A5);
        SET_STATE(IS_HIGH(_pin_AC2), _pin_A6);
    }
}
VOID I3000_589IK01_Model::RUN_JLL() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("JLL"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif

    SET_STATE(_PR_latch[2], _pin_A0);
    SET_STATE(_PR_latch[3], _pin_A1);
    SET_STATE(true, _pin_A2);
    SET_STATE(false, _pin_A3);
    if (IS_HIGH(_pin_ERA)) {
        SET_STATE(IS_HIGH(_pin_AC0), _pin_A4);
        SET_STATE(IS_HIGH(_pin_AC1), _pin_A5);
        SET_STATE(IS_HIGH(_pin_AC2), _pin_A6);
    }
}
VOID I3000_589IK01_Model::RUN_JCE() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("JCE"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif
    if (IS_HIGH(_pin_ERA)) {
        SET_STATE(IS_HIGH(_pin_AC0), _pin_A4);
        SET_STATE(IS_HIGH(_pin_AC1), _pin_A5);
        SET_STATE(IS_HIGH(_pin_AC2), _pin_A6);
    }
    SET_STATE(_PR_latch[0], _pin_PK0);
    SET_STATE(_PR_latch[1], _pin_PK1);
    SET_STATE(_PR_latch[2], _pin_PK2);
}
VOID I3000_589IK01_Model::RUN_JPX() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("JPX"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif

    set_PR_latch();
    SET_STATE(IS_LOW(_pin_K4), _pin_A0);
    SET_STATE(IS_LOW(_pin_K5), _pin_A1);
    SET_STATE(IS_LOW(_pin_K6), _pin_A2);
    SET_STATE(IS_LOW(_pin_K7), _pin_A3);
    if (IS_HIGH(_pin_ERA)) {
        SET_STATE(IS_HIGH(_pin_AC0), _pin_A4);
        SET_STATE(IS_HIGH(_pin_AC1), _pin_A5);
    }
}
VOID I3000_589IK01_Model::RUN_JRL() {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("JRL"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif

    SET_STATE(_PR_latch[0], _pin_A0);
    SET_STATE(_PR_latch[1], _pin_A1);
    SET_STATE(true, _pin_A2);
    SET_STATE(true, _pin_A3);
    if (IS_HIGH(_pin_ERA)) {
        SET_STATE(IS_HIGH(_pin_AC0), _pin_A4);
        SET_STATE(IS_HIGH(_pin_AC1), _pin_A5);
        SET_STATE(true, _pin_A6);
    }
}
I3000_589IK01_Model::MicroOperationMnemonic I3000_589IK01_Model::get_micro_operation() const {
#ifdef RK_MESSAGE_BOX
    MessageBox(nullptr, reinterpret_cast<LPCSTR>("get_micro_operation"), reinterpret_cast<LPCSTR>("Hello!"),
               MB_ICONERROR);
#endif

    if (IS_LOW(_pin_AC6) && IS_LOW(_pin_AC5)) {
        return JCC;
    }
    if (IS_LOW(_pin_AC6) && IS_HIGH(_pin_AC5) && IS_LOW(_pin_AC4)) {
#ifdef RK_MESSAGE_BOX
        MessageBox(nullptr, reinterpret_cast<LPCSTR>("JZR_op"), reinterpret_cast<LPCSTR>("Hello!"), MB_ICONERROR);
#endif
        return JZR;
    }
    if (IS_LOW(_pin_AC6) && IS_HIGH(_pin_AC5) && IS_HIGH(_pin_AC4)) {
        return JCR;
    }
    if (IS_HIGH(_pin_AC6) && IS_LOW(_pin_AC5) && IS_LOW(_pin_AC4)) {
        return JFL;
    }
    if (IS_HIGH(_pin_AC6) && IS_LOW(_pin_AC5) && IS_HIGH(_pin_AC4) && IS_LOW(_pin_AC3)) {
        return JCF;
    }
    if (IS_HIGH(_pin_AC6) && IS_LOW(_pin_AC5) && IS_HIGH(_pin_AC4) && IS_HIGH(_pin_AC3)) {
        return JZF;
    }
    if (IS_HIGH(_pin_AC6) && IS_HIGH(_pin_AC5) && IS_LOW(_pin_AC4) && IS_LOW(_pin_AC3)) {
        return JPR;
    }
    if (IS_HIGH(_pin_AC6) && IS_HIGH(_pin_AC5) && IS_LOW(_pin_AC4) && IS_HIGH(_pin_AC3)) {
        return JLL;
    }
    if (IS_HIGH(_pin_AC6) && IS_HIGH(_pin_AC5) && IS_HIGH(_pin_AC4) && IS_LOW(_pin_AC3)) {
        return JCE;
    }
    if (IS_HIGH(_pin_AC6) && IS_HIGH(_pin_AC5) && IS_HIGH(_pin_AC4) && IS_HIGH(_pin_AC3) && IS_LOW(_pin_AC2)) {
        return JPX;
    }
    if (IS_HIGH(_pin_AC6) && IS_HIGH(_pin_AC5) && IS_HIGH(_pin_AC4) && IS_HIGH(_pin_AC3) && IS_HIGH(_pin_AC2)) {
        return JRL;
    }
    throw 42;
}
void I3000_589IK01_Model::save_state(bool condition, IDSIMPIN2* pin) {
    if (pin == _pin_A0) {
        _A_values[0] = condition;
    } else if (pin == _pin_A1) {
        _A_values[1] = condition;
    } else if (pin == _pin_A2) {
        _A_values[2] = condition;
    } else if (pin == _pin_A3) {
        _A_values[3] = condition;
    } else if (pin == _pin_A4) {
        _A_values[4] = condition;
    } else if (pin == _pin_A5) {
        _A_values[5] = condition;
    } else if (pin == _pin_A6) {
        _A_values[6] = condition;
    } else if (pin == _pin_A7) {
        _A_values[7] = condition;
    } else if (pin == _pin_A8) {
        _A_values[8] = condition;
    }
}

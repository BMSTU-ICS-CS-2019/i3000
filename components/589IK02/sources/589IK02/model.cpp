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

VOID I3000_589IK02_Model::setup(IINSTANCE* instance, IDSIMCKT* dsimckt) {
    // INSTANCE
    _instance = instance;
    _ckt = dsimckt;

    // INPUT PINS
    _pin_CI = instance->getdsimpin("CI", true);
    _pin_RI = instance->getdsimpin("RI", true);
    _pin_M0 = instance->getdsimpin("M0", true);
    _pin_M1 = instance->getdsimpin("M1", true);
    _pin_I0 = instance->getdsimpin("I0", true);
    _pin_I1 = instance->getdsimpin("I1", true);
    _pin_K0 = instance->getdsimpin("K0", true);
    _pin_K1 = instance->getdsimpin("K1", true);
    _pin_F0 = instance->getdsimpin("F0", true);
    _pin_F1 = instance->getdsimpin("F1", true);
    _pin_F2 = instance->getdsimpin("F2", true);
    _pin_F3 = instance->getdsimpin("F3", true);
    _pin_F4 = instance->getdsimpin("F4", true);
    _pin_F5 = instance->getdsimpin("F5", true);
    _pin_F6 = instance->getdsimpin("F6", true);
    _pin_CLK = instance->getdsimpin("CLK", true);
    _pin_EA = instance->getdsimpin("EA", true);
    _pin_ED = instance->getdsimpin("ED", true);

    // OUTPUT PINS
    _pin_R0 = instance->getdsimpin("R0", true);
    _pin_C0 = instance->getdsimpin("C0", true);
    _pin_X = instance->getdsimpin("X", true);
    _pin_Y = instance->getdsimpin("Y", true);
    _pin_A0 = instance->getdsimpin("A0", true);
    _pin_A1 = instance->getdsimpin("A1", true);
    _pin_D0 = instance->getdsimpin("D0", true);
    _pin_D1 = instance->getdsimpin("D1", true);

    // SET 'SLO' STATE TO OUTPUT PINS
    _pin_R0->setstate(SLO);
    _pin_C0->setstate(SLO);
    _pin_X->setstate(SLO);
    _pin_Y->setstate(SLO);
    _pin_A0->setstate(SLO);
    _pin_A1->setstate(SLO);
    _pin_D0->setstate(SLO);
    _pin_D1->setstate(SLO);

    for (UINT& _ron : _rons) { _ron = 0U; }
    _T = 0;
    _PA = 0;
    _AC = 0;
}

VOID I3000_589IK02_Model::runctrl(RUNMODES mode) {}

VOID I3000_589IK02_Model::actuate(REALTIME time, ACTIVESTATE newstate) {}

BOOL I3000_589IK02_Model::indicate(REALTIME time, ACTIVEDATA* newstate) {
    return FALSE;
}

VOID I3000_589IK02_Model::simulate(ABSTIME time, DSIMMODES mode) {
    if (FALSE == prev_state && _pin_CLK->isposedge()) {

        // R-GROUP
        UINT R_group = TO_UINT(_pin_F3, _pin_F2, _pin_F1, _pin_F0);
        // F-GROUP
        UINT F_group = TO_UINT(_pin_F6, _pin_F5, _pin_F4);

        // Choosing Rn_AT or AT.
        UINT* Rn_AT;
        for (UINT& _ron : _rons) {
            if (_ron == F_group) { Rn_AT = &_ron; }
        }

        if (R_group > 9U) {
            if ((R_group & 1U) != 0U) {
                Rn_AT = &_AC;
            }
            else {
                Rn_AT = &_T;
            }
        }

        UINT Rn_M_AT;

        if (R_group == 10U || R_group == 11U) {
            Rn_M_AT = TO_INVERSE_UINT(_pin_M1, _pin_M0);
        }
        else {
            Rn_M_AT = *Rn_AT;
        }

        // Choosing B or AC.
        UINT B_AC;
        if (R_group < 14U) {
            B_AC = _AC;
        }
        else {
            B_AC = TO_INVERSE_UINT(_pin_I1, _pin_I0);
        }

        if (F_group > 1U) { B_AC = B_AC & TO_INVERSE_UINT(_pin_K1, _pin_K0); }

        UINT C1 = TO_INVERSE_UINT(_pin_CI);
        UINT R1 = TO_INVERSE_UINT(_pin_RI);
        UINT K = TO_INVERSE_UINT(_pin_K1, _pin_K0);

        C0 = 0U;
        R0 = 0U;

        switch (F_group) {
        case 0:
            if (R_group < 14U) {
                *Rn_AT = (Rn_M_AT + B_AC + C1) % 4;
            }
            else {
                R0 = 1 & Rn_M_AT & !B_AC;
                *Rn_AT = 2U & ((R1 << 1U) | (B_AC & Rn_M_AT));
                *Rn_AT |= 1U & ((Rn_M_AT & B_AC) | ((Rn_M_AT & B_AC) >> 1U));
            }
            break;
        case 1:
            if (R_group < 14) {
                _PA = K | Rn_M_AT;
                *Rn_AT = (Rn_M_AT + K + C1) % 4;
            }
            else {
                *Rn_AT = ((!Rn_M_AT | K) + (Rn_M_AT & K) + C1) % 4;
            }
            break;
        case 2:
            *Rn_AT = (B_AC - 1U + C1) % 4;
            break;
        case 3:
            *Rn_AT = (Rn_M_AT + B_AC + C1) % 4;
            break;
        case 4:
            C0 = C1 | (Rn_M_AT & B_AC);
            *Rn_AT = Rn_M_AT & B_AC;
            break;
        case 5:
            C0 = C1 | (Rn_M_AT & K);
            *Rn_AT = K & Rn_M_AT;
            break;
        case 6:
            C0 = C1 | B_AC;
            *Rn_AT = Rn_M_AT & B_AC;
            break;
        case 7:
            C0 = C1 | (Rn_M_AT & B_AC);
            *Rn_AT = !(Rn_M_AT ^ B_AC);
            break;
        default:
            break;
        }
        _AC = *Rn_AT;

        UINT a0 = TO_INVERSE_UINT(_pin_M0);
        UINT a1 = TO_INVERSE_UINT(_pin_M1);
        UINT b0 = TO_INVERSE_UINT(_pin_I0) & TO_INVERSE_UINT(_pin_K0);
        UINT b1 = TO_INVERSE_UINT(_pin_I1) & TO_INVERSE_UINT(_pin_K1);

        /*UINT*/ X = a0 & b0 | a1 & b1;
        /*UINT*/ Y = a1 & b1 | a0 & b1 | b0 & b1 | a0 & a1;

        if (ishigh(_pin_EA->getstate())) {
            A0 = 0U;
            A1 = 0U;
        }
        else {
            A0 = ~_PA & 1U;
            A1 = ~_PA & 2U;
        }

        if (ishigh(_pin_ED->getstate())) {
            D0 = 0U;
            D1 = 0U;
        }
        else {
            D0 = ~_AC & 1U;
            D1 = ~_AC & 2U;
        }
    }
    else if (TRUE == prev_state && !_pin_CLK->isposedge()) {
        /// Setting the states to outputs.
        SET_STATE(C0 == 0U, _pin_C0, time);
        SET_STATE(R0 == 0U, _pin_R0, time);
        SET_STATE(X != 0U, _pin_X, time);
        SET_STATE(Y != 0U, _pin_Y, time);

        SET_STATE(A0 != 0U, _pin_A0, time);
        SET_STATE(A1 != 0U, _pin_A1, time);
        SET_STATE(D0 != 0U, _pin_D0, time);
        SET_STATE(D1 != 0U, _pin_D1, time);
    }

    prev_state = _pin_CLK->isposedge();
}

VOID I3000_589IK02_Model::callback(ABSTIME time, EVENTID eventid) {}


UINT I3000_589IK02_Model::TO_UINT(IDSIMPIN* p8, IDSIMPIN* p4, IDSIMPIN* p2, IDSIMPIN* p1) {
    UINT res = 0U;
    if (ishigh(p8->istate())) { res += 8U; }
    if (ishigh(p4->istate())) { res += 4U; }
    if (ishigh(p2->istate())) { res += 2U; }
    if (ishigh(p1->istate())) { res += 1U; }
    return res;
}

UINT I3000_589IK02_Model::TO_UINT(IDSIMPIN* p4, IDSIMPIN* p2, IDSIMPIN* p1) {
    UINT res = 0U;
    if (ishigh(p4->istate())) { res += 4U; }
    if (ishigh(p2->istate())) { res += 2U; }
    if (ishigh(p1->istate())) { res += 1U; }
    return res;
}

UINT I3000_589IK02_Model::TO_INVERSE_UINT(IDSIMPIN* p2, IDSIMPIN* p1) {
    UINT res = 0U;
    if (islow(p2->istate())) { res += 2U; }
    if (islow(p1->istate())) { res += 1U; }
    return res;
}

UINT I3000_589IK02_Model::TO_INVERSE_UINT(IDSIMPIN2* p) {
    return islow(p->istate()) ? 1U : 0U;
}

VOID I3000_589IK02_Model::SET_STATE(bool condition, IDSIMPIN2* pin, ABSTIME time) {
    condition ? pin->setstate(time, details::DELAY, SHI) : pin->setstate(time, details::DELAY, SLO);
}

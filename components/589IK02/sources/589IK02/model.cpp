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

/*
ЗАПУСКАЕМ
░ГУСЯ░▄▀▀▀▄░РАБОТЯГИ░░
▄███▀░◐░░░▌░░░░░░░
░░░░▌░░░░░▐░░░░░░░
░░░░▐░░░░░▐░░░░░░░
░░░░▌░░░░░▐▄▄░░░░░
░░░░▌░░░░▄▀▒▒▀▀▀▀▄
░░░▐░░░░▐▒▒▒▒▒▒▒▒▀▀▄
░░░▐░░░░▐▄▒▒▒▒▒▒▒▒▒▒▀▄
░░░░▀▄░░░░▀▄▒▒▒▒▒▒▒▒▒▒▀▄
░░░░░░▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▀▄
░░░░░░░░░░░▌▌░▌▌░░░░░
░░░░░░░░░░░▌▌░▌▌░░░░░
░░░░░░░░░▄▄▌▌▄▌▌░░░░░
*/

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

    for (UINT& _ron: _rons) { _ron = 0U; }
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
        _instance->log("589IK02: R_group: %d, F_group: %d", R_group, F_group);

        // Choosing Rn_AT or AT.
        UINT* Rn_AT;// =X
        for (UINT i = 0U; i < 10U; ++i) {
            if (i == R_group) { Rn_AT = &_rons[i]; }
        }

        if (R_group > 9U) {
            if ((R_group & 1U) != 0U) {
                Rn_AT = &_AC;
            } else {
                Rn_AT = &_T;
            }
        }

        UINT Rn_M_AT = 0U;

        if (R_group == 10U || R_group == 11U) {
            Rn_M_AT = TO_INVERSE_UINT(_pin_M1, _pin_M0);
        } else {
            Rn_M_AT = *Rn_AT;
        }

        UINT I = TO_INVERSE_UINT(_pin_I1, _pin_I0);
        ;
        // Choosing B or AC.
        UINT B_AC;// = Y
        if (R_group < 14U) {
            B_AC = _AC;
        } else {
            B_AC = I;
        }


        UINT C1 = TO_INVERSE_UINT(_pin_CI);
        UINT R1 = TO_INVERSE_UINT(_pin_RI);
        UINT K = TO_INVERSE_UINT(_pin_K1, _pin_K0);

        if (F_group > 1U) { B_AC = B_AC & K; }

        _instance->log("589IK02: C1: %d, R1: %d, K: %d", C1, R1, K);

        C0 = 0U;
        R0 = 0U;

        int case2_result = 0U;

        UINT A = *Rn_AT;
        UINT B = 0;
        switch (F_group) {
            case 0:
                if (R_group < 14U) {
                    B = _AC & K;
                    // if ((Rn_M_AT + (_AC & K) + C1) > 3U) { C0 = 1U; }
                    *Rn_AT = (Rn_M_AT + (_AC & K) + C1) % 4;
                    if (R_group != 10U) { _AC = *Rn_AT; }
                } else {
                    B = I & K;
                    R0 = 1 & Rn_M_AT & ~(B_AC & K);
                    *Rn_AT = 2U & ((R1 << 1U) | (B_AC & K & Rn_M_AT));
                    *Rn_AT |= 1U & ((Rn_M_AT & B_AC & K) | ((Rn_M_AT & B_AC & K) >> 1U));
                }
                break;
            case 1:
                if (R_group < 14) {
                    B = K;
                    _PA = K | Rn_M_AT;
                    //    if ((Rn_M_AT + K + C1) > 3U) { C0 = 1U; }
                    *Rn_AT = (Rn_M_AT + K + C1) % 4;
                } else {
                    A = ((~Rn_M_AT) & 3) | K;
                    B = Rn_M_AT & K;
                    *Rn_AT = (A + B + C1) % 4;
                }
                break;
            case 2:
                B = _AC & K;
                A = 0;
                case2_result = B_AC - 1U + C1;
                if (case2_result < 0U) {
                    //C0 = 1U;
                    case2_result += 4;
                }
                *Rn_AT = case2_result;
                break;
            case 3:
                B = B_AC;
                //if ((Rn_M_AT + B_AC + C1) > 3U) { C0 = 1U; }
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
                *Rn_AT = Rn_M_AT | B_AC;
                break;
            case 7:
                C0 = C1 | (Rn_M_AT & B_AC);
                *Rn_AT = (~(Rn_M_AT ^ B_AC)) & 3;
                break;
            default:
                break;
        }

        _instance->log("589IK02: ron[0] = %d; ron[1] = %d; ron[2] = %d; ron[3] = %d; ron[4] = %d;", _rons[0], _rons[1],
                       _rons[2], _rons[3], _rons[4]);
        _instance->log("589IK02: ron[5] = %d; ron[6] = %d; ron[7] = %d; ron[8] = %d; ron[9] = %d;", _rons[5], _rons[6],
                       _rons[7], _rons[8], _rons[9]);

        _instance->log("589IK02: AC: %d, PA: %d, T: %d", _AC, _PA, _T);

        UINT a0 = A & 1U; //TO_INVERSE_UINT(_pin_M0); // 10 a0 = 00  a1 = 01
        UINT a1 = A >> 1U;//TO_INVERSE_UINT(_pin_M1);
        UINT b0 = B & 1U; //TO_INVERSE_UINT(_pin_I0) & TO_INVERSE_UINT(_pin_K0);
        UINT b1 = B >> 1U;//TO_INVERSE_UINT(_pin_I1) & TO_INVERSE_UINT(_pin_K1);

        if (F_group < 5) {
            X = a0 & b0 | a1 & b1;
            Y = a1 & b1 | a0 & b1 | b0 & b1 | a0 & a1;
            C0 = ((~(C1 & Y)) & 3) | (X & Y);
            // _instance->log("589IK02: A: %d, B: %d, R[0]: %d !!!!!!", A, B, *Rn_AT);
            if ((A != 0 || B != 0) && (*Rn_AT == 0)) { X = 1U; }
        } else {
            X = 0U;
            Y = 0U;
        }

        //_instance->log("589IK02: X: %d, Y: %d", X, Y);

        if (ishigh(_pin_EA->getstate())) {
            A0 = 0U;
            A1 = 0U;
        } else {
            A0 = ~_PA & 1U;
            A1 = ~_PA & 2U;
        }
        _instance->log("589IK02: A0: %d, A1: %d", A0, A1);

        if (ishigh(_pin_ED->getstate())) {
            D0 = 0U;
            D1 = 0U;
        } else {
            D0 = ~_AC & 1U;
            D1 = ~_AC & 2U;
        }
        _instance->log("589IK02: D0: %d, D1: %d", D0, D1);


    } else if (TRUE == prev_state && !_pin_CLK->isposedge()) {
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

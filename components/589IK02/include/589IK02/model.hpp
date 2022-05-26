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

#pragma once

#include <i3000/prelude.hpp>

namespace details{
    const RELTIME DELAY = 50'000 ;
}

class I3000_589IK02_Model : public IDSIMMODEL {
private:
    IINSTANCE* _instance;
    IDSIMCKT* _ckt;

    // INPUT PINS
    IDSIMPIN* _pin_CI;
    IDSIMPIN* _pin_RI;
    IDSIMPIN* _pin_M0;
    IDSIMPIN* _pin_M1;
    IDSIMPIN* _pin_I0;
    IDSIMPIN* _pin_I1;
    IDSIMPIN* _pin_K0;
    IDSIMPIN* _pin_K1;
    IDSIMPIN* _pin_F0;
    IDSIMPIN* _pin_F1;
    IDSIMPIN* _pin_F2;
    IDSIMPIN* _pin_F3;
    IDSIMPIN* _pin_F4;
    IDSIMPIN* _pin_F5;
    IDSIMPIN* _pin_F6;
    IDSIMPIN* _pin_CLK;
    IDSIMPIN* _pin_EA;
    IDSIMPIN* _pin_ED;

    // OUTPUT PINS
    IDSIMPIN* _pin_R0;
    IDSIMPIN* _pin_C0;
    IDSIMPIN* _pin_X;
    IDSIMPIN* _pin_Y;
    IDSIMPIN* _pin_A0;
    IDSIMPIN* _pin_A1;
    IDSIMPIN* _pin_D0;
    IDSIMPIN* _pin_D1;

    // REGISTERS
    UINT _rons[10]; // R0-R9
    UINT _T = 0; // R10
    UINT _PA = 0; // address register
    UINT _AC = 0; // battery register

    static UINT TO_UINT(IDSIMPIN* p8, IDSIMPIN* p4, IDSIMPIN* p2, IDSIMPIN* p1);

    static UINT TO_UINT(IDSIMPIN* p4, IDSIMPIN* p2, IDSIMPIN* p1);

    static UINT TO_INVERSE_UINT(IDSIMPIN *p2, IDSIMPIN *p1);

    static UINT TO_INVERSE_UINT(IDSIMPIN2 *p);

    static VOID SET_STATE(bool condition, IDSIMPIN2 *pin, ABSTIME time);


public:
    static constexpr DWORD MODEL_KEY = 0x00000002;

    INT isdigital(CHAR* pinname) override;

    VOID setup(IINSTANCE* instance, IDSIMCKT* dsim) override;

    VOID runctrl(RUNMODES mode) override;

    VOID actuate(REALTIME time, ACTIVESTATE newstate) override;

    BOOL indicate(REALTIME time, ACTIVEDATA* newstate) override;

    VOID simulate(ABSTIME time, DSIMMODES mode) override;

    VOID callback(ABSTIME time, EVENTID eventid) override;
};
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

class I3000_589IK14_Model : public IDSIMMODEL {
private:
    // INSTANCE
    IINSTANCE* _instance;

    // INPUT PINS
    IDSIMPIN* _pin_INE;
    IDSIMPIN* _pin_CLK;
    IDSIMPIN* _pin_P2;
    IDSIMPIN* _pin_P1;
    IDSIMPIN* _pin_P0;
    IDSIMPIN* _pin_GS;
    IDSIMPIN* _pin_EW;
    IDSIMPIN* _pin_ERC;
    IDSIMPIN* _pin_EG;
    IDSIMPIN* _pin_IR7;
    IDSIMPIN* _pin_IR6;
    IDSIMPIN* _pin_IR5;
    IDSIMPIN* _pin_IR4;
    IDSIMPIN* _pin_IR3;
    IDSIMPIN* _pin_IR2;
    IDSIMPIN* _pin_IR1;
    IDSIMPIN* _pin_IR0;

    // OUTPUT PINS
    IDSIMPIN* _pin_IC2;
    IDSIMPIN* _pin_IC1;
    IDSIMPIN* _pin_IC0;
    IDSIMPIN* _pin_GE;
    IDSIMPIN* _pin_IA;

public:
    static constexpr DWORD MODEL_KEY = 0x00000000;

    INT isdigital(CHAR* pinname) override;

    VOID setup(IINSTANCE* instance, IDSIMCKT* dsim) override;

    VOID runctrl(RUNMODES mode) override;

    VOID actuate(REALTIME time, ACTIVESTATE newstate) override;

    BOOL indicate(REALTIME time, ACTIVEDATA* newstate) override;

    VOID simulate(ABSTIME time, DSIMMODES mode) override;

    VOID callback(ABSTIME time, EVENTID eventid) override;
};

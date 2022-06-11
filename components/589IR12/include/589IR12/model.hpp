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
    const RELTIME DELAY = 50'000;
}

class I3000_589IR12_Model : public IDSIMMODEL {
private:
    // INSTANCE
    IINSTANCE* _instance;

    // INPUT PINS
    IDSIMPIN* _pin_D1;
    IDSIMPIN* _pin_D2;
    IDSIMPIN* _pin_D3;
    IDSIMPIN* _pin_D4;
    IDSIMPIN* _pin_D5;
    IDSIMPIN* _pin_D6;
    IDSIMPIN* _pin_D7;
    IDSIMPIN* _pin_D8;
    IDSIMPIN* _pin_CLR;
    IDSIMPIN* _pin_CS1;
    IDSIMPIN* _pin_CS2;
    IDSIMPIN* _pin_MD;
    IDSIMPIN* _pin_EW;

    // OUTPUT PINS
    IDSIMPIN* _pin_INR;
    IDSIMPIN* _pin_Q1;
    IDSIMPIN* _pin_Q2;
    IDSIMPIN* _pin_Q3;
    IDSIMPIN* _pin_Q4;
    IDSIMPIN* _pin_Q5;
    IDSIMPIN* _pin_Q6;
    IDSIMPIN* _pin_Q7;
    IDSIMPIN* _pin_Q8;

    // data
    BOOL data[8];

    VOID SET_STATE(STATE state, IDSIMPIN2* pin, ABSTIME time);

public:
    static constexpr DWORD MODEL_KEY = 0x00000010;

    INT isdigital(CHAR* pinname) override;

    VOID setup(IINSTANCE* instance, IDSIMCKT* dsim) override;

    VOID runctrl(RUNMODES mode) override;

    VOID actuate(REALTIME time, ACTIVESTATE newstate) override;

    BOOL indicate(REALTIME time, ACTIVEDATA* newstate) override;

    VOID simulate(ABSTIME time, DSIMMODES mode) override;

    VOID callback(ABSTIME time, EVENTID eventid) override;
};
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

class I3000_589IK03_Model : public IDSIMMODEL {
private:
    // INSTANCE
    IINSTANCE* _instance;
    IDSIMCKT* _ckt;

    // INPUT PINS
    IDSIMPIN* _pin_EC8;
    IDSIMPIN* _pin_Y7;
    IDSIMPIN* _pin_X7;
    IDSIMPIN* _pin_Y6;
    IDSIMPIN* _pin_X6;
    IDSIMPIN* _pin_Y5;
    IDSIMPIN* _pin_X5;
    IDSIMPIN* _pin_Y4;
    IDSIMPIN* _pin_X4;
    IDSIMPIN* _pin_Y3;
    IDSIMPIN* _pin_X3;
    IDSIMPIN* _pin_Y2;
    IDSIMPIN* _pin_X2;
    IDSIMPIN* _pin_Y1;
    IDSIMPIN* _pin_X1;
    IDSIMPIN* _pin_Y0;
    IDSIMPIN* _pin_X0;
    IDSIMPIN* _pin_CN;

    // OUTPUT PINS
    IDSIMPIN* _pin_CN8;
    IDSIMPIN* _pin_CN7;
    IDSIMPIN* _pin_CN6;
    IDSIMPIN* _pin_CN5;
    IDSIMPIN* _pin_CN4;
    IDSIMPIN* _pin_CN3;
    IDSIMPIN* _pin_CN2;
    IDSIMPIN* _pin_CN1;

    static VOID SET_STATE(bool condition, IDSIMPIN2 *pin, ABSTIME time);

public:
    static constexpr DWORD MODEL_KEY = 0x00000003;

    INT isdigital(CHAR* pinname) override;

    VOID setup(IINSTANCE* instance, IDSIMCKT* dsimckt) override;

    VOID runctrl(RUNMODES mode) override;

    VOID actuate(REALTIME time, ACTIVESTATE newstate) override;

    BOOL indicate(REALTIME time, ACTIVEDATA* newstate) override;

    VOID simulate(ABSTIME time, DSIMMODES mode) override;

    VOID callback(ABSTIME time, EVENTID eventid) override;
};
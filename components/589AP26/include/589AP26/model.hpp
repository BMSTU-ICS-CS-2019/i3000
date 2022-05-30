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

class I3000_589AP26_Model : public IDSIMMODEL {
private:
    // INSTANCE
    IINSTANCE* _instance;

    // PINS
    IDSIMPIN* _pin_DI0;
    IDSIMPIN* _pin_DI1;
    IDSIMPIN* _pin_DI2;
    IDSIMPIN* _pin_DI3;

    IDSIMPIN* _pin_DO0;
    IDSIMPIN* _pin_DO1;
    IDSIMPIN* _pin_DO2;
    IDSIMPIN* _pin_DO3;

    IDSIMPIN* _pin_DB0;
    IDSIMPIN* _pin_DB1;
    IDSIMPIN* _pin_DB2;
    IDSIMPIN* _pin_DB3;

    IDSIMPIN* _pin_DCE;
    IDSIMPIN* _pin_CS;

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

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

namespace k589 {

    class Ik14Model : public IDSIMMODEL {
    private:
        IINSTANCE* _instance = nullptr;

        // INPUT PINS
        IDSIMPIN* _pin_INE = nullptr;
        IDSIMPIN* _pin_CLK = nullptr;
        IDSIMPIN* _pin_P2 = nullptr;
        IDSIMPIN* _pin_P1 = nullptr;
        IDSIMPIN* _pin_P0 = nullptr;
        IDSIMPIN* _pin_GS = nullptr;
        IDSIMPIN* _pin_EW = nullptr;
        IDSIMPIN* _pin_ERC = nullptr;
        IDSIMPIN* _pin_EG = nullptr;
        IDSIMPIN* _pin_IR7 = nullptr;
        IDSIMPIN* _pin_IR6 = nullptr;
        IDSIMPIN* _pin_IR5 = nullptr;
        IDSIMPIN* _pin_IR4 = nullptr;
        IDSIMPIN* _pin_IR3 = nullptr;
        IDSIMPIN* _pin_IR2 = nullptr;
        IDSIMPIN* _pin_IR1 = nullptr;
        IDSIMPIN* _pin_IR0 = nullptr;

        // OUTPUT PINS
        IDSIMPIN* _pin_IC2 = nullptr;
        IDSIMPIN* _pin_IC1 = nullptr;
        IDSIMPIN* _pin_IC0 = nullptr;
        IDSIMPIN* _pin_GE = nullptr;
        IDSIMPIN* _pin_IA = nullptr;

        // registers

        // requested interruption
        BYTE _rgr = 0;
        BOOL _rgr_ANY = false;

        // priority
        BYTE _rgs = 0;
        BOOL _rgs_GS = false;

        // synthetic trigger
        BOOL _block_trigger_inverted = true;

    public:
        static constexpr DWORD MODEL_KEY = 0x00000000;
        static constexpr auto MODEL_NAME = "K589IK14";

        INT isdigital(CHAR* pinname) override;

        VOID setup(IINSTANCE* instance, IDSIMCKT* dsim) override;

        VOID runctrl(RUNMODES mode) override;

        VOID actuate(REALTIME time, ACTIVESTATE newstate) override;

        BOOL indicate(REALTIME time, ACTIVEDATA* newstate) override;

        VOID simulate(ABSTIME time, DSIMMODES mode) override;

        VOID callback(ABSTIME time, EVENTID eventid) override;

    private:
        VOID _update_rgr();

        VOID _update_rgs();
    };
} // namespace k589

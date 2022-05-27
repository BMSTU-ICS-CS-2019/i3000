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
    const RELTIME DELAY = 100'000;
}

class I3000_589IK01_Model : public IDSIMMODEL {
private:
    // INSTANCE
    IINSTANCE* _instance;
    IDSIMCKT* _ckt;

    // INPUT PINS
    IDSIMPIN* _pin_EWA;
    IDSIMPIN* _pin_FI;
    IDSIMPIN* _pin_AC6;
    IDSIMPIN* _pin_AC5;
    IDSIMPIN* _pin_AC4;
    IDSIMPIN* _pin_AC3;
    IDSIMPIN* _pin_AC2;
    IDSIMPIN* _pin_AC1;
    IDSIMPIN* _pin_AC0;
    IDSIMPIN* _pin_FC3;
    IDSIMPIN* _pin_FC2;
    IDSIMPIN* _pin_FC1;
    IDSIMPIN* _pin_FC0;
    IDSIMPIN* _pin_K7;
    IDSIMPIN* _pin_K6;
    IDSIMPIN* _pin_K5;
    IDSIMPIN* _pin_K4;
    IDSIMPIN* _pin_K3;
    IDSIMPIN* _pin_K2;
    IDSIMPIN* _pin_K1;
    IDSIMPIN* _pin_K0;
    IDSIMPIN* _pin_CLK;
    IDSIMPIN* _pin_ERA;
    IDSIMPIN* _pin_EN;

    // OUTPUT PINS
    IDSIMPIN* _pin_A8;
    IDSIMPIN* _pin_A7;
    IDSIMPIN* _pin_A6;
    IDSIMPIN* _pin_A5;
    IDSIMPIN* _pin_A4;
    IDSIMPIN* _pin_A3;
    IDSIMPIN* _pin_A2;
    IDSIMPIN* _pin_A1;
    IDSIMPIN* _pin_A0;
    IDSIMPIN* _pin_PK2;
    IDSIMPIN* _pin_PK1;
    IDSIMPIN* _pin_PK0;
    IDSIMPIN* _pin_INE;
    IDSIMPIN* _pin_FO;

    BOOL _previous_CLK_state = false;

    enum MicroOperationMnemonic {
        JCC,
        JZR,
        JCR,
        JFL,
        JCF,
        JZF,
        JPR,
        JLL,
        JCE,
        JPX,
        JRL,
    };
    enum FlagInputMnemonic {
        SCZ,
        STZ,
        STC,
        HCZ,
    };
    enum FlagOutputMnemonic{
        FF0,
        FFC,
        FFZ,
        FF1
    };

    MicroOperationMnemonic get_micro_operation() const;

    VOID RUN_JCC();
    VOID RUN_JZR();
    VOID RUN_JCR();
    VOID RUN_JFL();
    VOID RUN_JCF();
    VOID RUN_JZF();
    VOID RUN_JPR();
    VOID RUN_JLL();
    VOID RUN_JCE();
    VOID RUN_JPX();
    VOID RUN_JRL();
    // TRIGGERS
    bool _F = false;
    bool _C = false;
    bool _Z = false;

    BOOL _PR_latch[4];

    void set_flags();
    void output_flags();
    void set_PR_latch();
    void output_logic_A();
    void output_K_A();
    FlagInputMnemonic get_flag_input_mnemonic() const;
    FlagOutputMnemonic get_flag_output_mnemonic() const;
    VOID SET_STATE(bool condition, IDSIMPIN2 *pin, ABSTIME time = details::DELAY);
    static BOOL IS_HIGH(IDSIMPIN * pin);
    static BOOL IS_LOW(IDSIMPIN * pin);
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

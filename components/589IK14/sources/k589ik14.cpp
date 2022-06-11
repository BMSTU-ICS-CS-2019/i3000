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

#include "k589ik14.hpp"

namespace k589 {
    constexpr RELTIME IR_TO_IC_DELAY = 100'000;
    // FIXME: real-life values?
    constexpr ABSTIME TRIGGER_UPDATE_DELAY = 10'000;

    INT Ik14Model::isdigital(CHAR* pinname) {
        return 1;
    }

    VOID Ik14Model::setup(IINSTANCE* instance, IDSIMCKT* dsim) {
        _instance = instance;

        // INPUT PINS
        _pin_INE = instance->getdsimpin("INE", true);
        _pin_CLK = instance->getdsimpin("CLK", true);
        _pin_P2 = instance->getdsimpin("P2", true);
        _pin_P1 = instance->getdsimpin("P1", true);
        _pin_P0 = instance->getdsimpin("P0", true);
        _pin_GS = instance->getdsimpin("GS", true);
        _pin_EW = instance->getdsimpin("EW", true);
        _pin_ERC = instance->getdsimpin("ERC", true);
        _pin_EG = instance->getdsimpin("EG", true);
        _pin_IR7 = instance->getdsimpin("IR7", true);
        _pin_IR6 = instance->getdsimpin("IR6", true);
        _pin_IR5 = instance->getdsimpin("IR5", true);
        _pin_IR4 = instance->getdsimpin("IR4", true);
        _pin_IR3 = instance->getdsimpin("IR3", true);
        _pin_IR2 = instance->getdsimpin("IR2", true);
        _pin_IR1 = instance->getdsimpin("IR1", true);
        _pin_IR0 = instance->getdsimpin("IR0", true);

        // OUTPUT PINS
        _pin_IC2 = instance->getdsimpin("IC2", true);
        _pin_IC1 = instance->getdsimpin("IC1", true);
        _pin_IC0 = instance->getdsimpin("IC0", true);
        _pin_GE = instance->getdsimpin("GE", true);
        _pin_IA = instance->getdsimpin("IA", true);

        // make output pins default to SLO
        // note: all inputs except for GE are inverted thus default to HI
        _pin_IC2->setstate(SHI);
        _pin_IC1->setstate(SHI);
        _pin_IC0->setstate(SHI);
        _pin_GE->setstate(SLO);
        _pin_IA->setstate(SHI);
    }

    VOID Ik14Model::runctrl(RUNMODES mode) {}

    VOID Ik14Model::actuate(REALTIME time, ACTIVESTATE newstate) {}

    BOOL Ik14Model::indicate(REALTIME time, ACTIVEDATA* newstate) {
        return FALSE;
    }

    static void _set_state(IDSIMPIN* const pin, const ABSTIME time, const RELTIME delay, const boolean value) {
        pin->setstate(time, delay, value ? SHI : SLO);
    }

    VOID Ik14Model::simulate(ABSTIME time, DSIMMODES mode) {
        _instance->log("[%s] Simulating...", MODEL_NAME, time);

        // -- Step 0: reset block-trigger if `!IA` --
        // do block in case of currently being in interruption mode
        auto const ia_inverted = _pin_IA->isinactive();
        if (ia_inverted) {
            _block_trigger_inverted = true;
            _instance->log("[%s]   Unblocked due to -IA signal", MODEL_NAME);
        }

        // -- Step 1: update registers on demand --
        // if the conditions are not met the previous values persist in them
        if (_block_trigger_inverted) {
            _update_rgr();
            _instance->log("[%s]   Updated RGR to %d (has any: %d)", MODEL_NAME, _rgr, _rgr_ANY);
        }
        if (_pin_EW->isinactive()) {
            _update_rgs();
            _instance->log("[%s]   Updated RGS to %d (allow any: %d)", MODEL_NAME, _rgs, _rgs_GS);
        }

        // don't block any longer on `EW`
        if (_pin_EW->isposedge()) {
            _block_trigger_inverted = false;
            _instance->log("[%s]   Blocked because of EW positive edge", MODEL_NAME);
        }

        // -- Step 2: calculate ICx outputs --
        // these only require ERC, EG signals and current values of RGR
        auto const eg = _pin_EG->isactive();
        // register stores the interruption unconditionally
        {
            bool ic0, ic1, ic2;
            if (_pin_ERC->isinactive() && eg && _rgr_ANY) {
                ic0 = (_rgr & 0b001) != 0;
                ic1 = (_rgr & 0b010) != 0;
                ic2 = (_rgr & 0b100) != 0;
            } else {
                ic0 = ic1 = ic2 = false;
            }
            _set_state(_pin_IC0, time, k589::IR_TO_IC_DELAY, ic0);
            _set_state(_pin_IC1, time, k589::IR_TO_IC_DELAY, ic1);
            _set_state(_pin_IC2, time, k589::IR_TO_IC_DELAY, ic2);

            _instance->log("[%s]   Updated IC0 to %d, IC1 to %d IC2 to %d", MODEL_NAME, ic0, ic1, ic2);
        }

        // -- Step 3: perform comparison --
        // This is done with respect to stored GS value which allows to ignore actual comparison
        auto const comparison = _rgr > _rgs || _rgs_GS;
        // also update GE which does not need any extra inputs
        {
            auto const ge = eg && !_rgr_ANY && _rgs_GS;
            _set_state(_pin_GE, time, k589::IR_TO_IC_DELAY /* FIXME? */, ge);
            _instance->log("[%s]   Updated GE to %d", MODEL_NAME, ge);
        }

        // -- Step 4: update triggers --
        {
            auto const ine = _pin_INE->isactive();
            _instance->log("[%s]   Interruption requirements: CLK^=%d, has_any=%d, EG=%d, CMP=%d, unblocked=%d, ine=%d",
                           MODEL_NAME, _pin_CLK->isposedge(), _rgr_ANY, eg, comparison, _block_trigger_inverted, ine);
            if (_pin_CLK->isposedge() && (_rgr_ANY && eg && comparison && _block_trigger_inverted && ine)) {
                // invert the value (aka click)
                _set_state(_pin_IA, time, k589::TRIGGER_UPDATE_DELAY, ia_inverted);
                _instance->log("[%s]   Flipped interruption trigger to %d", MODEL_NAME, ia_inverted);
            }
        }
    }

    VOID Ik14Model::callback(ABSTIME time, EVENTID eventid) {}

    VOID Ik14Model::_update_rgr() {
        // note: all inputs are inverted
        if (_pin_IR7->isinactive()) {
            _rgr = 7;
            _rgr_ANY = true;
        } else if (_pin_IR6->isinactive()) {
            _rgr = 6;
            _rgr_ANY = true;
        } else if (_pin_IR5->isinactive()) {
            _rgr = 5;
            _rgr_ANY = true;
        } else if (_pin_IR4->isinactive()) {
            _rgr = 4;
            _rgr_ANY = true;
        } else if (_pin_IR3->isinactive()) {
            _rgr = 3;
            _rgr_ANY = true;
        } else if (_pin_IR2->isinactive()) {
            _rgr = 2;
            _rgr_ANY = true;
        } else if (_pin_IR1->isinactive()) {
            _rgr = 1;
            _rgr_ANY = true;
        } else if (_pin_IR0->isinactive()) {
            _rgr = 0;
            _rgr_ANY = true;
        } else {
            _rgr = 0;
            _rgr_ANY = false;
        }
    }

    VOID Ik14Model::_update_rgs() {
        _rgs = _pin_P0->isinactive() * 1 + _pin_P1->isinactive() * 2 + (_pin_P2->isinactive()) * 4;
        _rgs_GS = _pin_GS->isinactive();
    }
} // namespace k589

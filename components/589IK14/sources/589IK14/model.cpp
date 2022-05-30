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

#include <589IK14/model.hpp>

namespace model589IK14 {
    constexpr RELTIME IR_TO_IC_DELAY = 100'000;
    // FIXME: real-life values?
    constexpr ABSTIME TRIGGER_UPDATE_DELAY = 10'000;
}// namespace model589IK14

INT I3000_589IK14_Model::isdigital(CHAR* pinname) {
    return 1;
}

VOID I3000_589IK14_Model::setup(IINSTANCE* instance, IDSIMCKT* dsim) {
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

VOID I3000_589IK14_Model::runctrl(RUNMODES mode) {}

VOID I3000_589IK14_Model::actuate(REALTIME time, ACTIVESTATE newstate) {}

BOOL I3000_589IK14_Model::indicate(REALTIME time, ACTIVEDATA* newstate) {
    return FALSE;
}

static void _set_state(IDSIMPIN* const pin, const ABSTIME time, const RELTIME delay, const boolean value) {
    pin->setstate(time, delay, value ? SHI : SLO);
}

VOID I3000_589IK14_Model::simulate(ABSTIME time, DSIMMODES mode) {
    // -- Step 0: reset block-trigger if `!IA` --
    // do block in case of currently being in interruption mode
    if (_pin_IA->isinactive()) _block_trigger_inverted = false;

    // -- Step 1: update registers on demand --
    // if the conditions are not met the previous values persist in them
    if (_block_trigger_inverted) _update_rgr();
    if (_pin_EW->isinactive()) _update_rgs();

    // -- Step 2: calculate ICx outputs --
    // these only require ERC, EG signals and current values of RGR
    auto const eg = _pin_EG->isactive();
    // register stores the interruption unconditionally
    if (_pin_ERC->isinactive() && eg && _rgr_ANY) {
        _set_state(_pin_IC0, time, model589IK14::IR_TO_IC_DELAY, (_rgr & 0b001) != 0);
        _set_state(_pin_IC1, time, model589IK14::IR_TO_IC_DELAY, (_rgr & 0b010) != 0);
        _set_state(_pin_IC2, time, model589IK14::IR_TO_IC_DELAY, (_rgr & 0b100) != 0);
    } else {
        _set_state(_pin_IC0, time, model589IK14::IR_TO_IC_DELAY, false);
        _set_state(_pin_IC1, time, model589IK14::IR_TO_IC_DELAY, false);
        _set_state(_pin_IC2, time, model589IK14::IR_TO_IC_DELAY, false);
    }

    // -- Step 3: perform comparison --
    // This is done with respect to stored GS value which allows 0:0 comparison to result `true`
    auto const comparison = _rgr > _rgs || (_rgs_GS && _rgr > _rgs);
    // also update GE which does not need any extra inputs
    _set_state(_pin_GE, time, model589IK14::IR_TO_IC_DELAY /* FIXME? */, eg & !_rgr_ANY & _rgs_GS);

    // -- Step 4: update triggers --
    // cache the old values because triggers are co-dependant
    auto const ia_inverted = _pin_IA->isinactive();

    if (_pin_CLK->isposedge() && (_rgr_ANY && eg && comparison && _block_trigger_inverted && _pin_INE->isactive())) {
        // invert the value (aka click)
        _set_state(_pin_IA, time, model589IK14::TRIGGER_UPDATE_DELAY, ia_inverted);
    }

    // don't block any longer on `EW`
    if (_pin_EW->isposedge()) _block_trigger_inverted = true;
}

VOID I3000_589IK14_Model::callback(ABSTIME time, EVENTID eventid) {}

VOID I3000_589IK14_Model::_update_rgr() {
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


VOID I3000_589IK14_Model::_update_rgs() {
    _rgs = (_pin_P0->isinactive() ? 0 : 1) + (_pin_P1->isinactive() ? 0 : 2) + (_pin_P2->isinactive() ? 0 : 4);
    _rgs_GS = _pin_GS->isinactive();
}

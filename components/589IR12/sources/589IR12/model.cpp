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

#include <589IR12/model.hpp>

INT I3000_589IR12_Model::isdigital(CHAR* pinname) {
    return 1;
}

VOID I3000_589IR12_Model::setup(IINSTANCE* instance, IDSIMCKT* dsim) {
    this->_instance = instance;

    _pin_D1 = instance->getdsimpin("D1", true);
    _pin_D2 = instance->getdsimpin("D2", true);
    _pin_D3 = instance->getdsimpin("D3", true);
    _pin_D4 = instance->getdsimpin("D4", true);
    _pin_D5 = instance->getdsimpin("D5", true);
    _pin_D6 = instance->getdsimpin("D6", true);
    _pin_D7 = instance->getdsimpin("D7", true);
    _pin_D8 = instance->getdsimpin("D8", true);
    _pin_CLR= instance->getdsimpin("CLR", true);
    _pin_CS1 = instance->getdsimpin("CS1", true);
    _pin_CS2 = instance->getdsimpin("CS2", true);
    _pin_MD = instance->getdsimpin("MD", true);
    _pin_EW = instance->getdsimpin("EW", true);

    _pin_INR = instance->getdsimpin("INR", true);
    _pin_Q1 = instance->getdsimpin("Q1", true);
    _pin_Q2 = instance->getdsimpin("Q2", true);
    _pin_Q3 = instance->getdsimpin("Q3", true);
    _pin_Q4 = instance->getdsimpin("Q4", true);
    _pin_Q5 = instance->getdsimpin("Q5", true);
    _pin_Q6= instance->getdsimpin("Q6", true);
    _pin_Q7= instance->getdsimpin("Q7", true);
    _pin_Q8 = instance->getdsimpin("Q8", true);

    _pin_INR->setstate(SLO);
    _pin_Q1->setstate(SLO);
    _pin_Q2->setstate(SLO);
    _pin_Q3->setstate(SLO);
    _pin_Q4->setstate(SLO);
    _pin_Q5->setstate(SLO);
    _pin_Q6->setstate(SLO);
    _pin_Q7->setstate(SLO);
    _pin_Q8->setstate(SLO);

    _instance->log("MBR: Set up");
}

VOID I3000_589IR12_Model::runctrl(RUNMODES mode) {}

VOID I3000_589IR12_Model::actuate(REALTIME time, ACTIVESTATE newstate) {}

BOOL I3000_589IR12_Model::indicate(REALTIME time, ACTIVEDATA* newstate) {
    return FALSE;
}

VOID I3000_589IR12_Model::simulate(ABSTIME time, DSIMMODES mode) {
    /// Асинхронное обнуление
    if (_pin_CLR->isinactive()) {
        data[0] = false;
        data[1] = false;
        data[2] = false;
        data[3] = false;
        data[4] = false;
        data[5] = false;
        data[6] = false;
        data[7] = false;

        SET_STATE(SLO, _pin_Q1, time);
        SET_STATE(SLO, _pin_Q2, time);
        SET_STATE(SLO, _pin_Q3, time);
        SET_STATE(SLO, _pin_Q4, time);
        SET_STATE(SLO, _pin_Q5, time);
        SET_STATE(SLO, _pin_Q6, time);
        SET_STATE(SLO, _pin_Q7, time);
        SET_STATE(SLO, _pin_Q8, time);
        /// При установке системы в исходное состояние инзким уровнем сигнала CLR
        /// триггер запроса прерывания устанавливается в 1
        SET_STATE(true, _pin_INR, time);
        _instance->log("MBR: Reset");
        return;
    }

    BOOL selected = _pin_CS1->isinactive() && _pin_CS2->isactive();

    /// Триггер запроса прерывания устанавливается в 1 при условии выбора устройства
    if (selected && (_pin_CS1->isnegedge() || _pin_CS2->isposedge())) {
        SET_STATE(true, _pin_INR, time);
    }

    /** Режимы работы
     * При наличии лог. О на входе MD устройство работает в режиме ввода.
     * В этом режиме, выходные буферные каскады открыты, когда устройство выбрано.
     * Управление записью осуществляется сигналом по входу EW.
     *
     * При наличии лог. 1 на входе MD устройство работает в режиме вывода.
     * В этом случае выходные буферные каскады открыты независимо от выборки устройства.
     */

    if (selected && _pin_MD->isinactive()) {
        if (_pin_EW->isposedge()) {
            // read
            data[0] = _pin_D1->isactive();
            data[1] = _pin_D2->isactive();
            data[2] = _pin_D3->isactive();
            data[3] = _pin_D4->isactive();
            data[4] = _pin_D5->isactive();
            data[5] = _pin_D6->isactive();
            data[6] = _pin_D7->isactive();
            data[7] = _pin_D8->isactive();

            ///При работе в режиме ввода входной сигнал EW производит запись информации в регистр данных
            /// и установку триггера запроса в 0.

            SET_STATE(false, _pin_INR, time);
            _instance->log("MBR: Data read");
        }
        SET_STATE(data[0] ? SHI : SLO, _pin_Q1, time);
        SET_STATE(data[1] ? SHI : SLO, _pin_Q2, time);
        SET_STATE(data[2] ? SHI : SLO, _pin_Q3, time);
        SET_STATE(data[3] ? SHI : SLO, _pin_Q4, time);
        SET_STATE(data[4] ? SHI : SLO, _pin_Q5, time);
        SET_STATE(data[5] ? SHI : SLO, _pin_Q6, time);
        SET_STATE(data[6] ? SHI : SLO, _pin_Q7, time);
        SET_STATE(data[7] ? SHI : SLO, _pin_Q8, time);
    }

    if (_pin_MD->isactive()) {
        SET_STATE(data[0] ? SHI : SLO, _pin_Q1, time);
        SET_STATE(data[1] ? SHI : SLO, _pin_Q2, time);
        SET_STATE(data[2] ? SHI : SLO, _pin_Q3, time);
        SET_STATE(data[3] ? SHI : SLO, _pin_Q4, time);
        SET_STATE(data[4] ? SHI : SLO, _pin_Q5, time);
        SET_STATE(data[5] ? SHI : SLO, _pin_Q6, time);
        SET_STATE(data[6] ? SHI : SLO, _pin_Q7, time);
        SET_STATE(data[7] ? SHI : SLO, _pin_Q8, time);
    }

    // Если не выбрано, на выходе нули, независимо от того что хранится
    if (!selected) {
        SET_STATE(UNDEFINED, _pin_Q1, time);
        SET_STATE(UNDEFINED, _pin_Q2, time);
        SET_STATE(UNDEFINED, _pin_Q3, time);
        SET_STATE(UNDEFINED, _pin_Q4, time);
        SET_STATE(UNDEFINED, _pin_Q5, time);
        SET_STATE(UNDEFINED, _pin_Q6, time);
        SET_STATE(UNDEFINED, _pin_Q7, time);
        SET_STATE(UNDEFINED, _pin_Q8, time);
    }
}
VOID I3000_589IR12_Model::SET_STATE(STATE state, IDSIMPIN2* pin, ABSTIME time) {
    pin->setstate(time, details::DELAY, state);
}

VOID I3000_589IR12_Model::callback(ABSTIME time, EVENTID eventid) {}

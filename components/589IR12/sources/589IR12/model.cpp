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
}

VOID I3000_589IR12_Model::runctrl(RUNMODES mode) {}

VOID I3000_589IR12_Model::actuate(REALTIME time, ACTIVESTATE newstate) {}

BOOL I3000_589IR12_Model::indicate(REALTIME time, ACTIVEDATA* newstate) {
    return FALSE;
}

VOID I3000_589IR12_Model::simulate(ABSTIME time, DSIMMODES mode) {
    /// Асинхронное обнуление
    if (islow(_pin_CLR->getstate())) {
        _pin_Q1->setstate(SLO);
        _pin_Q2->setstate(SLO);
        _pin_Q3->setstate(SLO);
        _pin_Q4->setstate(SLO);
        _pin_Q5->setstate(SLO);
        _pin_Q6->setstate(SLO);
        _pin_Q7->setstate(SLO);
        _pin_Q8->setstate(SLO);
        /// При установке системы в исходное состояние инзким уровнем сигнала CLR
        /// триггер запроса прерывания устанавливается в 1
        _pin_INR->setstate(SHI);
        return;
    }
    /// Сигнал стробирования
    if (islow(_pin_EW->getstate())) return;

    BOOL selected = islow(_pin_CS1->getstate()) && ishigh(_pin_CS2->getstate());

    /// Триггер запроса прерывания устанавливается в 1 при условии выбора устройства
    if (selected) {
        _pin_INR->setstate(SHI);
    }

    /** Режимы работы
     * При наличии лог. О на входе MD устройство работает в режиме ввода.
     * В этом режиме, выходные буферные каскады открыты, когда устройство выбрано.
     * Управление записью осуществляется сигналом по входу EW.
     *
     * При наличии лог. 1 на входе MD устройство работает в режиме вывода.
     * В этом случае выходные буферные каскады открыты независимо от выборки устройства.
     */
    if (ishigh(_pin_MD->getstate())) return;

    /// MD=0 (режим ввода)
    /// При наличии лог. 0 иа входе CS1 н лог. 1 иа входе CS2 устройство выбрано.
    if (selected) {
        _pin_Q1->setstate(_pin_D1->getstate());
        _pin_Q2->setstate(_pin_D2->getstate());
        _pin_Q3->setstate(_pin_D3->getstate());
        _pin_Q4->setstate(_pin_D4->getstate());
        _pin_Q5->setstate(_pin_D5->getstate());
        _pin_Q6->setstate(_pin_D6->getstate());
        _pin_Q7->setstate(_pin_D7->getstate());
        _pin_Q8->setstate(_pin_D8->getstate());

        ///При работе в режиме ввода входной сигнал EW производит запись информации в регистр данных
        /// и установку триггера запроса в 0.
        _pin_INR->setstate(SLO);
    }
}

VOID I3000_589IR12_Model::callback(ABSTIME time, EVENTID eventid) {}

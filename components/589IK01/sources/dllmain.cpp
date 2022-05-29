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

#include <i3000/prelude.hpp>

#include <589IK01/model.hpp>
#include <iostream>

extern "C" {
    IDSIMMODEL __declspec(dllexport) * createdsimmodel(CHAR* device, ILICENCESERVER* license_server) {
        MessageBox(nullptr, reinterpret_cast<LPCSTR>("Compile Time " __DATE__ " " __TIME__),
                   reinterpret_cast<LPCSTR>("Hello!"),
                   MB_ICONERROR);
//        std::cout<<__DATE__<<std::endl;
        return license_server->authorize(I3000_589IK01_Model::MODEL_KEY) ? new I3000_589IK01_Model() : nullptr;
    }

    VOID __declspec(dllexport) deletedsimmodel(IDSIMMODEL* model) {
        delete (I3000_589IK01_Model*) model;
    }
}

BOOL WINAPI DllMain(HMODULE hmodule, DWORD call_reason, [[maybe_unused]] LPVOID _reserved) {
    return TRUE;
}
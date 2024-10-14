/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "MigrationPreparer.h"

namespace WPEFramework {
namespace Plugin {

    using namespace JsonData::MigrationPreparer;

    void MigrationPreparer::RegisterAll()
    {
        Register<WriteParamsInfo, WriteResultInfo>(_T("write"), &MigrationPreparer::endpoint_write, this);
        Register<ReadParamsInfo, ReadResultData>(_T("read"), &MigrationPreparer::endpoint_read, this);
        Register<DeleteKeyParamsInfo, DeleteKeyResultInfo>(_T("delete"), &MigrationPreparer::endpoint_delete, this);
        Register<void, GetComponentReadinessResultData>(_T("getComponentReadiness"), &MigrationPreparer::endpoint_getComponentReadiness, this);
        Register<SetComponentReadinessParamsData, void>(_T("setComponentReadiness"), &MigrationPreparer::endpoint_setComponentReadiness, this);
        Register<ResetParamsData, void>(_T("reset"), &MigrationPreparer::endpoint_reset, this);
    }

    void MigrationPreparer::UnregisterAll()
    {
        Unregister(_T("read"));
        Unregister(_T("write"));
        Unregister(_T("delete"));
        Unregister(_T("getComponentReadiness"));
        Unregister(_T("setComponentReadiness"));
        Unregister(_T("reset"));
    }

    uint32_t MigrationPreparer::endpoint_write(const WriteParamsInfo& params, WriteResultInfo& response)
    {
        auto result = _migrationPreparer->Write(
            params.name.Value(),
            params.value.Value());
        if (result == Core::ERROR_NONE) {
            response.Success = true;
        }

        return result;
    }

    uint32_t MigrationPreparer::endpoint_read(const ReadParamsInfo& params, ReadResultData& response)
    {
        string value;
        auto result = _migrationPreparer->Read(
                            params.name.Value(),
                            value);
        if (result == Core::ERROR_NONE) {
            response.Value = value;
            response.Success = true;
        }

        return result;
    }

    uint32_t MigrationPreparer::endpoint_delete(const DeleteKeyParamsInfo& params, DeleteKeyResultInfo& response)
    {
        auto result = _migrationPreparer->DeleteKey(
                            params.name.Value());

        if (result == Core::ERROR_NONE) {
            response.Success = true;
        }

        return result;
    }

    uint32_t MigrationPreparer::endpoint_getComponentReadiness(GetComponentReadinessResultData& response)
    {
        RPC::IStringIterator* it;
        auto result = _migrationPreparer->getComponentReadiness();
        if (result == Core::ERROR_NONE) {
            string element;
            while (it->Next(element) == true) {
                response.componentList.Add() = element;
            }
            it->Release();
            response.Success = true;
        }

        return result;
    }

    uint32_t MigrationPreparer::endpoint_setComponentReadiness(const SetComponentReadinessParamsData& params)
    {
        auto result = _migrationPreparer->setComponentReadiness(
                            params.componentName.Value());

        if (result == Core::ERROR_NONE) {
            response.Success = true;
        }
        return result;
    }


    uint32_t PersistentStore::endpoint_reset(ResetParamsData& response)
    {
        auto result = _migrationPreparer->reset();
        if (result == Core::ERROR_NONE) {
            response.Success = true;
        }

        return result;
    }

} // namespace Plugin
} // namespace WPEFramework

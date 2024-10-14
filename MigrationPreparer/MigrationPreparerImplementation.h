/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2024 RDK Management
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

#pragma once

#include "Module.h"
#include <interfaces/IMigrationPreparer.h>
#include "tracing/Logging.h"
#include <vector>

#define MIGRATIONPREPARER_NAMESPACE "MigrationPreparer"

namespace WPEFramework {
namespace Plugin {
    class MigrationPreparerImplementation : public Exchange::IMigrationPreparer{

    public:
        static const std::map<string, uint32_t> migrationPreparerMap;
     
        // We do not allow this plugin to be copied !!
        MigrationPreparerImplementation();
        ~MigrationPreparerImplementation() override;

        // We do not allow this plugin to be copied !!
        MigrationPreparerImplementation(const MigrationPreparerImplementation&) = delete;
        MigrationPreparerImplementation& operator=(const MigrationPreparerImplementation&) = delete;        

        enum ResetType {
            RESET_DATA,
            RESET_READINESS,
            RESET_ALL,
        };

        virtual uint32_t Register(Exchange::IMigrationPreparer::INotification *notification ) override ;
        virtual uint32_t Unregister(Exchange::IMigrationPreparer::INotification *notification ) override ;

        uint32_t Write(const string& name, const string &value) override;
        uint32_t Read(const string& name, string &value)  override;
        uint32_t Delete(const string& name)  override;

        void ValueChanged(const string& name, const string& value);

        uint32_t setComponentReadiness(const string& compName) override;
        uint32_t getComponentReadiness(RPC::IStringIterator*& compList) override;
        uint32_t reset(const string& type) override;

        BEGIN_INTERFACE_MAP(MigrationPreparerImplementation)
        INTERFACE_ENTRY(Exchange::IMigrationPreparer)
        END_INTERFACE_MAP

    private:
        mutable Core::CriticalSection _adminLock;
        std::list<Exchange::IMigrationPreparer::INotification*> _migrationPreparerNotification;
    };
} // namespace Plugin
} // namespace WPEFramework

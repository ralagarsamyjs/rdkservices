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

#include "MigrationPreparerImplementation.h"

namespace WPEFramework {
namespace Plugin {

    SERVICE_REGISTRATION(MigrationPreparerImplementation, 1, 0);

    MigrationPreparerImplementation::MigrationPreparerImplementation()
    : _adminLock()
    , _migrationPreparerNotification(*this)
    {
        LOGINFO("Create MigrationPreparerImplementation Instance");
    }

    MigrationPreparerImplementation::~MigrationPreparerImplementation()
    {
    }

    uint32_t MigrationPreparerImplementation::Register(Exchange::IMigrationPreparer::INotification *notification)
    {
        ASSERT (nullptr != notification);

        _adminLock.Lock();

        // Make sure we can't register the same notification callback multiple times
        if (std::find(_migrationPreparerNotification.begin(), _migrationPreparerNotification.end(), notification) == _migrationPreparerNotification.end())
        {
            LOGINFO("Register notification");
            _migrationPreparerNotification.push_back(notification);
            notification->AddRef();
        }

        _adminLock.Unlock();

        return Core::ERROR_NONE;
    }

    uint32_t MigrationPreparerImplementation::Unregister(Exchange::IMigrationPreparer::INotification *notification )
    {
        uint32_t status = Core::ERROR_GENERAL;

        ASSERT (nullptr != notification);

        _adminLock.Lock();

        // Make sure we can't unregister the same notification callback multiple times
        auto itr = std::find(_migrationPreparerNotification.begin(), _migrationPreparerNotification.end(), notification);
        if (itr != _migrationPreparerNotification.end())
        {
            (*itr)->Release();
            LOGINFO("Unregister notification");
            _migrationPreparerNotification.erase(itr);
            status = Core::ERROR_NONE;
        }
        else
        {
            LOGERR("notification not found");
        }

        _adminLock.Unlock();

        return status;
    }

    void MigrationPreparerImplementation::ValueChanged(const string& name, const string& value)
    {
         LOGINFO("name:%s value:%s",name.c_str(), value.c_str());
         _adminLock.Lock();
         std::list<Exchange::IMigrationPreparer::INotification*>::const_iterator index(_migrationPreparerNotification.begin());
         while (index != _migrationPreparerNotification.end())
         {
            (*index)->ValueChanged(name.String());
            index++;
         }
         _adminLock.Unlock();         
    }

    uint32_t MigrationPreparerImplementation::Write(const string& name, const string &value) const
    {
        uint32_t status = Core::ERROR_GENERAL;
        _adminLock.Lock();
        LOGINFO("Name[%s] value[%s] status[%d]", name.c_str(), value.c_str(), status);
        _adminLock.Unlock();
        return status;
    }
    
    uint32_t MigrationPreparerImplementation::Read(const string& name, string &value) const
    {
        uint32_t status = Core::ERROR_GENERAL;
        _adminLock.Lock();
        LOGINFO("Name[%s] value[%s] status[%d]", name.c_str(), value.c_str(), status);
        _adminLock.Unlock();
        return status;
    }

    uint32_t MigrationPreparerImplementation::Delete(const string& name) const
    {
        uint32_t status = Core::ERROR_GENERAL;
        _adminLock.Lock();
        LOGINFO("Name[%s] value[%s] status[%d]", name.c_str(), status);
        _adminLock.Unlock();
        return status;
    }


    uint32_t MigrationPreparerImplementation::setComponentReadiness(const string& compName)
    {
        uint32_t status = Core::ERROR_GENERAL;
        _adminLock.Lock();
        LOGINFO("Component Name[%s] status[%d]", compName.c_str(), status);
        _adminLock.Unlock();
        return status;
    }

    uint32_t MigrationPreparerImplementation::getComponentReadiness(RPC::IStringIterator*& compList)
    {
        uint32_t status = Core::ERROR_GENERAL;
        _adminLock.Lock();
         std::list<string> list;
        compList = (Core::Service<RPC::StringIterator>::Create<RPC::IStringIterator>(list));
        LOGINFO("Component status[%d]", status);
        _adminLock.Unlock();
        return status;
    }

    uint32_t MigrationPreparerImplementation::reset(const string& type)
    {
        uint32_t status = Core::ERROR_GENERAL;
        _adminLock.Lock();
        LOGINFO("Reset Type[%d] status[%d]", type, status);
        _adminLock.Unlock();
        return status;
    }

} // namespace Plugin
} // namespace WPEFramework

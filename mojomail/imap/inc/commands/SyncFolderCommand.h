// @@@LICENSE
//
//      Copyright (c) 2010-2013 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

#ifndef SYNCFOLDERCOMMAND_H_
#define SYNCFOLDERCOMMAND_H_

#include "commands/ImapClientCommand.h"
#include "client/SyncParams.h"
#include "activity/NetworkStatus.h"
#include "db/MojDbClient.h"

class ActivitySet;

class SyncFolderCommand : public ImapClientCommand
{
public:
	SyncFolderCommand(ImapClient& client, const MojObject& folderId, SyncParams params);
	virtual ~SyncFolderCommand();

	void Status(MojObject& status) const;
	std::string Describe() const;

protected:
	void RunImpl();
	void PrepareSync();

	void GetFolder();
	MojErr GetFolderResponse(MojObject& response, MojErr err);

	void SyncOutbox();
	MojErr SmtpResponse(MojObject& response, MojErr err);

	void StartActivities();
	MojErr StartActivitiesDone();

	MojErr AdoptDone();

	void CleanupActivities();
	MojErr CleanupActivitiesDone();

	void Cleanup();

	MojObject m_folderId;
	SyncParams m_syncParams;

	MojRefCountedPtr<ActivitySet>	m_activitySet;

	MojDbClient::Signal::Slot<SyncFolderCommand>		m_getFolderSlot;
	MojServiceRequest::ReplySignal::Slot<SyncFolderCommand> m_smtpSlot;
	MojSignal<>::Slot<SyncFolderCommand>				m_startActivitiesSlot;
	MojSignal<>::Slot<SyncFolderCommand>				m_adoptOnlySlot;
	MojSignal<>::Slot<SyncFolderCommand>				m_cleanupActivitiesSlot;
};

#endif /* SYNCFOLDERCOMMAND_H_ */

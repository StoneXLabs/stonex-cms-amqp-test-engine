#pragma once

#include "MessageReceiverConfiguration.h"
#include <utils/EventCounter.h>
#include <utils/MessageFile.h>

class FileMessageCountingReceiverConfiguration : public MessageReceiverConfiguration, public EventCounter, public MessageFile
{
public:
	FileMessageCountingReceiverConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& consumerId, const std::string& messageFile, long long message_count);
	friend bool operator== (const FileMessageCountingReceiverConfiguration& lhs, const FileMessageCountingReceiverConfiguration& rhs);
};


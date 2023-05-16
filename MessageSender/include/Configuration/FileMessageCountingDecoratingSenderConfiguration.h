#pragma once
#include "EventCounter.h"
#include "MessageFile.h"
#include "MessageSenderConfiguration.h"
#include <Configuration/MessageDecoratorConfiguration.h>

class FileMessageCountingDecoratingSenderConfiguration : public MessageSenderConfiguration, public MessageFile, public EventCounter, public MessageDecoratorConfiguration
{
public:
	FileMessageCountingDecoratingSenderConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::string& file_path, long long message_count, const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const FileMessageCountingDecoratingSenderConfiguration& lhs, const FileMessageCountingDecoratingSenderConfiguration& rhs);

};


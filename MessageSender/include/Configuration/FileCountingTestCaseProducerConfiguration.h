#pragma once
#include "EventCounter.h"
#include "MessageFile.h"
#include "TestCaseProducerConfiguration.h"

class FileCountingTestCaseProducerConfiguration : public TestCaseProducerConfiguration, public MessageFile, public EventCounter
{
public:
	FileCountingTestCaseProducerConfiguration(const std::string& producerId, const std::string& sessionId, const std::string& file_path, long long message_count);
	friend bool operator== (const FileCountingTestCaseProducerConfiguration& lhs, const FileCountingTestCaseProducerConfiguration& rhs);

};


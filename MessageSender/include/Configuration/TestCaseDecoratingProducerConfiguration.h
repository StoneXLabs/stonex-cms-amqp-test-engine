#include "TestCaseProducerConfiguration.h"
#include <Configuration/MessageDecoratorConfiguration.h>

class TestCaseDecoratingProducerConfiguration : public TestCaseProducerConfiguration, public MessageDecoratorConfiguration
{
public:
	TestCaseDecoratingProducerConfiguration(const std::string& connectionId, const std::string& sessionId, const std::string& producerId, const std::vector<MessageTestField*>& decorations);
	friend bool operator== (const TestCaseDecoratingProducerConfiguration& lhs, const TestCaseDecoratingProducerConfiguration& rhs);

};
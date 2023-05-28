#include "MessageSenderFactory.h"

#include <Configuration/FileCountingTestCaseProducerConfiguration.h>
#include <Configuration/FileTestCaseProducerConfiguration.h>
#include <Configuration/CountingCaseProducerConfiguration.h>
#include <Configuration/TestCaseProducerConfiguration.h>

MessageSender * MessageSenderFactory::create(const TestCaseProducerConfiguration & sender_configuration, CMSClientTestUnit & client_configuration, EventStatusObserver & parent) const
{
	if (auto concrete_configuration = dynamic_cast<const CountingCaseProducerConfiguration*>(&sender_configuration)) {
		
	}
	else if (auto concrete_configuration = dynamic_cast<const FileCountingTestCaseProducerConfiguration*>(&sender_configuration)) {
	}
	else if (auto concrete_configuration = dynamic_cast<const FileTestCaseProducerConfiguration*>(&sender_configuration)) {
	}
	else if (auto concrete_configuration = dynamic_cast<const TestCaseProducerConfiguration*>(&sender_configuration)) {
	}
	return nullptr;
}

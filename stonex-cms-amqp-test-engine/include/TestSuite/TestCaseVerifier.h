#pragma once

#include <Notifier/TestNotifier.h>
#include "Configuration/TestCaseVerifierConfiguration.h"
#include "Wrapper/CMSClientTestUnit.h"
#include <MessageReceiver/MessageReceiver.h>

class TestCaseVerifier 
{

public:
	TestCaseVerifier(const TestCaseVerifierConfiguration& params, CMSClientTestUnit& client_params, Notifier& notifier);
	

private:
	std::vector<MessageReceiver*> mReceivers;
};
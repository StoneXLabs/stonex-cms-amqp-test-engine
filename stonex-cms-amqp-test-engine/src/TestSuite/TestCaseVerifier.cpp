#include <TestSuite/TestCaseVerifier.h>
#include <Configuration/MessageReceiverConfiguration.h>
#include <MessageReceiver/MessageReceiverFactory.h>

TestCaseVerifier::TestCaseVerifier(const TestCaseVerifierConfiguration & params, CMSClientTestUnit & client_params, Notifier & notifier)
{
	MessageReceiverFactory receiverFactory;
	std::transform(std::cbegin(params.messageExpectations()), std::cend(params.messageExpectations()), std::back_inserter(mReceivers), [this, &client_params,&receiverFactory,&notifier](const MessageReceiverConfiguration* item) {
		auto receiver = receiverFactory.create(*item, client_params, notifier);
		auto consumer = client_params.consumer(item->connectionId(), item->sessionId(), item->consumerId());		
		if(consumer)
			consumer->setMessageListener(receiver);
		return receiver;
	});

}

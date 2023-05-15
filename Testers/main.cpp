
#include <boost/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>

#include <cms/MessageListener.h>

#include <Configuration/TestCaseProducerConfiguration.h>

#include <Configuration/TestCaseDecoratingProducerConfiguration.h>
#include <MessageSender/MessageDecoratingSender.h>


#include "Wrapper/CMSClientTestUnit.h"
#include <MessageSender/MessageSender.h>
#include <MessageReceiver/TestMessageReceiver.h>
#include "StdOutLogger/StdOutLogger.h"

#include <Notifier/EventStatusObserver.h>
#include <Notifier/TestNotifier.h>

class TestMessageSender : public MessageSender
{
public:
	TestMessageSender(const TestCaseProducerConfiguration& params, CMSClientTestUnit & client_params, EventStatusObserver& parent)
		:MessageSender(params, client_params, parent)
	{
	}

	bool send(int msg_delay_ms = 0) {
		if (mSession && mProducer)
		{
			auto mes = mSession->createTextMessage("hello");
			mProducer->send(mes);
			return true;
		}
		return false;

	};
};

class TestMessageListener : public cms::MessageListener
{
public:
	void onMessage(const cms::Message* message) override {
		std::cout << "Message Received"<<std::endl;
		mMessageReceived = true;
	}

	bool check() const 
	{
		return mMessageReceived;
	}

private:
	bool mMessageReceived{false};
};

int main()
{

	{

		auto consumer_config = ConsumerConfiguration("consumer1", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto producer_config = ProducerConfiguration("producer1", "queue", "CMS_CLIENT_QUEUE", {});
		auto session_config = SessionConfiguration("session1", true, false, { consumer_config }, { producer_config });
		auto connection_config = ConnectionConfiguration("connection1", "failover:(localhost:5672)?maxReconnectAttempts=5", "admin", "admin", "", { session_config });
		auto wrapper_config = WrapperConfiguration(std::vector< ConnectionConfiguration>({ connection_config }));

		auto logger = std::make_shared<StdOutLogger>();
		CMSClientTestUnit test_client(wrapper_config, logger);

		Notifier event_notifier(nullptr);
		EventStatusObserver event_observer(event_notifier);

		auto test_producer_config = TestCaseProducerConfiguration("connection1", "session1", "producer1");
		TestMessageSender sender(test_producer_config, test_client, event_observer);

		TestCaseMessageReceiverConfiguration test_consumer_config("connection1", "session1", "consumer1");
		TestMessageReceiver receiver(test_consumer_config, test_client, event_notifier);

		TestMessageListener test_listener;
		receiver.setMessageListener(&test_listener);

		assert(test_listener.check() == false);
		sender.send();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		assert(test_listener.check() == true);
	}

	{

		auto consumer_config = ConsumerConfiguration("consumer1", "queue", "CMS_CLIENT_QUEUE", "close", "");
		auto producer_config = ProducerConfiguration("producer1", "queue", "CMS_CLIENT_QUEUE", {});
		auto session_config = SessionConfiguration("session1", true, false, { consumer_config }, { producer_config });
		auto connection_config = ConnectionConfiguration("connection1", "failover:(localhost:5672)?maxReconnectAttempts=5", "admin", "admin", "", { session_config });
		auto wrapper_config = WrapperConfiguration(std::vector< ConnectionConfiguration>({ connection_config }));

		auto logger = std::make_shared<StdOutLogger>();
		CMSClientTestUnit test_client(wrapper_config, logger);

		Notifier event_notifier(nullptr);
		EventStatusObserver event_observer(event_notifier);

		auto test_producer_config = TestCaseDecoratingProducerConfiguration("connection1", "session1", "producer1", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"bool_property",false) });
		MessageDecoratingSender sender(test_producer_config, test_client, event_observer);

		TestCaseMessageReceiverConfiguration test_consumer_config("connection1", "session1", "consumer1");
		TestMessageReceiver receiver(test_consumer_config, test_client, event_notifier);

		TestMessageListener test_listener;
		receiver.setMessageListener(&test_listener);

		assert(test_listener.check() == false);
		sender.send();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		assert(test_listener.check() == true);
	}

	return 0;
}
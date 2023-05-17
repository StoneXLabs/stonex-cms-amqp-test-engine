#include "Wrapper/CMSClientTestUnit.h"
#include <boost/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>

#include <ConfigurationParser/TestCaseProducerConfigurationParser.h>
#include <Configuration/MessageCountingSenderConfiguration.h>
#include <Configuration/FileMessageSenderConfiguration.h>
#include <Configuration/FileMessageCountingSenderConfiguration.h>
#include <Configuration/FileMessageCountingDecoratingSenderConfiguration.h>


#include <MessageSender/MessageSender.h>
#include <MessageSender/MessageFileSender.h>
#include <MessageSender/MessageCountingSender.h>
#include <MessageSender/MessageDecoratingSender.h>
#include <MessageSender/MessageCountingFileSender.h>
#include <MessageSender/MessageDecoratingFileSender.h>
#include <MessageSender/MessageCountingDecoratingSender.h>
#include <MessageSender/MessageCountingDecoratingFileSender.h>

#include <ConfigurationParser/TestCaseReceiverConfigurationParser.h>
#include <Configuration/MessageCountingReceiverConfiguration.h>
#include <Configuration/FileMessageReceiverConfiguration.h>
#include <Configuration/FileMessageCountingReceiverConfiguration.h>
#include <Configuration/FileMessageCountingDecoratingReceiverConfiguration.h>
#include <Configuration/MessageDecoratingReceiverConfiguration.h>


#include <MessageReceiver/MessageReceiver.h>
#include <MessageReceiver/MessageFileReceiver.h>
#include <MessageReceiver/MessageCountingReceiver.h>
#include <MessageReceiver/MessageDecoratingReceiver.h>
#include <MessageReceiver/MessageCountingFileReceiver.h>
#include <MessageReceiver/MessageDecoratingFileReceiver.h>
#include <MessageReceiver/MessageCountingDecoratingReceiver.h>
#include <MessageReceiver/MessageCountingDecoratingFileReceiver.h>


#include "Wrapper/CMSClientTestUnit.h"
#include "StdOutLogger/StdOutLogger.h"

#include <Notifier/EventStatusObserver.h>
#include <Notifier/TestNotifier.h>

class TestMessageSender : public MessageSender
{
public:
	TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, EventStatusObserver& parent)
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

		{
			class TestMessageSender : public MessageSender
			{
			public:
				TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, EventStatusObserver& parent)
					:MessageSender(params, client_params, parent)
				{
				}


				std::string createMessageBody() override {
					return "test message";
				}
			};

			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1");
			TestMessageSender sender(test_producer_config, test_client, event_observer);

			auto test_consumer_config = MessageReceiverConfiguration("connection1", "session1", "consumer1");
			MessageReceiver receiver(test_consumer_config, test_client, event_observer);

			TestMessageListener test_listener;
			receiver.setMessageListener(&test_listener);

			assert(test_listener.check() == false);
			sender.sendMessage();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			assert(test_listener.check() == true);

		}

		{
			class TestMessageSender : public MessageSender
			{
			public:
				TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, EventStatusObserver& parent)
					:MessageSender(params, client_params, parent)
				{
				}


				std::string createMessageBody() override {
					return "test message";
				}
			};

			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1");
			TestMessageSender sender(test_producer_config, test_client, event_observer);

			auto test_consumer_config = MessageCountingReceiverConfiguration("connection1", "session1", "consumer1", 1);
			MessageCountingReceiver receiver(test_consumer_config, test_client, event_observer);


			assert(receiver.receivedMessageCount() == 0);
			sender.sendMessage();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			assert(receiver.receivedMessageCount() == receiver.expectedEventCount());

		}

		{
			class TestMessageSender : public MessageSender
			{
			public:
				TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, EventStatusObserver& parent)
					:MessageSender(params, client_params, parent)
				{
				}


				std::string createMessageBody() override {
					return "test message";
				}
			};

			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1");
			TestMessageSender sender(test_producer_config, test_client, event_observer);

			auto test_consumer_config = FileMessageReceiverConfiguration("connection1", "session1", "consumer1", "test_message_out.txt");
			MessageFileReceiver receiver(test_consumer_config, test_client, event_observer);


			TestMessageListener test_listener;
			receiver.setMessageListener(&test_listener);

			assert(test_listener.check() == false);
			sender.sendMessage();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			assert(test_listener.check() == true);

		}

		{
			class TestMessageSender : public MessageSender
			{
			public:
				TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, EventStatusObserver& parent)
					:MessageSender(params, client_params, parent)
				{
				}


				std::string createMessageBody() override {
					return "test message";
				}
			};

			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1");
			TestMessageSender sender(test_producer_config, test_client, event_observer);

			auto test_consumer_config = FileMessageCountingReceiverConfiguration("connection1", "session1", "consumer1", "test_message_out.txt", 1);
			MessageCountingFileReceiver receiver(test_consumer_config, test_client, event_observer);

			assert(receiver.receivedMessageCount() == 0);
			sender.sendMessage();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			assert(receiver.receivedMessageCount() == receiver.expectedEventCount());

		}

		{
			class TestMessageSender : public MessageSender
			{
			public:
				TestMessageSender(const MessageSenderConfiguration& params, CMSClientTestUnit & client_params, EventStatusObserver& parent)
					:MessageSender(params, client_params, parent)
				{
				}


				std::string createMessageBody() override {
					return "test message";
				}
			};

			auto test_producer_config = MessageSenderConfiguration("connection1", "session1", "producer1");
			TestMessageSender sender(test_producer_config, test_client, event_observer);

			auto test_consumer_config = FileMessageCountingDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "test_message_out.txt", 1, {new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY, "property", "false")});
			MessageCountingDecoratingFileReceiver receiver(test_consumer_config, test_client, event_observer);

			assert(receiver.receivedMessageCount() == 0);
			sender.sendMessage();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			assert(receiver.receivedMessageCount() == receiver.expectedEventCount());

		}
	}

	return 0;
}
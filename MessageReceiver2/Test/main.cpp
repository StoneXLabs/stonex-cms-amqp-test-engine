
#include "Wrapper/CMSClientTestUnit.h"
#include <boost/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>


#include "Wrapper/CMSClientTestUnit.h"
#include <MessageReceiver/MessageReceiver.h>
#include <MessageReceiver/MessageFileReceiver.h>
#include <MessageReceiver/MessageCountingReceiver.h>
#include <MessageReceiver/MessageDecoratingReceiver.h>
#include <MessageReceiver/MessageCountingFileReceiver.h>
#include <MessageReceiver/MessageDecoratingFileReceiver.h>
#include <MessageReceiver/MessageCountingDecoratingReceiver.h>
#include <MessageReceiver/MessageCountingDecoratingFileReceiver.h>

#include "StdOutLogger/StdOutLogger.h"

#include <Notifier/EventStatusObserver.h>
#include <Notifier/TestNotifier.h>


boost::json::value valueFromFile(const std::string& configFile)
{
	std::ifstream config_file(configFile);

	boost::json::stream_parser p;
	boost::json::error_code ec;
	do
	{
		char buf[4096];
		config_file.read(buf, sizeof(buf));
		p.write(buf, config_file.gcount(), ec);
	} while (!config_file.eof());

	p.finish(ec);

	return  p.release();
}






int main()
{
	TestCaseReceiverConfigurationParser parser;

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_receiver.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = MessageReceiverConfiguration("connection1", "session1", "consumer1");

		assert(consumer != nullptr);
		assert(*consumer == consumer_config);
	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_counting_receiver.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = MessageCountingReceiverConfiguration("connection1", "session1", "consumer1", 1);

		assert(consumer != nullptr);
		assert(dynamic_cast<MessageCountingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<MessageCountingReceiverConfiguration*>(consumer) == consumer_config);

	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_receiver_to_file.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = FileMessageReceiverConfiguration("connection1", "session1", "consumer1", "test_messages.txt");


		assert(consumer != nullptr);
		assert(dynamic_cast<FileMessageReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<FileMessageReceiverConfiguration*>(consumer) == consumer_config);
	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_decorating_receiver.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = MessageDecoratingReceiverConfiguration("connection1", "session1", "consumer1", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		assert(consumer != nullptr);
		assert(dynamic_cast<MessageDecoratingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<MessageDecoratingReceiverConfiguration*>(consumer) == consumer_config);
	}


	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_decorating_receiver_to_file.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = FileMessageDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "test_messages.txt", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		assert(consumer != nullptr);
		assert(dynamic_cast<FileMessageDecoratingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<FileMessageDecoratingReceiverConfiguration*>(consumer) == consumer_config);
	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_counting_receiver_to_file.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = FileMessageCountingReceiverConfiguration("connection1", "session1", "consumer1", "test_messages.txt", 1);

		assert(consumer != nullptr);
		assert(dynamic_cast<FileMessageCountingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<FileMessageCountingReceiverConfiguration*>(consumer) == consumer_config);
	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_decorating_counting_receiver.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = MessageCountingDecoratingReceiverConfiguration("connection1", "session1", "consumer1",  1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		assert(consumer != nullptr);
		assert(dynamic_cast<MessageCountingDecoratingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<MessageCountingDecoratingReceiverConfiguration*>(consumer) == consumer_config);
	}

	{
		boost::json::object::value_type message_receiver_config_json = *valueFromFile("test_message_decorating_counting_receiver_to_file.config").as_object().cbegin();
		auto consumer = parser.createTestCaseReceiverConfig(message_receiver_config_json.key_c_str(), message_receiver_config_json.value().as_object());
		auto consumer_config = FileMessageCountingDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "test_messages.txt", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });

		assert(consumer != nullptr);
		assert(dynamic_cast<FileMessageCountingDecoratingReceiverConfiguration*>(consumer) != nullptr);
		assert(*dynamic_cast<FileMessageCountingDecoratingReceiverConfiguration*>(consumer) == consumer_config);
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

		{
	
			auto test_consumer_config = MessageReceiverConfiguration("connection1", "session1", "consumer1");
			MessageReceiver receiver(test_consumer_config, test_client, event_observer);
			
		}

		{
			auto test_consumer_config = MessageCountingReceiverConfiguration("connection1", "session1", "consumer1",1);
			MessageCountingReceiver receiver(test_consumer_config, test_client, event_observer);
			
			//assert(receiver.receivedMessageCount() == 1);
		}

		{
			auto test_consumer_config = FileMessageReceiverConfiguration("connection1", "session1", "consumer1", "message_file.txt");
			MessageFileReceiver receiver(test_consumer_config, test_client, event_observer);
			
		}

		{
	
			auto test_consumer_config = MessageDecoratingReceiverConfiguration("connection1", "session1", "consumer1", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageDecoratingReceiver receiver(test_consumer_config, test_client, event_observer);
			
		}

		{
			auto test_consumer_config = FileMessageCountingReceiverConfiguration("connection1", "session1", "consumer1", "message_file.txt", 1);
			MessageCountingFileReceiver receiver(test_consumer_config, test_client, event_observer);
			
			//assert(receiver.receivedMessageCount() == 1);
		}

		{
	
			auto test_consumer_config = MessageCountingDecoratingReceiverConfiguration("connection1", "session1", "consumer1", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageCountingDecoratingReceiver receiver(test_consumer_config, test_client, event_observer);
			
			//assert(receiver.receivedMessageCount() == 1);
		}

		{
			auto test_consumer_config = FileMessageDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "message_file.txt", { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageDecoratingFileReceiver receiver(test_consumer_config, test_client, event_observer);
			
		}

		{
			auto test_consumer_config = FileMessageCountingDecoratingReceiverConfiguration("connection1", "session1", "consumer1", "message_file.txt", 1, { new MessageTestField(FIELD_TYPE::BOOLEANPROPERTY,"property","false") });
			MessageCountingDecoratingFileReceiver receiver(test_consumer_config, test_client, event_observer);
			
			//assert(receiver.receivedMessageCount() == 1);
		}


		

	}

	return 0;
	
}






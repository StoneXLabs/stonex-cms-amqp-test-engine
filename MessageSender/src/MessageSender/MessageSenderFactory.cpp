#include <MessageSender/MessageSenderFactory.h>

#include <Configuration/MessageCountingSenderConfiguration.h>
#include <Configuration/MessageDecoratingSenderConfiguration.h>
#include <Configuration/FileMessageSenderConfiguration.h>

#include <Configuration/FileMessageCountingSenderConfiguration.h>
#include <Configuration/FileMessageDecoratingSenderConfiguration.h>
#include <Configuration/MessageCountingDecoratingSenderConfiguration.h>

#include <Configuration/FileMessageCountingDecoratingSenderConfiguration.h>

#include <MessageSender/MessageCountingSender.h>
#include <MessageSender/MessageDecoratingSender.h>
#include <MessageSender/MessageFileSender.h>
#include <MessageSender/MessageCountingFileSender.h>
#include <MessageSender/MessageDecoratingFileSender.h>
#include <MessageSender/MessageCountingDecoratingSender.h>
#include <MessageSender/MessageCountingDecoratingFileSender.h>

MessageSender * MessageSenderFactory::create(const MessageSenderConfiguration & sender_configuration, CMSClientTestUnit & client_configuration, EventStatusObserver & parent) const
{
	if (auto sender = create_sender(sender_configuration, client_configuration, parent); sender == nullptr)
	{
		if (auto concrete_configuration = dynamic_cast<const FileMessageSenderConfiguration*>(&sender_configuration)) {
			return new MessageFileSender(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageCountingSenderConfiguration*>(&sender_configuration)) {
			return new MessageCountingFileSender(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageDecoratingSenderConfiguration*>(&sender_configuration)) {
			return new MessageDecoratingFileSender(*concrete_configuration, client_configuration, parent);
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageCountingDecoratingSenderConfiguration*>(&sender_configuration)) {
			return new MessageCountingDecoratingFileSender(*concrete_configuration, client_configuration, parent);
		}
		return nullptr;
	}
}

MessageSender * MessageSenderFactory::create_sender(const MessageSenderConfiguration & sender_configuration, CMSClientTestUnit & client_configuration, EventStatusObserver & parent) const
{
	/*if (auto concrete_configuration = dynamic_cast<const MessageSenderConfiguration*>(&sender_configuration)) {
		return new MessageSender(*concrete_configuration, client_configuration, parent);
	}
	else if (auto concrete_configuration = dynamic_cast<const MessageCountingSenderConfiguration*>(&sender_configuration)) {
		return new MessageCountingSender(*concrete_configuration, client_configuration, parent);
	}
	else if (auto concrete_configuration = dynamic_cast<const MessageDecoratingSenderConfiguration*>(&sender_configuration)) {
		return new MessageDecoratingSender(*concrete_configuration, client_configuration, parent);
	}
	else if (auto concrete_configuration = dynamic_cast<const MessageCountingDecoratingSenderConfiguration*>(&sender_configuration)) {
		return new MessageCountingDecoratingSender(*concrete_configuration, client_configuration, parent);
	}*/

	return nullptr;
}

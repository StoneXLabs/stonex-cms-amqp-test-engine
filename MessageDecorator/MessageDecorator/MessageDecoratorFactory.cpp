#include "MessageDecoratorFactory.h"
#include "ApplicationPropertyDecorator.h"
#include "CMSPropertyDecorator.h"
#include "ApplicationPropertyDecorator.h"

CMSMessageDecorator * MessageDecoratorFactory::create(const interoperability_tests::config::producer::MessageSenderConfiguration & config)
{
	CMSMessageDecorator* decorator{ nullptr };
	std::for_each(std::cbegin(config.properties()), std::cend(config.properties()), [&decorator](const MessageTestField& item) {
	
		CMSMessageDecorator* current_item{ nullptr };
		
		switch (item.type())
		{

		case FIELD_TYPE::BOOLEANPROPERTY:
		case FIELD_TYPE::BYTEPROPERTY:
		case FIELD_TYPE::DOUBLEPROPERTY:
		case FIELD_TYPE::FLOATPROPERTY:
		case FIELD_TYPE::INTPROPERTY:
		case FIELD_TYPE::LONGPROPERTY:
		case FIELD_TYPE::SHORTPROPERTY:
		case FIELD_TYPE::STRINGPROPERTY:
			current_item = new ApplicationPropertyDecorator(item);
		break;
		case FIELD_TYPE::CMS_CORRELATION_ID:
		case FIELD_TYPE::CMS_DELIVERY_MODE:
		case FIELD_TYPE::CMS_DESTINATION:
		case FIELD_TYPE::CMS_EXPIRATION:
		case FIELD_TYPE::CMS_MESSAGE_ID:
		case FIELD_TYPE::CMS_PRIORITY:
		case FIELD_TYPE::CMS_REDELIVERED:
		case FIELD_TYPE::CMS_REPLY_TO:
		case FIELD_TYPE::CMS_TIMESTAMP:
		case FIELD_TYPE::CMS_TYPE:
			current_item = new CMSPropertyDecorator(item);
			break;
		default:
			break;
		}

		if (decorator)
			decorator->addNext(current_item);
		else
			decorator = current_item;

	});

	return decorator;
}

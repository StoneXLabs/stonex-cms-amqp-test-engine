#include <MessageDecorator/CMSMessageDecorator.h>

CMSMessageDecorator::CMSMessageDecorator(MessageTestField other)
	:MessageTestField(other)
{
}

void CMSMessageDecorator::decorate(cms::Message * mes, cms::Session * sess) const
{
	if (mNext)
		mNext->decorate(mes, sess);
}

void CMSMessageDecorator::addNext(CMSMessageDecorator * next)
{
	if (!mNext)
		mNext = next;
	else
		mNext->addNext(next);
}

bool operator==(const CMSMessageDecorator & lhs, const CMSMessageDecorator & rhs)
{
	bool equal{ false };
	if (lhs.mName == rhs.mName &&
		lhs.mFieldType == rhs.mFieldType)
	{
		switch (lhs.mFieldType)
		{
		case FIELD_TYPE::BOOLEANPROPERTY:
			equal =  std::atoi(lhs.mValueString.c_str()) == std::atoi(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::BYTEPROPERTY:
			equal = lhs.mValueString == rhs.mValueString;
			break;
		case FIELD_TYPE::DOUBLEPROPERTY:
			equal = std::stod(lhs.mValueString.c_str()) == std::stod(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::FLOATPROPERTY:
			equal = std::stof(lhs.mValueString.c_str()) == std::stof(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::INTPROPERTY:
			equal = std::atoi(lhs.mValueString.c_str()) == std::atoi(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::LONGPROPERTY:
			equal = std::stod(lhs.mValueString.c_str()) == std::stod(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::SHORTPROPERTY:
			equal = std::atoi(lhs.mValueString.c_str()) == std::atoi(rhs.mValueString.c_str());
			break;
		case FIELD_TYPE::STRINGPROPERTY:
			equal = lhs.mValueString == rhs.mValueString;
			break;
		default:
			return false;
			break;
		}

		if (equal)
		{
			if (lhs.mNext == nullptr && rhs.mNext == nullptr)
				return true;
			else if (lhs.mNext == nullptr || rhs.mNext == nullptr)
				return false;
			else {
				return *lhs.mNext == *rhs.mNext;
			}
		}
		else
			return false;
	}
	else
		return false;
}

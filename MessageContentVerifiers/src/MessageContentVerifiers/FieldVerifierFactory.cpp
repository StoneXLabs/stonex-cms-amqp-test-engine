/*
 * Copyright 2022 StoneX Financial Ltd.
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <MessageContentVerifiers/FieldVerifierFactory.h>

IExpectedField* FieldVerifierFactory::create(FIELD_TYPE ft, bool check_existance, bool check_value, const boost::json::value& value, const std::string& msg_property)
{
	IExpectedField *ef{nullptr};

	switch (ft)
	{
	case FIELD_TYPE::CMS_CORRELATION_ID:
		ef = new ExpectedField<std::string>(ft, check_existance, check_value, value.as_string().c_str(), msg_property);
		break;
	case FIELD_TYPE::CMS_DELIVERY_MODE:
		ef = new ExpectedField<int>(ft, check_existance, check_value, value.to_number< int >(), msg_property);
		break;
	case FIELD_TYPE::CMS_DESTINATION:
		ef = new ExpectedField<cms::Destination*>(ft, check_existance, check_value/*, value, msg_property*/);
		break;
	case FIELD_TYPE::CMS_EXPIRATION:
		ef = new ExpectedField<long long>(ft, check_existance, check_value, value.to_number< long long >(), msg_property);
		break;
	case FIELD_TYPE::CMS_MESSAGE_ID:
		ef = new ExpectedField<std::string>(ft, check_existance, check_value, value.as_string().c_str());
		break;
	case FIELD_TYPE::CMS_PRIORITY:
		ef = new ExpectedField<int>(ft, check_existance, check_value, value.to_number< int >(), msg_property);
		break;
	case FIELD_TYPE::CMS_REDELIVERED:
		ef = new ExpectedField<bool>(ft, check_existance, check_value, value.as_bool(), msg_property);
		break;
	case FIELD_TYPE::CMS_REPLY_TO:
		ef = new ExpectedField<cms::Destination*>(ft, check_existance, check_value/*, value, msg_property*/);
		break;
	case FIELD_TYPE::CMS_TIMESTAMP:
		ef = new ExpectedField<long long>(ft, check_existance, check_value, value.to_number< long long >(), msg_property);
		break;
	case FIELD_TYPE::CMS_TYPE:
		ef = new ExpectedField<std::string>(ft, check_existance, check_value, value.as_string().c_str(), msg_property);//CHECK
		break;
	case FIELD_TYPE::INTPROPERTY :
		ef = new ExpectedField<int>(ft, check_existance, check_value, value.to_number< int >(), msg_property);
		break;
	case FIELD_TYPE::BOOLEANPROPERTY:
		ef = new ExpectedField<bool>(ft, check_existance, check_value, value.as_bool(), msg_property);
		break;
	case FIELD_TYPE::DOUBLEPROPERTY:
		ef = new ExpectedField<double>(ft, check_existance, check_value, value.to_number< double >(), msg_property);
		break;
	case FIELD_TYPE::LONGPROPERTY:
		ef = new ExpectedField<long>(ft, check_existance, check_value, value.to_number< long >(),msg_property);
		break;
	case FIELD_TYPE::STRINGPROPERTY:
		ef = new ExpectedField<std::string>(ft, check_existance, check_value, value.as_string().c_str(),msg_property);
		break;
	case FIELD_TYPE::BYTEPROPERTY:
		//ef = new ExpectedField<std::uint8_t>(ft, check_existance, check_value, value.as_string().data(), msg_property); //TO DO
		break;
	case FIELD_TYPE::FLOATPROPERTY:
		//ef = new ExpectedField<float>(ft, check_existance, check_value, value., msg_property); //TO DO
		break;
	case FIELD_TYPE::SHORTPROPERTY:
		//ef = new ExpectedField<short>(ft, check_existance, check_value, value.as_string().c_str(), msg_property); TO DO
		break;

	}

	return ef;
	
}


IExpectedField* FieldVerifierFactory::create(FIELD_TYPE ft, bool check_existance, bool check_value,  const std::string& value, const std::string& msg_property)
{
	IExpectedField *ef{ nullptr };

	switch (ft)
	{
	case FIELD_TYPE::CMS_CORRELATION_ID:
		ef = new ExpectedField<std::string>(ft, check_existance, check_value, value, msg_property);
		break;
	case FIELD_TYPE::CMS_DELIVERY_MODE:
		ef = new ExpectedField<int>(ft, check_existance, check_value, stoi(value), msg_property);
		break;
	case FIELD_TYPE::CMS_DESTINATION:
		ef = new ExpectedField<cms::Destination*>(ft, check_existance, check_value/*, value, msg_property*/);
		break;
	case FIELD_TYPE::CMS_EXPIRATION:
		ef = new ExpectedField<long long>(ft, check_existance, check_value, stoll(value), msg_property);
		break;
	case FIELD_TYPE::CMS_MESSAGE_ID:
		ef = new ExpectedField<std::string>(ft, check_existance, check_value, value, msg_property);
		break;
	case FIELD_TYPE::CMS_PRIORITY:
		ef = new ExpectedField<int>(ft, check_existance, check_value, stoi(value), msg_property);
		break;
	case FIELD_TYPE::CMS_REDELIVERED:
		ef = new ExpectedField<bool>(ft, check_existance, check_value, value == "true", msg_property);
		break;
	case FIELD_TYPE::CMS_REPLY_TO:
		ef = new ExpectedField<cms::Destination*>(ft, check_existance, check_value/*, value, msg_property*/);
		break;
	case FIELD_TYPE::CMS_TIMESTAMP:
		ef = new ExpectedField<long long>(ft, check_existance, check_value, stoll(value), msg_property);
		break;
	case FIELD_TYPE::CMS_TYPE:
		ef = new ExpectedField<std::string>(ft, check_existance, check_value, value, msg_property);//CHECK
		break;
	case FIELD_TYPE::INTPROPERTY:
		ef = new ExpectedField<int>(ft, check_existance, check_value, stoi(value), msg_property);
		break;
	case FIELD_TYPE::BOOLEANPROPERTY:
		ef = new ExpectedField<bool>(ft, check_existance, check_value, value == "true", msg_property);
		break;
	case FIELD_TYPE::DOUBLEPROPERTY:
		ef = new ExpectedField<double>(ft, check_existance, check_value, stod(value), msg_property);
		break;
	case FIELD_TYPE::LONGPROPERTY:
		ef = new ExpectedField<long>(ft, check_existance, check_value, stoll(value), msg_property);
		break;
	case FIELD_TYPE::STRINGPROPERTY:
		ef = new ExpectedField<std::string>(ft, check_existance, check_value, value, msg_property);
		break;
	case FIELD_TYPE::BYTEPROPERTY:
		//ef = new ExpectedField<std::uint8_t>(ft, check_existance, check_value, value.as_string().data(), msg_property); //TO DO
		break;
	case FIELD_TYPE::FLOATPROPERTY:
		//ef = new ExpectedField<float>(ft, check_existance, check_value, value., msg_property); //TO DO
		break;
	case FIELD_TYPE::SHORTPROPERTY:
		//ef = new ExpectedField<short>(ft, check_existance, check_value, value.as_string().c_str(), msg_property); TO DO
		break;

	}

	return ef;
}

IExpectedField * FieldVerifierFactory::create(const cms::Message * message, const IExpectedField* other)
{
	IExpectedField *ef{ nullptr };

	try
	{
		switch (other->expectedField())
		{
		case FIELD_TYPE::CMS_CORRELATION_ID:
			ef = new ExpectedField<std::string>(other->expectedField(), true, true, message->getCMSCorrelationID(), other->fieldName());
			break;
		case FIELD_TYPE::CMS_DELIVERY_MODE:
			ef = new ExpectedField<int>(other->expectedField(), true, true, message->getCMSDeliveryMode(), other->fieldName());
			break;
		case FIELD_TYPE::CMS_DESTINATION:
			ef = new ExpectedField<const cms::Destination*>(other->expectedField(), true, true, message->getCMSDestination(), other->fieldName());
			break;
		case FIELD_TYPE::CMS_EXPIRATION:
			ef = new ExpectedField<long long>(other->expectedField(), true, true, message->getCMSExpiration(), other->fieldName());
			break;
		case FIELD_TYPE::CMS_MESSAGE_ID:
			ef = new ExpectedField<std::string>(other->expectedField(), true, true, message->getCMSMessageID(), other->fieldName());
			break;
		case FIELD_TYPE::CMS_PRIORITY:
			ef = new ExpectedField<int>(other->expectedField(), true, true, message->getCMSPriority(), other->fieldName());
			break;
		case FIELD_TYPE::CMS_REDELIVERED:
			ef = new ExpectedField<bool>(other->expectedField(), true, true, message->getCMSRedelivered(), other->fieldName());
			break;
		case FIELD_TYPE::CMS_REPLY_TO:
			ef = new ExpectedField<const cms::Destination*>(other->expectedField(), true, true, message->getCMSReplyTo(), other->fieldName());
			break;
		case FIELD_TYPE::CMS_TIMESTAMP:
			ef = new ExpectedField<long long>(other->expectedField(), true, true, message->getCMSTimestamp(), other->fieldName());
			break;
		case FIELD_TYPE::CMS_TYPE:
			ef = new ExpectedField<std::string>(other->expectedField(), true, true, message->getCMSType(), other->fieldName());//CHECK
			break;
		case FIELD_TYPE::INTPROPERTY:
			ef = new ExpectedField<int>(other->expectedField(), true, true, message->getIntProperty(other->fieldName()), other->fieldName());
			break;
		case FIELD_TYPE::BOOLEANPROPERTY:
			ef = new ExpectedField<bool>(other->expectedField(), true, true, message->getBooleanProperty(other->fieldName()), other->fieldName());
			break;
		case FIELD_TYPE::DOUBLEPROPERTY:
			ef = new ExpectedField<double>(other->expectedField(), true, true, message->getDoubleProperty(other->fieldName()), other->fieldName());
			break;
		case FIELD_TYPE::LONGPROPERTY:
			ef = new ExpectedField<long>(other->expectedField(), true, true, message->getLongProperty(other->fieldName()), other->fieldName());
			break;
		case FIELD_TYPE::STRINGPROPERTY:
			ef = new ExpectedField<std::string>(other->expectedField(), true, true, message->getStringProperty(other->fieldName()), other->fieldName());
			break;
		case FIELD_TYPE::BYTEPROPERTY:
			ef = new ExpectedField<std::int8_t>(other->expectedField(), true, true, message->getByteProperty(other->fieldName()), other->fieldName()); //TO DO
			break;
		case FIELD_TYPE::FLOATPROPERTY:
			ef = new ExpectedField<float>(other->expectedField(), true, true, message->getFloatProperty(other->fieldName()), other->fieldName()); //TO DO
			break;
		case FIELD_TYPE::SHORTPROPERTY:
			ef = new ExpectedField<short>(other->expectedField(), true, true, message->getShortProperty(other->fieldName()), other->fieldName());// TO DO
			break;
		}
	}
	catch (const std::exception&)
	{
		
	}

	return ef;
}

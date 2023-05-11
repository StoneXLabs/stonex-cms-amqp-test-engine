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

#pragma once

#include <boost/json.hpp>

#include <ConfigurationParser/TestSuiteConfigParser.h>
#include <Configuration/TestSuiteConfiguration.h>
#include <Configuration/CMSExceptionsConfiguration.h>

#include <ConfigurationParser/CMSWrapperConfigurationParser.h>

class TestSuiteJsonConfigParser : public TestSuiteConfigParser, public CMSWrapperConfigurationParser
{
public:
	explicit TestSuiteJsonConfigParser(const std::string& configFile);

	TestSuiteConfiguration createConfiguration() const;

protected:
	boost::json::value fromFile() const;
	
	TestCaseConfiguration createTestCaseConfig(const std::string& configName, const boost::json::value& json) const;


	TestCasePerformerConfiguration createTestPerformerConfig(const boost::json::value & json) const;

	TestCaseVerifierConfiguration createTestVerifierConfig(const boost::json::value & json) const;

	virtual TestCaseProducerConfiguration* createTestCaseProducerConfig(const std::string& configName, const boost::json::value& json) const;
	virtual TestCaseMessageReceiverConfiguration* createTestReceiverConfig(const std::string& configName, const boost::json::value& json) const;
	virtual CMSExceptionsConfiguration* createTestExceptionConfig(const std::string& configName, const boost::json::value& json) const;

private:
	const std::string mConfigFilePath;
};
/*
 * Copyright 2023 StoneX Financial Ltd.
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

#include <fstream>
#include <boost/json.hpp>
#include <ConfigurationParser/TestSuiteJsonConfigParser.h>


TestSuiteJsonConfigParser::TestSuiteJsonConfigParser(const std::string& configFile)
	:mConfigFilePath{ configFile }
{
}

TestSuiteConfiguration TestSuiteJsonConfigParser::createConfiguration() const
{
	

	if (auto jsonConfig = fromFile(); jsonConfig.is_object())
	{
		std::list<TestCaseConfiguration> configuration;

		std::transform(std::cbegin(jsonConfig.as_object()), std::cend(jsonConfig.as_object()), std::back_inserter(configuration), [this](const boost::json::object::value_type obj) {
			return createTestCaseConfig(obj.key_c_str(), obj.value());
		});

		return TestSuiteConfiguration(mConfigFilePath, configuration);
	}
	else return TestSuiteConfiguration(mConfigFilePath, {});
}

boost::json::value TestSuiteJsonConfigParser::fromFile() const
{
	std::ifstream config_file(mConfigFilePath);

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

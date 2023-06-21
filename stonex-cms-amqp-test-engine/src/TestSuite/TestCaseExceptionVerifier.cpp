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

#include <algorithm>
#include <TestSuite/TestCaseExceptionVerifier.h>
#include <Wrapper/CMSExceptionListenerTestUnit.h>

TestCaseExceptionVerifier::TestCaseExceptionVerifier(const TestCaseVerifierConfiguration & config, Notifier& notifier)
{
	std::transform(std::cbegin(config.exceptionsExpectations()), std::cend(config.exceptionsExpectations()), std::back_inserter(mExceptionVerifier),
		[&notifier](const ExceptionsConfiguration* item) {return ExceptionVerifier(item->exceptionSourceId(), item->expectedExceptionCount(), notifier); });
}

//TestCaseExceptionVerifier::TestCaseExceptionVerifier(const TestCaseExceptionVerifier& other)
//{
//}
//
//TestCaseExceptionVerifier::TestCaseExceptionVerifier(TestCaseExceptionVerifier&& other)
//{
//}

void TestCaseExceptionVerifier::onException(const cms::CMSException & ex)
{
	if (auto _ex = dynamic_cast<const CMSExceptionTestUnit*>(&ex))
	{
		
		auto verifier = std::find_if(std::begin(mExceptionVerifier), std::end(mExceptionVerifier), [_ex](ExceptionVerifier& item) {return item.id() == _ex->id(); });
		if (verifier != std::end(mExceptionVerifier))
		{
			verifier->onException(ex);
		}
	}
}

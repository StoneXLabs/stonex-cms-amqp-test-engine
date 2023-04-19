#pragma once

#include <functional>
#include "TestCaseStatus.h"

class VerifierReport;

class TestCase
{
public:
	virtual TEST_CASE_STATUS run() = 0;
	virtual VerifierReport* getRaport() = 0;
	virtual std::string testName() const = 0;

};


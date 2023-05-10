
#include "ConfigurationParser/CMSWrapperConfigurationParser.h"
#include "Wrapper/CMSClientTestUnit.h"
#include <boost/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>

#include "StdOutLogger/StdOutLogger.h"

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

class TestExceptionListener : public cms::ExceptionListener {
public:
	void onException(const cms::CMSException& ex) { std::cout << "EXCEPTION " << ex.what() << std::endl; }
};

int main()
{
	
}






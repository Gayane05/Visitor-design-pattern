#include <iostream>
#include <boost/variant.hpp>
#include <sstream>

class A
{
public:
	A(const std::string& s) :str{ s }
	{
	}
	std::string str;
};

using var_t = boost::variant<int, double, A>;

class processor : public boost::static_visitor<int>
{
public:
	int operator()(int& val)
	{
		strm.str("");
		strm << "operator () for int: " << val << std::endl;
		return (strm.str()).size();
	}

	int operator()(double& val)
	{
		strm.str("");
		strm << "operator () for double: " << val << std::endl;
		return (strm.str()).size();
	}

	int operator()(A& val)
	{
		strm.str("");
		strm << "operator () for A: " << val.str << std::endl;
		return (strm.str()).size();
	}

	int process(var_t& v)
	{
		return boost::apply_visitor(*this, v);
	}

	std::ostringstream strm;
};


int main()
{
	var_t v1 = 11;
	var_t v2 = 3.14;
	var_t v3 = A("hi");

	processor proc;
	std::cout << "Symbols' count in the stream " << proc.process(v2) << std::endl;
	std::cout << "Symbols' count in the stream " << proc.process(v1) << std::endl;
	std::cout << "Symbols' count in the stream " << proc.process(v3) << std::endl;


	return 0;
}
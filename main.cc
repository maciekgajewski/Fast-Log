#include "logger.h"

void log1(const std::string& str, int number)
{
	LOG("str=%, number=%", str, number);
}

void log2(double d, int x)
{
	LOG("Hello myInt=% myChar=% myDouble=%", x, 'a', d);
}

int main(int argc, char* args[])
{
	log1("Hello", 42);
	log2(44.4, 66);

	Logger::Consume();
}


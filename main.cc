#include "logger.h"

int main(int argc, char* args[])
{
	LOG("Hello myInt=% myChar=% myDouble=%", 1, 'a', 42.3);

	LOG("Another log. The answer is %", 42);


	Logger::Consume();
}


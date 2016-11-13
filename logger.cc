#include "logger.h"

#include <iostream>

namespace Logger { namespace Detail {

static std::vector<char> gBuffer;

// naive implemntation, for demonstration purposes only

char* GetWriteBuffer(int size)
{
	size_t offset = gBuffer.size();
	gBuffer.resize(gBuffer.size() + size);
	return gBuffer.data() + offset;
}

const char* ConsumeRecord(const char* data)
{
	const Header* header = reinterpret_cast<const Header*>(data);
	const char* args = data + sizeof(Header);
	header->Formatter(std::cout, header->FormatString, args);
	return args + header->ArgsSize;
}

}

void Consume()
{
	const char* d = Detail::gBuffer.data();
	const char* end = d + Detail::gBuffer.size();
	while(d < end)
	{
		d = Detail::ConsumeRecord(d);
	}
	assert(d == end);
}

}

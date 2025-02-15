#pragma once
#include <vector>

class Packet
{
public:

	Packet(Packet const&) = delete;
	Packet& operator=(Packet const&) = delete;
	
	char* Type;

	unsigned char* Buffer;

	unsigned short Opcode;

	unsigned char* Data;

	unsigned int Length;

	Packet(char* type, unsigned char* buffer, unsigned int length);

private:

};

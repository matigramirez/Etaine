#pragma once
class Opcode
{
public:
	unsigned short Value;

	char* Label;

	Opcode(unsigned short value, char* label);
};

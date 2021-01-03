#pragma once
#ifndef REIKEUSEU_PACKETS_PACKET_H
#define REIKEUSEU_PACKETS_PACKET_H
#include <vector>

class Packet
{
public:

	Packet(Packet const&) = delete;
	Packet& operator=(Packet const&) = delete;
	
	char* Type;

	unsigned short Opcode;

	unsigned char* Data;

	unsigned int Length;

	Packet(char* type, unsigned char* buffer, unsigned int length);

private:

};

#endif

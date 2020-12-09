#pragma once
#ifndef REIKEUSEU_PACKETS_PACKET_H
#define REIKEUSEU_PACKETS_PACKET_H
#include <vector>

class Packet
{
public:

	Packet(Packet const&) = delete;
	Packet& operator=(Packet const&) = delete;
	
	unsigned short Opcode;

	unsigned char* Data;

	Packet(unsigned short packetType, unsigned char* buffer, unsigned int length);
	Packet(unsigned char* buffer, unsigned int length);

private:

};

#endif

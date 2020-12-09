#include <Reikeuseu/Packets/Packet.h>
#include <vector>
#include <iostream>

Packet::Packet(unsigned short opcode, unsigned char* buffer, unsigned int length)
{
	this->Opcode = opcode;
	this->Data = buffer;
}

Packet::Packet(unsigned char* buffer, unsigned int length)
{
	this->Opcode = *reinterpret_cast<unsigned short*>(buffer);
	this->Data = buffer + 2;
}
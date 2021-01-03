#include <Reikeuseu/Packets/Packet.h>
#include <vector>
#include <iostream>

Packet::Packet(char* type, unsigned char* buffer, unsigned int length)
{
	this->Type = type;
	this->Opcode = *reinterpret_cast<unsigned short*>(buffer);

	this->Data = new unsigned char[length];
	memcpy(this->Data, (void*)(buffer + 2), length);
	//this->Data = buffer + 2;
	this->Length = length;
} 
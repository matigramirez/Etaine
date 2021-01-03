#pragma once
#ifndef REIKEUSEU_FAKER_H
#define REIKEUSEU_FAKER_H

class Faker
{
public:
	static void __cdecl fakeSendPacket(unsigned char* buffer, unsigned int bufferLength);

	static void __cdecl fakeHandlePacket(unsigned short opcode, unsigned char* buffer);
};

#endif
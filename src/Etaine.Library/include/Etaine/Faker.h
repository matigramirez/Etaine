#pragma once
#ifndef Etaine_FAKER_H
#define Etaine_FAKER_H

class Faker
{
public:
	static void __cdecl fakeSendPacket(char* fakePacketBuffer);

	static void __cdecl fakeHandlePacket(unsigned char* buffer);
};

#endif
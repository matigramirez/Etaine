#pragma once

class Faker
{
public:
	static void __cdecl fakeSendPacket(char* fakePacketBuffer);

	static void __cdecl fakeHandlePacket(unsigned char* buffer);
};

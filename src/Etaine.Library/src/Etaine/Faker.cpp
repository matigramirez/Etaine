#include <Etaine/Faker.h>
#include <Etaine/Analyzer.h>
#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

void __cdecl Faker::fakeSendPacket(char* fakePacketBuffer) {
	int size = 0;
	int length = strlen(fakePacketBuffer);

	if (length < 4)
		return;

		size = ((length - 2) / 3) + 1;

	unsigned char* buffer = new unsigned char[size + 1];

	for (int x = 0; x < size; ++x)
	{
		buffer[x] = (BYTE)strtol(fakePacketBuffer + x * 3, NULL, 16);
	}

	Analyzer::originalSendPacket(buffer, size);


	if (buffer)
		delete[]buffer;
}

void __cdecl Faker::fakeHandlePacket(unsigned char* pBuffer) {
	unsigned short opcode = *reinterpret_cast<unsigned short*>(pBuffer);

	cout << "receiving fake packet with opcode: " << ">> 0x" << hex << setw(4) << setfill('0') << uppercase << opcode << endl;
	Analyzer::originalHandlePacket(opcode, pBuffer);
}
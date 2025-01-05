#include <Faker.h>
#include <Analyzer.h>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void __cdecl Faker::fakeSendPacket(char* fakePacketBuffer) {
	int packetLen = strlen(fakePacketBuffer);

	// 14 comes from "SEND>> 0xXXXX\0"
	if (packetLen < 14)
		return;

	const char prefix[] = "SEND>> ";
	if (std::strncmp(fakePacketBuffer, prefix, sizeof(prefix) - 1) != 0) {
		return;
	}

	// Skip "SEND>> 0" part
	char* trimmedBuffer = fakePacketBuffer + 8;
	// "xA1F2 0F 21 84 3F"
	// "F2 A1 0F 21 84 3F"

	auto temp = trimmedBuffer[1]; // A

	trimmedBuffer[0] = trimmedBuffer[3]; // F
	trimmedBuffer[4] = trimmedBuffer[2]; // 1
	trimmedBuffer[1] = trimmedBuffer[4]; // 2
	trimmedBuffer[3] = temp;
	trimmedBuffer[2] = ' ';

	int size = 0;
	int length = strlen(trimmedBuffer);

	if (length < 4)
		return;


	size = ((length - 2) / 3) + 1;

	unsigned char buffer[1024] = {};

	for (int x = 0; x < size; ++x)
	{
		buffer[x] = (BYTE)strtol(trimmedBuffer + x * 3, NULL, 16);
	}

	Analyzer::originalSendPacket(buffer, size);
}

void __cdecl Faker::fakeHandlePacket(unsigned char* pBuffer) {
	unsigned short opcode = *reinterpret_cast<unsigned short*>(pBuffer);

	cout << "receiving fake packet with opcode: " << ">> 0x" << hex << setw(4) << setfill('0') << uppercase << opcode << endl;
	Analyzer::originalHandlePacket(opcode, pBuffer);
}
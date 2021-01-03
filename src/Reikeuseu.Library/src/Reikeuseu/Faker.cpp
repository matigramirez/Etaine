#include <Reikeuseu/Faker.h>
#include <Reikeuseu/Analyzer.h>
#include <iostream>
#include <iomanip>

using namespace std;

void __cdecl Faker::fakeSendPacket(unsigned char* pBuffer, unsigned int bufferLength) {
	cout << "sending fake packet with length: " << bufferLength << endl;
	Analyzer::originalSendPacket(pBuffer, bufferLength);
}

void __cdecl Faker::fakeHandlePacket(unsigned short opcode, unsigned char* pBuffer) {
	cout << "receiving fake packet with opcode: " << ">> 0x" << hex << setw(4) << setfill('0') << uppercase << opcode << endl;
	Analyzer::originalHandlePacket(opcode, pBuffer);
}
#include <Reikeuseu/Faker.h>
#include <Reikeuseu/Analyzer.h>

void __cdecl Faker::fakeSendPacket(unsigned char* pBuffer, unsigned int bufferLength) {
	Analyzer::originalSendPacket(pBuffer, bufferLength);
}

void __cdecl Faker::fakeHandlePacket(unsigned short opcode, unsigned char* pBuffer) {
	Analyzer::originalHandlePacket(opcode, pBuffer);
}
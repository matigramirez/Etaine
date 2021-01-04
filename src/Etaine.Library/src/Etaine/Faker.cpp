#include <Etaine/Faker.h>
#include <Etaine/Analyzer.h>
#include <iostream>
#include <iomanip>

using namespace std;

void __cdecl Faker::fakeSendPacket(unsigned char* pBuffer, unsigned int bufferLength) {
	cout << "******************* FAKE SEND *******************" << endl;

	for (size_t i = 0; i < bufferLength; i++)
	{
		cout << hex << setw(2) << setfill('0') << uppercase << (int)pBuffer[i] << " ";
	}

	cout << endl;

	cout << "*************************************************" << endl;

	Analyzer::originalSendPacket(pBuffer, bufferLength);
}

void __cdecl Faker::fakeHandlePacket(unsigned short opcode, unsigned char* pBuffer) {
	cout << "receiving fake packet with opcode: " << ">> 0x" << hex << setw(4) << setfill('0') << uppercase << opcode << endl;
	Analyzer::originalHandlePacket(opcode, pBuffer);
}
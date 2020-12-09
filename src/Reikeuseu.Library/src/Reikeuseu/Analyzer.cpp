#include <Reikeuseu\Analyzer.h>
#include <Reikeuseu\Helpers\ConsoleHelper.h>
#include <iostream>
#include <iomanip>
#include <detours.h>
#include <Reikeuseu\Packets\Packet.h>

// Definition for the game's original send packet function
typedef void(__cdecl* _sendPacket)(unsigned char* buffer, unsigned int bufferLength);

// Definition for the game's original receive packet function
typedef void(__cdecl* _receivePacket)(unsigned char* buffer, int bufferLength);

// Definition for the game's original handle packet function
typedef void(__cdecl* _handlePacket)(unsigned short opcode, unsigned char* buffer);

// Episode 1 function addresses
// When hooking Ep1 functions, the receive packet function isn't needed because the handle packet function includes
// the length of the packet. This means that the definition of the function needs to change so this addresses won't
// work unless the functions are defined properly
DWORD sendPacketAddressEp1 = 0x00549C10;
DWORD handlePacketAddressEp1 = 0x0054D560;

// Episode 4 function addresses
DWORD sendPacketAddressEp4 = 0x00585640;
DWORD receivePacketAddressEp4 = 0x004010E0;
DWORD handlePacketAddressEp4 = 0x00582E10;

// Episode 8 function addresses
DWORD sendPacketAddressEp8 = 0x00661020;
DWORD receivePacketAddressEp8 = 0x00401110;
DWORD handlePacketAddressEp8 = 0x006687B0;

// Define starting addresses of the game's functions
_sendPacket originalSendPacket = (_sendPacket)(sendPacketAddressEp8);
_receivePacket originalReceivePacket = (_receivePacket)(receivePacketAddressEp8);
_handlePacket originalHandlePacket = (_handlePacket)(handlePacketAddressEp8);

// Initialize the buffer length for the received packets
unsigned int lastBufferLength = 0;


void Analyzer::Initialize()
{
	// Start detour transaction on current thread
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Attach hook functions to the game's original functions
	DetourAttach(&(PVOID&)originalSendPacket, (PVOID)sendPacketHook);
	DetourAttach(&(PVOID&)originalReceivePacket, (PVOID)receivePacketHook);
	DetourAttach(&(PVOID&)originalHandlePacket, (PVOID)handlePacketHook);

	// Commit detour transaction
	DetourTransactionCommit();

	// Create console to log packets
	ConsoleHelper::CreateConsole();
}

void __cdecl  Analyzer::sendPacketHook(unsigned char* buffer, unsigned int bufferLength)
{
	Packet* packet = new Packet(buffer, bufferLength);

	std::cout << "SEND> OPCODE: 0x" << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << packet->Opcode << std::endl;

	std::cout << "Packet: ";
	for (size_t i = 0; i < bufferLength - 2; i++)
	{
		std::cout << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)packet->Data[i] << " ";
	}

	std::cout << std::endl;

	delete packet;

	// Call original function
	originalSendPacket(buffer, bufferLength);
}

void __cdecl Analyzer::receivePacketHook(unsigned char* encryptedBuffer, int bufferLength) {
	// Set buffer length for the handle packet hook
	lastBufferLength = bufferLength;

	// Call original function
	originalReceivePacket(encryptedBuffer, bufferLength);
}

void __cdecl Analyzer::handlePacketHook(unsigned short opcode, unsigned char* buffer)
{
	// Check that the receive packet hook has defined the buffer's length
	if (lastBufferLength != 0) {
		Packet* packet = new Packet(opcode, buffer, lastBufferLength);

		std::cout << "RECV> OPCODE: 0x" << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << packet->Opcode << std::endl;

		std::cout << "Packet: ";
		for (size_t i = 0; i < lastBufferLength - 2; i++)
		{
			std::cout << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)packet->Data[i] << " ";
		}

		std::cout << std::endl;

		delete packet;
	}
	else {
		Packet* packet = new Packet(buffer, 2);

		std::cout << "RECV> opcode: 0x" << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << packet->Opcode;
		std::cout << "Couldn't determine buffer size" << std::endl;

		delete packet;
	}

	// Buffer length is reset because it will be different on the next packet
	lastBufferLength = 0;

	// Call original function
	originalHandlePacket(opcode, buffer);
}
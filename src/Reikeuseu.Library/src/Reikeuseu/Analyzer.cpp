#include <Reikeuseu\Analyzer.h>
#include <Reikeuseu\Helpers\ConsoleHelper.h>
#include <Reikeuseu\Packets\Packet.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <detours.h>
#include <string>

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

// Initialize the buffer length for the received packets
unsigned int lastBufferLength = 0;

// Define starting addresses of the game's functions
_sendPacket Analyzer::originalSendPacket = (_sendPacket)(sendPacketAddressEp4);
_receivePacket Analyzer::originalReceivePacket = (_receivePacket)(receivePacketAddressEp4);
_handlePacket Analyzer::originalHandlePacket = (_handlePacket)(handlePacketAddressEp4);

std::vector<Packet*> Analyzer::InOutPackets = std::vector<Packet*>();

std::vector<std::string> Analyzer::Packets = std::vector<std::string>();

void __cdecl Analyzer::Initialize()
{
	// Start detour transaction on current thread
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Attach hook functions to the game's original functions
	DetourAttach(&(PVOID&)Analyzer::originalSendPacket, (PVOID)sendPacketHook);
	DetourAttach(&(PVOID&)Analyzer::originalReceivePacket, (PVOID)receivePacketHook);
	DetourAttach(&(PVOID&)Analyzer::originalHandlePacket, (PVOID)handlePacketHook);

	// Commit detour transaction
	DetourTransactionCommit();

	// Create console to log packets
	//ConsoleHelper::CreateConsole();
}

//static void AddReceivedPacket(Packet* packet);
//static void AddSentPacket(Packet* packet);

void Analyzer::AddInOutPacket(Packet* packet) {
	std::stringstream sStream;

	sStream << packet->Type << ">> 0x" << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << packet->Opcode << " ";

	for (size_t i = 0; i < packet->Length - 2; i++)
	{
		sStream << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)packet->Data[i] << " ";
	}

	sStream << std::endl;

	std::string str = sStream.str();

	Analyzer::Packets.push_back(str);
	//Analyzer::InOutPackets.push_back(packet);
}

void __cdecl Analyzer::sendPacketHook(unsigned char* buffer, unsigned int bufferLength)
{
	Packet* packet = new Packet((char*)"SEND", buffer, bufferLength);

	std::cout << "SEND> OPCODE: 0x" << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << packet->Opcode << std::endl;

	std::cout << "Packet: ";
	for (size_t i = 0; i < bufferLength - 2; i++)
	{
		std::cout << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)packet->Data[i] << " ";
	}

	std::cout << std::endl;

	Analyzer::AddInOutPacket(packet);

	delete packet;

	// Call original function
	originalSendPacket(buffer, bufferLength);
}

void __cdecl Analyzer::receivePacketHook(unsigned char* encryptedBuffer, int bufferLength) {
	// Set buffer length for the handle packet hook
	lastBufferLength = bufferLength;

	std::cout << "Received buffer. Length: " << lastBufferLength << std::endl;

	// Call original function
	originalReceivePacket(encryptedBuffer, bufferLength);
}

void __cdecl Analyzer::handlePacketHook(unsigned short opcode, unsigned char* buffer)
{
	// Check that the receive packet hook has defined the buffer's length
	if (lastBufferLength != 0) {
		Packet* packet = new Packet((char*)"RECV", buffer, lastBufferLength);

		std::cout << "RECV> OPCODE: 0x" << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << packet->Opcode << std::endl;

		std::cout << "Packet: ";

		for (size_t i = 0; i < lastBufferLength - 2; i++)
		{
			std::cout << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)packet->Data[i] << " ";
		}

		std::cout << std::endl;

		Analyzer::AddInOutPacket(packet);

		delete packet;
	}
	else {
		Packet* packet = new Packet((char*)"RECV", buffer, 2);

		std::cout << "RECV> opcode: 0x" << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << packet->Opcode;
		std::cout << "Couldn't determine buffer size" << std::endl;

		Analyzer::AddInOutPacket(packet);

		delete packet;
	}

	// Buffer length is reset because it will be different on the next packet
	lastBufferLength = 0;

	// Call original function
	originalHandlePacket(opcode, buffer);
}
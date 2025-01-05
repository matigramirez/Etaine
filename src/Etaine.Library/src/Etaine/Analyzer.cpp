#include <Etaine\Analyzer.h>
#include <Etaine\Helpers\ConsoleHelper.h>
#include <Etaine\Packets\Packet.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <detours/detours.h>
#include <string>

using namespace std;

// Episode 1 function addresses
// When hooking Ep1 functions, the receive packet function isn't needed because the handle packet function includes
// the length of the packet. This means that the definition of the function needs to change so this addresses won't
// work unless the functions are defined properly
DWORD sendPacketAddressEp1v1 = 0x00549C10;
DWORD handlePacketAddressEp1v1 = 0x0054D560;

// Episode 4 function addresses
DWORD sendPacketAddressEp4v1 = 0x00585640;
DWORD receivePacketAddressEp4v1 = 0x004010E0;
DWORD handlePacketAddressEp4v1 = 0x00582E10;

// Episode 6 function addresses
DWORD sendPacketAddressEp6v1 = 0x005EA9A0;
DWORD receivePacketAddressEp6v1 = 0x00401080;
DWORD handlePacketAddressEp6v1 = 0x005F1E10;

// Episode 8 v1 function addresses
DWORD sendPacketAddressEp8v1 = 0x00661020;
DWORD receivePacketAddressEp8v1 = 0x00401110;
DWORD handlePacketAddressEp8v1 = 0x006687B0;

// Episode 8 v2 function addresses
DWORD sendPacketAddressEp8v2 = 0x00676640;
DWORD receivePacketAddressEp8v2 = 0x00401100;
DWORD handlePacketAddressEp8v2 = 0x0067DF90;

// Define starting addresses of the game's functions
_sendPacket Analyzer::originalSendPacket = (_sendPacket)(sendPacketAddressEp6v1);
_receivePacket Analyzer::originalReceivePacket = (_receivePacket)(receivePacketAddressEp6v1);
_handlePacket Analyzer::originalHandlePacket = (_handlePacket)(handlePacketAddressEp6v1);

vector<Packet*> Analyzer::InOutPackets = vector<Packet*>();

vector<string> Analyzer::Packets = vector<string>();

vector<bool> Analyzer::PacketSelection = vector<bool>();

int Analyzer::DisplayType = 0;

unsigned short Analyzer::MaxPacketCount = 100;

bool Analyzer::LogSent = true;
bool Analyzer::LogReceived = true;
bool Analyzer::Active = true;

vector<Opcode*> Analyzer::LabeledOpcodes = vector<Opcode*>();

vector<unsigned short> Analyzer::IgnoredOpcodes = vector<unsigned short>();

// Initialize the buffer length for the received packets
unsigned int lastBufferLength = 0;

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


void Analyzer::AddInOutPacket(Packet* packet) {
	if (!Active)
		return;

	stringstream sStream;

	sStream << packet->Type << ">> 0x" << hex << setw(4) << setfill('0') << uppercase << packet->Opcode << " ";

	if (DisplayType == 0) // HEX
	{
		for (size_t i = 0; i < packet->Length - 2; i++)
		{
			sStream << hex << setw(2) << setfill('0') << uppercase << (int)packet->Data[i] << " ";
		}
	}
	else if (DisplayType == 1) // Decimal
	{
		for (size_t i = 0; i < packet->Length - 2; i++)
		{
			sStream << dec << setw(3) << setfill('0') << (int)packet->Data[i] << " ";
		}
	}
	else // ASCII
	{
		for (size_t j = 0; j < packet->Length - 2; j++)
		{
			if ((int)packet->Data[j] != 0) {
				sStream << packet->Data[j] << " ";
			}
			else {
				sStream << "|| ";
			}
		}
	}

	sStream << endl;

	string packetString = sStream.str();

	// Remove first element if there are more than MaxPacketCount packets
	if (InOutPackets.size() > MaxPacketCount)
	{
		Packets.erase(Packets.begin());
		InOutPackets.erase(InOutPackets.begin());
		PacketSelection.erase(PacketSelection.begin());
	}

	Packets.push_back(packetString);
	InOutPackets.push_back(packet);
	PacketSelection.push_back(false);
}

void __cdecl Analyzer::sendPacketHook(unsigned char* buffer, unsigned int bufferLength)
{
	Packet* packet = new Packet((char*)"SEND", buffer, bufferLength);

	cout << packet->Type << ">> 0x" << hex << setw(4) << setfill('0') << uppercase << packet->Opcode << " ";

	for (size_t i = 0; i < packet->Length - 2; i++)
	{
		cout << hex << setw(2) << setfill('0') << uppercase << (int)packet->Data[i] << " ";
	}

	cout << endl;

	if (LogSent)
		AddInOutPacket(packet);
	else
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
	Packet* packet = new Packet((char*)"RECV", buffer, lastBufferLength);

	cout << packet->Type << ">> 0x" << hex << setw(4) << setfill('0') << uppercase << packet->Opcode << " ";

	for (size_t i = 0; i < packet->Length - 2; i++)
	{
		cout << hex << setw(2) << setfill('0') << uppercase << (int)packet->Data[i] << " ";
	}

	cout << endl;

	if (LogReceived)
		AddInOutPacket(packet);
	else
		delete packet;

	// Buffer length is reset because it will be different on the next packet
	lastBufferLength = 0;

	// Call original function
	originalHandlePacket(opcode, buffer);
}

void __cdecl Analyzer::ClearPackets() {
	InOutPackets = vector<Packet*>();
	Packets = vector<string>();
	PacketSelection = vector<bool>();
}
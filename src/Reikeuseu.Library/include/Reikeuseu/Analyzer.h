#pragma once
#ifndef REIKEUSEU_ANALYZER_H
#define REIKEUSEU_ANALYZER_H

#include <vector> 
#include <string>
#include "Packets/Packet.h"

// Definition for the game's original send packet function
typedef void(__cdecl* _sendPacket)(unsigned char* buffer, unsigned int bufferLength);

// Definition for the game's original receive packet function
typedef void(__cdecl* _receivePacket)(unsigned char* buffer, int bufferLength);

// Definition for the game's original handle packet function
typedef void(__cdecl* _handlePacket)(unsigned short opcode, unsigned char* buffer);

class Analyzer
{
public:
	/// <summary>
	/// Hooks all the functions 
	/// </summary>
	static void __cdecl Initialize();
	static _sendPacket originalSendPacket;
	static _receivePacket originalReceivePacket;
	static _handlePacket originalHandlePacket;
	static std::vector<Packet*> InOutPackets;
	static void AddInOutPacket(Packet* packet);
	static std::vector<std::string> Packets;

private:
	/// <summary>
	/// Hooks the game's packet send function
	/// </summary>
	/// <param name="buff">The packet's buffer</param>
	/// <param name="length">Buffer length</param>
	static void __cdecl sendPacketHook(unsigned char* buffer, unsigned int bufferLength);

	/// <summary>
	/// Hooks the game's packet reception function
	/// </summary>
	/// <param name="encryptedBuffer">The packet's encrypted buffer</param>
	/// <param name="bufferLength">Buffer length</param>
	static void __cdecl receivePacketHook(unsigned char* encryptedBuffer, int bufferLength);

	/// <summary>
	/// Hooks the game's handle packet function
	/// </summary>
	/// <param name="opcode"></param>
	/// <param name="buffer"></param>
	/// <returns></returns>
	static void __cdecl handlePacketHook(unsigned short opcode, unsigned char* buffer);
};

#endif
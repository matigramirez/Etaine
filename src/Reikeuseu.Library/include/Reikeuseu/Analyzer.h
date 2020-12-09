#pragma once
#ifndef REIKEUSEU_ANALYZER_H
#define REIKEUSEU_ANALYZER_H
class Analyzer
{
public:
	/// <summary>
	/// Hooks all the functions 
	/// </summary>
	static void Initialize();

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
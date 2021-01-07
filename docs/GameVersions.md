# Game.exe versions
## Episode 1
### Version 1 (probably unique)
Originally from [here](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/3808202-tiny-release-shaiya-episode-1-game-client-light-darkness.html)

SendPacket = `0x00549C10`  
HandlePacket = `0x0054D560`

**Prototypes**
```cpp 
typedef void(__cdecl* _sendPacket)(unsigned char* buff, unsigned short length);

typedef void(__cdecl* _handlePacket)(unsigned short packetType, unsigned char* buff, unsigned short length);
```

## Episode 4
### Version 1
Originally from [here](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/4137180-shaiya-us-clients.html)

SendPacket = `0x00585640`  
ReceivePacket = `0x004010E0`  
HandlePacket = `0x00582E10`  

**Prototypes**
```cpp
typedef void(__cdecl* _sendPacket)(unsigned char* buffer, unsigned int bufferLength);

typedef void(__cdecl* _receivePacket)(unsigned char* buffer, int bufferLength);

typedef void(__cdecl* _handlePacket)(unsigned short opcode, unsigned char* buffer);
```

## Episode 6
### Version 1
This game.exe was provided by *Bowie*, it's supposed to be the normal ep6 game.exe everyone uses which by default has a size of ~32mb. Bowie removed all the bloat from it, resulting in a much smaller game.exe.  

SendPacket = `0x005EA9A0`  
ReceivePacket = `0x00401080`  
HandlePacket = `0x005F1E10`  


**Prototypes**
```cpp
typedef void(__cdecl* _sendPacket)(unsigned char* buffer, unsigned int bufferLength);

typedef void(__cdecl* _receivePacket)(unsigned char* buffer, int bufferLength);

typedef void(__cdecl* _handlePacket)(unsigned short opcode, unsigned char* buffer);
```

## Episode 8
### Version 1
Originally from [here](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/4137555-shaiya-us-unpack-ep8-game-updater-exe.html)

SendPacket = `0x00661020`  
ReceivePacket = `0x00401110`  
HandlePacket = `0x006687B0`  


**Prototypes**
```cpp
typedef void(__cdecl* _sendPacket)(unsigned char* buffer, unsigned int bufferLength);

typedef void(__cdecl* _receivePacket)(unsigned char* buffer, int bufferLength);

typedef void(__cdecl* _handlePacket)(unsigned short opcode, unsigned char* buffer);
```

## Shaiya EG - Episode 8
Bypassed EterniaGames Shaiya game.exe. EG's game.exe change regularly so these addresses are valid for the January 2021 version, but we cant guarantee that they will be the same with newest versions.

*NOTE: EG's game.exe is different to the rest because when reading the dissasembly, the addresses can be found but they will change at runtime. This doesn't happen with any other game.exe, only with this one, thus, the addresses must be found by dissasemblying the game while it's running.*

### January 2021 Version
SendPacket = `0x00676640`  
ReceivePacket = `0x00401100`  
HandlePacket = `0x0067DF90`  


**Prototypes**
```cpp
typedef void(__cdecl* _sendPacket)(unsigned char* buffer, unsigned int bufferLength);

typedef void(__cdecl* _receivePacket)(unsigned char* buffer, int bufferLength);

typedef void(__cdecl* _handlePacket)(unsigned short opcode, unsigned char* buffer);
```
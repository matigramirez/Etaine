# Game.exe versions
## Episode 1
### Version 1 (possibly unique) - [`game.ep1.v1.exe`](https://github.com/matigramirez/Etaine/blob/main/game%20versions/game.ep1.v1.exe)
Originally from [here](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/3808202-tiny-release-shaiya-episode-1-game-client-light-darkness.html)

SendPacket = `0x00549C10`  
HandlePacket = `0x0054D560`

**Prototypes**
```cpp 
typedef void(__cdecl* _sendPacket)(unsigned char* buff, unsigned short length);

typedef void(__cdecl* _handlePacket)(unsigned short packetType, unsigned char* buff, unsigned short length);
```

## Episode 4
### Version 1 - [`game.ep4.v1.exe`](https://github.com/matigramirez/Etaine/blob/main/game%20versions/game.ep4.v1.exe)
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
### Version 1 - [`game.ep6.v1.exe`](https://github.com/matigramirez/Etaine/blob/main/game%20versions/game.ep6.v1.exe)
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
### Version 1 - [`game.ep8.v1.exe`](https://github.com/matigramirez/Etaine/blob/main/game%20versions/game.ep8.v1.exe)
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
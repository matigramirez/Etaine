# How to find game addresses
Most game.exe's share something in common, they have a logging function which logs incoming and outgoing packets on a text file. This text file formats the packets by appending the strings `"SEND>>"` and `"RECV>>"` before the packet data. This helps us find the functions where they are called by searching where in the game.exe these strings are referenced.  

## Send packet address
Once the reference for the `"SEND>>"` string is found, the enclosing function *should* be the `SendPacket` function. This can be verified by decompiling the function and seeing that it matches this signature:
```cpp
void SendPacket(unsigned char* buffer, unsigned int bufferLength);
```
*NOTE: the decompiled code might not look as nice as this prototype but the size of the paramers must match*

## Receive packet address
The `ReceivePacket` function address can be found some lines above the call for the `LogReceivedPacket` function, which takes the `"RECV>>"` string reference as a parameter.  
The `ReceivePacket` function is notably "far away" from it's call, likely always around ~ `0x00400000`. This can be used to verify that the address is found correctly.
The prototype for this function is:
```cpp
void ReceivePacket(unsigned char* buffer, int bufferLength);
```
*NOTE: The packet buffer that gets passed in as a parameter here is encrypted, so there's no way to read the packet data unless it's decrypted first. The decompiled code might not look as nice as this prototype but the size of the paramers must match.* 

## Handle packet address
The call for the `HandlePacket` function can be found right below the call for the `LogReceivedPacket` function, this should make it farily easy to find it.
The prototype for this function is:
```cpp
void HandlePacket(unsigned short opcode, unsigned char* buffer);
```
*NOTE: The packet buffer that gets passed in as a parasmeter here is already decrypted, so it can be read. The decompiled code might not look as nice as this prototype but the size of the paramers must match*
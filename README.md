# Etaine

Etaine is a Shaiya packet analyzer tool which provides a simple way to display incoming and outgoing game.exe packets and send fake packets to the game server.

# Prerequisites
* DirectX Software Development Kit June 2010. Can be downloaded [here](https://www.microsoft.com/en-us/download/details.aspx?id=6812). Install it to the default folder, which is `C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)`.

# Build
Build for x86 version.

# Run
## Via Cheat Engine (CE)
CE can be downloaded [here](https://cheatengine.org/downloads.php).

Run CE => Open process. Find game.exe => Memory view => Tools => Inject DLL (Ctrl + i) => Etaine.dll

Press F5 to show packet window.

## Via DLL injection on game start up
TBD

# Hotkeys
`F1` - Toggle tool display  
`F2` - Toggle packet activation (Start/Stop reading packets)  
`F3` - Cycle through packet data display type (Hex -> Decimal -> ASCII)  
`F11` - Clear the packet list

# Docs
To learn more about how this tool works and how it can be used with unsupported game.exe's, please refer to the documentation.
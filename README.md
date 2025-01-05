# Etaine

Etaine is a quick n' dirty Shaiya packet analyzer tool which provides a simple way to display incoming and outgoing game.exe packets and send fake packets to the game server.

# Prerequisites
* Visual Studio 2022
* vcpkg

# Build
Build for x86 platform

# Run
## Via Cheat Engine (CE)
CE can be downloaded [here](https://cheatengine.org/downloads.php).

Run CE => Open process. Find game.exe => Memory view => Tools => Inject DLL (Ctrl + i) => Etaine.dll

Press F5 to show packet window.

# Hotkeys
`F1` - Toggle tool display  
`F2` - Toggle packet activation (Start/Stop reading packets)  
`F3` - Cycle through packet data display type (Hex -> Decimal -> ASCII)  
`F11` - Clear the packet list

# Docs
To learn more about how this tool works and how it can be used with unsupported game.exe's, please refer to the documentation.
#include "Packets/Opcode.h"

Opcode::Opcode(unsigned short value, char* label) {
	this->Value = value;
	this->Label = label;
}
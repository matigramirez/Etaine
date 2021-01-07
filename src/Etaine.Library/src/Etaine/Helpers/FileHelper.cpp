#include <Etaine/Helpers/FileHelper.h>
#include <Etaine/Packets/Opcode.h>
#include <Etaine/Analyzer.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

void FileHelper::Initialize() {
	ParseIgnoredOpcodes();
	ParseOpcodeLabels();
}

void FileHelper::ParseIgnoredOpcodes() {
	string line;
	ifstream fin("ignored_opcodes.txt");

	// This doesn't work
	copy(istream_iterator<unsigned short>(fin),
		istream_iterator<unsigned short>(),
		back_inserter(Analyzer::IgnoredOpcodes));


	//// Read all file lines
	//while (getline(fin, line)) {

	//	stringstream ss(line);
	//	
	//	cout << "ignored opcode: " << line << endl;

	//	// Read value from string stream
	//	cout << "ignored opcode value: " << i << endl;
	//	Analyzer::IgnoredOpcodes.push_back(line);
	//}
}

void FileHelper::ParseOpcodeLabels() {

}

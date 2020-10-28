// *******************
// Author: Ana Zobec
// Date:   02/09/2019
// *******************
// Turing.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// Put your code into "turingCode.txt" file located in the Turing folder. The code should be written as shown below.
// turing code: 1323r --> state2, read, write, state2, direction
// input: 1345 --> start at index 4!! 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <conio.h>

class Turing {
	int state1, state2;
	char read, overwrite, direction;
	public:
		Turing(int state1, char read, char overwrite, int state2, char direction) {
			this->state1 = state1;
			this->read = read;
			this->overwrite = overwrite;
			this->state2 = state2;
			this->direction = direction;
		}

		int getState1() { return state1; }
		int getState2() { return state2; }
		char getRead() { return read; }
		char getOverwrite() { return overwrite; }
		char getDirection() { return direction; }
		std::string strValue() { return (std::to_string(state1) + read + overwrite + std::to_string(state2) + direction); }
};

// read the turing code from a vector and write it into a text file
Turing findState(int nowState, char inRead, std::vector<Turing> tVect);
std::string executeTuring(std::string input, std::string fileName);
void showWindow();


// -------------------------------------------
int main() {
	std::string in = "";
	std::cout << "Your input? ";
	std::cin >> in;
	std::cout << "\n\n..:::::Results:::::..\n\n";

	std::string out = executeTuring(in, "turingCode.txt");
	
	std::cout << "Input:  ...bbbb" << in << "bbbb...\n----------" << std::endl;
	std::cout << "Output: ..." << out << "..." << std::endl;

	return 0;
}
// -------------------------------------------
std::string executeTuring(std::string input, std::string fileName) {
	std::ifstream tRead(fileName);
	std::string line;
	int nowState = 1;
	std::string output = "bbbb" + input + "bbbb";

	std::vector<Turing> tVect;

	if (tRead.is_open()) {		// check if the file is now opened
		while (std::getline(tRead, line)) {		// Read from text file and write the data to vector
			int state1 = line[0] - '0';
			int state2 = line[3] - '0';
			Turing tLine(state1, line[1], line[2], state2, line[4]);
			tVect.push_back(tLine);
		}
		tRead.close();

		// Start executing the Turing code
		int i = 4;		// the starting index of the Output string
		while (i < output.size()) {		// go through the Output string
			char inRead = output.at(i);		// inRead -> character of the Output string at index 'i'
			Turing neededCode = findState(nowState, inRead, tVect);		// find the needed part of the Turing code with the specified state
			output.at(i) = neededCode.getOverwrite();		// overwrite the read input character with the new one as specified in the Turings code

			nowState = neededCode.getState2();		// updates the nowState value => the state that we're in right now

			if (neededCode.getDirection() == 'r')		// check for direction; r -> right (i = i + 1), l -> left (i = i - 1)
				i++;
			else i--;
		}
	}

	else return ("Error while opening a file");		// if the file hasn't opened, return an error message
	return output;
}

Turing findState(int nowState, char inRead, std::vector<Turing> tVect) {
	for (int i = 0; i < tVect.size(); i++) {
		if (tVect.at(i).getState1() == nowState)
			if (inRead == tVect.at(i).getRead())
				return tVect.at(i);
	}
	return Turing(0, 'b', 'b', 0, 'r');
}

void showWindow() {
	std::cout << "F1) New Turing Code \t F2) Run Program \t \t F3) Save \t F4) Save As \t F5) Exit" << std::endl;
	std::cout << "-------------------------" << std::endl;
}

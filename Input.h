#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

typedef enum _input {
	Cin,
	File,
	String
} input_type;

class Input {
	public:
	Input(string fname);
	~Input();
	static string readLine(char delim='\n');
	static string readAll();
	static ifstream file;
	static input_type type;
};

#endif

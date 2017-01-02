#include "Input.h"

Input::Input(string fname) {
	file.open(fname.c_str());
	type = File;
}

Input::~Input() {
    if ( file) {
        file.close();
    }
}

string Input::readLine(char delim) {
	string data;
	switch (type) {
		case Cin:
		getline(cin, data, delim);
		break;
		case File:
		break;
		case String:
		break;
		default:
		break;
	}
	return data;
}

string Input::readAll( ) {
    stringstream sfile;
    sfile << file;
    return sfile.str();
}

ifstream Input::file;

input_type Input::type = Cin;

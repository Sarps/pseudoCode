#include "Library.h"

Library::Library(){
    //ctor
}

Library::~Library(){
    //dtor
}

void Library::loadCSV( string fname){
    string temp, tcol;
    stringstream tsline;
    vector<string> vtemp;
    ifstream file(fname.c_str());
    if ( !file) {
        return;
    }
    // Load individual lines from file till EOF
    while ( !file.eof()){
        getline(file,temp);
        tsline.str(temp);
        int i = 0;
        // Load individual words from line till EOF
        while ( !tsline.eof()) {
            getline(tsline, temp, ',');
            results[i].push_back(temp);
            i++;
        }
    }
}

void Library::loadVerbs(){
    results.clear();
    results.reserve(3);
    loadCSV("verbs.csv");
}

void Library::loadAll(){
    results.clear();
    results.reserve(0);
    loadCSV("all.csv");
}

void Library::loadNouns(){
    results.clear();
    results.reserve(2);
    loadCSV("nouns.csv");
}

vector < string > Library::operator[](int index){
    vector < string > output;
    for ( auto result : results) {
        output.push_back(result[index]);
    }
    return output;
}

vector < string > Library::operator()(int grp){
    return results[grp];
}

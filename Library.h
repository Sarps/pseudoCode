#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

typedef enum lib_typ {
	PVERB=0,
	CVERB,
	SNOUN,
	PNOUN,
	START,
	END
} lib_type;

class Library
{
    public:
        Library();
        virtual ~Library();
        void loadVerbs();
        void loadAll();
        void loadNouns();
        char Contains(string value);
        vector < string > operator[](int index);
        vector < string > operator()(int grp);

    protected:
        static vector<string> terms[];

    private:
        void loadCSV( string fname);
        vector< vector < string > > results;

};

#endif // LIBRARY_H

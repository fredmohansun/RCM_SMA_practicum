#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

#include "backtest_class.h"

using namespace std;

int main(int argc, char const *argv[]){
    ifstream input_file(argv[1], std::ifstream::in);
    string line;
    getline(input_file, line); //metadata
    while(!input_file.eof()){
	getline(input_file, line);
	PSentimentEventMsg SMAentry = PSentimentEventMsg(line);
	cout.precision(10);
	cout<<line<<'\n';
	cout<<SMAentry.raw_s()<<','<<SMAentry.s()<<'\n';
    }
    return 0;
}

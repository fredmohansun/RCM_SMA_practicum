#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

using namespace std;

double str2num(string str){
    stringstream mystream(str);
    double num;
    mystream>>num;
    return num;
}

void data_helper(string line){
    stringstream mystring(line);
    std::vector< std::string > results((std::istream_iterator<std::string>(mystring)), std::istream_iterator<std::string>());
    /*
    for (std::vector<std::string>::iterator it = results.begin();it!=results.end();it++){
    	std::cout<<*it<<'\n';
    }
    */
    std::cout<<*(results.begin()+1)<<','<<*(results.begin()+2)<<'\n';
}

int main(int argc, char const *argv[]){
    ifstream input_file(argv[1], std::ifstream::in);
    string a, temp;
    getline(input_file, a);
    while(!input_file.eof()){
	getline(input_file, a);
    }
    return 0;
}

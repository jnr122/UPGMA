#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Tree.h"

using namespace std;

int main() {
    string name, str;
    vector<Sequence> seqs;

    // read file, create sequence vector
    ifstream f_in;
    f_in.open("3.in");
    while(f_in && f_in.peek() != EOF){
        getline(f_in, name);
        getline(f_in, str);
        name = name.substr(1);
        seqs.push_back(Sequence(name, str));
    }
    f_in.close();

    // print sequence vector
    for (int i = 0; i < seqs.size(); i++) {
        cout << seqs[i] << endl;
    }

    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Tree.h"
#include "Cluster.h"

using namespace std;

int main() {
    string name, str;
    vector<Cluster> seqs;
    vector<Sequence> seq;


    // read file, create sequence vector
    ifstream f_in;
    f_in.open("3.in");

    if (!f_in) {
        cout << "file not found " << endl;
    }
    while(f_in && f_in.peek() != EOF) {
        seq ={};
        getline(f_in, name);
        getline(f_in, str);
        name = name.substr(1);
        seq.push_back(Sequence(name, str));
        seqs.push_back(Cluster(seq));
    }
    f_in.close();

    // print sequence vector
    for (int i = 0; i < seqs.size(); i++) {
        cout << seqs[i].getSeqs()[0] << endl;
    }
    Tree t = Tree(seqs);

    return 0;
}
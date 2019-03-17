#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Sequence {
    Sequence(string name, string str);

    string name, str;

};

// Square constructor
Sequence::Sequence(string name, string str): name(name), str(str) {

}

int main() {
    string name, str;
    vector<Sequence> seqs;

    // File reading
    ifstream f_in;
    f_in.open("3.in");
    while(f_in && f_in.peek() != EOF){
        getline(f_in, name);
        getline(f_in, str);
        seqs.push_back(Sequence(name, str));
    }
    f_in.close();

    std::cout << "Hello, World!" << std::endl;

    for (int i = 0; i < seqs.size(); i++) {
        cout << seqs[i].name << endl;
        cout << seqs[i].str << endl;

    }

    return 0;
}
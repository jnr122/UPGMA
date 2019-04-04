//
// Created by Jonah Rubin on 2019-04-02.
//
#include <ostream>
#include <fstream>

#include "Cluster.h"

// Sequence constructor
Sequence::Sequence(string name, string str): name(name), str(str) {

}

// Overloaded sequence output
ostream &operator<<(ostream &os, const Sequence &sequence) {
    os << "name: " << sequence.name << " str: " << sequence.str;
    return os;
}

// Overloaded sequence equality
bool Sequence::operator==(const Sequence &seq) const {
    return name == seq.name;
}

// Cluster constructor
Cluster::Cluster(const vector<Sequence> &seqs) : seqs(seqs) {
    string name = "";
    string printString = "";
    for (int i = 0; i < seqs.size(); i++) {
        name += seqs[i].name;
    }
    this->name = name;
}

// Merge two clusters
void Cluster::merge(Cluster c, double min) {
    for (int i = 0; i < c.seqs.size(); i++) {
        this->seqs.push_back(c.seqs[i]);
    }

    // set up merge of clusters
    dist = min/2;
    oldNames = {};
    oldNames.push_back(name);
    oldNames.push_back(c.name);
    name = strip(name);
    c.name = strip(c.name);
    name += "/" + c.name;

    string printName = "";
    for (int i = 0; i < name.size(); i++) {

        if (i == 0) {
            printName += name[i];
        } else if (name[i] != 'S' and name[i] != '/') {
            printName += name[i];
        }
    }

    printString += (printName + ":" + to_string(dist) + "\n");

    ofstream out2("3.02");
    if (out2.is_open()) {
        out2 << printString;

        out2.close();
    }
}

// remove sentinel value from cluster name
string Cluster::strip(string s) {
    string newS = "";
    for (int i = 0; i < s.size(); i++ ) {
        if (s[i] != '/') {
            newS += s[i];
        }
    }
    return newS;
}

// Split cluster into two sub clusters
vector<string> Cluster::split() {
    vector<string> names;
    int sentInd = name.find('/');

    names.push_back(name.substr(0, sentInd));
    names.push_back(name.substr(sentInd + 1));

    return names;
}

// Overloaded Cluster ==
bool Cluster::operator==(const Cluster &c) const {
    return name == c.name;
}

// Getters
const string &Cluster::getName() const {
    return name;
}
const vector<Sequence> &Cluster::getSeqs() const {
    return seqs;
}
const vector<string> &Cluster::getOldNames() const {
    return oldNames;
}
double Cluster::getDist() const {
    return dist;
}
const string &Cluster::getPrintString() const {
    return printString;
}

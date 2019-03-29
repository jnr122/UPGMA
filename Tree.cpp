//
// Created by Jonah Rubin on 2019-03-19.
//
#include <ostream>
#include <iostream>
#include <fstream>

#include "Tree.h"

using namespace std;

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

// Tree constructor
Tree::Tree(vector<Cluster> &clusters) : newClusters(clusters){
    populate();
    calculateInitial();

}

// Populate default matrix
void Tree::populate() {
    for (int i = 0; i < newClusters.size(); i++) {
        vector<double> vec;
        for (int j = 0; j < newClusters.size(); j++) {
            vec.push_back(0);
        }
        newDistanceMatrix.push_back(vec);
    }
}

// Calculations for distance matrix
void Tree::calculateInitial() {
    double distance;
    for (int i = 0; i < newClusters.size() - 1; i++) {
        for (int j = i + 1; j < newClusters.size(); j++) {

            if (i == j) {
                newDistanceMatrix[i][j] = 0;
            } else {
                distance = compare(newClusters[i], newClusters[j]);
                newDistanceMatrix[i][j] = distance;
                newDistanceMatrix[j][i] = distance;
            }
        }
    }

    // file output
    ofstream out1("3.01");
    if (out1.is_open()) {
        out1 << "- ";
        for (int i = 0; i < newClusters.size(); i++) {
            out1 << newClusters[i].name << " ";
        }
        out1 << "\n";
        for (int i = 0; i < newDistanceMatrix.size(); i++) {
            for (int j = 0; j < newDistanceMatrix[0].size(); j++) {
                if (j == 0) {
                    out1 << newClusters[i].name << " ";
                }
                out1 << newDistanceMatrix[i][j] << " ";
            }
            out1 << "\n";
        }
        out1.close();
    }


    recalculate();
}

// repeated distance matrix calculations
void Tree::recalculate() {
    while (newClusters.size() > 1) {

        oldDistanceMatrix = newDistanceMatrix;
        group();
        newDistanceMatrix = {};
        populate();

        double distance;
        for (int i = 0; i < newClusters.size() - 1; i++) {
            for (int j = i + 1; j < newClusters.size(); j++) {

                if (i == j) {
                    newDistanceMatrix[i][j] = 0;
                } else {
                    distance = compare(newClusters[i], newClusters[j]);
                    newDistanceMatrix[i][j] = distance;
                    newDistanceMatrix[j][i] = distance;
                }
            }
        }
    }

    ofstream out3("3.03");
    if (out3.is_open()) {
        if (multiple) {
            out3 << "YES";
        } else {
            out3 << "NO";
        }

        out3.close();
    }


}

// Comparison of Sequences
const double Tree::compare(Cluster c1, Cluster c2) {
    int distance = 0;
    int c1Ind, c1Inda, c1Indb, c2Ind, c2Inda, c2Indb;
    vector<string> names;

    // bit redundant
    if (c1.seqs.size() == 1 and c2.seqs.size() == 1) {
        for (int i = 0; i < c1.seqs[0].str.size(); i++) {
            if (c1.seqs[0].str.at(i) != c2.seqs[0].str.at(i)) {
                ++distance;
            }
        }
    } else {
        c1Ind = contains(c1.name);
        c2Ind = contains(c2.name);

        // both contained in old clusters/matrix
        if (c1Ind != -1 and c2Ind != -1) {
            return oldDistanceMatrix[c1Ind][c2Ind];
        }

        // 1 not 2 contained in old clusters/matrix
        else if (c1Ind != -1) {
            c2Inda = contains(c2.oldNames[0]);
            c2Indb = contains(c2.oldNames[0]);
            return (oldDistanceMatrix[c1Ind][c2Inda] + oldDistanceMatrix[c1Ind][c2Indb])/2;
        }

        // 2 not 1 contained in old clusters/matrix
        else if (c2Ind != -1) {
            c1Inda = contains(c1.oldNames[0]);
            c1Indb = contains(c1.oldNames[1]);
            return (oldDistanceMatrix[c1Inda][c2Ind] + oldDistanceMatrix[c1Indb][c2Ind])/2;
        }  else {
            cout << "no" << endl;
        }
    }
    return distance;
}

// Check to see if cluster has already been used in the old matrix
int Tree::contains(string name) {
    for (int i = 0; i < oldClusters.size(); i++) {
        if (oldClusters[i].name == name) {
            return i;
        }
    }
    return -1;
}

void Tree::group() {
    double min = newClusters[0].seqs[0].str.size();
    int row;
    int col;
    double score;
    for (int i = 0; i < newDistanceMatrix.size() - 1; i++) {
        for (int j = i + 1; j < newDistanceMatrix[0].size(); j++) {
            score = newDistanceMatrix[i][j];
            if (score == min) {
                multiple = true;
            }
            if (i != j and score < min) {
                min = newDistanceMatrix[i][j];
                row = i;
                col = j;
            }
        }
    }
    oldClusters = newClusters;
    newClusters[row].merge(newClusters[col], min);
    newClusters.erase(newClusters.begin()+col);
}

// Overloaded <<
ostream &operator<<(ostream &os, const Tree &tree) {
    os << "distance_matrix: " << endl;

    os << "    ";
    for (int i = 0; i < tree.newClusters.size(); i++) {
        os << tree.newClusters[i].name << " ";

    }
    os << endl;

    for (int i = 0; i < tree.newDistanceMatrix.size(); i++) {
        for (int j = 0; j < tree.newDistanceMatrix[i].size(); j++) {
            if (j == 0) {
                // throws BAD_EXEC exception
                os << tree.newClusters[i].name << " ";
            }
            os  << tree.newDistanceMatrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

// Getters
const vector<Cluster> &Tree::getSeqs() const {
    return newClusters;
}

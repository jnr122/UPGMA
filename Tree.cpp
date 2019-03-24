//
// Created by Jonah Rubin on 2019-03-19.
//
#include <ostream>

#include "Tree.h"

// Sequence constructor
Sequence::Sequence(string name, string str): name(name), str(str) {

}

// Overloaded sequence output
ostream &operator<<(ostream &os, const Sequence &sequence) {
    os << "name: " << sequence.name << " str: " << sequence.str;
    return os;
}

// Tree constructor
Tree::Tree(vector<vector<Sequence>> &seqs) : seqs(seqs){
    populate();
}

// Populate default matrix
void Tree::populate() {
    for (int i = 0; i < seqs.size(); i++) {
        vector<int> vec;
        for (int j = 0; j < seqs.size(); j++) {
            vec.push_back(0);
        }
        distanceMatrix.push_back(vec);
    }
    calculateInitial();
}

// Calculations for distance matrix
void Tree::calculateInitial() {
    int distance;
    for (int i = 0; i < seqs.size() - 1; i++) {
        for (int j = i + 1; j < seqs.size(); j++) {

            if (i == j) {
                distanceMatrix[i][j] = 0;
            } else {
                distance = compare(seqs[i][0], seqs[j][0]);
                distanceMatrix[i][j] = distance;
                distanceMatrix[j][i] = distance;
            }
        }
    }

}

// Comparison of Sequences
const int Tree::compare(Sequence s1, Sequence s2) {
    int distance = 0;
    for (int i = 0; i < s1.str.size(); i++) {
        if (s1.str.at(i) != s2.str.at(i)) {
            ++distance;
        }
    }
    return distance;
}


// Overloaded <<
ostream &operator<<(ostream &os, const Tree &tree) {
    os << "distance_matrix: " << endl;

    os << "    ";
    for (int i = 0; i < tree.seqs.size(); i++) {
        os << tree.seqs[i][0].name << " ";

    }
    os << endl;

    for (int i = 0; i < tree.distanceMatrix.size(); i++) {
        for (int j = 0; j < tree.distanceMatrix[i].size(); j++) {
            if (j == 0) {
                os << tree.seqs[i][0].name << " ";
            }
            os  << tree.distanceMatrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

// Getters
const vector<vector<Sequence>> &Tree::getSeqs() const {
    return seqs;
}

const vector<vector<int>> &Tree::getDistanceMatrix() const {
    return distanceMatrix;
}

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
Tree::Tree(vector<Sequence> &seqs) : seqs(seqs){
    populate();
}

// Populate default matrix
void Tree::populate() {
    for (int i = 0; i < seqs.size(); i++) {
        vector<int> vec;
        for (int j = 0; j < seqs.size(); j++) {
            vec.push_back(0);
        }
        distance_matrix.push_back(vec);
    }
    calculate();
}

// Calculations for distance matrix
void Tree::calculate() {
    int distance;
    for (int i = 0; i < seqs.size() - 1; i++) {
        for (int j = i + 1; j < seqs.size(); j++) {
            distance = compare(seqs[i], seqs[j]);
            distance_matrix[i][j] = distance;
            distance_matrix[j][i] = distance;

        }
    }

}

const int Tree::compare(Sequence s1, Sequence s2) {
    int distance = 0;
    for (int i = 0; i < s1.str.size(); i++) {
        if (s1.str.at(i) != s2.str.at(i)) {
            ++distance;
        }
    }
    return distance;
}



ostream &operator<<(ostream &os, const Tree &tree) {
    os << "distance_matrix: " << endl;

    os << "    ";
    for (int i = 0; i < tree.seqs.size(); i++) {
        os << tree.seqs[i].name << " ";

    }
    os << endl;

    for (int i = 0; i < tree.distance_matrix.size(); i++) {
        for (int j = 0; j < tree.distance_matrix[i].size(); j++) {
            if (j == 0) {
                os << tree.seqs[i].name << " ";
            }
            os  << tree.distance_matrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

// Getters
const vector<Sequence> &Tree::getSeqs() const {
    return seqs;
}

// Setters
const vector<vector<int>> &Tree::getDistance_matrix() const {
    return distance_matrix;
}

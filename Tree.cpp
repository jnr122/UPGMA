//
// Created by Jonah Rubin on 2019-03-19.
//
#include <ostream>
#include <iostream>

using namespace std;

#include "Tree.h"

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
    for (int i = 0; i < seqs.size(); i++) {
        name += seqs[i].name;
    }
    this->name = name;
}

// Merge two clusters
void Cluster::merge(Cluster c) {
    for (int i = 0; i < c.seqs.size(); i++) {
        this->seqs.push_back(c.seqs[i]);
    }
    name += c.name;
}

// Overloaded Cluster ==
bool Cluster::operator==(const Cluster &c) const {
    return name == c.name;
}

// Tree constructor
Tree::Tree(vector<Cluster> &clusters) : newClusters(clusters){
    populate();
}

// Populate default matrix
void Tree::populate() {
    for (int i = 0; i < newClusters.size(); i++) {
        vector<int> vec;
        for (int j = 0; j < newClusters.size(); j++) {
            vec.push_back(0);
        }
        newDistanceMatrix.push_back(vec);
    }
    calculateInitial();
}

// Calculations for distance matrix
void Tree::calculateInitial() {
    int distance;
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

    group();

}

// Comparison of Sequences
const int Tree::compare(Cluster c1, Cluster c2) {
    int distance = 0;
    int c1Ind, c2Ind;

    if (c1.seqs.size() == 1 and c2.seqs.size() == 1) {
        for (int i = 0; i < c1.seqs[0].str.size(); i++) {
            if (c1.seqs[0].str.at(i) != c2.seqs[0].str.at(i)) {
                ++distance;
            }
        }
    } else {
        c1Ind = contains(c1);
        c2Ind = contains(c2);

        // both contained in old clusters/matrix
        if (c1Ind != -1 and c2Ind != -1) {
            return oldDistanceMatrix[c1Ind][c2Ind];
        }

        // 1 not 2 contained in old clusters/matrix
        if (c1Ind != -1 and c2Ind == -1) {

        }

        // 2 not 1 contained in old clusters/matrix
        if (c2Ind != -1 and c1Ind == -1) {

        }

        // neither contained in old clusters/matrix (is this possible?)

    }
    return distance;
}

// Check to see if cluster has already been used in the old matrix
int Tree::contains(Cluster c) {
    for (int i = 0; i < oldClusters.size(); i++) {
        if (oldClusters[i] == c) {
            return i;
        }
    }
    return -1;
}

void Tree::group() {
    int min = newClusters[0].seqs[0].str.size();
    int row, col, score;
    for (int i = 0; i < newDistanceMatrix.size() - 1; i++) {
        for (int j = i + 1; j < newDistanceMatrix[0].size(); j++) {
            score = newDistanceMatrix[i][j];
            if (i != j and score < min) {
                min = newDistanceMatrix[i][j];
                row = i;
                col = j;
            }
        }
    }
    oldClusters = newClusters;

    newClusters[row].merge(newClusters[col]);
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

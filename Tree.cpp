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
Tree::Tree(vector<vector<Sequence>> &clusters) : clusters(clusters){
    populate();
}

// Populate default matrix
void Tree::populate() {
    for (int i = 0; i < clusters.size(); i++) {
        vector<int> vec;
        for (int j = 0; j < clusters.size(); j++) {
            vec.push_back(0);
        }
        oldDistanceMatrix.push_back(vec);
    }
    calculateInitial();
}

// Calculations for distance matrix
void Tree::calculateInitial() {
    int distance;
    for (int i = 0; i < clusters.size() - 1; i++) {
        for (int j = i + 1; j < clusters.size(); j++) {

            if (i == j) {
                oldDistanceMatrix[i][j] = 0;
            } else {
                distance = compare(clusters[i], clusters[j]);
                oldDistanceMatrix[i][j] = distance;
                oldDistanceMatrix[j][i] = distance;
            }
        }
    }

    group();

}

// Comparison of Sequences
const int Tree::compare(vector<Sequence> v1, vector<Sequence> v2) {
    int distance = 0;

    if (v1.size() == 1 and v2.size() == 1) {
        for (int i = 0; i < v1[0].str.size(); i++) {
            if (v1[0].str.at(i) != v2[0].str.at(i)) {
                ++distance;
            }
        }
    } else {
        for (int i = 0; i < v1.size(); i++) {

        }
    }
    return distance;
}

void Tree::group() {
    int min = clusters[0][0].str.size();
    int row, col, score;
    for (int i = 0; i < oldDistanceMatrix.size(); i++) {
        for (int j = 0; j < oldDistanceMatrix[0].size(); j++) {
            score = oldDistanceMatrix[i][j];
            if (i != j and score < min) {
                min = oldDistanceMatrix[i][j];
                row = i;
                col = j;
            }
        }
    }
    for (int i = 0; i < clusters[col].size(); i++) {
        clusters[row].push_back(clusters[col][i]);
    }
    clusters.erase(clusters.begin()+col);

}

// Overloaded ==
bool Sequence::operator==(const Sequence &rhs) const {
    return name == rhs.name && str == rhs.str;
}

// Overloaded <<
ostream &operator<<(ostream &os, const Tree &tree) {
    os << "distance_matrix: " << endl;

    os << "    ";
    for (int i = 0; i < tree.clusters.size(); i++) {
        os << tree.clusters[i][0].name << " ";

    }
    os << endl;

    for (int i = 0; i < tree.oldDistanceMatrix.size(); i++) {
        for (int j = 0; j < tree.oldDistanceMatrix[i].size(); j++) {
            if (j == 0) {
                os << tree.clusters[i][0].name << " ";
            }
            os  << tree.oldDistanceMatrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

// Getters
const vector<vector<Sequence>> &Tree::getSeqs() const {
    return clusters;
}


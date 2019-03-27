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

// Cluster constructor
Cluster::Cluster(const vector<Sequence> &seqs) : seqs(seqs) {
    string name = "";
    for (int i = 0; i < seqs.size(); i++) {
        name += seqs[i].name;
    }
    this->name = name;
}


// Tree constructor
Tree::Tree(vector<Cluster> &clusters) : clusters(clusters){
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
const int Tree::compare(Cluster c1, Cluster c2) {
    int distance = 0;

    if (c1.seqs.size() == 1 and c2.seqs.size() == 1) {
        for (int i = 0; i < c1.seqs[0].str.size(); i++) {
            if (c1.seqs[0].str.at(i) != c2.seqs[0].str.at(i)) {
                ++distance;
            }
        }
    } else {
        for (int i = 0; i < c1.seqs.size(); i++) {

        }
    }
    return distance;
}

void Tree::group() {
    int min = clusters[0].seqs[0].str.size();
    int row, col, score;
    for (int i = 0; i < oldDistanceMatrix.size() - 1; i++) {
        for (int j = i + 1; j < oldDistanceMatrix[0].size(); j++) {
            score = oldDistanceMatrix[i][j];
            if (i != j and score < min) {
                min = oldDistanceMatrix[i][j];
                row = i;
                col = j;
            }
        }
    }

    // Cluster merge method

//    for (int i = 0; i < clusters[col].seqs.size(); i++) {
//        clusters[row].seqs.push_back(clusters[col][i]);
//    }
//    clusters.erase(clusters.begin()+col);

}

// Overloaded ==
bool Sequence::operator==(const Sequence &seq) const {
    return name == seq.name;
}

// Overloaded <<
ostream &operator<<(ostream &os, const Tree &tree) {
    os << "distance_matrix: " << endl;

    os << "    ";
    for (int i = 0; i < tree.clusters.size(); i++) {
        os << tree.clusters[i].seqs[0].name << " ";

    }
    os << endl;

    for (int i = 0; i < tree.oldDistanceMatrix.size(); i++) {
        for (int j = 0; j < tree.oldDistanceMatrix[i].size(); j++) {
            if (j == 0) {
                // throws BAD_EXEC exception
                os << tree.clusters[i].seqs[0].name << " ";
            }
            os  << tree.oldDistanceMatrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

// Getters
const vector<Cluster> &Tree::getSeqs() const {
    return clusters;
}

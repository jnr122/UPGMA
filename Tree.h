//
// Created by Jonah Rubin on 2019-03-19.
//
#include <string>
#include <vector>
#include <ostream>

#ifndef UPGMA_TREE_H
#define UPGMA_TREE_H

using namespace std;

struct Sequence {
    string name, str;

    /**
     * Sequence constructor
     * @param name
     * @param str
     */
    Sequence(string name, string str);
    friend ostream &operator<<(ostream &os, const Sequence &sequence);

};

class Tree {
public:

    /**
     * Tree constructor
     * @param seqs a vector of Sequence objects
     */
    Tree(vector<vector<Sequence>> &seqs);

    /**
     * Overloaded << opreator for tree
     * @param os
     * @param tree
     * @return
     */
    friend ostream &operator<<(ostream &os, const Tree &tree);

    /**
     * Getters
     */
    const vector<vector<Sequence>> &getSeqs() const;
    const vector<vector<int>> &getDistanceMatrix() const;

private:
    vector<vector<Sequence>> seqs;
    vector<vector<int>> distanceMatrix;

    /**
     * Populate a default matrix
     */
    void populate();

    /**
     * Calculate values for matrix
     */
    void calculateInitial();

    /**
     * Compare two sequence objects
     * @param s1
     * @param s2
     * @return distance score
     */
    const int compare(Sequence s1, Sequence s2);

};



#endif //UPGMA_TREE_H

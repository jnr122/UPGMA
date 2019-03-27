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

    bool operator==(const Sequence &rhs) const;
    bool operator!=(const Sequence &rhs) const;

};

struct Cluster {
    string name;
    vector<Sequence> seqs;

    Cluster(const vector<Sequence> &seqs);

};

class Tree {
public:

    /**
     * Tree constructor
     * @param clusters a vector of Sequence objects of the same length
     */
    Tree(vector<Cluster> &clusters);

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
    const vector<Cluster> &getSeqs() const;

private:
    vector<Cluster> clusters;
    vector<vector<int>> oldDistanceMatrix;

    /**
     * Populate a default matrix
     */
    void populate();

    /**
     * Calculate initial values for matrix
     */
    void calculateInitial();

    /**
     * Compare two sequence objects
     * @param s1
     * @param s2
     * @return distance score
     */
    const int compare(Cluster c1, Cluster c2);

    /**
     * Group two closest sequence clusters by distance
     */
    void group();

};



#endif //UPGMA_TREE_H

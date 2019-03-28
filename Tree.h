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

};

struct Cluster {
    string name;
    vector<Sequence> seqs;
    vector<string> oldNames;

    Cluster(const vector<Sequence> &seqs);

    /**
     * Merge two clusters by concatenating names and sequence vectors
     * @param c other cluster
     */
    void merge(Cluster c);

    /**
     * String to strip of sentinel value
     * @param s
     * @return stripped string
     */
    string strip(string s);

    /**
     * @return cluster name split at sentinel value
     */
    vector<string> split();

    bool operator==(const Cluster &rhs) const;

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
    vector<Cluster> oldClusters;
    vector<Cluster> newClusters;
    vector<vector<double>> oldDistanceMatrix;
    vector<vector<double>> newDistanceMatrix;


    /**
     * Populate a default matrix
     */
    void populate();

    /**
     * Calculate initial values for matrix
     */
    void calculateInitial();

    /**
     * All subsequence calculations
     */
    void recalculate();

    /**
     * Compare two sequence objects
     * @param s1
     * @param s2
     * @return distance score
     */
    const double compare(Cluster c1, Cluster c2);

    /**
     * Group two closest sequence clusters by distance
     */
    void group();

    /**
     * Check if a cluster is contained in the old distance matrix
     * @param c the cluster
     */
    int contains(string name);

};



#endif //UPGMA_TREE_H

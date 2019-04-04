//
// Created by Jonah Rubin on 2019-04-02.
//
#include <vector>
#include <string>

#ifndef UPGMA_CLUSTER_H
#define UPGMA_CLUSTER_H


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

class Cluster {
public:

    Cluster(const vector<Sequence> &seqs);

    /**
    * Merge two clusters by concatenating names and sequence vectors
    * @param c other cluster
    */
    void merge(Cluster c, double min);

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
    const string &getName() const;
    const vector<Sequence> &getSeqs() const;
    const vector<string> &getOldNames() const;
    double getDist() const;
    const string &getPrintString() const;


private:

    string name;
    vector<Sequence> seqs;
    vector<string> oldNames;
    double dist;
    string printString;

};

#endif //UPGMA_CLUSTER_H

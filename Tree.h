//
// Created by Jonah Rubin on 2019-03-19.
//
#include <string>
#include <vector>
#include <ostream>

#ifndef UPGMA_TREE_H
#define UPGMA_TREE_H

using namespace std;

// Sequence struct declaration
struct Sequence {
    string name, str;
    Sequence(string name, string str);
    friend ostream &operator<<(ostream &os, const Sequence &sequence);

};

class Tree {
public:
    Tree(vector<Sequence> &seqs);

    friend ostream &operator<<(ostream &os, const Tree &tree);

    const vector<Sequence> &getSeqs() const;

    const vector<vector<int>> &getDistance_matrix() const;

private:
    vector<Sequence> seqs;
    vector<vector<int>> distance_matrix;

    void populate();
    void calculate();
    const int compare(Sequence s1, Sequence s2);


};



#endif //UPGMA_TREE_H

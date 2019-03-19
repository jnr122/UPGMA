//
// Created by Jonah Rubin on 2019-03-19.
//
#include <string>
#include <vector>

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
    Tree(vector<Sequence> seqs);

private:
    vector<vector<int>> distance_matrix;
    void calculate();
};



#endif //UPGMA_TREE_H

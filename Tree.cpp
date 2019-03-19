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

Tree::Tree(vector<Sequence> seqs) : seqs(seqs) {

}
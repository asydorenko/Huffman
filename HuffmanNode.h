//#ifndef HCNODE_H
//#define HCNODE_H

#include <iostream>

using namespace std;

class HuffmanNode {

public:
    int count;
    unsigned char symbol; // byte in the file we're keeping track of
    HuffmanNode* c0;  // pointer to '0' child
    HuffmanNode* c1;  // pointer to '1' child
    HuffmanNode* p;   // pointer to parent

    HuffmanNode(int count,
      unsigned char symbol,
      HuffmanNode* c0 = 0,
      HuffmanNode* c1 = 0,
      HuffmanNode* p = 0)
        : count(count), symbol(symbol), c0(c0), c1(c1), p(p) { }

    bool operator<(const HuffmanNode& other) const;
};

//#endif

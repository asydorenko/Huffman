#include <stack> 
#include "HuffmanTree.h"

void HuffmanTree::build(const vector<int>& freqs) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, HuffmanNodeComparator> pq;

    // Create nodes with non-zero occurrences and push them on stack
    for(int i=0; i<256; i++)
        if(freqs.at(i) != 0) {
            HuffmanNode* node = new HuffmanNode(freqs.at(i), i, 0, 0, 0);
            leaves.at(i) = node;
            pq.push(node);
        }

    // in case all the bytes in file are the same
    if(pq.size()==1){
        HuffmanNode* node = new HuffmanNode(0, 0, 0, 0, 0);
        leaves.at(0) = node;
        pq.push(node);
    }

    // Create a single tree from all the nodes
    while(pq.size() > 1) {
        HuffmanNode* tmp0 = pq.top();
        pq.pop();
        HuffmanNode* tmp1 = pq.top();
        pq.pop();
        HuffmanNode* newNode = new HuffmanNode(tmp0->count + tmp1->count, tmp1->symbol, tmp0, tmp1, 0);
        tmp0->p = newNode;
        tmp1->p = newNode;
        pq.push(newNode);
    }

    // Assign root to be the top node of the tree
    if(!pq.empty())
        root = pq.top();
}

int HuffmanTree::encode(unsigned char symbol, ofstream& out, int& numberOfBits, unsigned char& buf) const {
    stack<unsigned char> code;
    HuffmanNode* curr = leaves.at(symbol);

    // Traverse from leaf node up to the root pushing bits to the stack
    while(curr != root) {
        if(curr == curr->p->c0)
            code.push(0);
        else
            code.push(1);
        curr = curr->p;
    }
    // number of bits to encode symbol
    int count = code.size();
    
    // write encoded bits in multiples of 8 to the output file
    while(!code.empty()) {
        unsigned char bit = code.top();
        code.pop();
        if((bit >> 0) & 1)
            buf = buf + (1 << 7-numberOfBits);
        numberOfBits++;
        if (numberOfBits == 8) {
            out << buf;
            numberOfBits = 0;
            buf = 0;
        }
    }
    return count;
}

int HuffmanTree::decode(fstream& in, int& counter, unsigned char& buf, int& numberOfBits) const {
    if(!root) 
        return 256;
    unsigned int index;
    HuffmanNode* curr = root;
    if(!curr->c0)
        return 256;

    /** Read bits from encoded file and traverse down to the needed node
     *  and write decoded byte to the output file 
     */
    while(1) {
        if (numberOfBits == 8) {
            buf = in.get();
            numberOfBits = 0;
        }
        if(counter == 0) return 256;
        unsigned int nextBit = ((buf >> 7-numberOfBits) & 1);
        numberOfBits++;
        counter--;
        
        if (nextBit == 0)
            curr = curr->c0;
        else
            curr = curr->c1;
        if (!curr->c0)
            return curr->symbol;
    }

    return 256;
}

HuffmanTree::~HuffmanTree(){
    deleteAll(root);
}

void HuffmanTree::deleteAll(HuffmanNode* n) {
      if (!n)
    return;
  if (n->c0)
    deleteAll(n->c0);
  if (n->c1)
    deleteAll(n->c1);
  delete(n);
}


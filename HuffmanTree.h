#include <queue>
#include <vector>
#include <fstream>
#include "HuffmanNode.h"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HuffmanNode*>.
 */
class HuffmanNodeComparator {
public:
    bool operator()(HuffmanNode*& lhs, HuffmanNode*& rhs) const {
        return *lhs < *rhs;
    }
};

// A Huffman Encoding Tree class.
class HuffmanTree {
private:
    HuffmanNode* root;
    vector<HuffmanNode*> leaves;

public:
    explicit HuffmanTree() : root(0) {
        leaves = vector<HuffmanNode*>(256, (HuffmanNode*) 0);
    }

    ~HuffmanTree();

    // Use the Huffman algorithm to build a Huffman encoding tree.
    void build(const vector<int>& freqs);

    // Write to the output file encoded sequence of bits.
    int encode(unsigned char symbol, ofstream& out, int& numberOfBits, unsigned char& buf) const;

    // Write to the output file decoded bytes.
    int decode(fstream& in, int& counter, unsigned char& buf, int& numberOfBits) const;

    void deleteAll(HuffmanNode* n);
};
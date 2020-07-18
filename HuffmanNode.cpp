#include <iostream>

#include "HuffmanNode.h"

using namespace std;

/** overloading < operator for proper functionality in priority_que
 *  while building the Huffman tree - small counts have a higher priority
 */
bool HuffmanNode::operator<(const HuffmanNode& other) const {
    if(count != other.count) 
        return count > other.count;
    return symbol < other.symbol;
}

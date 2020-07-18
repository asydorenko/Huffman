#include "HuffmanTree.h"

using namespace std;

int main(int argc, char* argv[]) {
    int numberOfBits = 0;       // current number of bits read from the Huffman tree 
    unsigned char buf = 0;      // one byte read from the input file
    int count = 0;              // number of bits written to the output file
    vector<int> freq(256, 0);   // vector of frequences of every byte in the input file
    unsigned int size;          // size of the input file in bytes
    char buffer[1];
    unsigned char x;
    fstream inFile(argv[1], ios::in | ios::binary);         // input file
    ofstream outFile(argv[2], ios::out | ios::binary);      // output file
    HuffmanTree mytree;                                          // Huffman encoding tree

    // determine the size of the input file
    inFile.seekg(0, ios::end);
    size = inFile.tellg();
    if(size == 0) return 0;
    inFile.seekg(0, ios::beg);

    /** calculate the frequency of occurence of each byte in the input file
     *  and store it in the freq vector
     */
    for(int i=0; i<size; i++) {
        inFile.read(buffer, 1);
        x = buffer[0];
        freq.at(x)++;
    }
    inFile.close();

    // build the Huffman encoding tree using frequencies of each byte
    mytree.build(freq);

    // write a header to the output file where we store 256 freqs using 3 bytes for each
    for(int num : freq) {
        int j = 0;
        int k = 0;
        char arr[3]{0};
        for(int i=0; i<24; i++) {
            if(i<8 && ((num>>i)&1))
                arr[2] = arr[2] + (1 << i);
            else
            if(i>7 && i<16){
               if ((num>>i)&1)
                arr[1] = arr[1] + (1 << j);
                j++;
            }
            else 
            if(i>15) {
                if((num>>i)&1) 
                    arr[0] = arr[0] + (1 << k);
                k++;
            }
        }
        outFile.write(arr, 3);
    }

    /** read each byte from input file, encode it using Huffman tree
     *  and write the new sequence of bits into output file
     */
    inFile.open(argv[1], ios::in | ios::binary);
    for(int i=0; i<size; i++){
        inFile.read(buffer, 1);
        x = buffer[0];
        count += mytree.encode(x, outFile, numberOfBits, buf);
    }
    /** if the last bits to be written to the output file are less than 8
     *  then just write those bits and leave remaining spots as 0
     */
    if (numberOfBits != 0) {
        outFile << buf;
    }
    
    // add the number of encoded bits at a new line in the output file
    outFile.put('\n');
    outFile<<count;
    outFile.close();
    inFile.close();
    return 0;
}

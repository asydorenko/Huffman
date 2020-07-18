#include "HuffmanTree.h"

int main(int argc, char* argv[]) {
    vector<int> freq(256, 0);
    string line;
    char index;
    unsigned int x;
    unsigned char buf = 0;          
    int numberOfBits = 8;  
    fstream inFile(argv[1], ios::in | ios::binary);
    ofstream outFile(argv[2], ios::out | ios::binary);
    HuffmanTree mytree;      

    // determine the size of the input file    
    inFile.seekg(0, ios::end);
    int size = inFile.tellg();
    if(size == 0) return 0;
    inFile.seekg(0, ios::beg);    
    
    /** read the header that contains the frequencies of occurance
     * of each byte in the original file, and save them into freq vector
     */
    for(int n=0; n<256; n++) {
        unsigned int res = 0;
        int j = 0;
        int k = 0;
        char arr[3]{0};
        inFile.read(arr, 3);
        for(int i=0; i<24; i++) {
            if(i<8 && (arr[2] >> i)&1)
                res = res + (1 << i);
        else
        if(i>7 && i<16){
             if((arr[1] >> j)&1)
                res = res + (1 << i);
             j++;
        }
        else 
        if(i>15){
           if((arr[0] >> k)&1)
               res = res + (1 << i);
           k++;
        }
    }
        freq.at(n) = res;
    }

    // Build the tree
   mytree.build(freq);

   int curr = inFile.tellg();       // save the current location in the file
   inFile.seekg(-1, ios::end);
   inFile.get(index);
   int i = 2;
   // traverse from the end of file until encounter '\n'
   while(index != '\n'){
       inFile.seekg(-i, ios::end);
       inFile.get(index);
       i++;
   }
   getline(inFile, line);
   int pos = stoi(line, nullptr, 10); // get the number of bits written during compression

   inFile.seekg(curr, ios::beg);        

    // Decode file
    i = 0;
    while((x = mytree.decode(inFile, pos, buf, numberOfBits)) != 256) {
        outFile.put(x);
        i++;
    }
    inFile.close();
    outFile.close();
}

DESCRIPTION:
This is my implementation of Huffman encoding algorithm. To encode a file, the
program first counts the frequency of occurance of each byte in the input file
and then uses this information to build a Huffman tree. Then it reads each byte
in the input file, substitutes it with the apropriate sequence of bits using the
Huffman tree, and writes these bits to the output file. 
In order to decode an encoded file the frequencies of occurance of each byte
from the original file are written as a header to encoded file. This information
is used to build the same Huffman tree during decoding, and then by reading each
bit from the encoded file and traversing the tree - the original byte is restored
and written to the output file.
In my implementation the header values are converted into 3-byte integers instead
of a regular 4-byte integer to shrink the header size. We can make these integer
values to be 2 or even 1 byte in the code if the input file is small, but I left
it as 3-bytes in this implementation. Also the total number of encoded bits
written to encoded file is written on a new line at the end of the file. This value
is helpful whilt pepforming decoding.

USAGE
to compile the program use the provided Makefile and just type:
    make

to delete the compiled files type:
    make clean

to encode a file type:
    ./encode input_file output_file

    this command will open the input_file, encode it
    and save the encoding into the output_file.

to decode a file:
    ./decode input_file output_file

    this command will open the encoded file input_file,
    decode it, and save the decoded version as output_file.

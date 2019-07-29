Title Of Project: Compression algorithm
                  (Huffman Algorithm)

Name: Yadnyi Vishant Deshpande

MIS ID: 111708017

Description:
This project will compress and decompress files

Usage:
./huff operation filename
Eg :
./huff -c1 test.txt result.txt
./huff -uc1 result.txt test1.txt

Language used : c

1) Huffman Compression:
PSEUDOCODE
      Calculate the frequency of characters.
      Make Huffman Tree using two queue's.
      Traverse the tree and find the Huffman codes.
      Write the Huffman codes and frequency as the header of the file being compressed
      Then Read the input file and store the compressed codes in the output file.

Huffman Decompression:
PSEUDOCODE
      Read the header of the input compressed file.
      The header will form the Huffman code dictionary.
      Start reading the input file after the header.
      As huffman codes are prefixed whenever,
      the code is matched it will be decoded and written into the output file.
     

Analysis:

1. Huffman is lossless method of compressing and decompressing data
2.Huffman stores the dictionary into it's compressed file.
4.Huffman is efficient for compressing data.

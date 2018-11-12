Title Of Project: Compression algorithms
                  (Hoffman & LZW)

Name: Yadnyi Vishant Deshpande

MIS ID: 111708017

Description:
This project will compress and decompress files

Usage:
./huff operation filename
Eg :
./huff -c1 test.txt result.txt
./huff -uc1 result.txt test1.txt

./lzw operation filename
Eg :
./lzw -c2 test.txt result.txt
./lzw -uc2 result.txt test1.txt

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

2)LZW Compression:
PSEUDOCODE
      Initialize table with single character strings
      P = first input character
          WHILE not end of input stream
          C = next input character
          IF P + C is in the string table
              P = P + C
          ELSE
              output the code for P
              add P + C to the string table
              P = C
      END WHILE
      output code for P

LZW Decompression:
PSEUDOCODE
      Initialize table with single character strings
      OLD = first input code
      output translation of OLD
      WHILE not end of input stream
          NEW = next input code
          IF NEW is not in the string table
                S = translation of OLD
                S = S + C
          ELSE
                S = translation of NEW
                output S
                C = first character of S
                OLD + C to the string table
                OLD = NEW
      END WHILE

Analysis:

1.Both LZW & Huffman are lossless methods of compressing and decompressing data
2.Huffman stores the dictionary into it's compressed file whereas,
    LZW creates the dictionary while traversing through the compressed file.
3. As LZW creates the dictionary dynamically while decompressing the file,
    it is slower as compared to Huffman.
4.Huffman is also much more efficient than LZW for compressing data.

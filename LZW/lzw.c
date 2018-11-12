#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "mapping.c" // binary file write & read
//#include "list.c"
#include "array.c" // a faster array for decompression

enum{
    dictSize = 4095, // maximum number of entries defined for the dict (2^12 = 4096)
    codeLength = 12, // the codes which are taking place of the substrings
    maxValue = dictSize - 1
};

// function declarations
void compress(FILE *fp, FILE *fd);
void decompress(FILE *fp, FILE *fd);
int decode(int code, FILE *fd);

// compression
void compress(FILE *fp, FILE *fd) {
    int prefix = getc(fp);
    if (prefix == EOF) {
        return;
    }
    int character;

    int nextCode;
    int index;

    // LZW starts out with a dict of 256 characters (in the case of 8 codeLength) and uses those as the "standard"
    //  character set.
    nextCode = 256; // next code is the next available string code
    dictInit();

    // while (there is still data to be read)
    while ((character = getc(fp)) != (unsigned)EOF) { // ch = read a character;

        // if (dict contains prefix+character)
        if ((index = dictLookup(prefix, character)) != -1) prefix = index; // prefix = prefix+character
        else { // ...no, try to add it
            // encode s to output file
            writeBinary(fd, prefix);

            // add prefix+character to dict
            if (nextCode < dictSize) dictAdd(prefix, character, nextCode++);

            // prefix = character
            prefix = character; //... output the last string after adding the new one
        }
    }
    // encode s to output file
    writeBinary(fd, prefix); // output the last code

    if (left > 0) fputc(leftBits << 4, fd);

    // free the dict here
    dictDestroy();
}

// decompression
// to reconstruct a string from an index we need to traverse the dict strings backwards, following each
//   successive prefix index until this prefix index is the empty index
void decompress(FILE * fp, FILE * fd) {
    // int prevcode, currcode
    int previousCode; int currentCode;
    int nextCode = 256; // start with the same dict of 256 characters

    int firstChar;

    // prevcode = read in a code
    previousCode = readBinary(fp);
    if (previousCode == 0) {
        return;
    }
    fputc(previousCode, fd);

    // while (there is still data to read)
    while ((currentCode = readBinary(fp)) > 0) { // currcode = read in a code

        if (currentCode >= nextCode) {
            fputc(firstChar = decode(previousCode, fd), fd); // S+C+S+C+S exception [2.]
            //printf("%c", firstChar);
            //appendCharacter(firstChar = decode(previousCode, fd));
        } else firstChar = decode(currentCode, fd); // first character returned! [1.]

        // add a new code to the string table
        if (nextCode < dictSize){
            dictArrayAdd(previousCode, firstChar, nextCode++);
        }
        // prevcode = currcode
        previousCode = currentCode;
    }
    //printf("\n");
}

int decode(int code, FILE * fd) {
    int character; int temp;

    if (code > 255) { // decode
        character = dictArrayCharacter(code);
        temp = decode(dictArrayPrefix(code), fd); // recursion
    }
    else {
        character = code; // ASCII
        temp = code;
    }
    fputc(character, fd);
    //printf("%c", character);
    //appendCharacter(character);
    return temp;
}

/*
 * The way this works is that 12 bits on fp are split into an 8 bit byte that is written
 *  to the inputFile and the leftover 4 bits are saved for next time with a leftover switch
 *  being flipped.
 * The next time we write another 12 bits we check for left, write it with 4 bits from
 *  the current fp and write the rest, a byte, as well.
 */

#include <stdio.h>
#include<string.h>

void writeBinary(FILE * w, int code);
int readBinary(FILE * r);

int left = 0;
int leftBits;
//r = inputFile w = outputFile

int readBinary(FILE * r) {    // function for Reading input file
    int code = fgetc(r);
    if (code == EOF) return 0;

    if (left > 0){
        code = (leftBits << 8) + code; //left shifting to form 8 bits

        left = 0;
    }
    else{
        int nextCode = fgetc(r);

        leftBits = nextCode & 0xF; // save left, the last 00001111
        left = 1;

        code = (code << 4) + (nextCode >> 4);
    }
    return code;
}

void writeBinary(FILE * w, int code) {
    if (left > 0) {
        int previousCode = (leftBits << 4) + (code >> 8);

        fputc(previousCode, w);
        fputc(code, w);

        left = 0; // no left now
    } else {
        leftBits = code & 0xF; // save left, the last 00001111
        left = 1;

        fputc(code >> 4, w);
    }
}

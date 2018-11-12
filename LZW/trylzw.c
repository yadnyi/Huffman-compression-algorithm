// Main code for LZW compression & decompression
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lzw.c" // LZW compression & decompression
//#include"list.h"


FILE *fp; //input file
FILE *fd; //output file

int main(int argc, char* argv[]) {
    if (argc > 2){
        if (strcmp(argv[1], "-c2") == 0){ // compression
            fp = fopen(argv[2], "r"); // read from the input file (HTML)
            fd = fopen(argv[3], "w+b"); // binary write to fd file

            if (fd == NULL || fp == NULL){
                printf("Can't open files\n'"); return 0;
            }

            compress(fp, fd);
        }
    else{ // decompression
            fp = fopen(argv[2], "rb"); // binary read from the input file
            fd = fopen(argv[3], "w"); // write to fd file (HTML)

            if (fd == NULL || fp == NULL){
                printf("Can't open files\n'"); return 0;
            }

            decompress(fp, fd);
        }

        fclose(fp);
        fclose(fd); // close files
    }
    else{
        //showing the path for compilingchar temp[20]; int length = strlen(argv[2])-4;-
        printf("lzw <command> <input file>\n\n");
        printf("<Commands>\n  -c2  compression\n  -uc2  Decompression\n");
    }

    return 0;
}

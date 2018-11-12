#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"huffqueue.h"
#include<errno.h>

//Recursive function to perform DFS of tree and generate variable length codes
void dfs(nodeq *current, char *a, int index, char map[][1024]){
    //If leaf node, save the generated variable length code in map
  if(current -> left == NULL && current -> right == NULL){
    char ch;
    int i;
    ch = current -> ch;

    for(i = 0; i< index; i++){
      map[(int)ch][i] = a[i];
    }
    map[(int)ch][i] = '\0';
    return;
  }
  //Go to left, and add 0 to code
  if(current -> left != NULL){
    a[index] = '0';
    dfs(current -> left, a, index + 1, map);
  }
  //Go to right, and add 1 to code
  if(current -> right != NULL){
    a[index] = '1';
    dfs(current -> right, a, index + 1, map);
  }
}

int main(int argc, char const *argv[]){
    //<program> <command> <inputfile> <outputfile> <keyfile>
  if(argc == 4){
      //Compression with Huffman
    if(strcmp(argv[1], "-c1") == 0){
      FILE *fp;
      char ch;
      int arr[257], i;
      //Initialize all frequencies to 0
      for(i = 0; i < 257; i++){
        arr[i] = 0;
      }
      fp = fopen(argv[2], "r");
      if(fp == NULL){
        perror("file not opened :");
        return errno;
      }
      do{
        ch = (char)fgetc(fp); //read character by character
        if(ch != -1){
          arr[(int)ch]++;   //increment freq of character
        }
      }while(!feof(fp));
      fclose(fp);

      queue q;
      initq(&q);  //initialise the queue

      //Open key file
      FILE *fkey;
      fkey = fopen("Huffman.key", "w");

      // arr[i] = frequency of char & we typecast int i to char
      for(i = 0; i < 256; i++){
          //Consider the char only if its freq is > than 0
        if(arr[i] > 0){
            //Create new node
          nodeq *temp;
          temp = (nodeq *)malloc(sizeof(nodeq));
          temp -> ch = (char)i; //Char
          temp -> frequency = arr[i]; //Freq
          temp -> next = NULL;
          temp -> left = NULL;
          temp -> right = NULL;
          //Enqueue the new node
          enqueue(&q, temp);
          //Write char and it's freq in key file
          fprintf(fkey, "%d %d\n", i, arr[i]);
        }
      }

      //add end character
      nodeq *temp;
      temp = (nodeq *)malloc(sizeof(nodeq));
      temp -> ch = (char)(256); //Dummy end character
      temp -> frequency = 0; //Freq set to 0 which indicates it is the end character
      temp -> next = NULL;
      temp -> left = NULL;
      temp -> right = NULL;
      enqueue(&q, temp);
      //Write char and it's freq in key file
      fprintf(fkey, "%d %d\n", 256, 0);
      //-1 -1 indicates end of key file
      fprintf(fkey, "%d %d\n", -1, -1);

      nodeq *root;
      while(1){
        //Huffman Tree formation
        nodeq *x, *y;
        x = dequeue(&q);
        y = dequeue(&q);
        int newFre;
        newFre = x -> frequency + y -> frequency;
        nodeq *temp;
        temp = (nodeq *)malloc(sizeof(nodeq));
        temp -> ch = 'c'; //dummy character
        temp -> frequency = newFre;
        temp -> next = NULL;
        temp -> left = x;
        temp -> right = y;
        //if the node is root node i.e last node
        if(isemptyq(&q)){
          root = temp;
          break;
        }
        enqueue(&q, temp);
      }

      //depth first traversal for generating code
      char map[257][1024]; //2D array to store code for each character
      char a[1024]; // String to store current variable length code
      dfs(root, a, 0, map);

      FILE *fd; //output file
      fp = fopen(argv[2], "r");
      fd = fopen(argv[3], "wb"); //file for writing the ouput
      int count = 0, num = 0; //count the bits.Group the 8 bits & write in the file
      do{
        i = 0;
        ch = (char)fgetc(fp); //read character by character

        //if end of file, replace char by our custom end char
        if((int)ch == -1)
            ch = (char)256;

        if(ch != -1){
          while(1){

              //8 bits are complete & current code is also complete
            if(map[(int)ch][i] == '\0' && count == 8){
              unsigned char charval;
              charval = num; // Converting 2 byte int to 1 byte char
              fwrite (&charval, 1, 1, fd); //Write the byte to output file

              //reset count & num
              count = 0;
              num = 0;

              //As code is complete, break from inner loop
              break;
            }

            //current code is complete
            else if(map[(int)ch][i] == '\0'){
                //As code is complete, break from inner loop
                break;
            }

            //8 bits are complete
            else if(count == 8){
              unsigned char charval;
              charval = num; //Converting 2 byte int to 1 byte char
              fwrite (&charval, 1, 1, fd); //Write the byte to output file

              //reset count & num
              count = 0;
              num = 0;

              //As code is not complete, don't break from inner loop
            }

            //Add current bit from code to the incomplete byte
            else{
                num = num << 1; //left shift
                //if 1, write 1
                if(map[(int)ch][i] == '1')
                    num = num | 1;
                //if 0, no need to do anything as by default after left shift the new leftmost bit will be 0

                //increment count & i
              count++;
              i++;
            }
          }
        }

        //break if end character (that is end of file too)
        if((int)ch == 256)
            break;
      }while(!feof(fp));

      //If last byte is incomplete, perform padding with 0s and write to file
      if(count > 0){
          num = num << (8 - count);
          unsigned char charval;
          charval = num;
          fwrite (&charval, 1, 1, fd);
      }
    }

    //Decompression with Huffman
    else if(strcmp(argv[1], "-uc1") == 0){
        FILE *fkey;
        //char ch;
        int arr[257], i;
        //Initialize all frequencies to 0
        for(i = 0; i < 257; i++){
          arr[i] = 0;
        }

        //read chars & freqs from key file and save in array
        fkey = fopen("Huffman.key", "r");
        while(1){
            int chVal, freq;
            fscanf(fkey, "%d %d", &chVal, &freq);
            if(chVal==-1 && freq==-1) {
                break;
            }
            arr[chVal] = freq;
        }

        //generate the same tree as done in compression
        queue q;
        initq(&q);  //initialise the queue

        for(i = 0; i < 256; i++){
          if(arr[i] > 0){
            //create new node
            nodeq *temp;
            temp = (nodeq *)malloc(sizeof(nodeq));
            temp -> ch = (char)i;
            temp -> frequency = arr[i];
            temp -> next = NULL;
            temp -> left = NULL;
            temp -> right = NULL;
            enqueue(&q, temp);
          }
        }

        //add end character
        nodeq *temp;
        temp = (nodeq *)malloc(sizeof(nodeq));
        temp -> ch = (char)(256);
        temp -> frequency = 0;
        temp -> next = NULL;
        temp -> left = NULL;
        temp -> right = NULL;
        enqueue(&q, temp);

        nodeq *root;
        while(1){
          //Tree formation
          nodeq *x, *y;
          x = dequeue(&q);
          y = dequeue(&q);
          int newFre;
          newFre = x -> frequency + y -> frequency;
          nodeq *temp;
          temp = (nodeq *)malloc(sizeof(nodeq));
          temp -> ch = 'c'; //dummy character
          temp -> frequency = newFre;
          temp -> next = NULL;
          temp -> left = x;
          temp -> right = y;
          //if the node is root node i.e last node
          if(isemptyq(&q)){
            root = temp;
            break;
          }
          enqueue(&q, temp);
        }

        FILE *fCompressed;
        fCompressed = fopen(argv[2], "r");
        FILE *fUncompressed;
        fUncompressed = fopen(argv[3], "w");

        char currentByte;
        //start with root
        nodeq *currentNode = root;
        do{
            //read 8 bits i.e. 1 byte
            currentByte = fgetc(fCompressed);
            int i;
            //Read each bit from that 1 byte
            //Start from 10000000 and end at 00000001
            for(i=0; i<8; i++){
                int currentBit = ((int)currentByte)&(128>>i);
                if(currentBit == 0)
                    currentNode = currentNode -> left;
                else
                    currentNode = currentNode -> right;

                //If leaf node
                if((currentNode -> left == NULL) && (currentNode -> right == NULL)){
                    //if freq is 0 then this is our custom end character and we have to stop here only
                    if(currentNode -> frequency == 0)
                        break;

                    //Write char to output file
                    fputc(currentNode -> ch, fUncompressed);

                    //As 1 complete char is recognized, reset current node to root again, to start from beginning
                    currentNode = root;
                }
            }
            //if i<8, it means we broke from inner loop, i.e. end of file
            if(i<8)
                break;
        }while(!feof(fCompressed));
    }
  }
  else{
    printf("Wrong inputs\n");
  }
  return 0;
}

/*
 * Priority queue is used to store frequency in increasing order i.e.
 * the first dequeue frequency would be less
 */

#include<stdio.h>
#include<stdlib.h>
#include"huffqueue.h"

void initq(queue *q){
  q -> head = NULL;
  q -> tail = NULL;
}

int isemptyq(queue *q){
  if(q -> head == NULL)
    return 1;
  else
    return 0;
}

void enqueue(queue *q,nodeq * temp){

  if(isemptyq(q)){
    q -> head = temp;
  }
  else{
    //node for traversing the ll, p follows node r
    nodeq *p, *r = NULL;
    p = q -> head;
    //r = p -> next;
    while(p != NULL){
      r = p -> next;
      if(p -> frequency > temp -> frequency){
        if(p == q -> head){
          temp -> next  = q -> head;
          q -> head =  temp;
          return;
        }
      }
      // compare fre with p & r and if r(p -> next) is NULL then temp will be last node
      else if((p -> frequency <= temp -> frequency) && ( r == NULL || temp -> frequency < r -> frequency)){
        //insert between two nodes
        temp -> next = r;
        p -> next  = temp;
        return;
      }
      p = p -> next;
    }
  }
}
nodeq* dequeue(queue *q){
    nodeq *tmp = q -> head; // to dequeue data
    q -> head = q -> head -> next; //for traversing
    return tmp;
}

void displayq(queue *q){
  nodeq *p;
  p = q -> head;
  while(p != NULL){
    printf("->%c, %d ", p -> ch, p -> frequency);
    p = p -> next;
  }
  printf("\n");
}

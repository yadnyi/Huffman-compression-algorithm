//typedef for queue
typedef struct nodeq{
  char ch;
  int frequency;
  struct nodeq *next, *left, *right; //left &right pointer are for the children in tree
}nodeq;

typedef struct queue{
  nodeq *head, *tail;
}queue;

//functions for the queue
void initq(queue *q);
int isemptyq(queue *q);
void enqueue(queue *q, nodeq * p);
nodeq* dequeue(queue *q);
void displayq(queue *q);

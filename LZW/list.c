//A singly linked list serving as a dictionary.

#include <stdio.h>
#include <stdlib.h>
#include"list.h"
// initialize the dictionary of ASCII characters @12bits
void dictInit() {
    int i;
    struct DictNode *node;
    for (i = 0; i < 256; i++) { // ASCII
        node = (struct DictNode *)malloc(sizeof(struct DictNode));
        node->prefix = emptyPrefix;
        node->character = i;
        appendNode(node);
    }
}

// add node to the list
void appendNode(struct DictNode *node) {
    if (head != NULL){
        tail->next = node;
    }
    else{
        head = node;
    }
    tail = node;
    node->next = NULL;
}

// destroy the whole dict down to NULL
void dictDestroy(){
    while(head != NULL) {
        head = head -> next; /* the head now links to the next element */
    }
}

// is prefix + character in the dict?
int dictLookup(int prefix, int character) {
    struct DictNode *node;
    for (node = head; node != NULL; node = node->next) { // ...traverse forward
        if (node->prefix == prefix && node->character == character) return node->value;
    }
    return emptyPrefix;
}

int dictPrefix(int value) {
    struct DictNode *node;
    for (node = head; node != NULL; node = node->next) { // ...traverse forward
        if (node->value == value) return node->prefix;
    }
    return -1;
}

int dictCharacter(int value) {
    struct DictNode *node;
    for (node = head; node != NULL; node = node->next) { // ...traverse forward
        if (node->value == value) {
            //printf("\nNODE %i %i %i\n", node->value, node->prefix, node->character);
            return node->character;
        }
    }
    return -1;
}

// add prefix + character to the dict
void dictAdd(int prefix, int character, int value) {
    struct DictNode *node;
    node = (struct DictNode *)malloc(sizeof(struct DictNode));
    node->value = value;
    node->prefix = prefix;
    node->character = character;
    //printf("\n(%i) = (%i) + (%i)\n", node->value, node->prefix, node->character);
    appendNode(node);
}

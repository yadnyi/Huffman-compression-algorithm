enum {
    emptyPrefix = -1 // empty prefix for ASCII characters
};

// the "string" in the dictionary consists of the last byte of the string and an index to a prefix for that string
typedef struct DictNode {
    int value; // the position in the list
    int prefix; // prefix for byte > 255
    int character; // the last byte of the string
    struct DictNode *next;
}DictNode;
// the dictionary
typedef struct DictNode *head, *tail;


void dictInit();
void appendNode(struct DictNode *node);
void dictDestroy();
int dictLookup(int prefix, int character);
int dictPrefix(int value);
int dictCharacter(int value);
void dictAdd(int prefix, int character, int value);

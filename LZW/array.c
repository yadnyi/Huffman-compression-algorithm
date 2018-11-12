//array decompression

typedef struct{
    int prefix; // prefix for byte > 255
    int character; // the last byte of the string
} DictElement;

void dictArrayAdd(int prefix, int character, int value);
int dictArrayPrefix(int value);
int dictArrayCharacter(int value);

DictElement dictArray[4095];

// add prefix + character to the dict
void dictArrayAdd(int prefix, int character, int value) {
    dictArray[value].prefix = prefix;
    dictArray[value].character = character;
}

int dictArrayPrefix(int value) {
    return dictArray[value].prefix;
}

int dictArrayCharacter(int value) {
    return dictArray[value].character;
}

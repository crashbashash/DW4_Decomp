/* Compares two big integers by word count and then word by word from the top; returns <0, 0 or >0
 * (newlib mprec __mcmp shape; name is a hypothesis). */
typedef struct BigInt {
    struct BigInt *next;
    int k;
    int maxWords;
    int sign;
    int words;
    unsigned int x[1];
} BigInt;

int FUN_00127cd0(BigInt *a, BigInt *b) {
    unsigned int *wordA;
    unsigned int *firstA;
    unsigned int *wordB;
    unsigned int *firstB;
    int i;
    int j;

    i = a->words;
    j = b->words;
    if (i -= j) {
        return i;
    }
    firstA = a->x;
    wordA = firstA + j;
    firstB = b->x;
    wordB = firstB + j;
    for (;;) {
        if (*--wordA != *--wordB) {
            return *wordA < *wordB ? -1 : 1;
        }
        if (wordA <= firstA) {
            break;
        }
    }
    return 0;
}

/* Takes a big-integer block of 2^k words from the reent free list, allocating the list or a fresh
 * block with FUN_00123798 when needed. */
typedef struct BigInt {
    struct BigInt *next;
    int k;
    int maxWords;
    int sign;
    int words;
    unsigned int x[1];
} BigInt;

typedef struct Reent {
    char f0[76];
    BigInt **freeList;
} Reent;

void *FUN_00123798(Reent *reent, int count, int size);

BigInt *FUN_001273e0(Reent *reent, int k) {
    int x;
    BigInt *result;

    if (reent->freeList == 0) {
        reent->freeList = FUN_00123798(reent, sizeof(BigInt *), 16);
        if (reent->freeList == 0) {
            return 0;
        }
    }
    if ((result = reent->freeList[k]) != 0) {
        reent->freeList[k] = result->next;
    } else {
        x = 1 << k;
        result = FUN_00123798(reent, 1, sizeof(BigInt) + (x - 1) * sizeof(result->x));
        if (result == 0) {
            return 0;
        }
        result->k = k;
        result->maxWords = x;
    }
    result->sign = result->words = 0;
    return result;
}

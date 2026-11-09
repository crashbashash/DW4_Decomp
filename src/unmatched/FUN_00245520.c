typedef struct HashLink {
    unsigned int key;
    struct BucketBinding *next;
    struct BucketBinding *prev;
} HashLink;

typedef struct BucketBinding {
    char pad0[12];
    HashLink link;
} BucketBinding;

void *Memory_AllocateDefaultBuffer(int size);
void Memory_FreeBufferAliasA(void *buffer);
void *memset(void *p, int c, unsigned int n);
void FUN_002454c0(HashLink *link, BucketBinding **table, unsigned int size, unsigned int bits);
extern unsigned int DAT_0056dee8;
extern BucketBinding **DAT_0056def0;
extern int DAT_0056def8;
extern unsigned int DAT_004986d0;
extern unsigned int DAT_004986d8;

void FUN_00245520(void)
{
    unsigned int count;
    unsigned int bits;
    unsigned int newBits;
    unsigned int newSize;
    BucketBinding **newTable;
    unsigned int i;
    BucketBinding *node;
    BucketBinding *next;

    if (DAT_0056def0 == 0) {
        DAT_0056def0 = Memory_AllocateDefaultBuffer(DAT_004986d8 * 4);
        memset(DAT_0056def0, 0, DAT_004986d8 * 4);
        return;
    }
    if (DAT_0056def8 != 0) return;
    count = DAT_0056dee8;
    if (count == 0) {
        Memory_FreeBufferAliasA(DAT_0056def0);
        DAT_0056def0 = 0;
        DAT_004986d8 = 256;
        return;
    }
    bits = DAT_004986d0;
    newBits = bits;
    if (DAT_004986d8 < count) {
        newBits = bits + 1;
    } else if (count < DAT_004986d8 >> 1 && bits > 8) {
        newBits = bits - 1;
    }
    if (newBits == bits) return;
    newSize = 1 << newBits;
    newTable = Memory_AllocateDefaultBuffer(newSize * 4);
    memset(newTable, 0, newSize * 4);
    for (i = 0; i < DAT_004986d8; i++) {
        for (node = DAT_0056def0[i]; node != 0; node = next) {
            next = node->link.next;
            FUN_002454c0(&node->link, newTable, newSize, newBits);
        }
    }
    DAT_004986d8 = newSize;
    DAT_004986d0 = newBits;
    Memory_FreeBufferAliasA(DAT_0056def0);
    DAT_0056def0 = newTable;
}

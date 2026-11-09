typedef struct TypeNode {
    unsigned int key;
    struct TypeNode *next;
    struct TypeNode *prev;
} TypeNode;

void *Memory_AllocateDefaultBuffer(int size);
void Memory_FreeBufferAliasA(void *buffer);
void *memset(void *p, int c, unsigned int n);
void FUN_002456d0(TypeNode *node, TypeNode **table, unsigned int size, unsigned int bits);
extern unsigned int DAT_0056df00;
extern TypeNode **DAT_0056df08;
extern int DAT_0056df10;
extern unsigned int DAT_004986e0;
extern unsigned int DAT_004986e8;

void FUN_00245710(void)
{
    unsigned int count;
    unsigned int bits;
    unsigned int newBits;
    unsigned int newSize;
    TypeNode **newTable;
    unsigned int i;
    TypeNode *node;
    TypeNode *next;

    if (DAT_0056df08 == 0) {
        DAT_0056df08 = Memory_AllocateDefaultBuffer(DAT_004986e8 * 4);
        memset(DAT_0056df08, 0, DAT_004986e8 * 4);
        return;
    }
    if (DAT_0056df10 != 0) return;
    count = DAT_0056df00;
    if (count == 0) {
        Memory_FreeBufferAliasA(DAT_0056df08);
        DAT_0056df08 = 0;
        DAT_004986e8 = 256;
        return;
    }
    bits = DAT_004986e0;
    newBits = bits;
    if (DAT_004986e8 < count) {
        newBits = bits + 1;
    } else if (count < DAT_004986e8 >> 1 && bits > 8) {
        newBits = bits - 1;
    }
    if (newBits == bits) return;
    newSize = 1 << newBits;
    newTable = Memory_AllocateDefaultBuffer(newSize * 4);
    memset(newTable, 0, newSize * 4);
    for (i = 0; i < DAT_004986e8; i++) {
        for (node = DAT_0056df08[i]; node != 0; node = next) {
            next = node->next;
            FUN_002456d0(node, newTable, newSize, newBits);
        }
    }
    DAT_004986e8 = newSize;
    DAT_004986e0 = newBits;
    Memory_FreeBufferAliasA(DAT_0056df08);
    DAT_0056df08 = newTable;
}

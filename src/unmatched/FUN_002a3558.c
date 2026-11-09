typedef struct BufPoolSlot {
    char * addr;
    int used;
} BufPoolSlot;

typedef struct BufPoolPool {
    int base;
    int count;
    int size;
    BufPoolSlot slot[18];
} BufPoolPool;

typedef struct BufPoolObj {
    char pad[44];
    int reserve;
    char pad48[8072];
    char *work;
} BufPoolObj;

int FUN_002a0bb8(BufPoolObj *obj, int code);
void FUN_002a7af0(BufPoolPool *pool);

int FUN_002a3558(BufPoolObj *obj, char * base, int count, int size)
{
    BufPoolPool *pool = (BufPoolPool *)(obj->work + 4096);
    int i;
    int addr;
    int n;

    if (base == 0 || count == 0 || size == 0) {
        FUN_002a7af0(pool);
        return 0;
    }
    if (count < obj->reserve + 4)
        return FUN_002a0bb8(obj, 0xFF000F1D);
    pool->base = base;
    i = 0;
    pool->slot[0].addr = base;
    base += size;
    pool->count = count;
    count -= 2;
    pool->slot[1].addr = base;
    base += size;
    pool->size = size;
    pool->slot[0].used = 0;
    pool->slot[1].used = 0;
    for (; i < (count < 17 ? count : 16); i++) {
        pool->slot[i + 2].used = 0;
        pool->slot[i + 2].addr = base;

        base += size;
    }
    return 0;
}

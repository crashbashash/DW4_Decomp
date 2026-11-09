typedef struct SjSkipChunk {
    char *addr;
    int size;
} SjSkipChunk;

typedef struct SjSkipSjVtbl {
    void *f0[6];
    void (*getChunk)(void *sj, int id, int size, SjSkipChunk *chunk);
    void (*ungetChunk)(void *sj, int id, SjSkipChunk *chunk);
    void (*putChunk)(void *sj, int id, SjSkipChunk *chunk);
} SjSkipSjVtbl;

typedef struct SjSkipSj {
    SjSkipSjVtbl *vtbl;
} SjSkipSj;

typedef struct SjSkipObj {
    char pad[904];
    SjSkipChunk chunk;
} SjSkipObj;

void FUN_0027d470(SjSkipChunk *src, int size, SjSkipChunk *head, SjSkipChunk *rest);
int FUN_00290520(SjSkipObj *obj, char *addr, int size);
void FUN_00290898(SjSkipSj *sj);

int FUN_00290430(SjSkipObj *obj, SjSkipSj *sj)
{
    SjSkipChunk *chunk = &obj->chunk;
    SjSkipChunk rest;
    char *base;
    int bits;
    int ret;

    sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, chunk);
    base = (char *)((int)chunk->addr & ~3);
    bits = (chunk->addr - base) * 8;
    ret = FUN_00290520(obj, chunk->addr, obj->chunk.size);
    base += 8;
    base += bits >> 3;
    base -= 4;
    FUN_0027d470(chunk, base - chunk->addr, chunk, &rest);

    sj->vtbl->putChunk(sj, 0, chunk);
    sj->vtbl->ungetChunk(sj, 1, &rest);
    FUN_00290898(sj);
    return ret;
}

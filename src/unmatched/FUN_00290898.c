typedef struct SjSeekChunk {
    char *addr;
    int size;
} SjSeekChunk;

typedef struct SjSeekSjVtbl {
    void *f0[6];
    void (*getChunk)(void *sj, int id, int size, SjSeekChunk *chunk);
    void (*ungetChunk)(void *sj, int id, SjSeekChunk *chunk);
    void (*putChunk)(void *sj, int id, SjSeekChunk *chunk);
} SjSeekSjVtbl;

typedef struct SjSeekSj {
    SjSeekSjVtbl *vtbl;
} SjSeekSj;

void FUN_0027d470(SjSeekChunk *src, int size, SjSeekChunk *head, SjSeekChunk *rest);
int FUN_0028dc78(char *p);
char *FUN_0028de10(char *buf, int len, int mask);

int FUN_00290898(SjSeekSj *sj)
{
    SjSeekChunk chunk;
    SjSeekChunk rest;
    char *p;
    int code;

    for (;;) {
        sj->vtbl->getChunk(sj, 1, 0x7FFFFFFF, &chunk);
        if (chunk.size < 4) {
            sj->vtbl->ungetChunk(sj, 1, &chunk);
            code = 0;
            break;
        }
        p = FUN_0028de10(chunk.addr, chunk.size, -1);
        if (p == 0) {
            FUN_0027d470(&chunk, chunk.size - 3, &chunk, &rest);
            sj->vtbl->putChunk(sj, 0, &chunk);
            sj->vtbl->ungetChunk(sj, 1, &rest);
        } else {
            code = FUN_0028dc78(p);
            FUN_0027d470(&chunk, p - chunk.addr, &chunk, &rest);
            sj->vtbl->putChunk(sj, 0, &chunk);
            sj->vtbl->ungetChunk(sj, 1, &rest);
            break;
        }
    }
    return code;
}

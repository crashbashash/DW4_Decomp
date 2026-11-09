typedef struct {
    char *ptr;
    int len;
} CriSjChunk;

typedef struct {
    int f0;
    int used;
    int f8;
    int bytes;
    int pos;
    char *base;
    int f24;
    void (*err)(int, int);
    int errobj;
} SjMem;

void FUN_0027b2e0(const char *message);
extern char DAT_004f1bf8[];
extern char DAT_004f1c28[];

void FUN_0027b810(SjMem *sj, int line, int nbyte, CriSjChunk *ck)
{
    if (sj == 0) {
        FUN_0027b2e0(DAT_004f1bf8);
        return;
    }
    if (sj->used == 0) {
        FUN_0027b2e0(DAT_004f1c28);
        return;
    }
    if (line == 0) {
        ck->len = 0;
        ck->ptr = 0;
        return;
    }
    if (line == 1) {
        ck->len = (sj->bytes < nbyte) ? sj->bytes : nbyte;
        ck->ptr = sj->base + sj->pos;
        sj->pos += ck->len;
        sj->bytes -= ck->len;
        return;
    }
    ck->len = 0;
    ck->ptr = 0;
    if (sj->err != 0) {
        sj->err(sj->errobj, -3);
    }
}

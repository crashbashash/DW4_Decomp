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
    int size;
    void (*err)(int, int);
    int errobj;
} SjMem;

void FUN_0027b2e0(const char *message);
extern char DAT_004f1cb8[];
extern char DAT_004f1ce8[];

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void FUN_0027ba10(SjMem *sj, int line, CriSjChunk *ck)
{
    int pos;

    if (sj == 0) {
        FUN_0027b2e0(DAT_004f1cb8);
        return;
    }
    if (sj->used == 0) {
        FUN_0027b2e0(DAT_004f1ce8);
        return;
    }
    if (ck->len <= 0 || ck->ptr == 0) {
        return;
    }
    if (line == 0) {
        if (sj->err != 0) {
            sj->err(sj->errobj, -3);
        }
    } else if (line == 1) {
        pos = sj->pos - ck->len;
        if (pos < 0) {
            pos = 0;
        }
        sj->pos = pos;
        sj->bytes = MIN(sj->size, sj->bytes + ck->len);
        if (pos != ck->ptr - sj->base) {
            if (sj->err != 0) {
                sj->err(sj->errobj, -3);
            }
        }
    } else {
        ck->len = 0;
        ck->ptr = 0;
        if (sj->err != 0) {
            sj->err(sj->errobj, -3);
        }
    }
}

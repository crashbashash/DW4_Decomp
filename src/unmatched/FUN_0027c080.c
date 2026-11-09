typedef struct {
    char *ptr;
    int len;
} CriSjChunk;

typedef struct {
    int f0;
    int used;
    char pad8[4];
    int ndata;
    int nfree;
    int wpos;
    int rpos;
    char *buf;
    int bsize;
    int xsize;
    int got_free;
    int total_free;
    int got_data;
    int total_data;
    void (*err)(int, int);
    int errobj;
} SjRbf;

void FUN_0027b2e0(const char *message);
extern char DAT_004f1e58[];
extern char DAT_004f1e88[];
extern char DAT_004f1eb8[];

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void FUN_0027c080(SjRbf *sj, int line, int nbyte, CriSjChunk *ck)
{
    if (sj == 0) {
        FUN_0027b2e0(DAT_004f1e58);
        return;
    }
    if (sj->used == 0) {
        FUN_0027b2e0(DAT_004f1e88);
        return;
    }
    if (sj->bsize == 0) {
        FUN_0027b2e0(DAT_004f1eb8);
        return;
    }
    if (line == 0) {
        ck->len = MIN(MIN(sj->nfree, sj->bsize - sj->wpos + sj->xsize), nbyte);
        ck->ptr = sj->buf + sj->wpos;
        sj->wpos = (sj->wpos + ck->len) % sj->bsize;
        sj->nfree -= ck->len;
        sj->got_free += ck->len;
    } else if (line == 1) {
        ck->len = MIN(MIN(sj->ndata, sj->bsize - sj->rpos + sj->xsize), nbyte);
        ck->ptr = sj->buf + sj->rpos;
        sj->rpos = (sj->rpos + ck->len) % sj->bsize;
        sj->ndata -= ck->len;
        sj->got_data += ck->len;
    } else {
        ck->len = 0;
        ck->ptr = 0;
        if (sj->err != 0) {
            sj->err(sj->errobj, -3);
        }
    }
}

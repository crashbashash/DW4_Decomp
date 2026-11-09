typedef struct {
    void *ptr;
    int len;
} CriSjChunk;

typedef struct Sj Sj;
typedef struct {
    void *pad0[6];
    void (*get_chunk)(Sj *, int, int, CriSjChunk *);
    void (*unget_chunk)(Sj *, int, CriSjChunk *);
    void (*put_chunk)(Sj *, int, CriSjChunk *);
} SjVtbl;
struct Sj {
    SjVtbl *vt;
};

typedef struct {
    char f0;
    char f1;
    signed char nch;
    char pad3[9];
    Sj *sj[2];
    char pad20[144];
    int nsmpl;
} AdxsSkip;

void FUN_00266f18(AdxsSkip *x)
{
    CriSjChunk ck;
    int i;
    int n;
    int half;

    n = x->nsmpl * 2;
    for (i = 0; i < x->nch; i++) {
        x->sj[i]->vt->get_chunk(x->sj[i], 1, 0x7fffffff, &ck);
        if (ck.len <= n) {
            n = ck.len;
        }
        x->sj[i]->vt->unget_chunk(x->sj[i], 1, &ck);
    }
    half = n / 2;
    n = half * 2;
    if (n <= 0) {
        return;
    }
    for (i = 0; i < x->nch; i++) {
        x->sj[i]->vt->get_chunk(x->sj[i], 1, n, &ck);
        x->sj[i]->vt->put_chunk(x->sj[i], 0, &ck);
    }
    x->nsmpl -= half;
}

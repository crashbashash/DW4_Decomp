typedef struct {
    void *ptr;
    int len;
} CriSjChunk;

typedef struct Sj Sj;
typedef struct {
    void *pad0[6];
    void (*get_chunk)(Sj *, int, int, CriSjChunk *);
    void (*unget_chunk)(Sj *, int, CriSjChunk *);
} SjVtbl;
struct Sj {
    SjVtbl *vt;
};

typedef struct {
    char f0;
    char stat;
    char pad2[2];
    Sj *in[2];
    Sj *out;
    char pad16[28];
    int total;
    char pad48[40];
    int nch;
    int f92;
    char pad96[4];
    int f100;
    char pad104[24];
    void *flt[2];
    short prev1[2];
    short prev2[2];
    char pad144[568];
    short first1[2];
    short first2[2];
} AdxEnc;

int FUN_00268b10(AdxEnc *e, Sj *out);
void FUN_00267de8(void *flt, int a, int b);

void FUN_00269988(AdxEnc *e)
{
    CriSjChunk ck;
    Sj *out;
    int i;
    int n;

    out = e->out;
    for (i = 0; i < e->nch; i++) {
        e->in[i]->vt->get_chunk(e->in[i], 1, 2, &ck);
        if (ck.len == 0) {
            break;
        }
        e->first1[i] = e->first2[i] = *(short *)ck.ptr;
        e->in[i]->vt->unget_chunk(e->in[i], 1, &ck);
    }
    if (i < e->nch) {
        return;
    }
    for (i = 0; i < e->nch; i++) {
        e->prev1[i] = e->first1[i];
        e->prev2[i] = e->first2[i];
    }
    n = FUN_00268b10(e, out);
    if (n == 0) {
        return;
    }
    e->total += n;
    for (i = 0; i < e->nch; i++) {
        FUN_00267de8(e->flt[i], e->f100, e->f92);
    }
    e->stat = 2;
}

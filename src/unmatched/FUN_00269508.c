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
    char f2;
    char f3;
    Sj *sj[9];
    int f40;
    int f44;
    int f48;
    char pad52[36];
    int nch;
    char pad92[12];
    int nsmpl;
} AdxbOut;

void *memset(void *dst, int c, unsigned int n);

/* matching construct: statement-order sweep of the five trailing stores */
void FUN_00269508(AdxbOut *x)
{
    CriSjChunk ck;
    int i;
    int len;

    for (i = 0; i < x->nch; i++) {
        len = x->nsmpl * 2;
        if (len > 0) {
            x->sj[i]->vt->get_chunk(x->sj[i], 0, len, &ck);
            if (ck.len != len) {
                x->sj[i]->vt->unget_chunk(x->sj[i], 0, &ck);
                for (;;) {
                }
            }
            memset(ck.ptr, 0, ck.len);
            x->sj[i]->vt->put_chunk(x->sj[i], 1, &ck);
        }
    }
    x->f40 = 0;
    x->f44 = 0;
    x->f48 = 0;
    x->f3 = 0;
    x->f1 = 1;
}

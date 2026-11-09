typedef struct {
    void *ptr;
    unsigned int len;
} CriSjChunk;

typedef struct Sj Sj;
typedef struct {
    void *pad0[6];
    void (*get_chunk)(Sj *, int, int, CriSjChunk *);
    void (*unget_chunk)(Sj *, int, CriSjChunk *);
    void (*put_chunk)(Sj *, int, CriSjChunk *);
    unsigned int (*get_num_data)(Sj *, int);
} SjVtbl;
struct Sj {
    SjVtbl *vt;
};

typedef struct {
    char f0[4];
    Sj *sj[21];
    int nch;
} AdxbIn;

void *memcpy(void *dst, const void *src, unsigned int n);

int FUN_00268018(AdxbIn *x, int arg1, int n, short **bufs)
{
    CriSjChunk ck;
    int i;
    int cnt;
    Sj **sj;

    sj = x->sj;
    cnt = 0;
    for (i = 0; i < x->nch; i++) {
        cnt = sj[i]->vt->get_num_data(sj[i], 1) / 2;
        if (cnt < n) {
            return 0;
        }
    }
    for (i = 0; i < x->nch; i++) {
        for (cnt = 0; cnt < n;) {
            sj[i]->vt->get_chunk(sj[i], 1, n * 2, &ck);
            memcpy(&bufs[i][cnt], ck.ptr, ck.len);
            cnt += (short)(ck.len / 2);
            sj[i]->vt->put_chunk(sj[i], 0, &ck);
        }
    }
    return cnt;
}

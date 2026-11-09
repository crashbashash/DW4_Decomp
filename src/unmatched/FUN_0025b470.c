typedef struct {
    void *ptr;
    int len;
} CriSjChunk;

typedef struct Sj Sj;
typedef struct {
    void *pad0[5];
    void (*reset)(Sj *);
    void (*get_chunk)(Sj *, int, int, CriSjChunk *);
    void (*unget_chunk)(Sj *, int, CriSjChunk *);
    void (*put_chunk)(Sj *, int, CriSjChunk *);
    int (*get_num_data)(Sj *, int);
} SjVtbl;
struct Sj {
    SjVtbl *vt;
};

typedef struct {
    signed char used;
    char stat;
    signed char nch;
    char pad3;
    Sj *sj[2];
    Sj *out[2];
    int f20[2];
    int nch_;
    int freq;
    float f36;
    float f40;
    int f44;
} AdxRna;

void *memset(void *dst, int value, unsigned int size);

void FUN_0025b470(AdxRna *rna)
{
    CriSjChunk ck;
    Sj *sj;
    int i;

    for (i = 0; i < rna->nch; i++) {
        rna->f20[i] = 0;
    }
    rna->f44 = 0;
    for (i = 0; i < rna->nch; i++) {
        sj = rna->sj[i];
        sj->vt->reset(sj);
        sj->vt->get_chunk(sj, 0, sj->vt->get_num_data(sj, 0), &ck);
        memset(ck.ptr, 0, ck.len);
        sj->vt->unget_chunk(sj, 0, &ck);
    }
    for (i = 0; i < rna->nch; i++) {
        sj = rna->out[i];
        sj->vt->reset(sj);
        sj->vt->get_chunk(sj, 0, sj->vt->get_num_data(sj, 0), &ck);
        memset(ck.ptr, 0, ck.len);
        sj->vt->unget_chunk(sj, 0, &ck);
    }
    rna->stat = 2;
}

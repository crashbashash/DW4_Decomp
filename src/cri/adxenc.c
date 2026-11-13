typedef struct CriSjChunk {
    void *ptr;
    int len;
} CriSjChunk;

typedef struct Sj Sj;
typedef struct SjVtbl {
    void *pad0[6];
    void (*get_chunk)(Sj *sj, int id, int nbyte, CriSjChunk *ck);
    void (*unget_chunk)(Sj *sj, int id, CriSjChunk *ck);
    void (*put_chunk)(Sj *sj, int id, CriSjChunk *ck);
    int (*get_num_data)(Sj *sj, int id);
} SjVtbl;
struct Sj {
    SjVtbl *vt;
};

typedef struct AdxEncPredictor {
    signed char used;   /* 0x00 */
    char pad1[3];
    short k0;           /* 0x04 */
    short k1;           /* 0x06 */
    short h0;           /* 0x08 */
    short h1;           /* 0x0a */
} AdxEncPredictor;

typedef struct AdxEncFilter {
    char used;                  /* 0x00 */
    char pad1[3];
    short k0;                   /* 0x04 */
    short k1;                   /* 0x06 */
    short h0;                   /* 0x08 */
    short h1;                   /* 0x0a */
    char pad12[8];
    int nsmpl;                  /* 0x14 */
    short res[32];              /* 0x18 */
    signed char nibble[32];     /* 0x58 */
    int peak;                   /* 0x78 */
    short scale;                /* 0x7c */
    char pad126[2];
    double rscale;              /* 0x80 */
    AdxEncPredictor *pred;      /* 0x88 */
    char pad140[4];
} AdxEncFilter;

typedef struct AdxEnc {
    signed char used;           /* 0x00 */
    signed char stat;           /* 0x01 */
    signed char nch_b;          /* 0x02 */
    signed char ended;          /* 0x03 */
    Sj *in[2];                  /* 0x04 */
    Sj *out;                    /* 0x0c */
    char pad16[24];
    int f40;                    /* 0x28 */
    int total;                  /* 0x2c */
    int pos;                    /* 0x30 */
    int f52;                    /* 0x34 */
    int f56;                    /* 0x38 */
    int end;                    /* 0x3c */
    int f64;                    /* 0x40 */
    int blklen;                 /* 0x44 */
    int hdrsize;                /* 0x48 */
    int f76;                    /* 0x4c */
    int f80;                    /* 0x50 */
    int f84;                    /* 0x54 */
    int nch;                    /* 0x58 */
    int f92;                    /* 0x5c */
    int f96;                    /* 0x60 */
    int f100;                   /* 0x64 */
    int nsmpl;                  /* 0x68 */
    int f108;                   /* 0x6c */
    int f112;                   /* 0x70 */
    int f116;                   /* 0x74 */
    int f120;                   /* 0x78 */
    int f124;                   /* 0x7c */
    AdxEncFilter *flt[2];       /* 0x80 */
    short prev1[2];             /* 0x88 */
    short prev2[2];             /* 0x8c */
    short buf[2][32];           /* 0x90 */
    short resid[2][32];         /* 0x110 */
    short norm[2][32];          /* 0x190 */
    short recon[2][32];         /* 0x210 */
    short scale[2];             /* 0x290 */
    char pad660[4];
    double rscale[2];           /* 0x298 */
    int data[2][4];             /* 0x2a8 */
    short first1[2];            /* 0x2c8 */
    short first2[2];            /* 0x2cc */
    unsigned short key_x;       /* 0x2d0 */
    unsigned short key_mul;     /* 0x2d2 */
    unsigned short key_add;     /* 0x2d4 */
    signed char has_name;       /* 0x2d6 */
    char name[16];              /* 0x2d7 */
    char pad743;
    short f744;                 /* 0x2e8 */
    short f746[2];              /* 0x2ea */
    signed char has_loop;       /* 0x2ee */
    char pad751;
    int lsmpl;                  /* 0x2f0 */
    int esmpl;                  /* 0x2f4 */
} AdxEnc;

extern int DAT_004a5d58;
extern void (*DAT_004a5d5c)(void *obj, const char *msg);
extern void *DAT_004a5d60;
extern int DAT_004a5d68;
extern AdxEnc DAT_004a5d70[8];
extern AdxEncPredictor DAT_004a7530[16];
extern AdxEncFilter DAT_004a75f0[16];
extern const short DAT_004ecff8[1024];
extern const char DAT_004ee3e8[];
extern const char DAT_004ee428[];

void *memset(void *dst, int value, unsigned int size);
void *memcpy(void *dst, const void *src, unsigned int size);
unsigned int strlen(const char *s);
int abs(int value);
char *strncpy(char *dst, const char *src, unsigned int size);
int ADX_GetCoefficient(short id, int arg, short *first, short *second);
int FUN_0025f588(unsigned short *data, int size, short *out_a, char *out_b, char *out_c, char *out_d, char *out_e, int *out_f, int *out_g, int *out_h);

int adxenc_EncodeBlock(AdxEnc *e, int ch);
void FUN_002683e8(AdxEnc *e, int ch);
int FUN_00268b10(AdxEnc *e, Sj *out);

int FUN_002674e8(void)
{
    return 0;
}

int FUN_002674f0(void (*func)(void *obj, const char *msg), void *obj)
{
    DAT_004a5d5c = func;
    DAT_004a5d60 = obj;
    return 0;
}

int FUN_00267508(const char *msg)
{
    if (DAT_004a5d5c != 0) {
        DAT_004a5d5c(DAT_004a5d60, msg);
    }
    return 0;
}

int FUN_00267540(void)
{
    DAT_004a5d58 += 1;
    return 0;
}

int FUN_00267560(void)
{
    DAT_004a5d58 -= 1;
    return 0;
}

int FUN_00267580(const char *str, int len, unsigned short *k0, unsigned short *k1, unsigned short *k2)
{
    int i;
    short a;
    short b;
    short c;

    if (DAT_004a5d58 == 0) {
        FUN_00267540();
    }
    *k0 = 0;
    *k1 = 0;
    *k2 = 0;
    if (str == 0 && len <= 0) {
        return 0;
    }
    a = DAT_004ecff8[256];
    for (i = 0; i < len; i++) {
        a = DAT_004ecff8[a * DAT_004ecff8[128 + str[i]] % 1024];
    }
    b = DAT_004ecff8[512];
    for (i = 0; i < len; i++) {
        b = DAT_004ecff8[b * DAT_004ecff8[128 + str[i]] % 1024];
    }
    c = DAT_004ecff8[768];
    for (i = 0; i < len; i++) {
        c = DAT_004ecff8[c * DAT_004ecff8[128 + str[i]] % 1024];
    }
    *k0 = a;
    *k1 = b;
    *k2 = c;
    return 0;
}

int FUN_00267738(unsigned short *k0, unsigned short *k1, unsigned short *k2)
{
    if (DAT_004a5d58 == 0) {
        FUN_00267540();
    }
    FUN_00267580(DAT_004ee3e8, 6, k0, k1, k2);
    return 0;
}

int FUN_002677a8(unsigned short *x, unsigned short *mul, unsigned short *add)
{
    *x = *x * *mul + *add;
    return 0;
}

int FUN_002677c8(void)
{
    return 256;
}

const char *FUN_002677d0(void)
{
    return DAT_004ee428;
}

int FUN_002677e0(int count, int base, int bits)
{
    return (bits + 31) / 32 * count * 18 + base + 4;
}

int FUN_00267968(unsigned short *data, int size, int *out_c, int *out_e, int *out_f, int *out_g)
{
    short value_a;
    char value_b;
    char value_c;
    char value_d;
    char value_e;
    int value_h;
    int result;

    result = FUN_0025f588(data, size, &value_a, &value_b, &value_c, &value_d, &value_e, out_f, out_g, &value_h);
    *out_e = value_e;
    *out_c = value_c;
    return result;
}

int FUN_002679d0(void *src, int size, int n, Sj *sj)
{
    CriSjChunk ck;
    int nbyte;
    int i;
    int *s4;
    int *d4;
    short *s2;
    short *d2;
    int w;

    nbyte = size * n;
    sj->vt->get_chunk(sj, 0, nbyte, &ck);
    if (ck.len < nbyte) {
        sj->vt->unget_chunk(sj, 0, &ck);
        return 0;
    }
    if (size == 4) {
        s4 = src;
        d4 = ck.ptr;
        for (i = 0; i < n; i++) {
            w = *s4++;
            *d4++ = ((w >> 24) & 0xff) | ((w >> 8) & 0xff00) | ((w << 8) & 0xff0000) | (w << 24);
        }
    } else if (size == 2) {
        s2 = src;
        d2 = ck.ptr;
        for (i = 0; i < n; i++) {
            *d2++ = ((*s2 >> 8) & 0xff) | ((*s2 << 8) & 0xff00);
            s2++;
        }
    } else if (size == 1) {
        memcpy(ck.ptr, src, (unsigned short)n);
    } else {
        for (;;) {
        }
    }
    sj->vt->put_chunk(sj, 1, &ck);
    return n;
}

void FUN_00267b90(void)
{
    memset(DAT_004a7530, 0, sizeof(DAT_004a7530));
}

AdxEncPredictor *FUN_00267bb8(void)
{
    AdxEncPredictor *entry;
    int i;

    for (i = 0; i < 16; i++) {
        entry = &DAT_004a7530[i];
        if (entry->used == 0) {
            break;
        }
    }
    if (i < 16) {
        return entry;
    }
    return 0;
}

void FUN_00267c18(AdxEncPredictor *entry)
{
    if (entry != 0) {
        entry->used = 0;
        memset(entry, 0, sizeof(AdxEncPredictor));
    }
}

void FUN_00267c50(AdxEncPredictor *p, short k0, short k1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    p->k0 = k0;
    p->k1 = k1;
}

void adxenc_SetPredHistory(AdxEncPredictor *p, short h0, short h1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    p->h0 = h0;
    p->h1 = h1;
}

void adxenc_GetPredHistory(AdxEncPredictor *p, unsigned short *h0, unsigned short *h1)
{
    unsigned short t = p->h0;
    *h0 = t;
    *h1 = p->h1;
}

short adxenc_PredictSample(AdxEncPredictor *state, short input)
{
    int value;
    short output;

    if (state != 0) {
        value = ((state->k0 * state->h0 + state->k1 * state->h1) >> 12) + input;
        if (value < 32767) {
            output = value < -32768 ? -32768 : value;
        } else {
            output = 32767;
        }
        state->h1 = state->h0;
        state->h0 = output;
        return output;
    }
    return input;
}

AdxEncFilter *FUN_00267d00(int nsmpl)
{
    AdxEncPredictor *pred = FUN_00267bb8();
    AdxEncFilter *entry;
    int i;

    if (pred == 0) {
        return 0;
    }
    for (i = 0; i < 16; i++) {
        entry = &DAT_004a75f0[i];
        if (entry->used == 0) {
            break;
        }
    }
    /* Retail writes these even when the table is full (into the last entry). */
    entry->nsmpl = nsmpl;
    entry->pred = pred;
    if (i < 16) {
        entry->used = 1;
        return entry;
    }
    return 0;
}

void FUN_00267da0(AdxEncFilter *entry)
{
    if (entry != 0) {
        entry->used = 0;
        memset(entry, 0, sizeof(AdxEncFilter));
    }
}

void FUN_00267dd8(AdxEncFilter *f, short k0, short k1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    f->k0 = k0;
    f->k1 = k1;
}

void FUN_00267de8(AdxEncFilter *f, int id, int arg)
{
    short first;
    short second;

    ADX_GetCoefficient(id, arg, &first, &second);
    FUN_00267dd8(f, first, second);
    FUN_00267c50(f->pred, first, second);
}

void adxenc_SetFilterHistory(AdxEncFilter *f, short h0, short h1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    f->h0 = h0;
    f->h1 = h1;
}

void adxenc_FilterSample(AdxEncFilter *f, int i, short input)
{
    int j;
    int value;
    short output;
    int level;
    unsigned short prev;

    if (i == 0) {
        for (j = 0; j < f->nsmpl; j++) {
            f->res[j] = 0;
        }
        f->peak = 0;
    }
    if (f != 0) {
        value = input - ((f->k0 * f->h0) >> 12) - ((f->k1 * f->h1) >> 12);
        f->res[i] = output = value > 32767 ? 32767 : (value < -32768 ? -32768 : value);
        level = abs(output);
        if (f->peak < level) {
            f->peak = level;
        }
        prev = f->h0;
        f->h0 = input;
        f->h1 = prev;
    }
}

void adxenc_CalcScale(AdxEncFilter *f)
{
    int scale;
    int n;

    n = (f->peak - 1) / 7 + 1;
    scale = (n < DAT_004a5d68) ? n : DAT_004a5d68;
    scale = (scale < 1) ? 1 : scale;
    f->scale = scale;
    if (f->peak == 0) {
        f->rscale = 32767.0;
    } else {
        f->rscale = 32767.0 / f->peak;
    }
}

short adxenc_GetResidual(AdxEncFilter *f, int i)
{
    short v;

    v = 0;
    if (f != 0) {
        v = f->res[i];
    }
    return v;
}

int FUN_00267ff0(AdxEncFilter *f, int i)
{
    int v;

    v = 0;
    if (f != 0) {
        v = f->nibble[i];
    }
    return v;
}

void adxenc_SetNibble(AdxEncFilter *f, int i, signed char v)
{
    f->nibble[i] = v;
}

int FUN_00268018(AdxEnc *x, int pos, int n, short **bufs)
{
    CriSjChunk ck;
    int i;
    int cnt;
    Sj **sj;

    sj = x->in;
    cnt = 0;
    for (i = 0; i < x->nch; i++) {
        cnt = sj[i]->vt->get_num_data(sj[i], 1) / sizeof(short);
        if (cnt < n) {
            return 0;
        }
    }
    for (i = 0; i < x->nch; i++) {
        for (cnt = 0; cnt < n;) {
            sj[i]->vt->get_chunk(sj[i], 1, n * 2, &ck);
            memcpy(&bufs[i][cnt], ck.ptr, ck.len);
            cnt += (short)(ck.len / sizeof(short));
            sj[i]->vt->put_chunk(sj[i], 0, &ck);
        }
    }
    return cnt;
}

int adxenc_EncodeBlock(AdxEnc *e, int ch)
{
    AdxEncFilter *f;
    AdxEncPredictor *pred;
    unsigned short h0;
    unsigned short h1;
    short sample;
    short decoded;
    int level;
    int i;

    f = e->flt[ch];
    pred = f->pred;
    adxenc_SetFilterHistory(f, e->prev1[ch], e->prev2[ch]);
    /* matching construct: variant search — the samples are read as *(e->buf[ch] + i), not e->buf[ch][i]; the row offset then stays a loop invariant of its own in both loops */
    for (i = 0; i < e->blklen; i++) {
        adxenc_FilterSample(f, i, *(e->buf[ch] + i));
    }
    adxenc_CalcScale(f);
    adxenc_SetPredHistory(f->pred, e->prev1[ch], e->prev2[ch]);
    for (i = 0; i < e->blklen; i++) {
        sample = *(e->buf[ch] + i);
        adxenc_GetPredHistory(pred, &h0, &h1);
        adxenc_SetFilterHistory(f, h0, h1);
        adxenc_FilterSample(f, i, sample);
        level = adxenc_GetResidual(f, i) * f->rscale;
        level = (short)(level > 32767 ? 32767 : (level < -32768 ? -32768 : level));
        level = (level < 0 ? level - 2340 : level + 2340) / 4681;
        level = level >= 7 ? 7 : (level < -8 ? -8 : level);
        adxenc_SetNibble(f, i, level);
        level *= f->scale;
        decoded = level > 32767 ? 32767 : (level < -32768 ? -32768 : level);
        adxenc_PredictSample(f->pred, decoded);
    }
    return 0;
}

int FUN_00268670(AdxEnc *e)
{
    short *bufs[2];
    unsigned short h0;
    unsigned short h1;
    int n;
    int i;
    int ch;
    AdxEncFilter *f;
    AdxEncPredictor *pred;

    bufs[0] = e->buf[0];
    bufs[1] = e->buf[1];
    n = e->end - e->pos;
    if (e->blklen < n) {
        n = e->blklen;
    }
    if (FUN_00268018(e, e->pos, n, bufs) == 0) {
        return 0;
    }
    if (n < e->blklen) {
        for (i = 0; i < e->nch; i++) {
            if (bufs[i] != 0) {
                memset(bufs[i] + n, 0, (e->blklen - n) * 2);
            }
        }
    }
    e->pos += e->blklen;
    for (ch = 0; ch < e->nch; ch++) {
        adxenc_EncodeBlock(e, ch);
        f = e->flt[ch];
        pred = f->pred;
        e->scale[ch] = f->scale;
        e->rscale[ch] = f->rscale;
        adxenc_GetPredHistory(pred, &h0, &h1);
        e->prev1[ch] = h0;
        e->prev2[ch] = h1;
        FUN_002683e8(e, ch);
    }
    return e->blklen;
}

int FUN_00268830(AdxEnc *e)
{
    int *blk;
    Sj *sj;
    short s;
    char b;
    int total;
    int i;

    total = 0;
    sj = e->out;
    for (i = 0; i < e->nch; i++) {
        s = e->key_x ^ (e->scale[i] - 1);
        blk = e->data[i];
        e->key_x = (e->key_x * e->key_mul + e->key_add) & 0x7fff;
        if (blk[0] == 0 && blk[1] == 0 && blk[2] == 0 && blk[3] == 0) {
            s = 0;
        }
        b = s >> 8;
        FUN_002679d0(&b, 1, 1, sj);
        b = s;
        FUN_002679d0(&b, 1, 1, sj);
        FUN_002679d0(blk, 1, 16, sj);
        total += 18;
    }
    return total;
}

int FUN_00268960(AdxEnc *e)
{
    Sj *sj;
    int total;

    total = 0;
    sj = e->out;
    do {
        if (sj->vt->get_num_data(sj, 0) / 18 / e->nch <= 0) {
            break;
        }
        if (FUN_00268670(e) == 0) {
            break;
        }
        total += FUN_00268830(e);
    } while (e->pos < e->end);
    return total;
}

int FUN_00268a10(AdxEnc *e)
{
    int len;
    unsigned short tag;
    char zero;
    int n;
    int i;
    Sj *sj;
    int ofst;

    sj = e->out;
    ofst = e->total;
    if (e->f108 <= 0) {
        len = e->f80;
    } else {
        len = (ofst + e->f80 + 2047) / 2048 * 2048 - ofst;
    }
    n = len - 4;
    if (sj->vt->get_num_data(sj, 0) < len) {
        return 0;
    }
    tag = 0x8001;
    FUN_002679d0(&tag, 2, 1, sj);
    tag = n;
    FUN_002679d0(&tag, 2, 1, sj);
    zero = 0;
    for (i = 0; i < n; i++) {
        FUN_002679d0(&zero, 1, 1, sj);
    }
    return len;
}

void FUN_00269268(void)
{
    FUN_00267540();
    memset(DAT_004a5d70, 0, sizeof(DAT_004a5d70));
}

void FUN_00269298(void)
{
    FUN_00267560();
    memset(DAT_004a5d70, 0, sizeof(DAT_004a5d70));
}

/* matching construct: statement-order sweep of the five trailing stores */
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);

void FUN_00269498(AdxEnc *e)
{
    if (e == 0) {
        return;
    }
    ADXCRS_Lock();
    if (e->flt[0] != 0) {
        FUN_00267da0(e->flt[0]);
    }
    if (e->flt[1] != 0) {
        FUN_00267da0(e->flt[1]);
    }
    /* matching construct: hand search — the four status bytes are cleared together, one word store */
    memset(e, 0, 4);
    ADXCRS_Unlock();
}

void FUN_00269508(AdxEnc *x)
{
    CriSjChunk ck;
    int i;
    int len;

    for (i = 0; i < x->nch; i++) {
        len = x->nsmpl * 2;
        if (len > 0) {
            x->in[i]->vt->get_chunk(x->in[i], 0, len, &ck);
            if (ck.len != len) {
                x->in[i]->vt->unget_chunk(x->in[i], 0, &ck);
                for (;;) {
                }
            }
            memset(ck.ptr, 0, ck.len);
            x->in[i]->vt->put_chunk(x->in[i], 1, &ck);
        }
    }
    x->f40 = 0;
    x->total = 0;
    x->pos = 0;
    x->ended = 0;
    x->stat = 1;
}

int FUN_00269500(AdxEnc *e)
{
    return e->stat;
}

void ADXENC_SetEnd(AdxEnc *e)
{
    e->ended = 1;
}

void FUN_00269640(AdxEnc *e, int v)
{
    e->f92 = v;
}

void FUN_00269648(AdxEnc *e, int v)
{
    e->hdrsize = v;
}

void FUN_00269650(AdxEnc *e, int v)
{
    e->nch = v;
}

void FUN_00269658(AdxEnc *e, int v)
{
    e->f84 = v;
}

void FUN_00269660(AdxEnc *e, int blklen)
{
    e->blklen = blklen;
    if (e->flt[0] != 0) {
        FUN_00267da0(e->flt[0]);
    }
    e->flt[0] = FUN_00267d00(e->blklen);
    if (e->flt[1] != 0) {
        FUN_00267da0(e->flt[1]);
    }
    e->flt[1] = FUN_00267d00(e->blklen);
}

void FUN_002696c8(AdxEnc *e, int v)
{
    e->f80 = v;
}

void FUN_002696d0(AdxEnc *e, int v)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    e->end = v;
    e->f96 = v;
}

void FUN_002696e0(AdxEnc *e, int v)
{
    e->f100 = v;
}

void FUN_002696e8(AdxEnc *e, int v)
{
    e->f108 = v;
}

void FUN_002696f0(AdxEnc *e, int v)
{
    e->nsmpl = v;
}

void FUN_002696f8(AdxEnc *e, int v)
{
    e->f112 = v;
}

void FUN_00269700(AdxEnc *e, int v)
{
    e->f116 = v;
}

void FUN_00269708(AdxEnc *e, int v)
{
    e->f120 = v;
}

void FUN_00269710(AdxEnc *e, int v)
{
    e->f124 = v;
}

void FUN_00269718(AdxEnc *e, int v)
{
    if (e->has_name != 1) {
        e->has_name = 1;
        e->hdrsize += 36;
    }
    e->f744 = v;
}

void FUN_00269740(AdxEnc *e, int i, int v)
{
    if (e->has_name != 1) {
        e->has_name = 1;
        e->hdrsize += 36;
    }
    e->f746[i] = v;
}

void FUN_00269770(AdxEnc *e, const char *name)
{
    if (e->has_name != 1) {
        e->has_name = 1;
        e->hdrsize += 36;
    }
    memset(e->name, 0, 16);
    strncpy(e->name, name, 16);
}

void FUN_002697d8(AdxEnc *e)
{
    if (e->has_name == 1) {
        e->has_name = 0;
        e->hdrsize += 36;
    }
    e->f744 = 0;
    e->f746[0] = -128;
    e->f746[1] = -128;
    memset(e->name, 0, 16);
}

void FUN_00269828(AdxEnc *e, int lsmpl, int esmpl)
{
    if (e->has_loop != 1) {
        e->has_loop = 1;
        e->lsmpl = lsmpl;
        e->esmpl = esmpl;
        e->hdrsize += (esmpl + 2047) / 2048 * 2048 + 4;
    }
}

void FUN_00269878(AdxEnc *e, int nch, int f92, int end)
{
    /* matching construct: permuter — the no-op a2++/a2-- raises a2's use count so ee-gcc gives it s0 (retail order s0=a2, s1=object, s2=a3) */
    f92++;
    f92--;
    FUN_00269650(e, nch);
    FUN_00269640(e, f92);
    FUN_002696d0(e, end);
    FUN_00269648(e, 284);
}

void FUN_002698d8(AdxEnc *e, const char *text)
{
    unsigned short a, b, c;

    FUN_00267580(text, strlen(text), &a, &b, &c);
    e->key_x = a;
    e->key_mul = b;
    e->key_add = c;
}

int FUN_00269940(AdxEnc *e)
{
    return e->total;
}

int FUN_00269948(AdxEnc *e)
{
    return e->pos;
}

void FUN_00269950(AdxEnc *e, int v)
{
    e->pos = v;
}

int FUN_00269958(AdxEnc *e)
{
    return e->pos;
}

void FUN_00269960(AdxEnc *e, unsigned int i, Sj *sj)
{
    if (i < 2) {
        e->in[i] = sj;
    }
}

void FUN_00269980(AdxEnc *e, Sj *sj)
{
    e->out = sj;
}

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

void FUN_00269af8(AdxEnc *e)
{
    int count;

    /* matching construct: goto — retail re-tests the ended flag after setting it; structured loops reorder the blocks */
loop:
    if (e->ended == 0) {
        while ((count = FUN_00268960(e)) != 0) {
            e->total += count;
            if (e->pos >= e->end) {
                e->ended = 1;
                goto loop;
            }
        }
        return;
    }
    if (FUN_00268a10(e) > 0) {
        e->stat = 3;
    }
}

void FUN_00269b90(AdxEnc *e)
{
    if (e->stat == 1) {
        FUN_00269988(e);
    } else if (e->stat == 2) {
        FUN_00269af8(e);
    }
}

void FUN_00269bd0(void)
{
    int i;
    AdxEnc *e;

    e = DAT_004a5d70;
    i = 7;
    do {
        if (e->used == 1) {
            FUN_00269b90(e);
        }
        i -= 1;
        e++;
    } while (i >= 0);
}

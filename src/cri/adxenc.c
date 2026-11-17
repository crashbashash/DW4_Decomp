#include <string.h>
#include "dw4/cri/adxt.h"

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
    signed char cinf_flg;       /* 0x2ee */
    char pad751;
    void *cinf;                 /* 0x2f0 */
    int cinf_len;               /* 0x2f4 */
} AdxEnc;

extern int skg_init_count;
extern void (*DAT_004a5d5c)(void *obj, const char *msg);
extern void *DAT_004a5d60;
extern int DAT_004a5d68;
extern char *DAT_004a5d6c;
extern AdxEnc DAT_004a5d70[8];
extern AdxEncPredictor adxsje_iirflt_obj[16];
extern AdxEncFilter adxsje_prdflt_obj[16];
extern const short skg_tbl[1024];
extern const char DAT_004ee3e8[];
extern const char DAT_004ee428[];

int abs(int value);
int ADX_GetCoefficient(short id, int arg, short *first, short *second);
int ADX_DecodeInfo(unsigned short *data, int size, short *out_a, char *out_b, char *out_c, char *out_d, char *out_e, int *out_f, int *out_g, int *out_h);

int ADX_CalcHdrInfoLen(int type, int len, int ofst, unsigned int blk);
int adxsje_calc_rsig(AdxEnc *e, int ch);
void adxsje_set_rsig(AdxEnc *e, int ch);
int adxsje_output_header(AdxEnc *e, Sj *out);

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
    skg_init_count += 1;
    return 0;
}

int FUN_00267560(void)
{
    skg_init_count -= 1;
    return 0;
}

int ADXKEY_GenerateKey(const char *str, int len, unsigned short *k0, unsigned short *k1, unsigned short *k2)
{
    int i;
    short a;
    short b;
    short c;

    if (skg_init_count == 0) {
        FUN_00267540();
    }
    *k0 = 0;
    *k1 = 0;
    *k2 = 0;
    if (str == 0 && len <= 0) {
        return 0;
    }
    a = skg_tbl[256];
    for (i = 0; i < len; i++) {
        a = skg_tbl[a * skg_tbl[128 + str[i]] % 1024];
    }
    b = skg_tbl[512];
    for (i = 0; i < len; i++) {
        b = skg_tbl[b * skg_tbl[128 + str[i]] % 1024];
    }
    c = skg_tbl[768];
    for (i = 0; i < len; i++) {
        c = skg_tbl[c * skg_tbl[128 + str[i]] % 1024];
    }
    *k0 = a;
    *k1 = b;
    *k2 = c;
    return 0;
}

int ADXKEY_GetDefKey(unsigned short *k0, unsigned short *k1, unsigned short *k2)
{
    if (skg_init_count == 0) {
        FUN_00267540();
    }
    ADXKEY_GenerateKey(DAT_004ee3e8, 6, k0, k1, k2);
    return 0;
}

int SKG_GetNextKey(unsigned short *x, unsigned short *mul, unsigned short *add)
{
    *x = *x * *mul + *add;
    return 0;
}

int ADXSJE_GetVersion(void)
{
    return 256;
}

const char *ADXSJE_GetVerStr(void)
{
    return DAT_004ee428;
}

int adxsje_nsmpl_to_ofst(int count, int base, int bits)
{
    return (bits + 31) / 32 * count * 18 + base + 4;
}

void ADXSJE_CalcLpInfo(int nch, int len, int len2, int *hdrlen, int *pad, int *size, int *size2)
{
    int blk;
    int nblk;
    int body;
    int hdr;
    int tail;

    blk = nch == 1 ? 64 : 32;
    *pad = (blk - len % blk) % blk;
    nblk = (len + *pad) / 32 * nch;
    body = nblk * 18;
    hdr = ADX_CalcHdrInfoLen(1, 0, 4, 4);
    tail = (2048 - (body + hdr + 4) % 2048) % 2048;
    *hdrlen = hdr + tail;
    *size = adxsje_nsmpl_to_ofst(nch, *hdrlen, len + *pad);
    *size2 = adxsje_nsmpl_to_ofst(nch, *hdrlen, len2 + *pad);
}

int ADXSJE_GetInfo(unsigned short *data, int size, int *out_c, int *out_e, int *out_f, int *out_g)
{
    short value_a;
    char value_b;
    char value_c;
    char value_d;
    char value_e;
    int value_h;
    int result;

    result = ADX_DecodeInfo(data, size, &value_a, &value_b, &value_c, &value_d, &value_e, out_f, out_g, &value_h);
    *out_e = value_e;
    *out_c = value_c;
    return result;
}

int adxsje_write68(void *src, int size, int n, Sj *sj)
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

void iirflt_init(void)
{
    memset(adxsje_iirflt_obj, 0, sizeof(adxsje_iirflt_obj));
}

AdxEncPredictor *iirflt_create(void)
{
    AdxEncPredictor *entry;
    int i;

    for (i = 0; i < 16; i++) {
        entry = &adxsje_iirflt_obj[i];
        if (entry->used == 0) {
            break;
        }
    }
    if (i < 16) {
        return entry;
    }
    return 0;
}

void iirflt_destroy(AdxEncPredictor *entry)
{
    if (entry != 0) {
        entry->used = 0;
        memset(entry, 0, sizeof(AdxEncPredictor));
    }
}

void iirflt_set_coef(AdxEncPredictor *p, short k0, short k1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    p->k0 = k0;
    p->k1 = k1;
}

void iirflt_set_delay(AdxEncPredictor *p, short h0, short h1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    p->h0 = h0;
    p->h1 = h1;
}

void iirflt_get_delay(AdxEncPredictor *p, unsigned short *h0, unsigned short *h1)
{
    unsigned short t = p->h0;
    *h0 = t;
    *h1 = p->h1;
}

short iirflt_put_sig(AdxEncPredictor *state, short input)
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

AdxEncFilter *pflt_create(int nsmpl)
{
    AdxEncPredictor *pred = iirflt_create();
    AdxEncFilter *entry;
    int i;

    if (pred == 0) {
        return 0;
    }
    for (i = 0; i < 16; i++) {
        entry = &adxsje_prdflt_obj[i];
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

void pflt_destroy(AdxEncFilter *entry)
{
    if (entry != 0) {
        entry->used = 0;
        memset(entry, 0, sizeof(AdxEncFilter));
    }
}

void pflt_set_coef(AdxEncFilter *f, short k0, short k1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    f->k0 = k0;
    f->k1 = k1;
}

void pflt_calc_coef(AdxEncFilter *f, int id, int arg)
{
    short first;
    short second;

    ADX_GetCoefficient(id, arg, &first, &second);
    pflt_set_coef(f, first, second);
    iirflt_set_coef(f->pred, first, second);
}

void pflt_set_delay(AdxEncFilter *f, short h0, short h1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    f->h0 = h0;
    f->h1 = h1;
}

void pflt_put_sig(AdxEncFilter *f, int i, short input)
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

void pflt_calc_gain(AdxEncFilter *f)
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

short pflt_get_rsig(AdxEncFilter *f, int i)
{
    short v;

    v = 0;
    if (f != 0) {
        v = f->res[i];
    }
    return v;
}

int pflt_get_rsig_q(AdxEncFilter *f, int i)
{
    int v;

    v = 0;
    if (f != 0) {
        v = f->nibble[i];
    }
    return v;
}

void pflt_set_rsig_q(AdxEncFilter *f, int i, signed char v)
{
    f->nibble[i] = v;
}

int adxsje_get_pcm_data(AdxEnc *x, int pos, int n, short **bufs)
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

int adxsje_calc_rsig(AdxEnc *e, int ch)
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
    pflt_set_delay(f, e->prev1[ch], e->prev2[ch]);
    /* matching construct: variant search — the samples are read as *(e->buf[ch] + i), not e->buf[ch][i]; the row offset then stays a loop invariant of its own in both loops */
    for (i = 0; i < e->blklen; i++) {
        pflt_put_sig(f, i, *(e->buf[ch] + i));
    }
    pflt_calc_gain(f);
    iirflt_set_delay(f->pred, e->prev1[ch], e->prev2[ch]);
    for (i = 0; i < e->blklen; i++) {
        sample = *(e->buf[ch] + i);
        iirflt_get_delay(pred, &h0, &h1);
        pflt_set_delay(f, h0, h1);
        pflt_put_sig(f, i, sample);
        level = pflt_get_rsig(f, i) * f->rscale;
        level = (short)(level > 32767 ? 32767 : (level < -32768 ? -32768 : level));
        level = (level < 0 ? level - 2340 : level + 2340) / 4681;
        level = level >= 7 ? 7 : (level < -8 ? -8 : level);
        pflt_set_rsig_q(f, i, level);
        level *= f->scale;
        decoded = level > 32767 ? 32767 : (level < -32768 ? -32768 : level);
        iirflt_put_sig(f->pred, decoded);
    }
    return 0;
}

/* Quantizes channel ch's block: the filter residuals, scaled to 16 bits, become 4-bit nibbles (4681 = 32768 / 7 per
 * step, rounded half away from zero) packed big-end first into e->data[ch]; recon gets the dequantized samples. */
void adxsje_set_rsig(AdxEnc *e, int ch)
{
    int j = 0;
    AdxEncFilter *f;
    short *resid;
    short *norm;
    short *recon;
    unsigned char *data;
    int per;
    int byte;
    int level;
    int i;
    int nib;

    resid = e->resid[ch];
    norm = e->norm[ch];
    recon = e->recon[ch];
    data = (unsigned char *)e->data[ch];
    per = 8 / e->f84;
    f = e->flt[ch];
    byte = -1;
    for (i = 0; i < e->blklen; i++) {
        resid[i] = pflt_get_rsig(f, i);
        level = resid[i] * f->rscale;
        level = (level > 32767) ? 32767 : ((level < -32768) ? -32768 : level);
        norm[i] = level;
        if (norm[i] < 0) {
            level = (level - 2340) / 4681;
        } else {
            level = (level + 2340) / 4681;
        }
        nib = level >= 7 ? 7 : (level < -8 ? -8 : level);
        level = nib * f->scale * f->rscale;
        level = (level > 32767) ? 32767 : ((level < -32768) ? -32768 : level);
        recon[i] = level;
        if (i % per == 0) {
            byte++;
            data[byte] = 0;
            j = 1;
        }
        nib = ((nib << (8 - e->f84)) & 0xff) >> (8 - e->f84);
        data[byte] |= nib << ((per - j) * e->f84);
        j++;
    }
}

int adxsje_encode_blk(AdxEnc *e)
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
    if (adxsje_get_pcm_data(e, e->pos, n, bufs) == 0) {
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
        adxsje_calc_rsig(e, ch);
        f = e->flt[ch];
        pred = f->pred;
        e->scale[ch] = f->scale;
        e->rscale[ch] = f->rscale;
        iirflt_get_delay(pred, &h0, &h1);
        e->prev1[ch] = h0;
        e->prev2[ch] = h1;
        adxsje_set_rsig(e, ch);
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
        adxsje_write68(&b, 1, 1, sj);
        b = s;
        adxsje_write68(&b, 1, 1, sj);
        adxsje_write68(blk, 1, 16, sj);
        total += 18;
    }
    return total;
}

int adxsje_encode_data(AdxEnc *e)
{
    Sj *sj;
    int total;

    total = 0;
    sj = e->out;
    do {
        if (sj->vt->get_num_data(sj, 0) / 18 / e->nch <= 0) {
            break;
        }
        if (adxsje_encode_blk(e) == 0) {
            break;
        }
        total += FUN_00268830(e);
    } while (e->pos < e->end);
    return total;
}

int adxsje_write_end_code(AdxEnc *e)
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
    adxsje_write68(&tag, 2, 1, sj);
    tag = n;
    adxsje_write68(&tag, 2, 1, sj);
    zero = 0;
    for (i = 0; i < n; i++) {
        adxsje_write68(&zero, 1, 1, sj);
    }
    return len;
}

/* Writes one item of the header and counts its bytes; a short write abandons the header. */
#define ADXSJE_PUT(p, size, n)                                    \
    if (adxsje_write68((p), (size), (n), sj) != (n)) {            \
        goto err;                                                 \
    }                                                             \
    len += (size) * (n)

/* Writes the ADX header: the fixed part, the loop records, the AINF and CINF chunks, zero padding and the
 * copyright string. Returns its size, or 0 when the output stream has no room or a write falls short. */
int adxsje_output_header(AdxEnc *e, Sj *sj)
{
    CriSjChunk ck;
    int i4;
    unsigned short tag;
    short hdr;
    short i2;
    signed char i1;
    int padlen;
    int crilen;
    int room;
    int len;
    int i;

    crilen = strlen(DAT_004a5d6c);
    sj->vt->get_chunk(sj, 0, 0x7fffffff, &ck);
    room = ck.len;
    sj->vt->unget_chunk(sj, 0, &ck);
    if (room < e->hdrsize + 4) {
        return 0;
    }
    tag = 0x8000;
    if (adxsje_write68(&tag, 2, 1, sj) != 1) {
        goto err;
    }
    hdr = e->hdrsize;
    if (adxsje_write68(&hdr, 2, 1, sj) != 1) {
        goto err;
    }
    len = 0;
    i1 = e->f76;
    ADXSJE_PUT(&i1, 1, 1);
    i1 = e->f80;
    ADXSJE_PUT(&i1, 1, 1);
    i1 = e->f84;
    ADXSJE_PUT(&i1, 1, 1);
    i1 = e->nch;
    ADXSJE_PUT(&i1, 1, 1);
    i4 = e->f92;
    ADXSJE_PUT(&i4, 4, 1);
    i4 = e->f96;
    ADXSJE_PUT(&i4, 4, 1);
    i2 = e->f100;
    ADXSJE_PUT(&i2, 2, 1);
    i1 = 4;
    ADXSJE_PUT(&i1, 1, 1);
    if ((short)e->key_x == 0) {  /* matching construct: the key is read signed */
        i1 = 0;
    } else {
        i1 = 8;
    }
    ADXSJE_PUT(&i1, 1, 1);
    i4 = 0;
    ADXSJE_PUT(&i4, 4, 1);
    i2 = e->first1[0];
    ADXSJE_PUT(&i2, 2, 1);
    i2 = e->first2[0];
    ADXSJE_PUT(&i2, 2, 1);
    i2 = e->first1[1];
    ADXSJE_PUT(&i2, 2, 1);
    i2 = e->first2[1];
    ADXSJE_PUT(&i2, 2, 1);
    if (e->f108 > 0) {
        i2 = e->nsmpl;
        ADXSJE_PUT(&i2, 2, 1);
        i2 = e->f108;
        ADXSJE_PUT(&i2, 2, 1);
        for (i = 0; i < e->f108; i++) {
            i2 = i;
            ADXSJE_PUT(&i2, 2, 1);
            i2 = 1;
            ADXSJE_PUT(&i2, 2, 1);
            i4 = e->f112;
            ADXSJE_PUT(&i4, 4, 1);
            i4 = e->f116;
            ADXSJE_PUT(&i4, 4, 1);
            i4 = e->f120;
            ADXSJE_PUT(&i4, 4, 1);
            i4 = e->f124;
            ADXSJE_PUT(&i4, 4, 1);
        }
    }
    if (e->has_name == 1) {
        if (e->f108 == 0) {
            i4 = 0;
            ADXSJE_PUT(&i4, 4, 1);
        }
        i4 = 0x41494e46;  /* "AINF" */
        ADXSJE_PUT(&i4, 4, 1);
        i4 = 24;
        ADXSJE_PUT(&i4, 4, 1);
        ADXSJE_PUT(e->name, 1, 16);
        i2 = e->f744;
        ADXSJE_PUT(&i2, 2, 1);
        i2 = 0;
        ADXSJE_PUT(&i2, 2, 1);
        i2 = e->f746[0];
        ADXSJE_PUT(&i2, 2, 1);
        i2 = e->f746[1];
        ADXSJE_PUT(&i2, 2, 1);
    }
    if (e->cinf_flg == 1) {
        if (e->f108 == 0) {
            i4 = 0;
            ADXSJE_PUT(&i4, 4, 1);
        }
        i4 = 0x43494e46;  /* "CINF" */
        ADXSJE_PUT(&i4, 4, 1);
        i4 = e->cinf_len;
        ADXSJE_PUT(&i4, 4, 1);
        if (e->cinf_len != 0 && e->cinf != 0) {
            ADXSJE_PUT(e->cinf, 1, e->cinf_len);
        }
    }
    i1 = 0;
    padlen = e->hdrsize - crilen;
    while (len < padlen) {
        ADXSJE_PUT(&i1, 1, 1);
    }
    ADXSJE_PUT(DAT_004a5d6c, 1, crilen);
    return len + 4;
err:
    return 0;
}

void ADXSJE_Init(void)
{
    FUN_00267540();
    memset(DAT_004a5d70, 0, sizeof(DAT_004a5d70));
}

void ADXSJE_Finish(void)
{
    FUN_00267560();
    memset(DAT_004a5d70, 0, sizeof(DAT_004a5d70));
}

/* Takes a free encoder for nch input streams and one output stream, with the defaults: 4-bit ADX at 44100 Hz
 * in 18-byte blocks, a cutoff of 500 and no loop. */
AdxEnc *ADXSJE_Create(int nch, Sj **in, Sj *out)
{
    AdxEnc *e;
    int i;
    int j;

    for (i = 0; i < 8; i++) {
        if (DAT_004a5d70[i].used == 0) {
            break;
        }
    }
    if (i == 8) {
        return 0;
    }
    e = &DAT_004a5d70[i];
    e->nch_b = nch;
    for (j = 0; j < nch; j++) {
        e->in[j] = in[j];
    }
    e->out = out;
    e->stat = 0;
    e->f40 = 0;
    e->total = 0;
    e->pos = 0;
    e->f52 = 0x7fff0000;
    e->hdrsize = ADX_CalcHdrInfoLen(0, 0, 4, 4);
    e->f76 = 3;
    e->nch = nch;
    e->f92 = 44100;
    e->f84 = 4;
    e->f80 = 18;
    e->blklen = (e->f80 - 2) * 8 / e->f84;
    e->f96 = 0x7fff0000;
    e->f100 = 500;
    e->nsmpl = 0;
    e->f108 = 0;
    e->f112 = 0;
    e->f116 = 0;
    e->f120 = 0;
    e->f124 = 0;
    e->f56 = 0;
    e->end = 0;
    e->f64 = ((e->f96 - 1) / e->blklen + 1) * e->blklen;
    e->flt[0] = pflt_create(e->blklen);
    e->flt[1] = pflt_create(e->blklen);
    e->first1[0] = e->first2[0] = 0;
    e->first1[1] = e->first2[1] = 0;
    e->has_name = 0;
    e->f744 = 0;
    e->f746[0] = -128;
    e->f746[1] = -128;
    memset(e->name, 0, 16);
    e->used = 1;
    return e;
}

/* matching construct: statement-order sweep of the five trailing stores */
void ADXCRS_Lock(void);

void ADXSJE_Destroy(AdxEnc *e)
{
    if (e == 0) {
        return;
    }
    ADXCRS_Lock();
    if (e->flt[0] != 0) {
        pflt_destroy(e->flt[0]);
    }
    if (e->flt[1] != 0) {
        pflt_destroy(e->flt[1]);
    }
    /* matching construct: hand search — the four status bytes are cleared together, one word store */
    memset(e, 0, 4);
    ADXCRS_Unlock();
}

void ADXSJE_Start(AdxEnc *x)
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

int ADXSJE_GetStat(AdxEnc *e)
{
    return e->stat;
}

void ADXSJE_Stop(AdxEnc *e)
{
    e->ended = 1;
}

void ADXSJE_SetSfreq(AdxEnc *e, int v)
{
    e->f92 = v;
}

void ADXSJE_SetHdInfoSize(AdxEnc *e, int v)
{
    e->hdrsize = v;
}

void ADXSJE_SetNumChan(AdxEnc *e, int v)
{
    e->nch = v;
}

void ADXSJE_SetOutBps(AdxEnc *e, int v)
{
    e->f84 = v;
}

void ADXSJE_SetBlkSmpl(AdxEnc *e, int blklen)
{
    e->blklen = blklen;
    if (e->flt[0] != 0) {
        pflt_destroy(e->flt[0]);
    }
    e->flt[0] = pflt_create(e->blklen);
    if (e->flt[1] != 0) {
        pflt_destroy(e->flt[1]);
    }
    e->flt[1] = pflt_create(e->blklen);
}

void ADXSJE_SetBlkLen(AdxEnc *e, int v)
{
    e->f80 = v;
}

void ADXSJE_SetTotalNumSmpl(AdxEnc *e, int v)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    e->end = v;
    e->f96 = v;
}

void ADXSJE_SetCof(AdxEnc *e, int v)
{
    e->f100 = v;
}

void ADXSJE_SetNumLoop(AdxEnc *e, int v)
{
    e->f108 = v;
}

void ADXSJE_SetLpInsNsmpl(AdxEnc *e, int v)
{
    e->nsmpl = v;
}

void ADXSJE_SetLpStartPos(AdxEnc *e, int v)
{
    e->f112 = v;
}

void ADXSJE_SetLpStartOfst(AdxEnc *e, int v)
{
    e->f116 = v;
}

void ADXSJE_SetLpEndPos(AdxEnc *e, int v)
{
    e->f120 = v;
}

void ADXSJE_SetLpEndOfst(AdxEnc *e, int v)
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

void FUN_00269828(AdxEnc *e, void *cinf, int len)
{
    if (e->cinf_flg != 1) {
        e->cinf_flg = 1;
        e->cinf = cinf;
        e->cinf_len = len;
        e->hdrsize += (len + 2047) / 2048 * 2048 + 4;
    }
}

void ADXSJE_SetConfigSfa(AdxEnc *e, int nch, int f92, int end)
{
    /* matching construct: permuter — the no-op a2++/a2-- raises a2's use count so ee-gcc gives it s0 (retail order s0=a2, s1=object, s2=a3) */
    f92++;
    f92--;
    ADXSJE_SetNumChan(e, nch);
    ADXSJE_SetSfreq(e, f92);
    ADXSJE_SetTotalNumSmpl(e, end);
    ADXSJE_SetHdInfoSize(e, 284);
}

void FUN_002698d8(AdxEnc *e, const char *text)
{
    unsigned short a, b, c;

    ADXKEY_GenerateKey(text, strlen(text), &a, &b, &c);
    e->key_x = a;
    e->key_mul = b;
    e->key_add = c;
}

int ADXSJE_GetEncDtLen(AdxEnc *e)
{
    return e->total;
}

int ADXSJE_GetEncNumSmpl(AdxEnc *e)
{
    return e->pos;
}

void ADXSJE_SetEncPos(AdxEnc *e, int v)
{
    e->pos = v;
}

int ADXSJE_GetEncPos(AdxEnc *e)
{
    return e->pos;
}

void ADXSJE_SetInSj(AdxEnc *e, unsigned int i, Sj *sj)
{
    if (i < 2) {
        e->in[i] = sj;
    }
}

void ADXSJE_SetOutSj(AdxEnc *e, Sj *sj)
{
    e->out = sj;
}

void adxsje_encode_prep(AdxEnc *e)
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
    n = adxsje_output_header(e, out);
    if (n == 0) {
        return;
    }
    e->total += n;
    for (i = 0; i < e->nch; i++) {
        pflt_calc_coef(e->flt[i], e->f100, e->f92);
    }
    e->stat = 2;
}

void adxsje_encode_exec(AdxEnc *e)
{
    int count;

    /* matching construct: goto — retail re-tests the ended flag after setting it; structured loops reorder the blocks */
loop:
    if (e->ended == 0) {
        while ((count = adxsje_encode_data(e)) != 0) {
            e->total += count;
            if (e->pos >= e->end) {
                e->ended = 1;
                goto loop;
            }
        }
        return;
    }
    if (adxsje_write_end_code(e) > 0) {
        e->stat = 3;
    }
}

void ADXSJE_ExecHndl(AdxEnc *e)
{
    if (e->stat == 1) {
        adxsje_encode_prep(e);
    } else if (e->stat == 2) {
        adxsje_encode_exec(e);
    }
}

void ADXSJE_ExecServer(void)
{
    int i;
    AdxEnc *e;

    e = DAT_004a5d70;
    i = 7;
    do {
        if (e->used == 1) {
            ADXSJE_ExecHndl(e);
        }
        i -= 1;
        e++;
    } while (i >= 0);
}

typedef struct AdxPdObj {
    char pad0[16];
    int nblk;
    char pad20[12];
    short *src;
    short *dst;
} AdxPdObj;

typedef struct AdxbBuf {
    int f0;
    int len;
    int nch;
    int f12;
    int blk;
    int f20;
    int top;
    int f28;
    int pos;
    int lim;
    int end;
} AdxbBuf;

typedef struct AdxbObj AdxbObj;
struct AdxbObj {
    short used;
    short f2;
    int stat;
    AdxPdObj *rna;
    signed char f12;
    signed char f13;
    signed char f14;
    signed char f15;
    int f16;
    int f20;
    int f24;
    short f28;
    short f30;
    int f32;
    short f36;
    short f38;
    int f40;
    int f44;
    int f48;
    int f52;
    int f56;
    int f60;
    int f64;
    int f68;
    AdxbBuf buf;
    int f116;
    int (*cb120)(AdxbObj *obj, int *a, int *b, int *c);
    AdxbObj *obj124;
    void (*cb128)(AdxbObj *obj, int a, int b);
    AdxbObj *obj132;
    int f136;
    int f140;
    int f144;
    int f148;
    short f152;
    unsigned short f154;
    short f156;
    short f158;
    short f160;
    short f162;
    short f164;
    short f166;
    short f168;
    short f170;
    int f172;
    int f176;
    int f180;
    char pad184[20];
    int f204;
    char f208[16];
    short f224;
    short f226[2];
    char pad230[2];
    int f232;
    char pad236[8];
    int f244;
    int f248;
    void (*f252)(void *context, int count, int bytes);
    void *f256;
};

extern void (*DAT_00498c6c)(AdxbObj *obj, int v, short *src, short *dst);
extern void (*DAT_00498c70)(void);
extern unsigned short DAT_00498c74;
extern unsigned short DAT_00498c76;
extern unsigned short DAT_00498c78;
extern AdxbObj DAT_00498c80[16];
extern char DAT_004ed848[];

void *memset(void *dst, int value, unsigned int size);
unsigned int strlen(const char *string);
int sprintf(char *dst, const char *format, ...);

void FUN_0025d078(void);
void FUN_0025d098(void);
void FUN_0025d0b8(const char *text, unsigned int length, unsigned short *first, unsigned short *second,
                  unsigned short *third);
void FUN_0026ee48(void);
void FUN_0026ee70(void);
AdxPdObj *FUN_0026ee98(void);
void FUN_0026f010(AdxPdObj *rna);
void FUN_0026efb8(AdxPdObj *rna, int *a, int *b);
void FUN_0026eff0(AdxPdObj *rna, short *a, short *b, short *c);
void FUN_0026ef90(AdxPdObj *rna, int *a, int *b);
void FUN_0026efe0(AdxPdObj *rna, int a, int b, int c);
int FUN_0025f588(unsigned short *hdr, int size, short *hdrlen, signed char *type, signed char *bits,
                 signed char *blksize, signed char *nch, int *rate, int *total, int *f16);
int FUN_0025f708(unsigned short *hdr, int size, unsigned char *ver, unsigned char *flag);
int FUN_0025f688(unsigned short *hdr, int size, short *out);
int FUN_0025f780(unsigned short *hdr, int size, int *a, int *b);
void FUN_0025f8b8(unsigned short *hdr, int size, int *f32, short *f36, short *f38, int *f40, int *f44, int *f48,
                  int *f52);
void FUN_0025fb18(unsigned short *hdr, int size, int *f204, char *f208, short *f224, short *f226);
void FUN_00260840(const char *code, const char *message);
void FUN_0026ef68(AdxPdObj *rna, int rate, int f28);
extern void (*DAT_00498c68)(int ahx, unsigned short *keys);
extern char DAT_004ed800[];
extern char DAT_004ed820[];

void FUN_0026f108(AdxPdObj *rna);
void FUN_0026f130(AdxPdObj *rna);
void FUN_0026f058(AdxPdObj *rna, int a, int b, int c, int d);
void FUN_0026f088(AdxPdObj *rna, int a, int b, int c, int d);
void FUN_0026f0b8(AdxPdObj *rna, int a, int b, int c, int d);
void FUN_0026f0e8(AdxPdObj *rna);
int FUN_0026f148(AdxPdObj *rna);
int FUN_0026f050(AdxPdObj *rna);
void FUN_0026f160(AdxPdObj *rna);
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);

int FUN_0025e9f8(unsigned short *hdr);
int FUN_0025e788(AdxbObj *dec, unsigned short *hdr, int size);
int FUN_0025f200(unsigned short *hdr);
int FUN_0025ec50(AdxbObj *dec, unsigned short *hdr, int size);
int FUN_0025bfd0(unsigned short *hdr);
int FUN_0025c148(AdxbObj *dec, unsigned short *hdr, int size);
int FUN_0025c8b8(unsigned short *hdr);
int FUN_0025ca20(AdxbObj *dec, unsigned short *hdr, int size);
int FUN_0025bac8(unsigned short *hdr);
int FUN_0025ba18(AdxbObj *dec, unsigned short *hdr, int size);

void FUN_0025bbe8(AdxbObj *obj);
void FUN_0025e880(AdxbObj *obj);
void FUN_0025c578(AdxbObj *obj);
void FUN_0025cfe0(AdxbObj *obj);
void FUN_0025f268(AdxbObj *obj);
void FUN_0025b9e8(AdxbObj *obj);

int FUN_0025d370(AdxbObj *obj, int *a, int *b, int *c);
void FUN_0025d4f8(AdxbObj *p);
void FUN_0025e018(AdxbObj *d);
int FUN_0025dcc8(AdxbObj *adx, unsigned char ver, unsigned char type, int name,
                 unsigned short *k0, unsigned short *k1, unsigned short *k2);
void FUN_0025e5a0(AdxbObj *obj);

void FUN_0025d300(void)
{
    FUN_0026ee48();
    FUN_0025d078();
    memset(DAT_00498c80, 0, 0x1040);
}

void FUN_0025d338(void)
{
    FUN_0026ee70();
    FUN_0025d098();
    memset(DAT_00498c80, 0, 0x1040);
}

void FUN_0025d3a0(AdxbObj *obj, int a, int b)
{
    obj->f140 += b;
    obj->f136 += b;
}

/* matching construct: store-order search over the eight stores, 117 of 150 steps */
AdxbObj *FUN_0025d3c0(int a0, int a1, int a2, int a3)
{
    AdxbObj *p;
    int i;
    for (i = 0; i < 16; i++) {
        if (DAT_00498c80[i].used == 0) {
            break;
        }
    }
    if (i == 16) {
        return 0;
    }
    p = &DAT_00498c80[i];
    memset(p, 0, sizeof(*p));
    p->used = 1;
    p->rna = FUN_0026ee98();
    if (p->rna == 0) {
        FUN_0025d4f8(p);
        return 0;
    }
    p->f56 = a0;
    p->f60 = a1;
    p->f64 = a2;
    p->f68 = a3;
    p->cb120 = FUN_0025d370;
    p->obj124 = p;
    p->obj132 = p;
    p->cb128 = FUN_0025d3a0;
    p->f204 = 0;
    p->f224 = 0;
    p->f226[0] = -128;
    p->f226[1] = -128;
    memset(p->f208, 0, 16);
    return p;
}

void FUN_0025d4f8(AdxbObj *rec)
{
    if (rec != 0) {
        AdxPdObj *handle = rec->rna;
        rec->rna = 0;
        FUN_0026f010(handle);
        memset(rec, 0, sizeof(*rec));
        rec->used = 0;
    }
}

int FUN_0025d540(AdxbObj *obj, unsigned short *hdr, int size)
{
    int a16[4];
    int a32[4];
    unsigned short keys[4];
    short hdrlen;
    unsigned char ver;
    unsigned char flag;
    short k0;
    short k1;
    short k2;
    obj->f2 = 1;
    if (FUN_0025f588(hdr, size, &hdrlen, &obj->f12, &obj->f13, &obj->f15, &obj->f14, &obj->f20, &obj->f24,
                     &obj->f16) < 0) {
        return 0;
    }
    if (obj->f12 >= 5) {
        if (obj->f180 == 0) {
            FUN_00260840(DAT_004ed800, DAT_004ed820);
            return -1;
        }
        obj->f13 = 8;
        obj->f15 = obj->f14 * 192;
        obj->f16 = 96;
        obj->f152 = 10;
        obj->f28 = 0;
        obj->f36 = 0;
        obj->f38 = 0;
        obj->f32 = 0;
        obj->f40 = 0;
        obj->f44 = 0;
        obj->f48 = 0;
        obj->f52 = 0;
        obj->f136 = 0;
        if (FUN_0025f708(hdr, size, &ver, &flag) < 0) {
            return 0;
        }
        keys[0] = 0;
        if (FUN_0025dcc8(obj, ver, flag, obj->f24, &keys[1], &keys[2], &keys[3]) < 0) {
            return -1;
        }
        if (DAT_00498c68 != 0) {
            DAT_00498c68(obj->f180, keys);
        }
    } else {
        if (FUN_0025f708(hdr, size, &ver, &flag) < 0) {
            return 0;
        }
        if (FUN_0025dcc8(obj, ver, flag, obj->f24, &k0, &k1, &k2) < 0) {
            return -1;
        }
        FUN_0026efe0(obj->rna, k0, k1, k2);
        if (FUN_0025f688(hdr, size, &obj->f28) < 0) {
            return 0;
        }
        if (FUN_0025f780(hdr, size, a16, a32) < 0) {
            return 0;
        }
        FUN_0026ef68(obj->rna, obj->f20, obj->f28);
        FUN_0026ef90(obj->rna, a16, a32);
        FUN_0025f8b8(hdr, size, &obj->f32, &obj->f36, &obj->f38, &obj->f40, &obj->f44, &obj->f48, &obj->f52);
        FUN_0025fb18(hdr, size, &obj->f204, obj->f208, &obj->f224, obj->f226);
        obj->f152 = 0;
    }
    obj->buf.nch = obj->f14;
    obj->buf.f12 = obj->f15;
    obj->buf.blk = obj->f16;
    obj->buf.f20 = obj->f60;
    obj->buf.top = obj->f64;
    obj->buf.f28 = obj->f68;
    obj->f140 = 0;
    return hdrlen;
}

void FUN_0025d830(AdxbObj *obj)
{
    obj->f154 = 0;
}

void FUN_0025d838(AdxbObj *block)
{
    block->f2 = 1;
    block->f20 = 48000;
    block->f14 = 2;
    block->f13 = 16;
    block->f24 = 0x7fffffff;
    block->f15 = 127;
    block->f16 = 1024;
    block->f152 = block->f154;
    block->buf.nch = 2;
    block->buf.f12 = 127;
    block->buf.blk = 1024;
    block->buf.f20 = block->f60;
    block->buf.top = block->f64;
    block->buf.f28 = block->f68;
    block->f140 = 0;
    block->f28 = 0;
    block->f36 = 0;
    block->f38 = 0;
    block->f32 = 0;
    block->f40 = 0;
    block->f44 = 0;
    block->f48 = 0;
    block->f52 = 0;
    block->f136 = 0;
}

#define SWAP16(x) ((unsigned short)(((x) << 8) | ((x) >> 8)))
int FUN_0025d8d8(AdxbObj *dec, unsigned short *hdr, int size)
{
    if (SWAP16(*hdr) == 0x8000) {
        return FUN_0025d540(dec, hdr, size);
    }
    if (FUN_0025e9f8(hdr) != 0) {
        return FUN_0025e788(dec, hdr, size);
    }
    if (FUN_0025f200(hdr) != 0) {
        return FUN_0025ec50(dec, hdr, size);
    }
    if (FUN_0025bfd0(hdr) != 0) {
        return FUN_0025c148(dec, hdr, size);
    }
    if (FUN_0025c8b8(hdr) != 0) {
        return FUN_0025ca20(dec, hdr, size);
    }
    if (FUN_0025bac8(hdr) != 0) {
        return FUN_0025ba18(dec, hdr, size);
    }
    return -1;
}

void FUN_0025da40(AdxbObj *obj, int (*cb)(AdxbObj *obj, int *a, int *b, int *c), AdxbObj *arg)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    obj->cb120 = cb;
    obj->obj124 = arg;
}

void FUN_0025da50(AdxbObj *obj, void (*cb)(AdxbObj *obj, int a, int b), AdxbObj *arg)
{
    obj->cb128 = cb;
    obj->obj132 = arg;
}

int FUN_0025da60(AdxbObj *obj)
{
    return obj->f60;
}

short FUN_0025da68(AdxbObj *obj)
{
    return obj->f152;
}

int FUN_0025da70(AdxbObj *obj)
{
    return obj->f20;
}

int FUN_0025da78(AdxbObj *obj)
{
    if (obj->f14 == 1 && obj->f232 != 0) {
        return 2;
    }
    return obj->f14;
}

char FUN_0025daa8(AdxbObj *obj)
{
    return obj->f13;
}

int FUN_0025dab0(AdxbObj *block)
{
    short mode = block->f152;
    if (mode == 0) {
        return 16;
    }
    if (mode == 2) {
        if (block->f156 == 2) {
            return 4;
        }
        if (block->f156 == 1) {
            return 8;
        }
        return 16;
    }
    if (mode == 1) {
        if (block->f156 == 2) {
            return 4;
        }
        return 16;
    }
    return 16;
}

int FUN_0025db10(AdxbObj *obj)
{
    return obj->f16;
}

char FUN_0025db18(AdxbObj *obj)
{
    return obj->f15;
}

int FUN_0025db20(AdxbObj *obj)
{
    return obj->f24;
}

short FUN_0025db28(AdxbObj *obj)
{
    return obj->f28;
}

int FUN_0025db30(AdxbObj *obj)
{
    return obj->f32;
}

short FUN_0025db38(AdxbObj *obj)
{
    return obj->f36;
}

int FUN_0025db40(AdxbObj *obj)
{
    return obj->f40;
}

int FUN_0025db48(AdxbObj *obj)
{
    int var_v0;
    var_v0 = 0;
    if (obj != 0) {
        var_v0 = obj->f44;
    }
    return var_v0;
}

int FUN_0025db60(AdxbObj *obj)
{
    return obj->f48;
}

int FUN_0025db68(AdxbObj *obj)
{
    return obj->f52;
}

int FUN_0025db70(AdxbObj *obj)
{
    return obj->f204;
}

short FUN_0025db78(AdxbObj *obj)
{
    return obj->f224;
}

short FUN_0025db80(int arg0, int arg1)
{
    arg1 *= 2;
    arg1 += arg0;
    return *(short *)((char *)arg1 + 226);
}

char *FUN_0025db90(AdxbObj *obj)
{
    return obj->f208;
}

void FUN_0025db98(AdxbObj *obj)
{
    FUN_0026efb8(obj->rna, &obj->f172, &obj->f176);
    FUN_0026eff0(obj->rna, &obj->f166, &obj->f168, &obj->f170);
}

void FUN_0025dbd8(AdxbObj *rec)
{
    FUN_0026ef90(rec->rna, &rec->f172, &rec->f176);
    FUN_0026efe0(rec->rna, rec->f166, rec->f168, rec->f170);
}

void FUN_0025dc18(AdxbObj *block, const char *text)
{
    unsigned short first;
    unsigned short second;
    unsigned short third;
    FUN_0025d0b8(text, strlen(text), &first, &second, &third);
    block->f160 = first;
    block->f162 = second;
    block->f164 = third;
}

void FUN_0025dc80(const char *text)
{
    FUN_0025d0b8(text, strlen(text), &DAT_00498c74, &DAT_00498c76, &DAT_00498c78);
}

int FUN_0025dcc8(AdxbObj *adx, unsigned char ver, unsigned char type, int name,
                 unsigned short *k0, unsigned short *k1, unsigned short *k2)
{
    char buf[16];
    if (ver < 4) {
        *k0 = 0;
        *k1 = 0;
        *k2 = 0;
    } else if (type >= 16) {
        sprintf(buf, DAT_004ed848, name);
        FUN_0025d0b8(buf, 8, k0, k1, k2);
    } else if (type >= 8) {
        if (adx->f160 == 0 && adx->f162 == 0 && adx->f164 == 0) {
            adx->f160 = DAT_00498c74;
            adx->f162 = DAT_00498c76;
            adx->f164 = DAT_00498c78;
        }
        *k0 = adx->f160;
        *k1 = adx->f162;
        *k2 = adx->f164;
    } else {
        *k0 = 0;
        *k1 = 0;
        *k2 = 0;
    }
    return 0;
}

int FUN_0025ddc8(AdxbObj *obj)
{
    return obj->stat;
}

void FUN_0025ddd0(AdxbObj *block, int buffer, int bytes)
{
    if (block->f152 == 0) {
        block->buf.f0 = buffer;
        block->buf.len = bytes / block->f15;
        block->f116 = 0;
    } else {
        block->buf.f0 = buffer;
        block->buf.len = bytes / (block->f13 / 8 * block->f14);
        block->f116 = 0;
    }
    block->f144 = 0;
    block->f148 = 0;
    block->f248 = 0;
    block->f244 = 0;
}

void FUN_0025de50(AdxbObj *obj)
{
    if (obj->stat == 0) {
        obj->stat = 1;
    }
}

void FUN_0025de68(AdxbObj *rec)
{
    if (rec->f232) {
        DAT_00498c70();
    }
    FUN_0026f108(rec->rna);
    rec->stat = 0;
}

void FUN_0025deb0(AdxbObj *obj)
{
    if (obj->stat == 3) {
        FUN_0026f130(obj->rna);
        obj->f140 = 0;
        obj->stat = 0;
    }
}

int FUN_0025def0(AdxbObj *obj)
{
    return obj->f148;
}

int FUN_0025def8(AdxbObj *obj)
{
    return obj->f144;
}

void FUN_0025df00(AdxbObj *obj, void (*cb)(void *context, int count, int bytes), void *context)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    obj->f252 = cb;
    obj->f256 = context;
}

AdxPdObj *FUN_0025df10(AdxbObj *obj)
{
    return obj->rna;
}

void FUN_0025df18(AdxbObj *obj, int n)
{
    AdxPdObj *temp_s0;
    AdxbBuf *temp_v0;
    temp_v0 = &obj->buf;
    temp_s0 = obj->rna;
    FUN_0026f058(temp_s0, obj->buf.f0, n, temp_v0->f20 + temp_v0->pos * 2, 0);
    FUN_0026f0e8(temp_s0);
}

void FUN_0025df68(AdxbObj *obj, int n)
{
    int temp_a3;
    AdxPdObj *temp_s0;
    AdxbBuf *temp_v1;
    temp_v1 = &obj->buf;
    temp_s0 = obj->rna;
    temp_a3 = temp_v1->f20 + temp_v1->pos * 2;
    FUN_0026f088(temp_s0, obj->buf.f0, n * 2, temp_a3, temp_a3 + temp_v1->f28 * 2);
    FUN_0026f0e8(temp_s0);
}

void FUN_0025dfc0(AdxbObj *obj, int n)
{
    int temp_a3;
    AdxPdObj *temp_s0;
    AdxbBuf *temp_v1;
    temp_v1 = &obj->buf;
    temp_s0 = obj->rna;
    temp_a3 = temp_v1->f20 + temp_v1->pos * 2;
    FUN_0026f0b8(temp_s0, obj->buf.f0, n, temp_a3, temp_a3 + temp_v1->f28 * 2);
    FUN_0026f0e8(temp_s0);
}

void FUN_0025e120(short *dst, short *src, int count)
{
    while (count > 0) {
        *dst++ = *src++;
        count--;
    }
}

void FUN_0025e150(short *buffer, int offset, int second, int count)
{
    FUN_0025e120(buffer, buffer + offset, count);
    FUN_0025e120(buffer + second, buffer + (second + offset), count);
}

void FUN_0025e1c0(short *buffer, int offset, int unused, int count)
{
    FUN_0025e120(buffer, buffer + offset, count);
}

/* matching construct: statement-order search, first step */
void FUN_0025e1e0(AdxbObj *d)
{
    AdxbBuf *b = &d->buf;
    int blk;
    int nch;
    int t;
    int r;
    int q;
    int done;
    int n;
    int pos;
    int size;
    int a;
    int f12;
    short *dst;
    blk = b->blk;
    t = b->end + blk - 1;
    size = d->f64;
    dst = (short *)b->f20;
    a = d->f68;
    f12 = b->f12;
    q = t / blk;
    r = blk - t % blk - 1;
    pos = b->pos;
    done = FUN_0026f148(d->rna);
    nch = b->nch;
    n = done * blk / nch;
    n = (done < q * nch) ? n : n - r;
    pos += n;
    d->f148 = done * f12;
    d->f144 = n;
    if (pos >= size) {
        pos -= size;
        if (b->nch == 2 || d->f232 != 0) {
            FUN_0025e150(dst, size, a, pos);
        } else {
            FUN_0025e1c0(dst, size, a, pos);
        }
    }
}

void FUN_0025e368(AdxbObj *w)
{
    AdxPdObj *rna;
    int i;
    if (w->stat == 1) {
        if (FUN_0026f050(w->rna) == 0) {
            w->cb120(w->obj124, &w->buf.pos, &w->buf.lim, &w->buf.end);
            FUN_0025e018(w);
            w->stat = 2;
        }
    }
    if (w->stat == 2) {
        FUN_0026f160(w->rna);
        if (FUN_0026f050(w->rna) == 3) {
            if (w->f232 != 0) {
                rna = w->rna;
                FUN_0025f2d0();
                for (i = 0; i < rna->nblk * 32; i++) {
                    DAT_00498c6c(w, rna->src[i], &rna->src[i], &rna->dst[i]);
                }
                FUN_0025f2e8();
            }
            FUN_0025e1e0(w);
            FUN_0026f130(w->rna);
            w->cb128(w->obj132, w->f148, w->f144);
            w->stat = 3;
        }
    }
}

void FUN_0025e4b8(AdxbObj *v)
{
    if (v->f152 == 0) {
        FUN_0025e368(v);
    } else if (v->f152 == 10) {
        FUN_0025bbe8(v);
    } else if (v->f152 == 2) {
        FUN_0025e880(v);
    } else if (v->f152 == 3) {
        FUN_0025c578(v);
    } else if (v->f152 == 4) {
        FUN_0025cfe0(v);
    } else if (v->f152 == 1) {
        FUN_0025f268(v);
    } else if (v->f152 == 15) {
        FUN_0025b9e8(v);
    }
    if (v->f252 != 0) {
        FUN_0025e5a0(v);
    }
}

void FUN_0025e5a0(AdxbObj *block)
{
    int frames;
    int count = block->f148 - block->f244;
    frames = block->f144; /* matching construct: permuter — f144 read into a local before the wrap test */
    if (count < 0) {
        count += 0x7fffffff;
    }
    block->f252(block->f256, count, frames * block->f14 * 2);
    block->f244 = block->f148;
}

void FUN_0025e608(void)
{
    AdxbObj *slot = DAT_00498c80;
    int remaining = 15;
    do {
        if (slot->used == 1) {
            FUN_0025e4b8(slot);
        }
        remaining--;
        slot++;
    } while (remaining >= 0);
}

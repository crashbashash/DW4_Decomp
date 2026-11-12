extern int FUN_001f8b50();
extern int FUN_001fffb0();
extern int FUN_00200980();
extern int FUN_00201a90();
extern int FUN_00204ea0();
extern int p2DirtyFlags[4];
extern int DAT_00568e50[4];
extern int DAT_0056b3b0[4];
extern int DAT_0056b3b4[4];
extern int DAT_0056b3b8[4];
extern int DAT_0056b3c0[4];
extern int DAT_0056b448[4];
extern int DAT_0056b480[4];
extern long long DAT_0056b5a8[4];
extern long long DAT_0056b5b0[4];
extern long long DAT_0056b5b8[4];
extern long long DAT_0056b5c0[4];
extern long long DAT_0056b5c8[4];
extern long long DAT_0056b5d0[4];
extern long long DAT_0056b5d8[4];
extern long long DAT_0056b5e0[4];
extern long long DAT_0056b5e8[4];
extern long long DAT_0056b5f0[4];
extern int p2LightCalcPending[4];
extern int DAT_0056b608[4];
extern int DAT_0056ba00[16];
extern int DAT_0056ba20[4];
struct P { long long m0; long long m8; int p16; struct P *next; int sh; int count; int tab[1]; };
struct E { int w0; int w4; };
extern long long p2VertexArrayMask[4];
extern int DAT_00562da0[16];
extern int DAT_0056b490[4];
int FUN_001eadf0();
int FUN_001eb490(long long, int *, int);
int FUN_001eb500();
void *FUN_00203000();
extern int DAT_004915a8[4];
extern int DAT_0056ae40[4];
extern int DAT_0056b078[4];
extern int DAT_0056b080[4];
extern int DAT_0056b090[4];
extern int DAT_0056b098[4];
extern int DAT_0056b0a0[4];
extern int DAT_0056b0e0[4];
extern int DAT_0056b0e8[4];
extern int DAT_0056b0f0[4];
extern int DAT_0056b100[4];
extern int DAT_0056b110[4];
extern int DAT_0056b130[4];
extern int DAT_0056b160[4];
extern int DAT_0056b170[4];
extern int DAT_0056b1c0[4];
extern int DAT_0056b220[4];
extern int DAT_0056b260[4];
extern int DAT_0056b268[4];
extern int DAT_0056b270[4];
extern int DAT_0056b278[4];
extern int DAT_0056b290[4];
extern int DAT_0056b2d0[4];
extern int DAT_0056b2d4[4];
extern int DAT_0056b2d8[4];
extern int DAT_0056b2e8[4];
extern int DAT_0056b2f0[4];
extern int DAT_0056b2f4[4];
extern int DAT_0056b2f8[4];
extern int DAT_0056b308[4];
extern int DAT_0056b310[4];
extern int DAT_0056b330[4];
extern int DAT_0056b334[4];
extern int DAT_0056b338[4];
extern int DAT_0056b33c[4];
extern int DAT_0056b340[4];
extern int DAT_0056b344[4];
extern int DAT_0056b348[4];
extern int DAT_0056b34c[4];
extern int DAT_0056b350[4];
extern int DAT_0056b354[4];
extern int DAT_0056b358[4];
extern int DAT_0056b35c[4];
extern int DAT_0056b360[4];
extern int DAT_0056b364[4];
extern int DAT_0056b368[4];
extern int DAT_0056b36c[4];
extern int DAT_0056b370[4];
extern int DAT_0056b380[4];
extern int DAT_0056b3a0[4];
extern int DAT_0056b3e0[4];
extern int DAT_0056b400[4];
extern int DAT_0056b420[4];
extern int DAT_0056b430[4];
extern int DAT_0056b440[4];
extern int DAT_0056b44c[4];
extern void *DAT_0056b460[8];
extern int * DAT_0056b4a4[4];
extern int DAT_0056b4a8[4];
extern int * DAT_0056b4ac[4];
extern int DAT_0056b4b0[4];
extern int * DAT_0056b4b4[4];
extern int DAT_0056b4b8[4];
extern int * DAT_0056b4bc[4];
extern int DAT_0056b4c0[4];
extern int * DAT_0056b4c4[4];
extern int DAT_0056b4c8[4];
extern int * DAT_0056b4cc[4];
extern int DAT_0056b4d0[4];
extern int * DAT_0056b4d4[4];
extern int DAT_0056b4d8[4];
extern int * DAT_0056b4dc[4];
extern int * DAT_0056b4e4[4];
extern int DAT_0056b4e8[4];
extern int * DAT_0056b4ec[4];
extern int DAT_0056b500[4];
extern int * DAT_0056b504[4];
extern int * DAT_0056b50c[4];
extern int * DAT_0056b514[4];
extern int * DAT_0056b51c[4];
extern int DAT_0056b528[4];
extern int * DAT_0056b52c[4];
extern int DAT_0056b540[4];
extern int * DAT_0056b544[4];
extern int DAT_0056b550[4];
extern int * DAT_0056b554[4];
extern int DAT_0056b558[4];
extern int * DAT_0056b55c[4];
extern int DAT_0056b560[4];
extern int * DAT_0056b564[4];
extern int DAT_0056b578[4];
extern int * DAT_0056b57c[4];
extern int DAT_0056b580[4];
extern int * DAT_0056b584[4];
extern int DAT_0056b590[4];
extern int * DAT_0056b594[4];
extern int DAT_0056b600[4];
extern int DAT_0056b604[4];
extern unsigned int p2ProgramFlags[4];
extern int DAT_0056b058[4];
extern int DAT_0056b4f8[4];
extern int DAT_0056b530[4];
extern int DAT_0056b568[4];
int FUN_00330770();
void *FUN_00330730();
double sqrt(double);

void FUN_001ff3b0(int arg0) {
    int s;
    int f;
    int n, a;
    s = p2DirtyFlags[0] & arg0;
    if (s != 0) {
        DAT_0056b5a8[0] += 1;
    }
    if (DAT_00568e50[0] == 0) {
        if (s & 4) {
            DAT_0056b5c0[0] += 1;
            FUN_001f8b50();
            s = p2DirtyFlags[0] & arg0;
        }
        if (s & 0x193) {
            DAT_0056b608[0] = FUN_00204ea0();
            s = p2DirtyFlags[0] & arg0;
            if (DAT_0056b608[0] == 0 || (DAT_0056b608[0] == 1 && (s & 0x100))) {
                if (s & 0x10) {
                    FUN_001fffb0(DAT_0056b608[0]);
                    s |= 0x80;
                    p2DirtyFlags[0] |= 0x80;
                }
                if (s & 1) {
                    FUN_00200980();
                    s = p2DirtyFlags[0] & arg0;
                }
                if (s & 2) {
                    if (DAT_00568e50[0] == 0) {
                        f = DAT_0056b480[0];
                        a = f & 0x10;
                        n = 0;
                        if (a && (f & 0x20)) {
                            n++;
                            DAT_0056ba00[0] = DAT_0056b3b8[0];
                        } else if (f & 0x20) {
                            n++;
                            DAT_0056ba00[0] = DAT_0056b3b4[0];
                        } else if (a) {
                            n++;
                            DAT_0056ba00[0] = DAT_0056b3b0[0];
                        }
                        if (f & 0x40) {
                            DAT_0056ba00[n] = DAT_0056b3c0[0];
                            n++;
                        }
                        if (f & 0x1C00) {
                            DAT_0056ba00[n] = DAT_0056b3c0[(f & 0x1C00) >> 10];
                            n++;
                        }
                        DAT_0056ba00[n] = DAT_0056b448[0];
                        DAT_0056ba20[0] = n + 1;
                        if (DAT_0056ba20[0] > 1) {
                            p2LightCalcPending[0] = 1;
                        } else {
                            p2LightCalcPending[0] = 0;
                        }
                    }
                }
                if (s & 0x80) {
                    FUN_00201a90();
                }
            }
        }
        if (s & 1) DAT_0056b5b0[0] += 1;
        if (s & 2) DAT_0056b5b8[0] += 1;
        if (s & 0x10) DAT_0056b5d0[0] += 1;
        if (s & 0x80) DAT_0056b5e8[0] += 1;
        if (s & 8) DAT_0056b5c8[0] += 1;
        if (s & 0x100) DAT_0056b5f0[0] += 1;
        if (s & 0x40) DAT_0056b5e0[0] += 1;
        if (s & 0x20) DAT_0056b5d8[0] += 1;
    }
}

typedef struct GsPacketBuffer { char pad0[40]; unsigned int *end; unsigned int pad44; unsigned int *cursor; } GsPacketBuffer;
typedef union VifCode { unsigned int word; unsigned short imm; } VifCode;
typedef struct GifTag {
    unsigned long long NLOOP:15;
    unsigned long long EOP:1;
    unsigned long long pad16:16;
    unsigned long long id:14;
    unsigned long long PRE:1;
    unsigned long long PRIM:11;
    unsigned long long FLG:2;
    unsigned long long NREG:4;
    unsigned long long REGS;
} GifTag;
extern GsPacketBuffer *DAT_00568f04;
void FUN_001ee600();
void p2SubmitDmaPacket();
extern int DAT_00491480;
extern int DAT_00490d38;
extern int DAT_00569308;
extern int p2CurrentProgram;
extern char *DAT_0056ad80;
extern unsigned int DAT_004914f0, DAT_004914f4, DAT_004914f8, DAT_004914fc;
extern VifCode DAT_00491500;
extern GifTag DAT_00491510, DAT_00491520, DAT_00491530;
extern __int128 DAT_0056b760, DAT_0056b770;

static inline int remap(int prim) {
    if (prim == 9) {
        return 3;
    } else if (prim == 8) {
        return 4;
    } else if (prim == 7) {
        return 4;
    }
    return prim;
}

void FUN_001ffcf0(void) {
    int texPrim;
    int prim;
    unsigned int *p;
    int flag;
    GifTag *tag;
    int bits;

    p = DAT_00568f04->cursor;
    prim = DAT_00491480;
    if (prim == 0) {
        texPrim = 0;
        prim = 0;
    } else if (prim == 1 || prim == 2) {
        texPrim = 1;
    } else if (prim == 6) {
        if (DAT_00569308 != 0) {
            prim = 3;
            texPrim = 5;
        } else {
            texPrim = 6;
            prim = 6;
        }
    } else if (DAT_00490d38 == 0) {
        texPrim = 0;
        prim = 0;
    } else if (DAT_00490d38 == 1) {
        texPrim = 2;
        prim = 2;
    } else {
        prim = remap(prim);
        texPrim = 5;
    }
    flag = (p2ProgramFlags[p2CurrentProgram] >> 23) & 1;
    DAT_00491500.imm = 24;
    if (DAT_0056b490[0] & 0x100) {
        tag = &DAT_00491520;
    } else {
        tag = &DAT_00491530;
    }
    if (flag) {
        bits = *(int *)(DAT_0056ad80 + 160) & 0x7F8;
        texPrim |= bits;
        prim |= bits;
    }
    DAT_00491510.PRIM = texPrim;
    tag->PRIM = prim;
    p[0] = DAT_004914f0;
    p[1] = DAT_004914f4;
    p[2] = DAT_004914f8;
    p[3] = DAT_004914fc;
    p[4] = DAT_00491500.word;
    p[5] = ((unsigned int *)tag)[0];
    p[6] = ((unsigned int *)tag)[1];
    p[7] = ((unsigned int *)tag)[2];
    DAT_00491500.imm++;
    p[8] = DAT_00491500.word;
    p[9] = ((unsigned int *)&DAT_00491510)[0];
    p[10] = ((unsigned int *)&DAT_00491510)[1];
    p[11] = ((unsigned int *)&DAT_00491510)[2];
    DAT_0056b760 = ((__int128 *)p)[1];
    DAT_0056b770 = ((__int128 *)p)[2];
    DAT_00568f04->cursor = p + 12;
    if (DAT_00568f04->cursor >= DAT_00568f04->end) {
        if (DAT_00568e50[0] != 0) {
            FUN_001ee600();
        } else {
            p2SubmitDmaPacket(1);
        }
    }
}

int FUN_00200830(struct P *p, long long *out) {
    extern struct E DAT_0056b4a0[16];
    int res = 0;
    long long m;
    int i;
    int j;
    int w;
    int k;
    int f;
    int lo;
    int hi;
    struct E *e;
    for (; p != 0; p = p->next) {
        m = p->m0;
        if (m == (m & p2VertexArrayMask[0])) {
            if (!(p->m8 & p2VertexArrayMask[0])) {
                for (i = 0; i < 32; i++) {
                    if (m & (1LL << i)) break;
                }
                j = 32;
                for (; j > 0; j--) {
                    if (m & (1LL << j)) break;
                }
                e = &DAT_0056b4a0[i];
                w = e->w0 | (DAT_0056b4a0[j].w0 << p->sh);
                k = p->tab[w];
                if (k != -1) {
                    e->w0 = w;
                    e->w4 = (int)p->tab;
                    *out &= ~p->m0 | (1LL << i);
                    f = *(int *)((char *)DAT_00562da0 + (k << 6) + 40);
                    lo = f & 0x30;
                    if (lo != 0) {
                        DAT_0056b480[0] = (DAT_0056b480[0] & 0x1cc0) | lo;
                    }
                    hi = f & 0x300;
                    if (hi != 0) {
                        DAT_0056b490[0] = hi;
                    }
                    res = 1;
                }
            }
        }
    }
    return res;
}

void FUN_00202300(void) {
    void *FUN_00202f60(void *, long long);
    int FUN_00202fa0(long long);
    extern int DAT_0056b4a0[4];
    int *temp_v0;
    int *temp_v0_10;
    int *temp_v0_11;
    int *temp_v0_12;
    int *temp_v0_13;
    int *temp_v0_14;
    int *temp_v0_15;
    int *temp_v0_16;
    int *temp_v0_17;
    int *temp_v0_18;
    int *temp_v0_19;
    int *temp_v0_20;
    int *temp_v0_21;
    int *temp_v0_22;
    int *temp_v0_23;
    int *temp_v0_24;
    int *temp_v0_25;
    int *temp_v0_2;
    int *temp_v0_3;
    int *temp_v0_4;
    int *temp_v0_5;
    int *temp_v0_6;
    int *temp_v0_7;
    int *temp_v0_8;
    int *temp_v0_9;
    int temp_v0_26;
    int var_a0;
    int var_a1;
    int var_a1_10;
    int var_a1_11;
    int var_a1_12;
    int var_a1_13;
    int var_a1_14;
    int var_a1_15;
    int var_a1_16;
    int var_a1_17;
    int var_a1_18;
    int var_a1_19;
    int var_a1_20;
    int var_a1_21;
    int var_a1_22;
    int var_a1_23;
    int var_a1_24;
    int var_a1_2;
    int var_a1_3;
    int var_a1_4;
    int var_a1_5;
    int var_a1_6;
    int var_a1_7;
    int var_a1_8;
    int var_a1_9;
    int var_s3;
    long long temp_s5;
    char *temp_s4;
    void *var_s2;
    void **temp_s1;
    int var_s0;
    void *var_v0;

    var_a1 = 0;
    DAT_0056b090[0] = -1;
    DAT_0056b098[0] = -1;
    DAT_0056b0e0[0] = -1;
    DAT_0056b0e8[0] = -1;
    do {
        temp_v0 = (int *)(&(&DAT_0056b0f0[0])[var_a1]);
        *temp_v0 = -1;
        var_a1 += 1;
    } while (var_a1 < 2);
    var_a1_2 = 0;
    do {
        temp_v0_2 = (int *)(&(&DAT_0056b100[0])[var_a1_2]);
        *temp_v0_2 = -1;
        var_a1_2 += 1;
    } while (var_a1_2 < 4);
    var_a1_3 = 0;
    DAT_0056b078[0] = -1;
    do {
        temp_v0_3 = (int *)(&(&DAT_0056b080[0])[var_a1_3]);
        *temp_v0_3 = -1;
        var_a1_3 += 1;
    } while (var_a1_3 < 4);
    var_a1_4 = 0;
    do {
        temp_v0_4 = (int *)(&(&DAT_0056b110[0])[var_a1_4]);
        *temp_v0_4 = -1;
        var_a1_4 += 1;
    } while (var_a1_4 < 8);
    var_a1_5 = 0;
    do {
        temp_v0_5 = (int *)(&(&DAT_0056b160[0])[var_a1_5]);
        *temp_v0_5 = -1;
        var_a1_5 += 1;
    } while (var_a1_5 < 2);
    var_a1_6 = 0;
    do {
        temp_v0_6 = (int *)(&(&DAT_0056b130[0])[var_a1_6]);
        *temp_v0_6 = -1;
        var_a1_6 += 1;
    } while (var_a1_6 < 0xB);
    var_a1_7 = 0;
    do {
        temp_v0_7 = (int *)(&(&DAT_0056b1c0[0])[var_a1_7]);
        *temp_v0_7 = -1;
        var_a1_7 += 1;
    } while (var_a1_7 < 0x16);
    var_a1_8 = 0;
    do {
        temp_v0_8 = (int *)(&(&DAT_0056b170[0])[var_a1_8]);
        *temp_v0_8 = -1;
        var_a1_8 += 1;
    } while (var_a1_8 < 0x14);
    var_a1_9 = 0;
    do {
        temp_v0_9 = (int *)(&(&DAT_0056b220[0])[var_a1_9]);
        *temp_v0_9 = -1;
        var_a1_9 += 1;
    } while (var_a1_9 < 0x10);
    var_a1_10 = 0;
    DAT_0056b260[0] = -1;
    do {
        temp_v0_10 = (int *)(&(&DAT_0056b268[0])[var_a1_10]);
        *temp_v0_10 = -1;
        var_a1_10 += 1;
    } while (var_a1_10 < 2);
    var_a1_11 = 0;
    DAT_0056b270[0] = -1;
    do {
        temp_v0_11 = (int *)(&(&DAT_0056b278[0])[var_a1_11]);
        *temp_v0_11 = -1;
        var_a1_11 += 1;
    } while (var_a1_11 < 3);
    var_a1_12 = 0;
    do {
        temp_v0_12 = (int *)(&(&DAT_0056b290[0])[var_a1_12]);
        *temp_v0_12 = -1;
        var_a1_12 += 1;
    } while (var_a1_12 < 0xE);
    var_a1_13 = 0;
    do {
        temp_v0_13 = (int *)(&(&DAT_0056b2d0[0])[var_a1_13]);
        *temp_v0_13 = -1;
        var_a1_13 += 1;
    } while (var_a1_13 < 0x10);
    var_a1_14 = 0;
    do {
        temp_v0_14 = (int *)(&(&DAT_0056b310[0])[var_a1_14]);
        *temp_v0_14 = -1;
        var_a1_14 += 1;
    } while (var_a1_14 < 8);
    var_a1_15 = 0;
    do {
        temp_v0_15 = (int *)(&(&DAT_0056b330[0])[var_a1_15]);
        *temp_v0_15 = -1;
        var_a1_15 += 1;
    } while (var_a1_15 < 0x10);
    var_a1_16 = 0;
    do {
        temp_v0_16 = (int *)(&(&DAT_0056b370[0])[var_a1_16]);
        *temp_v0_16 = -1;
        var_a1_16 += 1;
    } while (var_a1_16 < 2);
    var_a1_17 = 0;
    do {
        temp_v0_17 = (int *)(&(&DAT_0056b3a0[0])[var_a1_17]);
        *temp_v0_17 = -1;
        var_a1_17 += 1;
    } while (var_a1_17 < 2);
    var_a1_18 = 0;
    do {
        temp_v0_18 = (int *)(&(&DAT_0056b380[0])[var_a1_18]);
        *temp_v0_18 = -1;
        var_a1_18 += 1;
    } while (var_a1_18 < 8);
    var_a1_19 = 0;
    do {
        temp_v0_19 = (int *)(&(&DAT_0056b3b0[0])[var_a1_19]);
        *temp_v0_19 = -1;
        var_a1_19 += 1;
    } while (var_a1_19 < 0xB);
    var_a1_20 = 0;
    do {
        temp_v0_20 = (int *)(&(&DAT_0056b440[0])[var_a1_20]);
        *temp_v0_20 = -1;
        var_a1_20 += 1;
    } while (var_a1_20 < 8);
    var_a1_21 = 0;
    do {
        temp_v0_21 = (int *)(&(&DAT_0056b3e0[0])[var_a1_21]);
        *temp_v0_21 = -1;
        var_a1_21 += 1;
    } while (var_a1_21 < 8);
    var_a1_22 = 0;
    do {
        temp_v0_22 = (int *)(&(&DAT_0056b400[0])[var_a1_22]);
        *temp_v0_22 = -1;
        var_a1_22 += 1;
    } while (var_a1_22 < 8);
    var_a1_23 = 0;
    do {
        temp_v0_23 = (int *)(&(&DAT_0056b420[0])[var_a1_23]);
        *temp_v0_23 = -1;
        var_a1_23 += 1;
    } while (var_a1_23 < 4);
    var_a1_24 = 0;
    do {
        temp_v0_24 = (int *)(&(&DAT_0056b430[0])[var_a1_24]);
        *temp_v0_24 = -1;
        var_a1_24 += 1;
    } while (var_a1_24 < 3);
    DAT_0056b4d8[0] = 0;
    DAT_0056b4dc[0] = (int *)(&DAT_0056b130[0]);
    DAT_0056b50c[0] = (int *)(&DAT_0056b160[0]);
    DAT_0056b514[0] = (int *)(&DAT_0056b1c0[0]);
    DAT_0056b4e4[0] = (int *)(&DAT_0056b170[0]);
    DAT_0056b51c[0] = (int *)(&DAT_0056b220[0]);
    DAT_0056b4a4[0] = (int *)(&DAT_0056b078[0]);
    DAT_0056b4ac[0] = (int *)(&DAT_0056b080[0]);
    DAT_0056b4b4[0] = (int *)(&DAT_0056b110[0]);
    DAT_0056b4bc[0] = (int *)(&DAT_0056b090[0]);
    DAT_0056b4c4[0] = (int *)(&DAT_0056b098[0]);
    DAT_0056b4d4[0] = (int *)(&DAT_0056b0e0[0]);
    DAT_0056b4ec[0] = (int *)(&DAT_0056b0e8[0]);
    DAT_0056b504[0] = (int *)(&DAT_0056b100[0]);
    DAT_0056b52c[0] = (int *)(&DAT_0056b268[0]);
    DAT_0056b544[0] = (int *)(&DAT_0056b270[0]);
    DAT_0056b564[0] = (int *)(&DAT_0056b278[0]);
    DAT_0056b554[0] = (int *)(&DAT_0056b2d0[0]);
    DAT_0056b55c[0] = (int *)(&DAT_0056b310[0]);
    DAT_0056b584[0] = (int *)(&DAT_0056b3a0[0]);
    DAT_0056b57c[0] = (int *)(&DAT_0056b380[0]);
    DAT_0056b590[0] = 4;
    DAT_0056b594[0] = (int *)(&DAT_0056b440[0]);
    DAT_0056b4cc[0] = (int *)(&DAT_0056b0a0[0]);
    DAT_0056b4a0[0] = 0;
    DAT_0056b4a8[0] = 0;
    DAT_0056b4b0[0] = 0;
    DAT_0056b4b8[0] = 0;
    DAT_0056b4c0[0] = 0;
    DAT_0056b4d0[0] = 0;
    DAT_0056b4e8[0] = 0;
    DAT_0056b500[0] = 0;
    DAT_0056b528[0] = 0;
    DAT_0056b540[0] = 0;
    DAT_0056b560[0] = 0;
    DAT_0056b550[0] = 0;
    DAT_0056b558[0] = 0;
    DAT_0056b580[0] = 0;
    DAT_0056b578[0] = 0;
    DAT_0056b4c8[0] = 0;
    FUN_001eb490(1, &DAT_0056b078[0], 1);
    FUN_001eb490(2, &DAT_0056b080[0], 4);
    FUN_001eb490(4, &DAT_0056b110[0], 8);
    FUN_001eb490(8, &DAT_0056b090[0], 1);
    FUN_001eb490(0x10, &DAT_0056b098[0], 1);
    FUN_001eb490(0x40, &DAT_0056b0e0[0], 1);
    FUN_001eb490(0x20, &DAT_0056b0a0[0], 0x10);
    FUN_001eb490(0x200, &DAT_0056b0e8[0], 1);
    FUN_001eb490(0x800, &DAT_0056b0f0[0], 2);
    FUN_001eb490(0x1000, &DAT_0056b100[0], 4);
    FUN_001eb490(4, &DAT_0056b110[0], 8);
    FUN_001eb490(0x2000, &DAT_0056b160[0], 2);
    FUN_001eb490(0x80, &DAT_0056b130[0], 0xB);
    FUN_001eb490(0x4000, &DAT_0056b1c0[0], 0x16);
    FUN_001eb490(0x100, &DAT_0056b170[0], 0x14);
    FUN_001eb490(0x8000, &DAT_0056b220[0], 0x10);
    FUN_001eb490(0x40000, &DAT_0056b260[0], 1);
    FUN_001eb490(0x20000, &DAT_0056b268[0], 2);
    FUN_001eb490(0x100000, &DAT_0056b270[0], 1);
    FUN_001eb490(0x01000000, &DAT_0056b278[0], 3);
    FUN_001eb490(0x80000, &DAT_0056b290[0], 0xE);
    FUN_001eb490(0x400000, &DAT_0056b2d0[0], 0x10);
    FUN_001eb490(0x800000, &DAT_0056b310[0], 8);
    FUN_001eb490(0x02000000, &DAT_0056b330[0], 0x10);
    FUN_001eb490(0x04000000, &DAT_0056b370[0], 2);
    FUN_001eb490(0x10000000, &DAT_0056b3a0[0], 2);
    FUN_001eb490(0x08000000, &DAT_0056b380[0], 8);
    FUN_001eb490(0x20000000, &DAT_0056b3b0[0], 0xB);
    FUN_001eb490(0x40000000, &DAT_0056b440[0], 8);
    FUN_001eb490(0x400, &DAT_0056b3e0[0], 8);
    FUN_001eb490(0x10000, &DAT_0056b400[0], 8);
    FUN_001eb490(0x200000, &DAT_0056b420[0], 4);
    FUN_001eb490(0x80000000LL, &DAT_0056b430[0], 3);
    DAT_0056ae40[0] = DAT_0056b440[0];
    DAT_0056b2f0[0] = DAT_0056b2d0[0];
    DAT_0056b2f4[0] = DAT_0056b2d4[0];
    DAT_0056b2f8[0] = DAT_0056b2d8[0];
    DAT_0056b308[0] = DAT_0056b2e8[0];
    DAT_0056b360[0] = DAT_0056b350[0] = DAT_0056b340[0] = DAT_0056b330[0];
    DAT_0056b344[0] = DAT_0056b334[0];
    DAT_0056b348[0] = DAT_0056b338[0];
    DAT_0056b34c[0] = DAT_0056b33c[0];
    DAT_0056b354[0] = DAT_0056b334[0];
    DAT_0056b364[0] = DAT_0056b334[0];
    DAT_0056b358[0] = DAT_0056b338[0];
    DAT_0056b368[0] = DAT_0056b338[0];
    DAT_0056b35c[0] = DAT_0056b33c[0];
    DAT_0056b36c[0] = DAT_0056b33c[0];
    if (DAT_004915a8[0] != 0) {
        DAT_0056b600[0] = FUN_001eadf0(DAT_0056b448[0], DAT_0056b334[0], DAT_0056b2d0[0], DAT_0056b440[0]);
        DAT_0056b604[0] = FUN_001eadf0(DAT_0056b44c[0]);
        var_a0 = 0;
        do {
            temp_v0_25 = (int *)((char *)DAT_0056b460 + (var_a0 * 4));
            var_a0 += 1;
            *temp_v0_25 = 0;
        } while (var_a0 < 6);
        DAT_004915a8[0] = 0;
    }
    var_s3 = 0;
    var_s0 = 0;
    do {
        var_s2 = 0;
        temp_s1 = (void **)((char *)DAT_0056b460 + (var_s0 * 4));
        while ((var_s3 = FUN_001eb500(var_s0 + 2, var_s3)) != 0) {
            temp_s4 = (char *)DAT_00562da0 + (var_s3 << 6);
            temp_s5 = FUN_00202fa0(*(long long *)((char *)(temp_s4) + 0));
            var_v0 = (void *)(FUN_00202f60(*temp_s1, *(long long *)((char *)(temp_s4) + 0)));
            if (var_v0 == 0) {
                var_v0 = (void *)(FUN_00203000(var_s3));
                if (var_v0 != 0) {
                    *(long long *)((char *)(var_v0) + 8) = temp_s5;
                    if (var_s2 != 0) {
                        *(int *)((char *)(var_s2) + 20) = (int)(var_v0);
                    }
                    var_s2 = (void *)(var_v0);
                    if (*temp_s1 == 0) {
                        *temp_s1 = var_v0;
                    }
                }
            }
            *(int *)((char *)(((char *)var_v0 + (((unsigned int) (*(int *)((char *)(temp_s4) + 40) & 0xFFFF0000) >> 0x10) * 4))) + 32) = var_s3;
            var_s3 += 1;
        }
        var_s0 += 1;
    } while (var_s0 < 6);
}

int FUN_00202e20(int arg0) {
    int temp_a1;
    int temp_a2;
    int var_v0;

    var_v0 = 0;
    if (DAT_0056b058[0] < arg0) {
        return 0;
    }
    temp_a2 = ((unsigned int) p2ProgramFlags[0] >> 6) & 1;
    temp_a1 = ((unsigned int) p2ProgramFlags[0] >> 0xF) & 3;
    if (arg0 == 1) {
        if (p2VertexArrayMask[0] & 0x400) {
            return FUN_001eadf0(DAT_0056b0f0[DAT_0056b4f8[0]], temp_a1, temp_a2);
        }
        goto block_6;
    }
block_6:
    if ((arg0 == 1) && (p2VertexArrayMask[0] & 0x10000)) {
        return FUN_001eadf0(DAT_0056b260[DAT_0056b530[0]], temp_a1, temp_a2);
    }
    if ((temp_a2 != 0) || (temp_a1 != 0)) {
        return FUN_001eadf0(DAT_0056b2d0[DAT_0056b550[0]], temp_a1, temp_a2);
    }
    if (p2VertexArrayMask[0] & 0x210400) {
        var_v0 = FUN_001eadf0(DAT_0056b330[DAT_0056b568[0]], temp_a1, temp_a2);
    }
    return var_v0;
}

int *FUN_00202f60(int *arg0, long long arg1) {
    for (; arg0 != 0; arg0 = (int *)arg0[5]) {
        if (arg1 == *(long long *)((char *)DAT_00562da0 + (arg0[4] << 6))) break;
    }
    return arg0;
}

long long FUN_00202fa0(int arg0) {
    int m;
    unsigned int i;
    int c;
    int j;
    int b;

    m = arg0;
    for (i = 0; i < 0x20U; i++) {
        b = 1 << i;
        if (arg0 & b) {
            break;
        }
        m |= b;
    }
    j = 0x1F;
    while (1) {
        c = 1 << j;
        if (arg0 & c) {
            break;
        }
        m |= c;
        j--;
    }
    return ~m;
}

void *FUN_00203000(int index) {
    struct P *p;
    int counts[32];
    int n;
    long long mask;
    int i;
    int total;
    int prev;

    n = 0;
    mask = *(long long *)((char *)DAT_00562da0 + (index << 6));
    if (mask & 1) counts[n++] = 1;
    if (mask & 2) counts[n++] = 4;
    if (mask & 4) counts[n++] = 8;
    if (mask & 8) counts[n++] = 1;
    if (mask & 0x40) counts[n++] = 1;
    if (mask & 0x20) counts[n++] = 0x10;
    if (mask & 0x80) counts[n++] = 0xB;
    if (mask & 0x200) counts[n++] = 1;
    if (mask & 0x800) counts[n++] = 2;
    if (mask & 0x1000) counts[n++] = 4;
    if (mask & 0x2000) counts[n++] = 2;
    if (mask & 0x100) counts[n++] = 0x14;
    if (mask & 0x4000) counts[n++] = 0x16;
    if (mask & 0x8000) counts[n++] = 0x10;
    if (mask & 0x40000) counts[n++] = 1;
    if (mask & 0x20000) counts[n++] = 2;
    if (mask & 0x100000) counts[n++] = 1;
    if (mask & 0x1000000) counts[n++] = 3;
    if (mask & 0x80000) counts[n++] = 0xE;
    if (mask & 0x800000) counts[n++] = 8;
    if (mask & 0x2000000) counts[n++] = 0x10;
    if (mask & 0x4000000) counts[n++] = 2;
    if (mask & 0x10000000) counts[n++] = 2;
    if (mask & 0x8000000) counts[n++] = 8;
    if (mask & 0x20000000) counts[n++] = 0xB;
    if (mask & 0x40000000) counts[n++] = 8;
    if (mask & 0x400) counts[n++] = 8;
    if (mask & 0x10000) counts[n++] = 8;
    if (mask & 0x200000) counts[n++] = 4;
    if (mask & 0x80000000LL) counts[n++] = 3;
    total = 1;
    prev = 0;
    for (i = 0; i < n; i++) {
        prev = total;
        total *= counts[i];
    }
    p = FUN_00330730(total * 4 + 0x28, 0x14);
    if (p != 0) {
        p->next = 0;
        p->m0 = *(long long *)((char *)DAT_00562da0 + (index << 6));
        p->m8 = 0;
        p->p16 = index;
        p->sh = sqrt(prev);
        p->count = total;
        for (i = 0; i < total; i++) {
            p->tab[i] = -1;
        }
    }
    return p;
}

void FUN_00203500(void) {
    int i;
    void *p;
    void *next;

    i = 0;
    do {
        p = DAT_0056b460[i];
        while (p != 0) {
            next = *(void **)((char *)p + 20);
            FUN_00330770(p, 0x14);
            p = next;
        }
        DAT_0056b460[i] = 0;
        i += 1;
    } while (i < 6);
}

typedef struct CriSjChunk {
    void *ptr;
    int len;
} CriSjChunk;

typedef struct Sj Sj;
typedef struct SjVtbl {
    void *pad0[3];
    void (*destroy)(Sj *sj);
    void *pad16[2];
    void (*get_chunk)(Sj *sj, int id, int nbyte, CriSjChunk *ck);
    void (*unget_chunk)(Sj *sj, int id, CriSjChunk *ck);
    void (*put_chunk)(Sj *sj, int id, CriSjChunk *ck);
} SjVtbl;
struct Sj {
    SjVtbl *vt;
};

typedef struct AdxEnc AdxEnc;

typedef struct AdxtObject {
    char pad0[20];
    Sj *sji;
} AdxtObject;

extern int DAT_0049c8d8;
extern int DAT_0049c8e0;
extern int DAT_0049c8e4;
extern int DAT_0049c8ec;
extern volatile int DAT_0049c8f0;
extern char DAT_0049d538[];
extern char DAT_0049d938[];
extern int DAT_004a9b1c;

void FUN_002607e8(const char *message);
int FUN_0026cbd8();
int ADXT_ExecFsSvr();
int LSC_ExecServer();
void *memcpy(void *dst, const void *src, unsigned int n);
void FUN_002632c0(void);
void FUN_0026b900(void);
void FUN_00265c18(void);
void FUN_00260b30(void);
void FUN_00269c98(void);
void FUN_00277918(void);
void FUN_0025f2d0(void);
void FUN_0027e6d0(int key, int value);
void FUN_0027ec50(void);
void FUN_00265f88(void);
void FUN_00260788(void);
void FUN_0027b390(void);
void FUN_0027bcd0(void);
void FUN_0027c810(void);
void FUN_0025f2e8(void);
void FUN_00269268(void);
void FUN_00269298(void);
AdxEnc *FUN_002692c8(int nch, Sj **out, Sj *in);
void FUN_00269878(AdxEnc *enc, int nch, int f92, int end);
void FUN_00269508(AdxEnc *enc);
void FUN_00269bd0(void);
void FUN_00269630(AdxEnc *enc);
void FUN_00269498(AdxEnc *enc);
Sj *FUN_0027bd48(void *buf, int size, int f8);
Sj *FUN_0027b408(void *buf, int size);

extern char *volatile DAT_0056dfa8;
extern char DAT_004ee080[];
extern int DAT_0049c8e8;
extern char DAT_0049c8f8[];
void *memset(void *dst, int value, unsigned int size);
int ADXCRS_Init();
int FUN_0027c798();
int FUN_0027bc58();
int FUN_0027b318();
int FUN_00260750();
int FUN_00269c60();
int FUN_00265f58();
int FUN_00260a60();
int FUN_00265c00();
int LSC_Init();
int FUN_0027ec10();
int FUN_00265c30();
int LSC_EntryErrFunc();
int ADXM_IsSetupThrd();
int FUN_0027e748();
int FUN_0027e600();
int FUN_0026c798();
void FUN_002631c8(int value) {
    DAT_0049c8e4 = value;
}

void FUN_002631d8(void *unused, const char *message) {
    FUN_002607e8(message);
}

void FUN_002631f0(void *unused, const char *message) {
    FUN_002607e8(message);
}

void FUN_00263208(void) {
    DAT_0049c8f0 += 1;
    FUN_0026cbd8();
}

int FUN_00263230(void *arg) {
    LSC_ExecServer();
    return 0;
}

int FUN_00263280(void *arg);
int FUN_002632a0(void *arg);

int FUN_00263250(void *arg) {
    FUN_00263280(0);
    FUN_002632a0(0);
    FUN_00263230(0);
    return 0;
}

int FUN_00263280(void *arg) {
    FUN_0026cbd8();
    return 0;
}

int FUN_002632a0(void *arg) {
    ADXT_ExecFsSvr();
    return 0;
}

void FUN_002632c0(void)
{
    DAT_0056dfa8 = DAT_004ee080;
    if (DAT_0049c8d8 == 0) {
        ADXCRS_Init();
        FUN_0025f2d0();
        FUN_0027c798();
        FUN_0027bc58();
        FUN_0027b318();
        FUN_00260750();
        FUN_00269c60();
        FUN_00265f58();
        FUN_00260a60();
        FUN_00265c00();
        LSC_Init();
        FUN_0027ec10();
        FUN_00265c30(FUN_002631d8, 0);
        LSC_EntryErrFunc(FUN_002631f0, 0);
        memset(DAT_0049c8f8, 0, 3136);
        if (ADXM_IsSetupThrd() == 1 && DAT_0049c8e4 == 1) {
            FUN_0027e748(2, 1, FUN_00263280, 0);
            DAT_0049c8ec = FUN_0027e600(4, FUN_002632a0, 0);
            DAT_0049c8e0 = FUN_0027e600(5, FUN_00263230, 0);
        } else {
            DAT_0049c8e0 = FUN_0027e600(5, FUN_00263250, 0);
        }
        DAT_0049c8f0 = 0;
        DAT_0049c8e8 = 0;
        FUN_0026c798(60);
        FUN_0025f2e8();
    }
    DAT_0049c8d8++;
}

void FUN_00263450(void) {
    DAT_0049c8d8 = 0;
    FUN_002632c0();
}

void FUN_00263470(void) {
    if (--DAT_0049c8d8 == 0) {
        DAT_004a9b1c = 0;
        FUN_0026b900();
        FUN_00265c18();
        FUN_00260b30();
        FUN_00269c98();
        FUN_00277918();
        FUN_0025f2d0();
        FUN_0027e6d0(2, 1);
        FUN_0027e6d0(4, DAT_0049c8ec);
        FUN_0027e6d0(5, DAT_0049c8e0);
        FUN_0027ec50();
        FUN_00265f88();
        FUN_00260788();
        FUN_0027b390();
        FUN_0027bcd0();
        FUN_0027c810();
        FUN_0025f2e8();
        DAT_004a9b1c = 1;
    }
}

void FUN_00263548(AdxtObject *adxt, int nch, int f92, int end)
{
    Sj *out[2];
    CriSjChunk ckIn;
    CriSjChunk ckOut;
    Sj *in;
    Sj *dst;
    AdxEnc *enc;
    FUN_00269268();
    in = FUN_0027bd48(DAT_0049d538, 1024, 0);
    out[0] = FUN_0027b408(DAT_0049d938, 32);
    out[1] = FUN_0027b408(DAT_0049d938 + 32, 32);
    dst = adxt->sji;
    enc = FUN_002692c8(2, out, in);
    FUN_00269878(enc, nch, f92, end);
    FUN_00269508(enc);
    FUN_00269bd0();
    in->vt->get_chunk(in, 1, 1024, &ckIn);
    if (ckIn.len == 0) {
        for (;;) {
        }
    }
    dst->vt->get_chunk(dst, 0, ckIn.len, &ckOut);
    if (ckOut.len < ckIn.len) {
        for (;;) {
        }
    }
    memcpy(ckOut.ptr, ckIn.ptr, ckIn.len);
    in->vt->put_chunk(in, 0, &ckIn);
    dst->vt->put_chunk(dst, 1, &ckOut);
    FUN_00269630(enc);
    FUN_00269498(enc);
    in->vt->destroy(in);
    out[1]->vt->destroy(out[1]);
    out[0]->vt->destroy(out[0]);
    FUN_00269298();
}

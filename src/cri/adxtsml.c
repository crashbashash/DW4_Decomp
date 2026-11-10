typedef struct AdxtSj AdxtSj;
typedef struct AdxtSjVtbl {
    void (*slot[6])(AdxtSj *self);
} AdxtSjVtbl;
struct AdxtSj {
    AdxtSjVtbl *vt;
};

typedef struct AdxtHandle {
    char f0;
    char f1;
    char state;
    char pad3[13];
    int f16;
    AdxtSj *sji;
    char pad24[38];
    short sectors;
    char pad64[84];
    void *stm;
    char pad152[24];
    int f176;
} AdxtHandle;

extern char DAT_004ee0d0[];
extern char DAT_004ee100[];
extern char DAT_004ee178[];
extern char DAT_004ee1a8[];
extern char DAT_004ee1d8[];
extern char DAT_004ee210[];
extern char DAT_004ee240[];
extern char DAT_004ee270[];

void FUN_002607e8(const char *message);
void FUN_00260840(const char *message, const char *detail);
int FUN_00277038(void *stm, const char *name, int ofst, int first, int last);
void FUN_00277278(void *stm);
void FUN_00277768(void *stm, int enable);
int FUN_002773d0(void *stm);
void FUN_002771d0(void *stm);
void FUN_00277210(void *stm);
void FUN_00277658(void *stm, int bytes);
void FUN_0026bbc0(void);
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void FUN_0026b978(AdxtHandle *adxt, int value);
void FUN_0026d158(AdxtHandle *adxt, int value);
void FUN_00263768(AdxtHandle *adxt, const char *name, int first, int last);
void FUN_002637d8(AdxtHandle *adxt, int afs, int fid);

void FUN_00263748(AdxtHandle *adxt, const char *name) {
    FUN_00263768(adxt, name, 0, 0xFFFFF);
}

void FUN_00263768(AdxtHandle *adxt, const char *name, int first, int last) {
    /* the file list is read before the null check (retail loads it in the branch delay slot) */
    void *stm = adxt->stm;
    if (adxt == 0) {
        FUN_002607e8(DAT_004ee0d0);
        return;
    }
    if (FUN_00277038(stm, name, 0, first, last) < 0) {
        FUN_00260840(DAT_004ee100, name);
    }
}

void FUN_002638a0(AdxtHandle *adxt) {
    void *stm = adxt->stm;
    AdxtSj *sji;
    if (adxt == 0) {
        FUN_002607e8(DAT_004ee178);
        return;
    }
    FUN_0026bbc0();
    FUN_0025f2d0();
    FUN_0026b978(adxt, adxt->f16);
    sji = adxt->sji;
    sji->vt->slot[5](sji);
    adxt->state = 4;
    FUN_00277658(stm, adxt->sectors << 11);
    FUN_0025f2e8();
    FUN_00277210(stm);
    FUN_0026d158(adxt, 1);
}

void FUN_00263950(AdxtHandle *adxt, int enable) {
    if (adxt == 0) {
        FUN_002607e8(DAT_004ee1a8);
        return;
    }
    FUN_00277768(adxt->stm, enable);
}

void FUN_002639a0(AdxtHandle *adxt, const char *name, int first, int last);

void FUN_00263980(AdxtHandle *adxt, const char *name)
{
    FUN_002639a0(adxt, name, 0, 0xfffff);
}

void FUN_002639a0(AdxtHandle *adxt, const char *name, int first, int last) {
    void *stm;
    if (adxt == 0 || name == 0) {
        FUN_002607e8(DAT_004ee1d8);
        return;
    }
    stm = adxt->stm;
    FUN_00277278(stm);
    FUN_00263768(adxt, name, first, last);
    FUN_00277768(stm, 1);
    FUN_002638a0(adxt);
}

void FUN_00263a50(AdxtHandle *adxt, int afs, unsigned int fid) {
    void *stm;
    if (adxt == 0 || afs >= 1 || fid > 0x10000) {
        FUN_002607e8(DAT_004ee210);
        return;
    }
    stm = adxt->stm;
    FUN_00277278(stm);
    FUN_002637d8(adxt, afs, fid);
    FUN_00277768(stm, 1);
    FUN_002638a0(adxt);
}

void FUN_00263b00(void)
{
}

int FUN_00263b08(AdxtHandle *adxt) {
    if (adxt == 0) {
        FUN_002607e8(DAT_004ee240);
        return -1;
    }
    return FUN_002773d0(adxt->stm);
}

void FUN_00263b40(AdxtHandle *adxt) {
    if (adxt == 0) {
        FUN_002607e8(DAT_004ee270);
        return;
    }
    /* matching construct: manual — early return (not an if block) lets ee-gcc emit the tail call */
    if (adxt->f1 != 0) {
        return;
    }
    FUN_002771d0(adxt->stm);
}

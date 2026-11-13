#define BSWAP32(x) ((((x) >> 24) & 0xff) | (((x) >> 8) & 0xff00) | (((x) << 8) & 0xff0000) | ((x) << 24))

typedef struct {
    int ofs;
    int len;
} AcxEntry;

typedef struct {
    int f0;
    int count;
    AcxEntry ent[1];
} AcxHeader;

typedef struct {
    char f0;
    signed char state;
    char mode;
} AdxtHandle;

extern char DAT_004eed68[];
extern char DAT_004eed98[];
void FUN_002607e8(const char *message);
void ADXT_Stop(AdxtHandle *adxt);
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void *FUN_0027b408(void *data, int size);
void FUN_0026b978(AdxtHandle *adxt, void *sj);
void FUN_0026d158(AdxtHandle *adxt, int value);

void FUN_0026d8b8(AdxtHandle *adxt, AcxHeader *acx, int no)
{
    void *sj;

    if (adxt == 0 || acx == 0 || no < 0) {
        FUN_002607e8(DAT_004eed68);
        return;
    }
    ADXT_Stop(adxt);
    if (no >= BSWAP32(acx->count) || no < 0) {
        return;
    }
    FUN_0025f2d0();
    sj = FUN_0027b408((char *)acx + BSWAP32((acx->ent + no)->ofs), 0x40000000);
    if (sj == 0) {
        FUN_0025f2e8();
        FUN_002607e8(DAT_004eed98);
        return;
    }
    FUN_0026b978(adxt, sj);
    adxt->mode = 2;
    FUN_0026d158(adxt, 0);
    FUN_0025f2e8();
}

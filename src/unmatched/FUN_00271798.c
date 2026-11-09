typedef struct {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} CdReadMode;

typedef struct {
    char f0;
    signed char req;
    signed char stat;
    char pad3;
    int f4;
    int lsn;
    int sectors;
    void *buf;
    CdReadMode mode;
} SrdRequest;

void FUN_002725a0(int);
int sceCdSync(int mode);
void FUN_0027e1f0(void);
void FUN_0027e268(void);

int FUN_00271798(SrdRequest *srd, int lsn, int sectors, void *buf, CdReadMode *mode)
{
    int ret;
    int busy;

    ret = 0;
    FUN_002725a0(0x1200);
    busy = sceCdSync(1);
    FUN_002725a0(0x1201);
    if (busy == 1) {
        return 0;
    }
    FUN_0027e1f0();
    if (srd->stat == 0 || srd->stat == 3 || srd->stat == 9) {
        srd->req = 1;
        srd->stat = 1;
        srd->lsn = lsn;
        srd->mode = *mode;
        srd->sectors = sectors;
        srd->buf = buf;
        srd->f4 = 0;
        ret = 1;
    }
    FUN_0027e268();
    return ret;
}

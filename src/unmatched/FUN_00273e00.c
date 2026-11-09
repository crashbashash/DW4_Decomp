typedef struct {
    int lsn;
    unsigned int size;
    char pad8[24];
} DvCiFileLoc;

typedef struct DvCiFile {
    char used;
    char cached;
    char state;
    char pad3;
    unsigned int size;
    int totalSct;
    int curSct;
    int nreq;
    int lastReq;
    void *buf;
    int req;
    DvCiFileLoc info;
} DvCiFile;

extern char DAT_004ab300[];
extern char DAT_004f0270[];
extern char DAT_004f0298[];
extern char DAT_004f02c0[];
extern char DAT_004f02f0[];
extern char DAT_004f0318[];
void FUN_002739b8(int detail, const char *message);
DvCiFile *FUN_00273da8(void);
void FUN_00273de0(DvCiFile *h);
int FUN_00274e30(const char *name, DvCiFileLoc *info);
void FUN_002745c0(const char *name, char *path);
void FUN_002659a0(const char *format, ...);
void FUN_002725a0(int mark);
int FUN_00116c80(int mode);
int FUN_002739e8(DvCiFileLoc *info, const char *path);

DvCiFile *FUN_00273e00(const char *fname, void *atr, int rw)
{
    DvCiFile *h;
    int ret;

    if (fname == 0) {
        FUN_002739b8(0, DAT_004f0270);
        return 0;
    }
    if (rw != 0) {
        FUN_002739b8(0, DAT_004f0298);
        return 0;
    }
    h = FUN_00273da8();
    if (h == 0) {
        FUN_002739b8(0, DAT_004f02c0);
        return 0;
    }
    ret = FUN_00274e30(fname, &h->info);
    if (h->info.size == 0) {
        FUN_002745c0(fname, DAT_004ab300);
        FUN_002659a0(DAT_004f02f0, DAT_004ab300);
        FUN_002725a0(0x8300);
        FUN_00116c80(0);
        FUN_002725a0(0x8301);
        if (FUN_002739e8(&h->info, DAT_004ab300) == 0) {
            FUN_002739b8(0, DAT_004f0318);
            FUN_00273de0(h);
            return 0;
        }
        h->cached = 0;
    } else {
        h->cached = 1;
    }
    h->totalSct = (h->info.size + 2047) / 2048;
    h->used = 1;
    h->size = h->info.size;
    h->curSct = 0;
    h->buf = 0;
    h->nreq = 0;
    h->lastReq = 0;
    h->state = 0;
    h->req = 0;
    if (ret == 1) {
        h->totalSct = 0x7fffffff;
    }
    return h;
}

typedef struct {
    int fd;
    int size;
} HtCiFileLoc;

typedef struct {
    char used;
    char cached;
    signed char state;
    char pad3[5];
    long long size;
    int nsct;
    int f20;
    int fd;
    int pos;
    char *buf;
    int req;
    int done;
    void *stm;
} HtCiFile;

void *memset(void *dst, int value, unsigned int size);
extern char DAT_004ab8c0[];
extern int DAT_004aba00;
extern char DAT_004f0768[];
extern char DAT_004f0790[];
extern char DAT_004f07b8[];
extern char DAT_004f07e8[];
extern char DAT_004f0810[];
void FUN_002753d8(int detail, const char *message);
HtCiFile *FUN_00275980(void);
void FUN_002759b8(HtCiFile *h);
void FUN_00276b18(const char *fname, HtCiFileLoc *loc);
void FUN_00276220(const char *name, char *path);
void FUN_00265928(const char *format, ...);
long long FUN_00275740(const char *fname);
void FUN_002725a0(int mark);
int FUN_002728b0(char *path, int mode);

HtCiFile *FUN_002759d8(const char *fname, void *atr, int rw)
{
    HtCiFileLoc loc;
    HtCiFile *h;

    memset(&loc, 0, sizeof(loc));
    if (fname == 0) {
        FUN_002753d8(0, DAT_004f0768);
        return 0;
    }
    if (rw != 0) {
        FUN_002753d8(0, DAT_004f0790);
        return 0;
    }
    h = FUN_00275980();
    if (h == 0) {
        FUN_002753d8(0, DAT_004f07b8);
        return 0;
    }
    FUN_00276b18(fname, &loc);
    if (loc.size == 0) {
        FUN_00276220(fname, DAT_004ab8c0);
        FUN_00265928(DAT_004f07e8, fname);
        h->size = FUN_00275740(fname);
        if (h->size == 0) {
            return 0;
        }
        FUN_002725a0(0x4900);
        h->fd = FUN_002728b0(DAT_004ab8c0, DAT_004aba00);
        FUN_002725a0(0x4901);
        if (h->fd < 0) {
            FUN_002753d8(0, DAT_004f0810);
            FUN_002759b8(h);
            return 0;
        }
        h->cached = 0;
    } else {
        h->cached = 1;
        h->fd = loc.fd;
        h->size = loc.size;
    }
    h->pos = 0;
    h->buf = 0;
    h->req = 0;
    h->nsct = (h->size + 2047) >> 11;
    h->f20 = 0;
    h->state = 0;
    h->used = 1;
    return h;
}

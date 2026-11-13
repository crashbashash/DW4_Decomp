typedef struct SrdObj SrdObj;

typedef struct CdReadMode {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} CdReadMode;

typedef struct sceCdlFILE {
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    unsigned int flag;
} sceCdlFILE;

typedef struct DvCiFile {
    signed char used;       /* 0x00 */
    signed char cached;     /* 0x01 */
    signed char state;      /* 0x02 */
    char pad3;
    unsigned int size;      /* 0x04 */
    int nsct;               /* 0x08 */
    int pos;                /* 0x0c */
    int req;                /* 0x10 */
    int done;               /* 0x14 */
    char *buf;              /* 0x18 */
    SrdObj *stm;            /* 0x1c */
    sceCdlFILE fp;          /* 0x20 */
    CdReadMode rmode;       /* 0x44 */
} DvCiFile;

typedef struct DvCiFileLoc {
    unsigned int lsn;
    unsigned int size;
} DvCiFileLoc;

typedef struct DvCiTable {
    int files;
    int nfiles;
    int nent;
    int namelen;
} DvCiTable;

extern char *volatile DAT_004aa740;
extern void (*DAT_004aa744)(void *context, const char *message, void *detail);
extern void *DAT_004aa748;
extern int DAT_004aa74c;
extern int DAT_004aa750;
extern int DAT_004aa758[];
extern DvCiFile DAT_004aa7c0[40];
extern char DAT_004ab300[];
extern DvCiTable DAT_004ab430;
extern CdReadMode DAT_004ab440;
extern int DAT_004ab444;
extern int DAT_004ab448;
extern char DAT_004ab450[];
extern char DAT_004ab558[];
extern char DAT_0056e780[];

void *memset(void *dst, int value, unsigned int n);
void *memcpy(void *dst, const void *src, unsigned int n);
char *strcpy(char *dst, const char *src);
char *strcat(char *dst, const char *src);
unsigned int strlen(const char *s);
int strcmp(const char *a, const char *b);
int strcasecmp(const char *a, const char *b);
unsigned long strtoul(const char *s, char **end, int base);
void FUN_00265928(const char *format, ...);
void ADXMSG_PrintErr(const char *format, ...);
void InvalidDCache(void *start, void *end);
int sceCdSync(int mode);
int sceCdRead(unsigned int lsn, unsigned int sectors, void *buf, CdReadMode *mode);
int FUN_00116740(sceCdlFILE *fp, const char *name, int layer);

SrdObj *FUN_00271670(void);
void FUN_002716f8(SrdObj *stm);
int FUN_00271798(SrdObj *stm, int lsn, int sectors, void *buf, CdReadMode *mode);
int FUN_00271938(SrdObj *stm);
void FUN_00271a68(SrdObj *stm);
void FUN_00271b98(SrdObj *stm);
void FUN_00272118(void);
void FUN_00272228(void);
void FUN_002725a0(int marker);
int FUN_002765e0(const char *name, void *buf);
void SVM_LockVar(void);
void SVM_UnlockVar(void);
int SVM_TestAndSet(int *flag);

void FUN_00273be8(char *path);
void FUN_00274248(DvCiFile *h);
int FUN_00274330(DvCiFile *h);
void FUN_002745c0(const char *name, char *path);
void FUN_00274c40(sceCdlFILE *out, const char *name, DvCiFileLoc *files, int n);
int FUN_00274e30(const char *name, sceCdlFILE *fp);
void dvCiSetRootDir(const char *path);

int *dvCiGetInterface(void)
{
    DAT_004aa740;
    dvCiSetRootDir(0);
    return DAT_004aa758;
}

void FUN_002739b8(void *detail, const char *message)
{
    if (DAT_004aa744 != 0) {
        DAT_004aa744(DAT_004aa748, message, detail);
    }
}

int FUN_002739e8(sceCdlFILE *fp, const char *name)
{
    int result;
    FUN_002725a0(0x8000);
    result = FUN_00116740(fp, name, DAT_004aa74c);
    FUN_002725a0(0x8001);
    return result;
}

int FUN_00273a40(void)
{
    int i;
    for (i = 0; i < 40; i++) {
        if (DAT_004aa7c0[i].used == 1 && DAT_004aa7c0[i].state == 2) {
            return 1;
        }
    }
    return 0;
}

void FUN_00273a90(DvCiFile *h)
{
    if (h->stm == 0)
        return;
    SVM_LockVar();
    switch (FUN_00271938(h->stm)) {
    case 9:
        h->state = 3;
        FUN_002716f8(h->stm);
        h->stm = 0;
        break;
    case 3:
        h->done = h->req;
        h->pos += h->req;
        h->state = 1;
        FUN_002716f8(h->stm);
        h->stm = 0;
        break;
    case 0:
        h->state = 0;
        FUN_002716f8(h->stm);
        h->stm = 0;
        break;
    case 1: case 2: case 4: case 5: case 6: case 7: case 8:
        break;
    }
    SVM_UnlockVar();
}

void FUN_00273b58(void)
{
    int i;
    if (SVM_TestAndSet(&DAT_004aa750) != 0) {
        for (i = 0; i < 40; i++) {
            if (DAT_004aa7c0[i].used == 1) {
                FUN_00273a90(&DAT_004aa7c0[i]);
            }
        }
        DAT_004aa750 = 0;
    }
}

void FUN_00273bd0(void (*callback)(void *context, const char *message, void *detail), void *context)
{
    DAT_004aa744 = callback;
    DAT_004aa748 = context;
}

void FUN_00273be8(char *path)
{
    unsigned int len;
    unsigned int i;
    len = strlen(path);
    for (i = 0; i < len; i++) {
        if (path[i] == '/') {
            path[i] = '\\';
        }
        if ((unsigned char)path[i] >= 'a' && (unsigned char)path[i] <= 'z') {
            path[i] -= 32;
        }
    }
}

int FUN_00273c60(const char *name)
{
    sceCdlFILE fp;
    if (name == 0) {
        return 0;
    }
    FUN_00274e30(name, &fp);
    if (fp.size == 0) {
        FUN_002745c0(name, DAT_004ab300);
        FUN_002725a0(0x8100);
        sceCdSync(0);
        FUN_002725a0(0x8101);
        if (FUN_002739e8(&fp, DAT_004ab300) == 0) {
            return 0;
        }
    }
    return 1;
}

int FUN_00273ce8(const char *fname)
{
    sceCdlFILE fp;
    if (fname == 0) {
        FUN_002739b8(0, "E0092901:fname is null.(dvCiGetFileSize)");
        return 0;
    }
    FUN_00274e30(fname, &fp);
    if (fp.size == 0) {
        FUN_002745c0(fname, DAT_004ab300);
        FUN_002725a0(0x8200);
        sceCdSync(0);
        FUN_002725a0(0x8201);
        if (FUN_002739e8(&fp, DAT_004ab300) == 0) {
            ADXMSG_PrintErr("DVCI: sceCdSearchFile failed. \"%s\"\n", DAT_004ab300);
            FUN_002739b8(0, "E0092902:can't find file.(dvCiGetFileSize)");
            return 0;
        }
    }
    return fp.size;
}

DvCiFile *FUN_00273da8(void)
{
    DvCiFile *found = 0;
    int i;
    for (i = 0; i < 40; i++) {
        if (DAT_004aa7c0[i].used == 0)
            found = &DAT_004aa7c0[i];
    }
    return found;
}

void FUN_00273de0(DvCiFile *h)
{
    memset(h, 0, sizeof(DvCiFile));
}

DvCiFile *FUN_00273e00(const char *fname, void *atr, int rw)
{
    DvCiFile *h;
    int ret;
    if (fname == 0) {
        FUN_002739b8(0, "E0092908:fname is null.(dvCiOpen)");
        return 0;
    }
    if (rw != 0) {
        FUN_002739b8(0, "E0092909:rw is illigal.(dvCiOpen)");
        return 0;
    }
    h = FUN_00273da8();
    if (h == 0) {
        FUN_002739b8(0, "E0092910:not enough handle resource.(dvCiOpen)");
        return 0;
    }
    ret = FUN_00274e30(fname, &h->fp);
    if (h->fp.size == 0) {
        FUN_002745c0(fname, DAT_004ab300);
        ADXMSG_PrintErr("DVCI: File cache was not hit. \"%s\"\n", DAT_004ab300);
        FUN_002725a0(0x8300);
        sceCdSync(0);
        FUN_002725a0(0x8301);
        if (FUN_002739e8(&h->fp, DAT_004ab300) == 0) {
            FUN_002739b8(0, "E0092911:sceCdSearchFile fail.(dvCiOpen)");
            FUN_00273de0(h);
            return 0;
        }
        h->cached = 0;
    } else {
        h->cached = 1;
    }
    h->nsct = (h->fp.size + 2047) / 2048;
    h->used = 1;
    h->size = h->fp.size;
    h->pos = 0;
    h->buf = 0;
    h->req = 0;
    h->done = 0;
    h->state = 0;
    h->stm = 0;
    if (ret == 1) {
        h->nsct = 0x7fffffff;
    }
    return h;
}

void FUN_00273f78(DvCiFile *h)
{
    if (h != 0) {
        if ((unsigned char)h->state >= 2) {
            FUN_00274248(h);
        }
        h->used = 0;
        FUN_00273de0(h);
    }
}

int FUN_00273fd0(DvCiFile *h, int offset, int origin)
{
    int position;
    if (h == 0) {
        FUN_002739b8(h, "E0092912:handl is null.");
        return 0;
    }
    if (origin == 0) {
        h->pos = offset;
    } else if (origin == 2) {
        h->pos = h->nsct + offset;
    } else if (origin == 1) {
        h->pos += offset;
    }
    position = h->pos;
    h->done = 0;
    if (position >= h->nsct) {
        position = h->nsct;
    }
    if (position < 0) {
        position = 0;
    }
    h->pos = position;
    return position;
}

int FUN_00274068(DvCiFile *h)
{
    if (h == 0) {
        FUN_002739b8(0, "E0092912:handl is null.");
        return 0;
    }
    return h->pos;
}

int FUN_002740a0(DvCiFile *h, int nsct, char *buf)
{
    int n, rem;
    int ready;
    if (h == 0) {
        FUN_002739b8(h, "E0092912:handl is null.");
        return 0;
    }
    if (nsct < 0) {
        FUN_002739b8(h, "E0092913:nsct < 0.(dvCiReqRd)");
        return 0;
    }
    if (buf == 0) {
        FUN_002739b8(h, "E0092914:buf is null.(dvCiReqRd)");
        return 0;
    }
    if (h->state == 2)
        return 0;
    if (nsct == 0) {
        h->state = 1;
        return 0;
    }
    h->stm = FUN_00271670();
    if (h->stm == 0)
        return 0;
    rem = h->nsct - h->pos;
    n = nsct < rem ? nsct : rem;
    h->rmode.trycount = DAT_004ab440.trycount;
    h->rmode.spindlctrl = DAT_004ab440.spindlctrl;
    h->rmode.datapattern = DAT_004ab440.datapattern;
    h->buf = buf;
    h->req = n;
    InvalidDCache(buf, buf + (n << 11) - 1);
    if (FUN_00271798(h->stm, h->fp.lsn + h->pos, h->req, h->buf, &h->rmode) == 0) {
        FUN_002716f8(h->stm);
        return 0;
    }
    ready = DAT_004ab444;
    if (ready == 1) {
        sceCdSync(0);
        FUN_00272228();
        FUN_00272118();
        FUN_00271a68(h->stm);
        FUN_002716f8(h->stm);
        h->stm = 0;
        h->done = nsct;
        h->state = ready;
        h->pos += h->req;
    } else {
        h->state = 2;
    }
    return h->req;
}

void FUN_00274248(DvCiFile *h)
{
    int i;
    i = 0;
    if (h == 0) {
        FUN_002739b8(0, "E0092912:handl is null.");
        return;
    }
    if ((unsigned char)h->state < 2) {
        return;
    }
    if (h->stm != 0) {
        FUN_00271b98(h->stm);
    }
    while (1) {
        FUN_00272118();
        FUN_00273b58();
        FUN_00274330(h);
        if (h->state != 2) {
            break;
        }
        if (++i > 0x9ffff) {
            ADXMSG_PrintErr("DVCI: dvCiStopTr timeout. (10sec)\r\n");
            break;
        }
    }
    h->state = 0;
    h->done = 0;
}

int FUN_00274330(DvCiFile *h)
{
    if (h == 0) {
        FUN_002739b8(0, "E0092912:handl is null.");
        return 0;
    }
    return h->state;
}

int FUN_00274368(void)
{
    return 0x800;
}

int FUN_00274370(DvCiFile *h)
{
    if (h == 0) {
        FUN_002739b8(0, "E0092912:handl is null.");
        return 0;
    }
    if (h->state == 1) {
        return h->done << 11;
    }
    return 0;
}

void FUN_002743c0(int value)
{
    DAT_004ab448 = value;
}

int FUN_002743d0(void)
{
    return DAT_004ab448;
}

void dvCiSetLayer(unsigned int layer)
{
    DAT_004aa74c = layer;
    if (layer >= 2) {
        DAT_004aa74c = 0;
    }
}

int dvCiGetLayer(void)
{
    return DAT_004aa74c;
}

int FUN_00274410(const char *fname)
{
    sceCdlFILE fp;
    FUN_00274e30(fname, &fp);
    if (fp.size == 0) {
        FUN_002745c0(fname, DAT_004ab300);
        FUN_002725a0(0x8400);
        sceCdSync(0);
        FUN_002725a0(0x8401);
        if (FUN_002739e8(&fp, DAT_004ab300) == 0) {
            ADXMSG_PrintErr("DVCI: sceCdSearchFile failed. \"%s\"\n", DAT_004ab300);
            return 0;
        }
    }
    return fp.size;
}

int FUN_002744a8(h)
    DvCiFile *h;
{
    return (long)h->done * 2048 >> 32;
}

int FUN_002744b8(h)
    DvCiFile *h;
{
    return ((long long)h->done << 11) & 0xFFFFFFFF;
}

int FUN_002744d8(fname)
    const char *fname;
{
    return 0;
}

int FUN_002744e0(fname)
    const char *fname;
{
    return FUN_00274410(fname);
}

/* matching construct: old-style getter definitions called with no arguments; retail never loads a0 before these calls */
int FUN_002744f8(void *obj, int code)
{
    int result;
    result = 0;
    if (obj == 0) {
        return 0;
    }
    switch (code) {
    case 200:
        result = FUN_002744a8();
        break;
    case 201:
        result = FUN_002744b8();
        break;
    case 202:
    case 204:
        result = FUN_002744d8();
        break;
    case 203:
    case 205:
        result = FUN_002744e0();
        break;
    case 299:
        result = 1;
        break;
    }
    return result;
}

void FUN_002745c0(const char *name, char *path)
{
    char c;
    strcpy(path, DAT_004ab450);
    c = *name;
    if (c != '/' && c != '\\') {
        strcat(path, "\\");
    }
    strcat(path, name);
    if (strcmp(path + strlen(path) - 2, ";1") != 0) {
        strcat(path, ";1");
    }
    FUN_00273be8(path);
}

char FUN_00274668(char c)
{
    char upper;
    upper = c;
    if ((unsigned int)(upper - 'a') < 26) {
        upper -= 32;
    }
    return ((c ^ 0x5C) != 0) ? upper : 0x2F;
}

int FUN_002746a0(char a, char b)
{
    int ca;
    ca = FUN_00274668(a);
    return ((ca ^ FUN_00274668(b)) != 0) ? -1 : 0;
}

int FUN_002746f8(const char *a, const char *b)
{
    int len;
    int i;
    len = strlen(a);
    if (len != strlen(b)) {
        return -1;
    }
    for (i = 0; i < len; i++) {
        if (FUN_002746a0(a[i], b[i]) != 0) {
            return -1;
        }
    }
    return 0;
}

int FUN_00274790(char *buf, char *list, int listlen, int n, int nameLen)
{
    int i;
    int start;
    int count;
    int len;
    char *dst;
    i = 0;
    count = 0;
    start = 0;
    while (list[i] != 0) {
        if (list[i] == '\n' || list[i] == 0) {
            if (list[i + 1] == '\n' || list[i + 1] == 0) {
                i++;
            }
            len = i - start;
            if (list[i - 1] == '\n' || list[i - 1] == '\r') {
                list[i - 1] = 0;
            }
            if (list[i - 2] == '\n' || list[i - 2] == '\r') {
                list[i - 2] = 0;
            }
            dst = buf + (n * sizeof(DvCiFileLoc) + count * (nameLen + 1));
            memcpy(dst, list + start, len);
            FUN_00273be8(dst);
            if (dst[len - 1] != 0) {
                dst[len] = 0;
            }
            start = i + 1;
            count++;
            if (count == n) {
                break;
            }
        }
        i++;
        if (i > listlen) {
            break;
        }
    }
    if (DAT_004ab430.files == 0) {
        DAT_004ab430.files = (int)buf;
        DAT_004ab430.nfiles = count;
        DAT_004ab430.nent = n;
        DAT_004ab430.namelen = nameLen;
    }
    return count;
}

int FUN_00274928(const char *path, void *buf)
{
    sceCdlFILE fp;
    CdReadMode mode;
    char dev[5];
    memcpy(dev, path, 5);
    dev[4] = 0;
    if (strcasecmp(dev, "HST:") == 0) {
        return FUN_002765e0(path + 4, buf);
    }
    memset(DAT_004ab558, 0, 128);
    FUN_002745c0(path, DAT_004ab558);
    FUN_002725a0(0x9000);
    while (sceCdSync(1) == 1) {
    }
    FUN_002725a0(0x9001);
    FUN_002725a0(0x9100);
    if (FUN_002739e8(&fp, DAT_004ab558) == 0) {
        FUN_002725a0(0x9101);
        return 0;
    }
    FUN_002725a0(0x9102);
    mode.trycount = 0;
    mode.spindlctrl = 1;
    mode.datapattern = 0;
    mode.pad = 0;
    FUN_002725a0(0x9200);
    if (sceCdRead(fp.lsn, 2, buf, &mode) == 0) {
        FUN_002725a0(0x9201);
        return 0;
    }
    FUN_002725a0(0x9202);
    FUN_002725a0(0x9300);
    while (sceCdSync(1) == 1) {
    }
    FUN_002725a0(0x9301);
    return 1;
}

int FUN_00274ab0(DvCiFileLoc *files, int n)
{
    sceCdlFILE fp;
    int missing;
    int found = 0;
    int i;
    char *name;
    missing = 0;
    for (i = 0; i < n; i++) {
        name = (char *)files + ((DAT_004ab430.nent << 3) + (DAT_004ab430.namelen * i + i));
        if (*name == 0)
            continue;
        FUN_002745c0(name, DAT_004ab558);
        FUN_002725a0(0x9400);
        while (sceCdSync(1) == 1)
            ;
        FUN_002725a0(0x9401);
        FUN_002725a0(0x9500);
        if (FUN_002739e8(&fp, DAT_004ab558) == 1) {
            FUN_002725a0(0x9501);
            found++;
            files[i].lsn = fp.lsn;
            files[i].size = fp.size;
            FUN_00265928("DVCI: \"%s\" found.\n", name);
        } else {
            FUN_002725a0(0x9502);
            missing++;
            FUN_00265928("DVCI: \"%s\" Not found.\n", name);
        }
    }
    FUN_00265928("DVCI: Total %d files.\n", found);
    if (missing > 0)
        ADXMSG_PrintErr("DVCI: Warning, Can't load all cache file.%c", 10);
    return found;
}

void FUN_00274c40(sceCdlFILE *out, const char *name, DvCiFileLoc *files, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        if (FUN_002746f8(name, (char *)files + ((DAT_004ab430.nent << 3) + (DAT_004ab430.namelen * i + i))) == 0) {
            out->lsn = files[i].lsn;
            out->size = files[i].size;
            return;
        }
    }
    out->lsn = 0;
    out->size = 0;
}

void FUN_00274d08(void)
{
    memset(&DAT_004ab430, 0, sizeof(DvCiTable));
}

int FUN_00274d30(const char *name)
{
    if (strlen(name) != 17) {
        return 0;
    }
    return name[8] == '.';
}

int FUN_00274d70(const char *name, int *lsn, int *nsct)
{
    char *p;
    p = (char *)name;
    *lsn = strtoul(p, &p, 16);
    if (*p != 0) {
        p++;
    }
    if (nsct != 0) {
        *nsct = strtoul(p, &p, 16);
    }
    FUN_00265928("DVCI: \"%s\" opened. ", name);
    FUN_00265928("LSN=%d, ", *lsn);
    FUN_00265928("Size=%d[sector]\n", *nsct);
    return 1;
}

int FUN_00274e30(const char *name, sceCdlFILE *fp)
{
    int lsn;
    int nsct;
    if (strcmp("DVD-ROM", name) == 0) {
        fp->size = -1;
        fp->lsn = 0;
        ADXMSG_PrintErr("DVCI: CD/DVD-ROM Image opened%c\n", '.');
        return 1;
    }
    if (FUN_00274d30(name) == 1) {
        FUN_00274d70(name, &lsn, &nsct);
        fp->lsn = lsn;
        fp->size = nsct << 11;
        return 0;
    }
    fp->lsn = 0;
    fp->size = 0;
    if (DAT_004ab430.files != 0) {
        FUN_00274c40(fp, name, (DvCiFileLoc *)DAT_004ab430.files, DAT_004ab430.nfiles);
    }
    return 0;
}

int dvCiLoadDirInfo(const char *path, char *buf, unsigned int size, int nameLen)
{
    int n;
    int found;
    memset(DAT_0056e780, 0, 4096);
    if (DAT_004ab430.files != 0) {
        FUN_00274d08();
    }
    if (path == 0 || buf == 0 || size == 0) {
        FUN_00274d08();
    }
    if (path == 0) {
        return 0;
    }
    if (buf == 0) {
        FUN_00265928("DVCI: Invalidate filelist buffer pointer.\r\n", 0);
        return 0;
    }
    if (size == 0) {
        FUN_00265928("DVCI: Invalidate filelist buffer size.\r\n", 0);
        return 0;
    }
    memset(buf, 0, size);
    if (FUN_00274928(path, DAT_0056e780) == 0) {
        FUN_00265928("DVCI: Can't read filelist file.(%s)\n", path);
        FUN_002739b8(0, "E0111501:can't read filelist.(dvCiLoadDirInfo)");
        return 0;
    }
    n = FUN_00274790(buf, DAT_0056e780, 4096, size / (nameLen + 9), nameLen);
    found = FUN_00274ab0((DvCiFileLoc *)buf, n);
    return size / (nameLen + 9) * 8 + found * (nameLen + 1);
}

int dvCiLoadDirInfoMem(char *list, int listlen, char *buf, unsigned int size, int nameLen)
{
    int n;
    int found;
    memset(DAT_0056e780, 0, 4096);
    if (DAT_004ab430.files != 0) {
        FUN_00274d08();
    }
    if (list == 0 || buf == 0 || listlen == 0 || size == 0) {
        FUN_00274d08();
    }
    if (list == 0) {
        return 0;
    }
    if (buf == 0) {
        FUN_00265928("DVCI: Invalidate filelist buffer pointer.\r\n", 0);
        return 0;
    }
    if (listlen == 0 || size == 0) {
        FUN_00265928("DVCI: Invalidate filelist buffer size.\r\n", 0);
        return 0;
    }
    n = FUN_00274790(buf, list, listlen, size / (nameLen + 9), nameLen);
    found = FUN_00274ab0((DvCiFileLoc *)buf, n);
    return size / (nameLen + 9) * 8 + found * (nameLen + 1);
}

int dvCiIsExistFile(const char *name)
{
    sceCdlFILE fp;
    FUN_00274e30(name, &fp);
    return fp.lsn != 0;
}

void dvCiSetRdMode(int trycount, int spindlctrl, int datapattern, int mode)
{
    DAT_004ab440.trycount = trycount;
    DAT_004ab440.spindlctrl = spindlctrl;
    DAT_004ab440.datapattern = datapattern;
    DAT_004ab444 = mode;
}

void dvCiSetRootDir(const char *path)
{
    char c;
    if (path == 0) {
        DAT_004ab450[0] = 0;
        return;
    }
    if (path[0] != '/' && path[0] != '\\') {
        strcpy(DAT_004ab450, "\\");
    } else {
        DAT_004ab450[0] = 0;
    }
    strcat(DAT_004ab450, path);
    c = path[strlen(path) - 1];
    if (c == '/' || c == '\\') {
        DAT_004ab450[strlen(DAT_004ab450) - 1] = 0;
    }
}

char *FUN_002752e8(void)
{
    return DAT_004ab450;
}

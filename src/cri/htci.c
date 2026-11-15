#include "dw4/cri/cvfs.h"

typedef struct SrdObj SrdObj;

typedef struct HtCiFile {
    signed char used;       /* 0x00 */
    signed char cached;     /* 0x01 */
    signed char state;      /* 0x02 */
    char pad3[5];
    long long size;         /* 0x08 */
    int nsct;               /* 0x10 */
    int f20;                /* 0x14 */
    int fd;                 /* 0x18 */
    int pos;                /* 0x1c */
    char *buf;              /* 0x20 */
    int req;                /* 0x24 */
    int done;               /* 0x28 */
    SrdObj *stm;            /* 0x2c */
} HtCiFile;

typedef struct HtCiFileLoc {
    int fd;
    int size;
} HtCiFileLoc;

typedef struct HtCiTable {
    int files;
    unsigned int nfiles;
    int nent;
    int namelen;
} HtCiTable;

void htCiExecServer(void);
void htCiEntryErrFunc(void (*callback)(void *context, const char *message, void *detail), void *context);
int htCiGetFileSize(const char *fname);
HtCiFile *htCiOpen(const char *fname, void *atr, int rw);
void htCiClose(HtCiFile *h);
int htCiSeek(HtCiFile *h, int offset, int origin);
int htCiTell(HtCiFile *h);
int htCiReqRd(HtCiFile *h, int nsct, char *buf);
void htCiStopTr(HtCiFile *h);
int htCiGetStat(HtCiFile *h);
int htCiGetSctLen(void);
int htCiGetNumTr(HtCiFile *h);
int htCiIsExistFileOnHost(const char *name);
int htCiOptFn1(void *obj, int code);

static char *volatile htci_build = "\nHTCI/PS2EE Ver.2.69 Build:Oct  6 2004 11:47:42\n";
static void (*htci_err_func)(void *context, const char *message, void *detail) = 0;
static void *htci_err_obj = 0;
static int htci_lock = 0;
static CvFsVtbl htci_vtbl = {
    (int)htCiExecServer, (int)htCiEntryErrFunc, (int)htCiGetFileSize, 0,
    (int)htCiOpen, (int)htCiClose, (int)htCiSeek, (int)htCiTell,
    (int)htCiReqRd, 0, (int)htCiStopTr, (int)htCiGetStat,
    (int)htCiGetSctLen, 0, (int)htCiGetNumTr, 0,
    (int)htCiIsExistFileOnHost, 0, 0, 0, 0, 0, 0, 0, (int)htCiOptFn1, 0
};
static HtCiFile htci_files[13] = {0};
static char htci_path[304] = {0};
static HtCiTable htci_dir_table = {0};
static int htci_open_mode = 0x8001;
static int htci_option = 0;
static char htci_root_dir[264];
static char htci_prefix[40];
static char htci_dir_buf[4096];

void *memset(void *dst, int value, unsigned int n);
void *memcpy(void *dst, const void *src, unsigned int n);
char *strcpy(char *dst, const char *src);
char *strcat(char *dst, const char *src);
unsigned int strlen(const char *s);
int strcmp(const char *a, const char *b);
void FUN_00265928(const char *format, ...);
void ADXMSG_PrintErr(const char *format, ...);

SrdObj *FUN_00271670(void);
void FUN_002716f8(SrdObj *stm);
int FUN_00271888(SrdObj *stm, int fd, long pos, unsigned long nbyte, char *buf);
int FUN_00271938(SrdObj *stm);
void FUN_00271b98(SrdObj *stm);
void FUN_00272118(void);
void FUN_00272228(void);
void FUN_002725a0(int marker);
long SRD_Lseek(int fd, long offset, int whence);
int FUN_00272838(int fd, int cmd, int *result);
int FUN_002728b0(const char *name, int flags);
int FUN_00272918(int fd);
int FUN_00272970(int fd, void *buf, int size);
void SVM_LockVar(void);
void SVM_UnlockVar(void);
int SVM_TestAndSet(int *flag);

long htCiGetFileSize64(const char *fname);
void htCiStopTr(HtCiFile *h);
int htCiGetStat(HtCiFile *h);
void FUN_00276220(const char *name, char *out);
int FUN_00276440(char *buf, char *list, int n, int nameLen);
int FUN_002765e0(const char *name, void *buf);
int FUN_00276740(HtCiFileLoc *files, int n);
int FUN_002768f8(void);
void FUN_00276af0(void);
void FUN_00276b18(const char *name, HtCiFileLoc *loc);
void htCiSetRootDir(const char *path);
void FUN_00276da8(const char *prefix);

CvFsVtbl *htCiGetInterface(void)
{
    htci_build;
    htCiSetRootDir(0);
    FUN_00276da8(0);
    return &htci_vtbl;
}

void FUN_002753a8(void)
{
    int count;
    /* matching construct: hand search — GCC deletes this empty loop when the test is `count >= 0` */
    for (count = 0x1FFF; count > -1; count -= 32) {
    }
}

void FUN_002753d8(void *detail, const char *message)
{
    if (htci_err_func != 0) {
        htci_err_func(htci_err_obj, message, detail);
    }
}

int FUN_00275408(void)
{
    int i;
    for (i = 0; i < 13; i++) {
        if (htci_files[i].used == 1 && htci_files[i].state == 2) {
            return 1;
        }
    }
    return 0;
}

int FUN_00275458(HtCiFile *h)
{
    int result;
    int ret;
    FUN_002725a0(0x4000);
    result = FUN_00272838(h->fd, 1, &h->f20);
    FUN_002725a0(0x4001);
    ret = 0;
    if (result >= 0) {
        ret = h->f20 != 1;
    }
    return ret;
}

void FUN_002754c0(HtCiFile *h, int nsct)
{
    unsigned long long end;
    int n;
    end = ((unsigned long long)h->pos + h->req) << 11;
    if (h->size < end) {
        n = end - h->size;
        memset(h->buf + (h->req << 11) - n, 0, n);
    }
}

void FUN_00275520(HtCiFile *h)
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

void htCiExecServer(void)
{
    int i;
    if (SVM_TestAndSet(&htci_lock) != 0) {
        for (i = 0; i < 13; i++) {
            if (htci_files[i].used == 1) {
                FUN_00275520(&htci_files[i]);
            }
        }
        htci_lock = 0;
    }
}

void htCiEntryErrFunc(void (*callback)(void *context, const char *message, void *detail), void *context)
{
    htci_err_func = callback;
    htci_err_obj = context;
}

int htCiIsExistFileOnHost(const char *name)
{
    HtCiFileLoc loc;
    int fd;
    if (name == 0) {
        return 0;
    }
    FUN_00276b18(name, &loc);
    if (loc.size == 0) {
        FUN_00276220(name, htci_path);
        FUN_002725a0(0x4200);
        fd = FUN_002728b0(htci_path, 1);
        FUN_002725a0(0x4201);
        if (fd < 0) {
            return 0;
        }
        FUN_002725a0(0x4300);
        FUN_00272918(fd);
        FUN_002725a0(0x4301);
    }
    return 1;
}

int htCiGetFileSize(const char *fname)
{
    return htCiGetFileSize64(fname);
}

long htCiGetFileSize64(const char *fname)
{
    HtCiFileLoc loc;
    long size;
    int fd;
    if (fname == 0) {
        FUN_002753d8(0, "E0092704:fname is null.(htCiGetFileSize)");
        return 0;
    }
    FUN_00276b18(fname, &loc);
    if (loc.size == 0) {
        FUN_00276220(fname, htci_path);
        FUN_002725a0(0x4400);
        fd = FUN_002728b0(htci_path, 1);
        FUN_002725a0(0x4401);
        if (fd < 0) {
            ADXMSG_PrintErr("HTCI: sceOpen failed. \"%s\"\n", htci_path);
            FUN_002753d8(0, "E0092705:sceOpen fail.(htCiGetFileSize)");
            return 0;
        }
        if (fd == 0x10004) {
            ADXMSG_PrintErr("HTCI: sceOpen failed. IOP Module version is invalid.\n");
            FUN_002753d8(0, "E0082101:sceOpen fail.(htCiGetFileSize)");
            return 0;
        }
        if (fd == 19) {
            ADXMSG_PrintErr("HTCI: sceOpen failed. file desc is insufficient.\n");
            FUN_002753d8(0, "E0082101:sceOpen fail.(htCiGetFileSize)");
            return 0;
        }
        FUN_002725a0(0x4600);
        SRD_Lseek(fd, 0, 0);
        FUN_002725a0(0x4601);
        FUN_002725a0(0x4600);
        size = SRD_Lseek(fd, 0, 2);
        FUN_002725a0(0x4601);
        if (size < 0) {
            FUN_002753d8(0, "E0092706:sceLseek fail.(htCiGetFileSize)");
            FUN_002725a0(0x4500);
            FUN_00272918(fd);
            FUN_002725a0(0x4501);
            return 0;
        }
        FUN_002725a0(0x5000);
        fd = FUN_00272918(fd);
        FUN_002725a0(0x5001);
        if (fd < 0) {
            FUN_002753d8(0, "E0092707:sceClose fail.(htCiGetFileSize)");
            return 0;
        }
    } else {
        size = loc.size;
    }
    return size;
}

long FUN_002758f8(int fd)
{
    long result;
    FUN_002725a0(0x4700);
    result = SRD_Lseek(fd, 0, 0);
    FUN_002725a0(0x4701);
    if (result < 0) {
        return 0;
    }
    FUN_002725a0(0x4800);
    result = SRD_Lseek(fd, 0, 2);
    FUN_002725a0(0x4801);
    if (result < 0) {
        return 0;
    }
    return result;
}

HtCiFile *FUN_00275980(void)
{
    HtCiFile *found = 0;
    int i;
    for (i = 0; i < 13; i++) {
        if (htci_files[i].used == 0) {
            found = &htci_files[i];
        }
    }
    return found;
}

void FUN_002759b8(HtCiFile *h)
{
    memset(h, 0, sizeof(HtCiFile));
}

HtCiFile *htCiOpen(const char *fname, void *atr, int rw)
{
    HtCiFileLoc loc;
    HtCiFile *h;
    memset(&loc, 0, sizeof(loc));
    if (fname == 0) {
        FUN_002753d8(0, "E0092708:fname is null.(htCiOpen)");
        return 0;
    }
    if (rw != 0) {
        FUN_002753d8(0, "E0092709:rw is illigal.(htCiOpen)");
        return 0;
    }
    h = FUN_00275980();
    if (h == 0) {
        FUN_002753d8(0, "E0092710:not enough handle resource.(htCiOpen)");
        return 0;
    }
    FUN_00276b18(fname, &loc);
    if (loc.size == 0) {
        FUN_00276220(fname, htci_path);
        FUN_00265928("HTCI: File cache was not hit. \"%s\"\n", fname);
        h->size = htCiGetFileSize64(fname);
        if (h->size == 0) {
            return 0;
        }
        FUN_002725a0(0x4900);
        h->fd = FUN_002728b0(htci_path, htci_open_mode);
        FUN_002725a0(0x4901);
        if (h->fd < 0) {
            FUN_002753d8(0, "E0092711:sceOpen fail.(htCiOpen)");
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

void htCiClose(HtCiFile *h)
{
    int result;
    if (h != 0) {
        if ((unsigned char)h->state >= 2) {
            htCiStopTr(h);
        }
        if (h->cached == 0) {
            FUN_002725a0(0x5000);
            result = FUN_00272918(h->fd);
            FUN_002725a0(0x5001);
            if (result < 0) {
                FUN_00265928("HTCI: Failed sceClose\n");
            }
        }
        h->used = 0;
        FUN_002759b8(h);
    }
}

int htCiSeek(HtCiFile *h, int offset, int origin)
{
    int position;
    if (h == 0) {
        FUN_002753d8(h, "E0092712:handl is null.");
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

int htCiTell(HtCiFile *h)
{
    if (h == 0) {
        FUN_002753d8(0, "E0092712:handl is null.");
        return 0;
    }
    return h->pos;
}

int htCiReqRd(HtCiFile *h, int nsct, char *buf)
{
    unsigned long nbyte;
    if (h == 0) {
        FUN_002753d8(h, "E0092712:handl is null.");
        return 0;
    }
    if (nsct < 0) {
        FUN_002753d8(h, "E0092713:nsct < 0.(htCiReqRd)");
        return 0;
    }
    if (buf == 0) {
        FUN_002753d8(h, "E0092714:buf is null.(htCiReqRd)");
        return 0;
    }
    if (FUN_00275408() == 1) {
        return 0;
    }
    if (h->state == 2) {
        return 0;
    }
    if (nsct == 0) {
        h->state = 1;
        return 0;
    }
    h->stm = FUN_00271670();
    if (h->stm == 0) {
        return 0;
    }
    h->buf = buf;
    h->req = (nsct < h->nsct - h->pos) ? nsct : h->nsct - h->pos;
    nbyte = nsct << 11;
    if (h->size < nbyte) {
        nbyte = h->size;
    }
    FUN_002754c0(h, h->req);
    if (FUN_00271888(h->stm, h->fd, h->pos, nbyte, buf) == 0) {
        return 0;
    }
    if (htci_open_mode == 1) {
        FUN_00272228();
        FUN_00272118();
        h->pos += h->req;
        FUN_002716f8(h->stm);
        h->stm = 0;
        h->state = 1;
        h->done = h->req;
    } else {
        h->state = 2;
        h->done = 0;
    }
    h->f20 = 0;
    return h->req;
}

void htCiStopTr(HtCiFile *h)
{
    int i;
    i = 0;
    if (h == 0) {
        FUN_002753d8(0, "E0082401:handl is null.");
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
        htCiExecServer();
        htCiGetStat(h);
        if (h->state != 2) {
            break;
        }
        if (++i > 0x63fff6) {
            ADXMSG_PrintErr("HTCI: htCiStopTr timeout.\r\n");
            break;
        }
        FUN_002753a8();
    }
    h->state = 0;
    h->done = 0;
}

int htCiGetStat(HtCiFile *h)
{
    if (h == 0) {
        FUN_002753d8(0, "E0092712:handl is null.");
        return 0;
    }
    return h->state;
}

int htCiGetSctLen(void)
{
    return 0x800;
}

int htCiGetNumTr(HtCiFile *h)
{
    if (h == 0) {
        FUN_002753d8(0, "E0092712:handl is null.");
        return 0;
    }
    if (h->state == 1) {
        return h->done << 11;
    }
    return 0;
}

long FUN_00275fd8(const char *fname)
{
    return htCiGetFileSize64(fname);
}

int FUN_00275ff0(h)
    HtCiFile *h;
{
    unsigned long long size = (long long)h->done << 11;
    return (long long)(h->size < size ? h->size : size) >> 32;
}

int FUN_00276010(h)
    HtCiFile *h;
{
    unsigned long long size = (long long)h->done << 11;
    return (int)((h->size < size ? h->size : size) & 0xFFFFFFFF);
}

int FUN_00276040(fname)
    const char *fname;
{
    return FUN_00275fd8(fname) >> 0x20;
}

int FUN_00276060(fname)
    const char *fname;
{
    return (int)(FUN_00275fd8(fname) & 0xFFFFFFFF);
}

/* matching construct: old-style getter definitions called with no arguments; retail never loads a0 before these calls */
int htCiOptFn1(void *obj, int code)
{
    int result;
    result = 0;
    if (obj == 0) {
        return 0;
    }
    switch (code) {
    case 200:
        result = FUN_00275ff0();
        break;
    case 201:
        result = FUN_00276010();
        break;
    case 202:
    case 204:
        result = FUN_00276040();
        break;
    case 203:
    case 205:
        result = FUN_00276060();
        break;
    case 299:
        result = 1;
        break;
    }
    return result;
}

int FUN_00276158(const char *path)
{
    unsigned int len;
    unsigned int i;
    len = strlen(path);
    if (len > 16) {
        len = 16;
    }
    for (i = 0; i < len; i++) {
        if (path[i] == ':') {
            return 1;
        }
    }
    return 0;
}

int FUN_002761c8(const char *tag)
{
    char buf[6];
    memset(buf, 0, 6);
    memcpy(buf, tag, 4);
    buf[5] = 0;
    return strcmp(buf, "host") == 0;
}

void FUN_00276220(const char *name, char *out)
{
    char c;
    int len;
    int i;
    out[0] = 0;
    if (FUN_00276158(name) == 0) {
        strcpy(out, htci_prefix);
    }
    if (FUN_002761c8(out) == 1) {
        strcat(out, htci_root_dir);
        c = htci_root_dir[strlen(htci_root_dir) - 1];
        if (c != '\\' && c != '/' && c != 0 && name[0] != '\\' && name[0] != '/') {
            strcat(out, "/");
        }
    }
    strcat(out, name);
    len = strlen(out);
    for (i = 0; i < len; i++) {
        if (out[i] == '\\') {
            out[i] = '/';
        }
    }
}

char FUN_00276338(char c)
{
    return ((c ^ 0x5C) != 0) ? c : 0x2F;
}

int FUN_00276350(char a, char b)
{
    int ca;
    ca = FUN_00276338(a);
    return ((ca ^ FUN_00276338(b)) != 0) ? -1 : 0;
}

int FUN_002763a8(const char *a, const char *b)
{
    int len;
    int i;
    len = strlen(a);
    if (len != strlen(b)) {
        return -1;
    }
    for (i = 0; i < len; i++) {
        if (FUN_00276350(a[i], b[i]) != 0) {
            return -1;
        }
    }
    return 0;
}

int FUN_00276440(char *buf, char *list, int n, int nameLen)
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
        if (list[i] == '\\') {
            list[i] = '/';
        }
        if (list[i] == '\n' || list[i] == '\r' || list[i] == 0) {
            if (list[i + 1] == '\n' || list[i + 1] == '\r' || list[i + 1] == 0) {
                i++;
            }
            len = i - start;
            if (list[i - 1] == '\n' || list[i - 1] == '\r') {
                list[i - 1] = 0;
            }
            dst = buf + (n * sizeof(HtCiFileLoc) + count * (nameLen + 1));
            memcpy(dst, list + start, len);
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
    }
    if (htci_dir_table.files == 0) {
        htci_dir_table.files = (int)buf;
        htci_dir_table.nfiles = count;
        htci_dir_table.nent = n;
        htci_dir_table.namelen = nameLen;
    }
    return count;
}

int FUN_002765e0(const char *name, void *buf)
{
    char path[256];
    int fd;
    long size;
    int ret;
    memset(path, 0, 256);
    FUN_00276220(name, path);
    FUN_002725a0(0x6000);
    fd = FUN_002728b0(path, 1);
    FUN_002725a0(0x6001);
    if (fd < 0) {
        return 0;
    }
    FUN_002725a0(0x6100);
    size = SRD_Lseek(fd, 0, 2);
    FUN_002725a0(0x6101);
    if (size < 0) {
        return 0;
    }
    FUN_002725a0(0x6200);
    ret = SRD_Lseek(fd, 0, 0);
    FUN_002725a0(0x6201);
    if (ret < 0) {
        return 0;
    }
    if (size > 4096) {
        size = 4096;
    }
    FUN_002725a0(0x6300);
    ret = FUN_00272970(fd, buf, size);
    FUN_002725a0(0x6301);
    if (ret < 0) {
        FUN_002725a0(0x6500);
        FUN_00272918(fd);
        FUN_002725a0(0x6501);
        return 0;
    }
    FUN_002725a0(0x6400);
    FUN_00272918(fd);
    FUN_002725a0(0x6401);
    return 1;
}

int FUN_00276740(HtCiFileLoc *files, int n)
{
    char path[256];
    char *name;
    int i;
    int fd;
    int opened;
    int failed;
    opened = 0;
    failed = 0;
    memset(path, 0, 256);
    if (n > 13) {
        n = 13;
    }
    for (i = 0; i < n; i++) {
        name = (char *)files + (htci_dir_table.nent * 8 + (htci_dir_table.namelen + 1) * i);
        FUN_00276220(name, path);
        if (name[0] == 0) {
            continue;
        }
        FUN_002725a0(0x6600);
        fd = FUN_002728b0(path, 1);
        FUN_002725a0(0x6601);
        if (fd < 0) {
            failed++;
            FUN_00265928("HTCI: \"%s\" can't Open.(sceOpen)\n", path);
            continue;
        }
        files[i].fd = fd;
        opened++;
        files[i].size = FUN_002758f8(fd);
        FUN_00265928("HTCI: \"%s\" Opened.(sceOpen)\n", name);
        FUN_002725a0(0x6800);
        FUN_00272918(fd);
        FUN_002725a0(0x6801);
        FUN_002725a0(0x6700);
        FUN_002728b0(path, htci_open_mode);
        FUN_002725a0(0x6701);
    }
    FUN_00265928("HTCI: Total %d files.\n", opened);
    if (failed > 0) {
        ADXMSG_PrintErr("HTCI: Error, Can't load all cache file.%c", 10);
    }
    return opened;
}

int FUN_002768f8(void)
{
    char path[256];
    HtCiFileLoc *files;
    char *name;
    unsigned int i;
    unsigned int n;
    int closed;
    int ret;
    closed = 0;
    files = (HtCiFileLoc *)htci_dir_table.files;
    if (files == 0) {
        return 0;
    }
    n = htci_dir_table.nfiles;
    for (i = 0; i < n; i++) {
        name = (char *)files + (htci_dir_table.nent * 8 + (htci_dir_table.namelen + 1) * i);
        FUN_00276220(name, path);
        if (name[0] == 0) {
            continue;
        }
        FUN_002725a0(0x6900);
        ret = FUN_00272918(files[i].fd);
        FUN_002725a0(0x6901);
        if (ret < 0) {
            ADXMSG_PrintErr("HTCI: \"%s\" can't Close.(sceClose)\n", path);
        } else {
            ADXMSG_PrintErr("HTCI: \"%s\" Closed.(sceClose)\n", path);
            closed++;
        }
    }
    ADXMSG_PrintErr("HTCI: Total %d files\n", closed);
    FUN_00276af0();
    return 1;
}

/* matching construct: 16-variant sweep — the address sum */
void FUN_00276a28(HtCiFileLoc *out, const char *name, HtCiFileLoc *entries, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        const char *entryName = (char *)entries + (htci_dir_table.nent * sizeof(HtCiFileLoc) + i * (htci_dir_table.namelen + 1));
        if (FUN_002763a8(name, entryName) == 0) {
            out->fd = entries[i].fd;
            out->size = entries[i].size;
            return;
        }
    }
    out->fd = 0;
    out->size = 0;
}

void FUN_00276af0(void)
{
    memset(&htci_dir_table, 0, sizeof(HtCiTable));
}

void FUN_00276b18(const char *name, HtCiFileLoc *loc)
{
    loc->fd = 0;
    loc->size = 0;
    if (htci_dir_table.files != 0) {
        FUN_00276a28(loc, name, (HtCiFileLoc *)htci_dir_table.files, htci_dir_table.nfiles);
    }
}

int htCiLoadDirInfo(const char *path, void *buf, unsigned int size, int nameLen)
{
    int n;
    int found;
    int stride;
    memset(htci_dir_buf, 0, 4096);
    if (htci_dir_table.files == 0) {
        FUN_00276af0();
    }
    FUN_002768f8();
    if (path == 0) {
        return 0;
    }
    if (buf == 0) {
        FUN_00265928("HTCI: Invalidate filelist buffer pointer.\r\n", 0);
        return 0;
    }
    if (size == 0) {
        FUN_00265928("HTCI: Invalidate filelist buffer size.\r\n", 0);
        return 0;
    }
    memset(buf, 0, size);
    if (FUN_002765e0(path, htci_dir_buf) == 0) {
        FUN_00265928("HTCI: Can't read filelist file.(%s)\n", path);
        FUN_002753d8(0, "E0111501:can't read filelist.(htCiLoadDirInfo)");
        return 0;
    }
    n = FUN_00276440(buf, htci_dir_buf, size / (nameLen + 9), nameLen);
    stride = nameLen + 1;
    found = FUN_00276740(buf, n);
    return size / (nameLen + 9) * 8 + found * stride;
}

int htCiIsExistFile(const char *name)
{
    HtCiFileLoc loc;
    FUN_00276b18(name, &loc);
    return loc.size != 0;
}

/* matching construct: switch — retail tests mode 0 separately before mode 1, which an if/else does not emit. */
void htCiSetOpenMode(int mode)
{
    switch (mode) {
    case 0:
        htci_open_mode = 0x8001;
        break;
    case 1:
        htci_open_mode = mode;
        break;
    default:
        htci_open_mode = 0x8001;
        break;
    }
}

void htCiSetRootDir(const char *path)
{
    if (path == 0) {
        htci_root_dir[0] = 0;
        return;
    }
    if (path[0] != '/' && path[0] != '\\') {
        strcpy(htci_root_dir, "/");
    } else {
        htci_root_dir[0] = 0;
    }
    strcpy(htci_root_dir, path);
}

char *FUN_00276d98(void)
{
    return htci_root_dir;
}

void FUN_00276da8(const char *prefix)
{
    if (prefix == 0) {
        strcpy(htci_prefix, "host:");
    } else {
        strcpy(htci_prefix, prefix);
    }
}

char *FUN_00276e10(void)
{
    return htci_prefix;
}

int FUN_00276e20(void)
{
    return htci_open_mode;
}

void FUN_00276e30(int value)
{
    htci_option = value;
}

int FUN_00276e40(void)
{
    return htci_option;
}

static char htci_root_dir[264] = {0};
static char htci_prefix[40] = {0};

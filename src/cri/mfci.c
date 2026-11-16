#include "dw4/cri/cvfs.h"

typedef struct MfCiFile {
    signed char used;       /* 0x00 */
    signed char stat;       /* 0x01 */
    char pad2[2];
    int sctsize;            /* 0x04 */
    int size;               /* 0x08 */
    int nsct;               /* 0x0c */
    int pos;                /* 0x10 */
    int nbyte;              /* 0x14 */
    int reqsct;             /* 0x18 */
    char name[20];          /* 0x1c */
    int ofs;                /* 0x30 */
    int len;                /* 0x34 */
} MfCiFile;



unsigned int strlen(const char *s);
int sprintf(char *dst, const char *format, ...);
char *strcpy(char *dst, const char *src);
void *memcpy(void *dst, const void *src, unsigned int n);
void *memset(void *dst, int value, unsigned int n);
unsigned long strtoul(const char *s, char **end, int base);
void SVM_Lock(void);
void SVM_Unlock(void);

void mfCiExecServer(void);
void mfCiEntryErrFunc(void (*func)(void *context, const char *message, void *detail), void *context);
int mfCiGetFileSize(char *name);
MfCiFile *mfCiOpen(const char *fname, int reserved, int rw);
int mfCiClose(MfCiFile *fh);
int mfCiSeek(MfCiFile *fh, int offset, int origin);
int mfCiTell(MfCiFile *fh);
int mfCiReqRd(MfCiFile *fh, int nsct, char *buf);
void mfCiStopTr(MfCiFile *fh);
char mfCiGetStat(MfCiFile *fh);
int mfCiGetSctLen(MfCiFile *fh);
void mfCiSetSctLen(MfCiFile *fh, int sctsize);
int mfCiGetNumTr(MfCiFile *fh);

static char *volatile mfci_build = "\nMFCI/PS2EE Ver.1.09 Build:Oct  6 2004 11:47:43\n";
static void (*mfci_err_func)(void *context, const char *message, void *detail) = 0;
static void *mfci_err_obj = 0;
static CvFsVtbl mfci_vtbl = {
    (int)mfCiExecServer, (int)mfCiEntryErrFunc, (int)mfCiGetFileSize, 0,
    (int)mfCiOpen, (int)mfCiClose, (int)mfCiSeek, (int)mfCiTell,
    (int)mfCiReqRd, 0, (int)mfCiStopTr, (int)mfCiGetStat,
    (int)mfCiGetSctLen, (int)mfCiSetSctLen, (int)mfCiGetNumTr, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
static MfCiFile mfci_files[40] = {0};
static char mfci_msg[304] = {0};

void mfCiStopTr(MfCiFile *fh);

void mfCrsLock(void)
{
    SVM_Lock();
}

void mfCrsUnlock(void)
{
    SVM_Unlock();
}

CvFsVtbl *mfCiGetInterface(void)
{
    mfci_build;
    return &mfci_vtbl;
}

void mfci_call_errfn(void *detail, const char *message)
{
    if (mfci_err_func != 0) {
        mfci_err_func(mfci_err_obj, message, detail);
    }
}

unsigned long FUN_00277e18(const char *s, char **end, int base)
{
    return strtoul(s, end, base);
}

char *mfci_get_adr_size(char *name, int *size)
{
    char *p;
    char *data;

    if (strlen(name) != 17) {
        sprintf(mfci_msg, "E01100308:length of '%s' is not 17 bytes.(mfci_get_adr_size)", name);
        mfci_call_errfn(0, mfci_msg);
    }
    if (name[8] != '.') {
        sprintf(mfci_msg, "E01100309:illegal file name format '%s'(mfci_get_adr_size)", name);
        mfci_call_errfn(0, mfci_msg);
    }
    p = name;
    data = (char *)FUN_00277e18(p, &p, 16);
    if (*p != 0) {
        p++;
    }
    if (size != 0) {
        *size = FUN_00277e18(p, &p, 16);
    }
    return data;
}

void mfCiExecHndl(MfCiFile *fh)
{
}

void mfCiExecServer(void)
{
    int i;
    MfCiFile *fh;

    fh = mfci_files;
    i = 0x27;
    do {
        if (fh->used != 0) {
            mfCiExecHndl(fh);
        }
        i -= 1;
        fh += 1;
    } while (i >= 0);
}

void mfCiEntryErrFunc(void (*func)(void *context, const char *message, void *detail), void *context)
{
    mfci_err_func = func;
    mfci_err_obj = context;
}

int mfCiGetFileSize(char *name)
{
    int size;

    mfci_get_adr_size(name, &size);
    return size;
}

MfCiFile *mfci_alloc(void)
{
    MfCiFile *found = 0;
    int i;

    for (i = 0; i < 40; i++) {
        if (mfci_files[i].used == 0) {
            found = &mfci_files[i];
            break;
        }
    }
    return found;
}

void mfci_free(MfCiFile *fh)
{
    memset(fh, 0, 0x38);
}

void mfci_reset_hn(MfCiFile *fh)
{
    int size;

    fh->sctsize = 0x800;
    size = mfCiGetFileSize(fh->name);
    fh->size = size;
    fh->nsct = (size + fh->sctsize - 1) / fh->sctsize;
    fh->used = 1;
    fh->reqsct = 0;
    fh->nbyte = 0;
    fh->stat = 0;
    fh->pos = 0;
}

MfCiFile *mfCiOpen(const char *fname, int reserved, int rw)
{
    MfCiFile *fh;

    if (fname == 0) {
        mfci_call_errfn(0, "E01100301:fname is null.(mfCiOpen)");
        return 0;
    }
    if (rw != 0) {
        mfci_call_errfn(0, "E01100302:rw is illigal.(mfCiOpen)");
        return 0;
    }
    fh = mfci_alloc();
    if (fh == 0) {
        mfci_call_errfn(0, "E01100303:not enough handle resource.(mfCiOpen)");
        return 0;
    }
    strcpy(fh->name, fname);
    mfci_reset_hn(fh);
    return fh;
}

/* matching construct: hand search — int return type with no return value (implicit-int style); a void
   return type lets GCC turn the last call into a sibling call */
int mfCiClose(MfCiFile *fh)
{
    if (fh != 0) {
        mfCiStopTr(fh);
        if (fh->used == 1) {
            fh->used = 0;
            mfci_free(fh);
        }
    }
}

int mfCiSeek(MfCiFile *fh, int offset, int origin)
{
    int pos;

    if (fh == 0) {
        mfci_call_errfn(fh, "E01100305:handl is null.");
        return 0;
    }
    mfCrsLock();
    if (origin == 0) {
        fh->pos = offset;
    } else if (origin == 2) {
        fh->pos = fh->nsct + offset;
    } else if (origin == 1) {
        fh->pos += offset;
    }
    pos = fh->pos;
    if (pos >= fh->nsct) {
        pos = fh->nsct;
    }
    if (pos < 0) {
        pos = 0;
    }
    fh->pos = pos;
    mfCrsUnlock();
    return fh->pos;
}

int mfCiTell(MfCiFile *fh)
{
    if (fh == 0) {
        mfci_call_errfn(0, "E01100306:handl is null.");
        return 0;
    }
    return fh->pos;
}

int mfCiReqRd(MfCiFile *fh, int nsct, char *buf)
{
    char *data;
    int size;
    int n;
    int ofs;
    int len;
    int avail;

    if (fh == 0) {
        mfci_call_errfn(fh, "E01100307:handl is null.");
        return 0;
    }
    if (nsct < 0) {
        mfci_call_errfn(fh, "E01100308:nsct < 0.(mfCiReqRd)");
        return 0;
    }
    if (buf == 0) {
        mfci_call_errfn(fh, "E01100309:buf is null.(mfCiReqRd)");
        return 0;
    }
    if (nsct == 0) {
        fh->stat = 1;
        return 0;
    }
    if (fh->stat == 2) {
        return 0;
    }
    mfCrsLock();
    fh->nbyte = 0;
    n = fh->nsct - fh->pos;
    if (nsct < n) {
        n = nsct;
    }
    fh->reqsct = n;
    ofs = fh->pos * fh->sctsize;
    len = n * fh->sctsize;
    if (len == 0) {
        fh->stat = 1;
        mfCrsUnlock();
        return 0;
    }
    fh->ofs = ofs;
    fh->len = len;
    fh->stat = 2;
    data = mfci_get_adr_size(fh->name, &size);
    avail = (size - fh->ofs < fh->len) ? size - fh->ofs : fh->len;
    mfCrsUnlock();
    memcpy(buf, data + fh->ofs, fh->len);
    memset(buf + avail, 0, fh->len - avail);
    mfCrsLock();
    fh->stat = 1;
    fh->pos += fh->reqsct;
    fh->nbyte = fh->reqsct * fh->sctsize;
    mfCrsUnlock();
    return fh->reqsct;
}

void mfCiStopTr(MfCiFile *fh)
{
    if (fh == 0) {
        mfci_call_errfn(0, "E0092912:handl is null.");
        return;
    }
    mfCrsLock();
    fh->stat = 0;
    mfCrsUnlock();
}

char mfCiGetStat(MfCiFile *fh)
{
    if (fh == 0) {
        mfci_call_errfn(fh, "E0092912:handl is null.");
        return 0;
    }
    return fh->stat;
}

int mfCiGetSctLen(MfCiFile *fh)
{
    if (fh == 0) {
        mfci_call_errfn(0, "E0040301:handl is null.");
        return 0;
    }
    return fh->sctsize;
}

void mfCiSetSctLen(MfCiFile *fh, int sctsize)
{
    int old;
    int pos;

    if (fh == 0) {
        mfci_call_errfn(fh, "E0040302:handl is null.");
        return;
    }
    pos = fh->pos;
    old = fh->sctsize;
    fh->sctsize = sctsize;
    fh->nsct = (fh->size + sctsize - 1) / sctsize;
    fh->pos = pos * old / sctsize;
    fh->nbyte = fh->reqsct * sctsize;
}

int mfCiGetNumTr(MfCiFile *fh)
{
    if (fh == 0) {
        mfci_call_errfn(0, "E0092912:handl is null.");
        return 0;
    }
    return fh->nbyte;
}

MfCiFile *mfCiOpenEntry(int entry, int reserved, int rw)
{
    MfCiFile *fh;

    if (entry <= 0) {
        mfci_call_errfn(0, "E1041001:invalid entry number.(mfCiOpenEntry)");
        return 0;
    }
    if (rw != 0) {
        mfci_call_errfn(0, "E1041002:rw is illigal.(mfCiOpenEntry)");
        return 0;
    }
    fh = mfci_alloc();
    if (fh == 0) {
        mfci_call_errfn(0, "E1041002:not enough handle resource.(mfCiOpenEntry)");
        return 0;
    }
    mfci_reset_hn(fh);
    return fh;
}

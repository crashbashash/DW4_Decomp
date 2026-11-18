#include "dw4/cri/cri_cvfs.h"
#include <stdlib.h>
#include <string.h>
#include "dw4/cri/svm.h"
#include "dw4/cri/cri_srd.h"
#include "dw4/cri/dvci.h"
#include "dw4/cri/htci.h"
#include "dw4/cri/adxmsg.h"
#include "dw4/sony/libkernl.h"

typedef struct DvCiFile {
    signed char used;       /* 0x00 */
    signed char cached;     /* 0x01 */
    signed char state;      /* 0x02 */
    signed char instat;     /* 0x03 */
    unsigned int size;      /* 0x04 */
    int nsct;               /* 0x08 */
    int pos;                /* 0x0c */
    int req;                /* 0x10 */
    int done;               /* 0x14 */
    char *buf;              /* 0x18 */
    SrdObj *stm;            /* 0x1c */
    sceCdlFILE fp;          /* 0x20 */
    sceCdRMode rmode;       /* 0x44 */
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

void dvCiExecServer(void);
void dvCiEntryErrFunc(void (*callback)(void *context, const char *message, void *detail), void *context);
int dvCiGetFileSize(const char *fname);
DvCiFile *dvCiOpen(const char *fname, void *atr, int rw);
void dvCiClose(DvCiFile *h);
int dvCiSeek(DvCiFile *h, int offset, int origin);
int dvCiTell(DvCiFile *h);
int dvCiReqRd(DvCiFile *h, int nsct, char *buf);
void dvCiStopTr(DvCiFile *h);
int dvCiGetStat(DvCiFile *h);
int dvCiGetSctLen(void);
int dvCiGetNumTr(DvCiFile *h);
int dvCiIsExistFileOnDisc(const char *name);
int dvCiOptFn1(void *obj, int code);

static char *volatile dvci_build = "\nDVCI/PS2EE Ver.2.71 Build:Oct  6 2004 11:47:41\n";
static void (*dvci_err_func)(void *context, const char *message, void *detail) = 0;
static void *dvci_err_obj = 0;
static int dvci_layer = 0;
static int dvci_lock = 0;
static CvFsVtbl dvci_vtbl = {
    dvCiExecServer, (CvFsEntryErrFuncFn)dvCiEntryErrFunc, dvCiGetFileSize, 0,
    (CvFsOpenFn)dvCiOpen, (CvFsFdFn)dvCiClose, (CvFsSeekFn)dvCiSeek, (CvFsFdIntFn)dvCiTell,
    (CvFsXferFn)dvCiReqRd, 0, (CvFsFdFn)dvCiStopTr, (CvFsFdIntFn)dvCiGetStat,
    (CvFsFdIntFn)dvCiGetSctLen, 0, (CvFsFdIntFn)dvCiGetNumTr, 0,
    dvCiIsExistFileOnDisc, 0, 0, 0, 0, 0, 0, 0, dvCiOptFn1, 0
};
static DvCiFile dvci_files[40] = {0};
static char dvci_path[304] = {0};
static DvCiTable dvci_dir_table = {0};
static sceCdRMode dvci_rdmode = {0};
static int dvci_rd_sync = 0;
static int dvci_option = 0;
static char dvci_root_dir[264];
static char dvci_dir_path[128];
static char dvci_dir_buf[4096];

void dvci_to_large_to_yen(char *path);
void dvCiStopTr(DvCiFile *h);
int dvCiGetStat(DvCiFile *h);
void dvci_conv_fname(const char *name, char *path);
void get_fp_from_fname(sceCdlFILE *out, const char *name, DvCiFileLoc *files, int n);
int dvci_get_fstate(const char *name, sceCdlFILE *fp);

CvFsVtbl *dvCiGetInterface(void)
{
    dvci_build;
    dvCiSetRootDir(0);
    return &dvci_vtbl;
}

void dvci_call_errfn(void *detail, const char *message)
{
    if (dvci_err_func != 0) {
        dvci_err_func(dvci_err_obj, message, detail);
    }
}

int dvCiCdSearchFile(sceCdlFILE *fp, const char *name)
{
    int result;
    SRD_SetHistory(0x8000);
    result = sceCdLayerSearchFile(fp, name, dvci_layer);
    SRD_SetHistory(0x8001);
    return result;
}

int dvci_is_exec_hn(void)
{
    int i;
    for (i = 0; i < 40; i++) {
        if (dvci_files[i].used == 1 && dvci_files[i].state == 2) {
            return 1;
        }
    }
    return 0;
}

void dvCiExecHndl(DvCiFile *h)
{
    if (h->stm == 0)
        return;
    SVM_LockVar();
    switch (SRD_GetStat(h->stm)) {
    case 9:
        h->state = 3;
        SRD_Destroy(h->stm);
        h->stm = 0;
        break;
    case 3:
        h->done = h->req;
        h->pos += h->req;
        h->state = 1;
        SRD_Destroy(h->stm);
        h->stm = 0;
        break;
    case 0:
        h->state = 0;
        SRD_Destroy(h->stm);
        h->stm = 0;
        break;
    case 1: case 2: case 4: case 5: case 6: case 7: case 8:
        break;
    }
    SVM_UnlockVar();
}

void dvCiExecServer(void)
{
    int i;
    if (SVM_TestAndSet(&dvci_lock) != 0) {
        for (i = 0; i < 40; i++) {
            if (dvci_files[i].used == 1) {
                dvCiExecHndl(&dvci_files[i]);
            }
        }
        dvci_lock = 0;
    }
}

void dvCiEntryErrFunc(void (*callback)(void *context, const char *message, void *detail), void *context)
{
    dvci_err_func = callback;
    dvci_err_obj = context;
}

void dvci_to_large_to_yen(char *path)
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

int dvCiIsExistFileOnDisc(const char *name)
{
    sceCdlFILE fp;
    if (name == 0) {
        return 0;
    }
    dvci_get_fstate(name, &fp);
    if (fp.size == 0) {
        dvci_conv_fname(name, dvci_path);
        SRD_SetHistory(0x8100);
        sceCdSync(0);
        SRD_SetHistory(0x8101);
        if (dvCiCdSearchFile(&fp, dvci_path) == 0) {
            return 0;
        }
    }
    return 1;
}

int dvCiGetFileSize(const char *fname)
{
    sceCdlFILE fp;
    if (fname == 0) {
        dvci_call_errfn(0, "E0092901:fname is null.(dvCiGetFileSize)");
        return 0;
    }
    dvci_get_fstate(fname, &fp);
    if (fp.size == 0) {
        dvci_conv_fname(fname, dvci_path);
        SRD_SetHistory(0x8200);
        sceCdSync(0);
        SRD_SetHistory(0x8201);
        if (dvCiCdSearchFile(&fp, dvci_path) == 0) {
            ADXMSG_PrintErr("DVCI: sceCdSearchFile failed. \"%s\"\n", dvci_path);
            dvci_call_errfn(0, "E0092902:can't find file.(dvCiGetFileSize)");
            return 0;
        }
    }
    return fp.size;
}

DvCiFile *dvci_alloc(void)
{
    DvCiFile *found = 0;
    int i;
    for (i = 0; i < 40; i++) {
        if (dvci_files[i].used == 0)
            found = &dvci_files[i];
    }
    return found;
}

void dvci_free(DvCiFile *h)
{
    memset(h, 0, sizeof(DvCiFile));
}

DvCiFile *dvCiOpen(const char *fname, void *atr, int rw)
{
    DvCiFile *h;
    int ret;
    if (fname == 0) {
        dvci_call_errfn(0, "E0092908:fname is null.(dvCiOpen)");
        return 0;
    }
    if (rw != 0) {
        dvci_call_errfn(0, "E0092909:rw is illigal.(dvCiOpen)");
        return 0;
    }
    h = dvci_alloc();
    if (h == 0) {
        dvci_call_errfn(0, "E0092910:not enough handle resource.(dvCiOpen)");
        return 0;
    }
    ret = dvci_get_fstate(fname, &h->fp);
    if (h->fp.size == 0) {
        dvci_conv_fname(fname, dvci_path);
        ADXMSG_PrintErr("DVCI: File cache was not hit. \"%s\"\n", dvci_path);
        SRD_SetHistory(0x8300);
        sceCdSync(0);
        SRD_SetHistory(0x8301);
        if (dvCiCdSearchFile(&h->fp, dvci_path) == 0) {
            dvci_call_errfn(0, "E0092911:sceCdSearchFile fail.(dvCiOpen)");
            dvci_free(h);
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

void dvCiClose(DvCiFile *h)
{
    if (h != 0) {
        if ((unsigned char)h->state >= 2) {
            dvCiStopTr(h);
        }
        h->used = 0;
        dvci_free(h);
    }
}

int dvCiSeek(DvCiFile *h, int offset, int origin)
{
    int position;
    if (h == 0) {
        dvci_call_errfn(h, "E0092912:handl is null.");
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

int dvCiTell(DvCiFile *h)
{
    if (h == 0) {
        dvci_call_errfn(0, "E0092912:handl is null.");
        return 0;
    }
    return h->pos;
}

int dvCiReqRd(DvCiFile *h, int nsct, char *buf)
{
    int n, rem;
    int ready;
    if (h == 0) {
        dvci_call_errfn(h, "E0092912:handl is null.");
        return 0;
    }
    if (nsct < 0) {
        dvci_call_errfn(h, "E0092913:nsct < 0.(dvCiReqRd)");
        return 0;
    }
    if (buf == 0) {
        dvci_call_errfn(h, "E0092914:buf is null.(dvCiReqRd)");
        return 0;
    }
    if (h->state == 2)
        return 0;
    if (nsct == 0) {
        h->state = 1;
        return 0;
    }
    h->stm = SRD_Create();
    if (h->stm == 0)
        return 0;
    rem = h->nsct - h->pos;
    n = nsct < rem ? nsct : rem;
    h->rmode.trycount = dvci_rdmode.trycount;
    h->rmode.spindlctrl = dvci_rdmode.spindlctrl;
    h->rmode.datapattern = dvci_rdmode.datapattern;
    h->buf = buf;
    h->req = n;
    InvalidDCache(buf, buf + (n << 11) - 1);
    if (SRD_ReqRdDvd(h->stm, h->fp.lsn + h->pos, h->req, h->buf, &h->rmode) == 0) {
        SRD_Destroy(h->stm);
        return 0;
    }
    ready = dvci_rd_sync;
    if (ready == 1) {
        sceCdSync(0);
        SRD_WaitForExecServer();
        SRD_ExecServer();
        SRD_WaitComplete(h->stm);
        SRD_Destroy(h->stm);
        h->stm = 0;
        h->done = nsct;
        h->state = ready;
        h->pos += h->req;
    } else {
        h->state = 2;
    }
    return h->req;
}

void dvCiStopTr(DvCiFile *h)
{
    int i;
    i = 0;
    if (h == 0) {
        dvci_call_errfn(0, "E0092912:handl is null.");
        return;
    }
    if ((unsigned char)h->state < 2) {
        return;
    }
    if (h->stm != 0) {
        SRD_Break(h->stm);
    }
    while (1) {
        SRD_ExecServer();
        dvCiExecServer();
        dvCiGetStat(h);
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

int dvCiGetStat(DvCiFile *h)
{
    if (h == 0) {
        dvci_call_errfn(0, "E0092912:handl is null.");
        return 0;
    }
    return h->state;
}

int dvCiGetSctLen(void)
{
    return 0x800;
}

int dvCiGetNumTr(DvCiFile *h)
{
    if (h == 0) {
        dvci_call_errfn(0, "E0092912:handl is null.");
        return 0;
    }
    if (h->state == 1) {
        return h->done << 11;
    }
    return 0;
}

void dvCiSetOutputDebugLevel(int value)
{
    dvci_option = value;
}

int dvCiGetOutputDebugLevel(void)
{
    return dvci_option;
}

void dvCiSetDvdLayer(unsigned int layer)
{
    dvci_layer = layer;
    if (layer >= 2) {
        dvci_layer = 0;
    }
}

int dvCiGetDvdLayer(void)
{
    return dvci_layer;
}

int dvci_getfilesize32(const char *fname)
{
    sceCdlFILE fp;
    dvci_get_fstate(fname, &fp);
    if (fp.size == 0) {
        dvci_conv_fname(fname, dvci_path);
        SRD_SetHistory(0x8400);
        sceCdSync(0);
        SRD_SetHistory(0x8401);
        if (dvCiCdSearchFile(&fp, dvci_path) == 0) {
            ADXMSG_PrintErr("DVCI: sceCdSearchFile failed. \"%s\"\n", dvci_path);
            return 0;
        }
    }
    return fp.size;
}

int dvci_getnumtr_upper(h)
    DvCiFile *h;
{
    return (long)h->done * 2048 >> 32;
}

int dvci_getnumtr_lower(h)
    DvCiFile *h;
{
    return ((long long)h->done << 11) & 0xFFFFFFFF;
}

int dvci_filesize_upper(fname)
    const char *fname;
{
    return 0;
}

int dvci_filesize_lower(fname)
    const char *fname;
{
    return dvci_getfilesize32(fname);
}

/* matching construct: old-style getter definitions called with no arguments; retail never loads a0 before these calls */
int dvCiOptFn1(void *obj, int code)
{
    int result;
    result = 0;
    if (obj == 0) {
        return 0;
    }
    switch (code) {
    case 200:
        result = dvci_getnumtr_upper();
        break;
    case 201:
        result = dvci_getnumtr_lower();
        break;
    case 202:
    case 204:
        result = dvci_filesize_upper();
        break;
    case 203:
    case 205:
        result = dvci_filesize_lower();
        break;
    case 299:
        result = 1;
        break;
    }
    return result;
}

void dvci_conv_fname(const char *name, char *path)
{
    char c;
    strcpy(path, dvci_root_dir);
    c = *name;
    if (c != '/' && c != '\\') {
        strcat(path, "\\");
    }
    strcat(path, name);
    if (strcmp(path + strlen(path) - 2, ";1") != 0) {
        strcat(path, ";1");
    }
    dvci_to_large_to_yen(path);
}

char dvci_conv_cmp(char c)
{
    char upper;
    upper = c;
    if ((unsigned int)(upper - 'a') < 26) {
        upper -= 32;
    }
    return ((c ^ 0x5C) != 0) ? upper : 0x2F;
}

int dvci_charicmp(char a, char b)
{
    int ca;
    ca = dvci_conv_cmp(a);
    return ((ca ^ dvci_conv_cmp(b)) != 0) ? -1 : 0;
}

int dvci_stricmp(const char *a, const char *b)
{
    int len;
    int i;
    len = strlen(a);
    if (len != strlen(b)) {
        return -1;
    }
    for (i = 0; i < len; i++) {
        if (dvci_charicmp(a[i], b[i]) != 0) {
            return -1;
        }
    }
    return 0;
}

int dvci_analysis_flist(char *buf, char *list, int listlen, int n, int nameLen)
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
            dvci_to_large_to_yen(dst);
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
    if (dvci_dir_table.files == 0) {
        dvci_dir_table.files = (int)buf;
        dvci_dir_table.nfiles = count;
        dvci_dir_table.nent = n;
        dvci_dir_table.namelen = nameLen;
    }
    return count;
}

int load_flist(const char *path, void *buf)
{
    sceCdlFILE fp;
    sceCdRMode mode;
    char dev[5];
    memcpy(dev, path, 5);
    dev[4] = 0;
    if (strcasecmp(dev, "HST:") == 0) {
        return htci_load_flist(path + 4, buf);
    }
    memset(dvci_dir_path, 0, 128);
    dvci_conv_fname(path, dvci_dir_path);
    SRD_SetHistory(0x9000);
    while (sceCdSync(1) == 1) {
    }
    SRD_SetHistory(0x9001);
    SRD_SetHistory(0x9100);
    if (dvCiCdSearchFile(&fp, dvci_dir_path) == 0) {
        SRD_SetHistory(0x9101);
        return 0;
    }
    SRD_SetHistory(0x9102);
    mode.trycount = 0;
    mode.spindlctrl = 1;
    mode.datapattern = 0;
    mode.pad = 0;
    SRD_SetHistory(0x9200);
    if (sceCdRead(fp.lsn, 2, buf, &mode) == 0) {
        SRD_SetHistory(0x9201);
        return 0;
    }
    SRD_SetHistory(0x9202);
    SRD_SetHistory(0x9300);
    while (sceCdSync(1) == 1) {
    }
    SRD_SetHistory(0x9301);
    return 1;
}

int search_fstate(DvCiFileLoc *files, int n)
{
    sceCdlFILE fp;
    int missing;
    int found = 0;
    int i;
    char *name;
    missing = 0;
    for (i = 0; i < n; i++) {
        name = (char *)files + ((dvci_dir_table.nent << 3) + (dvci_dir_table.namelen * i + i));
        if (*name == 0)
            continue;
        dvci_conv_fname(name, dvci_dir_path);
        SRD_SetHistory(0x9400);
        while (sceCdSync(1) == 1)
            ;
        SRD_SetHistory(0x9401);
        SRD_SetHistory(0x9500);
        if (dvCiCdSearchFile(&fp, dvci_dir_path) == 1) {
            SRD_SetHistory(0x9501);
            found++;
            files[i].lsn = fp.lsn;
            files[i].size = fp.size;
            ADXPS2_PrintfWarn("DVCI: \"%s\" found.\n", name);
        } else {
            SRD_SetHistory(0x9502);
            missing++;
            ADXPS2_PrintfWarn("DVCI: \"%s\" Not found.\n", name);
        }
    }
    ADXPS2_PrintfWarn("DVCI: Total %d files.\n", found);
    if (missing > 0)
        ADXMSG_PrintErr("DVCI: Warning, Can't load all cache file.%c", 10);
    return found;
}

void get_fp_from_fname(sceCdlFILE *out, const char *name, DvCiFileLoc *files, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        if (dvci_stricmp(name, (char *)files + ((dvci_dir_table.nent << 3) + (dvci_dir_table.namelen * i + i))) == 0) {
            out->lsn = files[i].lsn;
            out->size = files[i].size;
            return;
        }
    }
    out->lsn = 0;
    out->size = 0;
}

void dvci_init_flist(void)
{
    memset(&dvci_dir_table, 0, sizeof(DvCiTable));
}

int dvci_is_lsn_fname(const char *name)
{
    if (strlen(name) != 17) {
        return 0;
    }
    return name[8] == '.';
}

int dvci_get_lsn_fname(const char *name, int *lsn, int *nsct)
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
    ADXPS2_PrintfWarn("DVCI: \"%s\" opened. ", name);
    ADXPS2_PrintfWarn("LSN=%d, ", *lsn);
    ADXPS2_PrintfWarn("Size=%d[sector]\n", *nsct);
    return 1;
}

int dvci_get_fstate(const char *name, sceCdlFILE *fp)
{
    int lsn;
    int nsct;
    if (strcmp("DVD-ROM", name) == 0) {
        fp->size = -1;
        fp->lsn = 0;
        ADXMSG_PrintErr("DVCI: CD/DVD-ROM Image opened%c\n", '.');
        return 1;
    }
    if (dvci_is_lsn_fname(name) == 1) {
        dvci_get_lsn_fname(name, &lsn, &nsct);
        fp->lsn = lsn;
        fp->size = nsct << 11;
        return 0;
    }
    fp->lsn = 0;
    fp->size = 0;
    if (dvci_dir_table.files != 0) {
        get_fp_from_fname(fp, name, (DvCiFileLoc *)dvci_dir_table.files, dvci_dir_table.nfiles);
    }
    return 0;
}

int dvCiLoadFcache(const char *path, char *buf, unsigned int size, int nameLen)
{
    int n;
    int found;
    memset(dvci_dir_buf, 0, 4096);
    if (dvci_dir_table.files != 0) {
        dvci_init_flist();
    }
    if (path == 0 || buf == 0 || size == 0) {
        dvci_init_flist();
    }
    if (path == 0) {
        return 0;
    }
    if (buf == 0) {
        ADXPS2_PrintfWarn("DVCI: Invalidate filelist buffer pointer.\r\n", 0);
        return 0;
    }
    if (size == 0) {
        ADXPS2_PrintfWarn("DVCI: Invalidate filelist buffer size.\r\n", 0);
        return 0;
    }
    memset(buf, 0, size);
    if (load_flist(path, dvci_dir_buf) == 0) {
        ADXPS2_PrintfWarn("DVCI: Can't read filelist file.(%s)\n", path);
        dvci_call_errfn(0, "E0111501:can't read filelist.(dvCiLoadDirInfo)");
        return 0;
    }
    n = dvci_analysis_flist(buf, dvci_dir_buf, 4096, size / (nameLen + 9), nameLen);
    found = search_fstate((DvCiFileLoc *)buf, n);
    return size / (nameLen + 9) * 8 + found * (nameLen + 1);
}

int dvCiSetFcache(char *list, int listlen, char *buf, unsigned int size, int nameLen)
{
    int n;
    int found;
    memset(dvci_dir_buf, 0, 4096);
    if (dvci_dir_table.files != 0) {
        dvci_init_flist();
    }
    if (list == 0 || buf == 0 || listlen == 0 || size == 0) {
        dvci_init_flist();
    }
    if (list == 0) {
        return 0;
    }
    if (buf == 0) {
        ADXPS2_PrintfWarn("DVCI: Invalidate filelist buffer pointer.\r\n", 0);
        return 0;
    }
    if (listlen == 0 || size == 0) {
        ADXPS2_PrintfWarn("DVCI: Invalidate filelist buffer size.\r\n", 0);
        return 0;
    }
    n = dvci_analysis_flist(buf, list, listlen, size / (nameLen + 9), nameLen);
    found = search_fstate((DvCiFileLoc *)buf, n);
    return size / (nameLen + 9) * 8 + found * (nameLen + 1);
}

int dvCiIsExistFcache(const char *name)
{
    sceCdlFILE fp;
    dvci_get_fstate(name, &fp);
    return fp.lsn != 0;
}

void dvCiSetRdMode(int trycount, int spindlctrl, int datapattern, int mode)
{
    dvci_rdmode.trycount = trycount;
    dvci_rdmode.spindlctrl = spindlctrl;
    dvci_rdmode.datapattern = datapattern;
    dvci_rd_sync = mode;
}

void dvCiSetRootDir(const char *path)
{
    char c;
    if (path == 0) {
        dvci_root_dir[0] = 0;
        return;
    }
    if (path[0] != '/' && path[0] != '\\') {
        strcpy(dvci_root_dir, "\\");
    } else {
        dvci_root_dir[0] = 0;
    }
    strcat(dvci_root_dir, path);
    c = path[strlen(path) - 1];
    if (c == '/' || c == '\\') {
        dvci_root_dir[strlen(dvci_root_dir) - 1] = 0;
    }
}

char *dvCiGetRootDir(void)
{
    return dvci_root_dir;
}

int dvCiSetSeekPos(int lsn)
{
    return SRD_SetDvdSeekPos(lsn);
}

static char dvci_root_dir[264] = {0};
static char dvci_dir_path[128] = {0};

/* CRI ADX on PS2, disc side: the disc and memory devices, the disc read mode and file cache, and memory files named by address. */
#include "dw4/cri/adxfs.h"

int sprintf(char *buf, const char *fmt, ...);

int dvCiLoadDirInfo(const char *flist, void *buf, int bufsize, int fnamelen);
int dvCiLoadDirInfoMem(const char *list, int listlen, void *buf, int bufsize, int fnamelen);
void dvCiSetRdMode(int trycount, int spindlctrl, int datapattern, int rdmode);
void dvCiSetRootDir(const char *rootdir);
int dvCiIsExistFile(const char *fname);
void dvCiSetLayer(unsigned int layer);
int dvCiGetLayer(void);
int dvCiSrdSeek(int lsn);
void ADXT_StartFname(void *adxt, const char *fname);
void ADXT_EntryFname(void *adxt, const char *fname);
void *ADXF_Open(const char *fname, void *dir);

extern int adxt_srd_rmode_sw;

void adxps2_dvd_errfn(void *obj, const char *msg, int code)
{
    ADXERR_CallErrFunc1(msg);
}

int ADXPS2_LoadFcacheDvd(AdxFcachePrm *prm)
{
    int size = 0;

    if (prm != 0) {
        size = dvCiLoadDirInfo(prm->flist, prm->buf, prm->bufsize, prm->fnamelen);
    } else {
        dvCiLoadDirInfo(0, 0, 0, 0);
    }
    return size;
}

int ADXPS2_LoadFcacheDvdMem(AdxFcachePrm *prm, const char *list, int listlen)
{
    int size = 0;

    if (prm != 0) {
        size = dvCiLoadDirInfoMem(list, listlen, prm->buf, prm->bufsize, prm->fnamelen);
    } else {
        dvCiLoadDirInfo(0, 0, 0, 0);
    }
    return size;
}

void ADXPS2_SetDvdFsPrm(AdxDvdFsPrm *prm)
{
    if (prm != 0) {
        dvCiSetRdMode(prm->trycount, prm->spindlctrl, prm->datapattern, prm->rdmode);
        dvCiSetRootDir(prm->rootdir);
        return;
    }
    dvCiSetRdMode(0, 0, 0, 0);
    dvCiSetRootDir(0);
}

int ADXPS2_IsExistFileDvd(const char *fname)
{
    return dvCiIsExistFile(fname);
}

void ADXPS2_SetDvdLayer(unsigned int layer)
{
    dvCiSetLayer(layer);
}

int ADXPS2_GetDvdLayer(void)
{
    return dvCiGetLayer();
}

int ADXPS2_SeekDvd(int lsn)
{
    return dvCiSrdSeek(lsn);
}

/* A memory file is named by its address and its size in sectors. */
void ADXT_StartMfs(void *adxt, void *addr, unsigned int size)
{
    char fname[32];

    sprintf(fname, "%08x.%08x", addr, (size + 2047) / 2048);
    ADXT_StartFname(adxt, fname);
}

void ADXT_EntryMfs(void *adxt, void *addr, unsigned int size)
{
    char fname[32];

    sprintf(fname, "%08x.%08x", addr, (size + 2047) / 2048);
    ADXT_EntryFname(adxt, fname);
}

void *ADXF_OpenMfs(void *addr, unsigned int size, void *dir)
{
    char fname[32];

    sprintf(fname, "%08x.%08x", addr, (size + 2047) / 2048);
    return ADXF_Open(fname, dir);
}

void ADXT_SetSrdRmodeSw(int sw)
{
    adxt_srd_rmode_sw = sw;
}

int ADXT_GetSrdRmodeSw(void)
{
    return adxt_srd_rmode_sw;
}

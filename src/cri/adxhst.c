/* CRI ADX on PS2, host side: the host and memory devices, the host open mode, root folder and file cache. */
#include "dw4/cri/adxfs.h"

void *htCiGetInterface(void);
void htCiSetOpenMode(int mode);
void htCiSetRootDir(const char *rootdir);
int htCiLoadDirInfo(const char *flist, void *buf, int bufsize, int fnamelen);
int htCiIsExistFile(const char *fname);
void htCiSetHost64(int sw);
void htCiSetHostLock(int sw);

void adxps2_hst_errfn(void *obj, const char *msg, int code)
{
    ADXERR_CallErrFunc1(msg);
}

/* Host files are read through HST by default; MFS serves files already in memory. */
void ADXPS2_SetupHostFs(AdxHstFsPrm *prm)
{
    cvFsEntryErrFunc(adxps2_hst_errfn, 0);
    cvFsAddDev("MFS", mfCiGetInterface, 0);
    cvFsEntryErrFunc(adxps2_hst_errfn, 0);
    cvFsAddDev("HST", htCiGetInterface, 0);
    cvFsSetDefDev("HST");
    if (prm != 0) {
        htCiSetOpenMode(prm->openmode);
        htCiSetRootDir(prm->rootdir);
        if (prm->host64 == 0) {
            htCiSetHost64(0);
        } else {
            htCiSetHost64(1);
        }
        if (prm->hostlock == 0) {
            htCiSetHostLock(0);
            return;
        }
        htCiSetHostLock(1);
        return;
    }
    htCiSetOpenMode(0);
    htCiSetRootDir(0);
    htCiSetHost64(0);
    htCiSetHostLock(0);
}

int ADXPS2_LoadFcacheHst(AdxFcachePrm *prm)
{
    int size;

    if (prm != 0) {
        size = htCiLoadDirInfo(prm->flist, prm->buf, prm->bufsize, prm->fnamelen);
    } else {
        size = htCiLoadDirInfo(0, 0, 0, 0);
    }
    return size;
}

int ADXPS2_IsExistFileHst(const char *fname)
{
    return htCiIsExistFile(fname);
}

void ADXPS2_SetHstFsPrm(AdxHstFsPrm *prm)
{
    if (prm != 0) {
        htCiSetOpenMode(prm->openmode);
        htCiSetRootDir(prm->rootdir);
        return;
    }
    htCiSetOpenMode(0);
    htCiSetRootDir(0);
}

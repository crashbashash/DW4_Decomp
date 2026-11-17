/* CRI ADX on PS2, disc side: the disc and memory devices, the disc read mode and file cache, and memory files named by address. */
#include "dw4/cri/adx_ps2.h"
#include <stdio.h>
#include "dw4/cri/cri_adxt.h"
#include "dw4/cri/adxerrs.h"
#include "dw4/cri/cri_adxf.h"
#include "dw4/cri/cri_cvfs.h"
#include "dw4/cri/dvci.h"
#include "dw4/cri/mfci.h"


/* the build string in two parts, read so it is linked */
extern volatile char adxrt_build[16];
extern volatile char adxrt_build_ver[29];

void adxps2_err_dvd(void *obj, const char *msg, int code)
{
    ADXERR_CallErrFunc1(msg);
}

void ADXPS2_SetupDvdFs(AdxDvdFsPrm *prm)
{
    adxrt_build;
    adxrt_build_ver;
    cvFsEntryErrFunc(adxps2_err_dvd, 0);
    cvFsAddDev("MFS", mfCiGetInterface, 0);
    cvFsEntryErrFunc(adxps2_err_dvd, 0);
    cvFsAddDev("CDV", dvCiGetInterface, 0);
    cvFsSetDefDev("CDV");
    if (prm != 0) {
        dvCiSetRdMode(prm->trycount, prm->spindlctrl, prm->datapattern, prm->rdmode);
        dvCiSetRootDir(prm->rootdir);
        return;
    }
    dvCiSetRdMode(0, 0, 0, 0);
    dvCiSetRootDir(0);
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

int ADXPS2_LoadFcacheDvdMem(AdxFcachePrm *prm, char *list, int listlen)
{
    int size = 0;

    if (prm != 0) {
        size = dvCiLoadDirInfoMem(list, listlen, prm->buf, prm->bufsize, prm->fnamelen);
    } else {
        dvCiLoadDirInfo(0, 0, 0, 0);
    }
    return size;
}

void ADXPS2_SetRdModeDvd(AdxDvdFsPrm *prm)
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
    return dvCiIsExistFcache(fname);
}

void ADXPS2_SetDvdLayer(unsigned int layer)
{
    dvCiSetDvdLayer(layer);
}

int ADXPS2_GetDvdLayer(void)
{
    return dvCiGetDvdLayer();
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

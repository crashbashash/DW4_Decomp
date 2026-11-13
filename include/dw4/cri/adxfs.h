/* CRI ADX on PS2: the setup of the cvFs devices ADX reads through (disc, host, memory). */
#ifndef DW4_CRI_ADXFS_H
#define DW4_CRI_ADXFS_H

/* Disc file system: the root folder and the sceCd read mode. */
typedef struct AdxDvdFsPrm {
    const char *rootdir;
    int rdmode;
    int trycount;
    int spindlctrl;
    int datapattern;
} AdxDvdFsPrm;

/* Host file system: the root folder, the IOP open mode and the SRD host switches. */
typedef struct AdxHstFsPrm {
    const char *rootdir;
    int openmode;
    int host64;         /* nonzero: the 64-bit host file system */
    int hostlock;       /* nonzero: SRD holds its lock across host reads */
} AdxHstFsPrm;

/* A file list loaded in advance, so opening a listed file needs no search. */
typedef struct AdxFcachePrm {
    const char *flist;
    int fnamelen;       /* longest file name in the list */
    void *buf;
    int bufsize;
} AdxFcachePrm;

typedef void *(*AdxFsGetIfFn)(void);

void cvFsAddDev(char *devname, AdxFsGetIfFn get_if, void *prm);
void cvFsSetDefDev(char *devname);
void cvFsEntryErrFunc(void (*func)(void *obj, const char *msg, int code), void *obj);
void ADXERR_CallErrFunc1(const char *msg);
void *mfCiGetInterface(void);

#endif

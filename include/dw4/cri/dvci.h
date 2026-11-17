/* CRI DVCI: the cvFs device that reads files from the DVD through SRD, with a cache of file locations
 * loaded from a file list; src/cri/dvci.c. */
#ifndef DW4_CRI_DVCI_H
#define DW4_CRI_DVCI_H

#include "dw4/cri/cri_cvfs.h"

#ifdef __cplusplus
extern "C" {
#endif

CvFsVtbl *dvCiGetInterface(void);
void dvCiSetOutputDebugLevel(int value);
int dvCiGetOutputDebugLevel(void);
void dvCiSetDvdLayer(unsigned int layer);
int dvCiGetDvdLayer(void);
int dvCiLoadFcache(const char *path, char *buf, unsigned int size, int nameLen);
int dvCiSetFcache(char *list, int listlen, char *buf, unsigned int size, int nameLen);
int dvCiIsExistFcache(const char *name);
void dvCiSetRdMode(int trycount, int spindlctrl, int datapattern, int mode);
void dvCiSetRootDir(const char *path);
char *dvCiGetRootDir(void);

int dvCiSetSeekPos(int lsn);

#ifdef __cplusplus
}
#endif

#endif

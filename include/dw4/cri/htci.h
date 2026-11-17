/* CRI HTCI: the cvFs device that reads host files through SRD, with a cache of open files loaded from a
 * file list; src/cri/htci.c. */
#ifndef DW4_CRI_HTCI_H
#define DW4_CRI_HTCI_H

#include "dw4/cri/cri_cvfs.h"

#ifdef __cplusplus
extern "C" {
#endif

CvFsVtbl *htCiGetInterface(void);
int htci_load_flist(const char *name, void *buf);
int htCiLoadFcache(const char *path, void *buf, unsigned int size, int nameLen);
int htCiIsExistFcache(const char *name);
void htCiSetOpenMode(int mode);
void htCiSetRootDir(const char *path);
char *htCiGetRootDir(void);
void htCiSetAccessName(const char *prefix);
char *htCiGetAccessName(void);
void htCiSetOutputDebugLevel(int value);
int htCiGetOutputDebugLevel(void);

/* htCiSetFileSystem64.c, htCiGetFileSystem64.c, htCiSetLockHost.c, htCiGetLockHost.c: the SRD host switches */
void htCiSetFileSystem64(int sw);
int htCiGetFileSystem64(void);
void htCiSetLockHost(int sw);
int htCiGetLockHost(void);

#ifdef __cplusplus
}
#endif

#endif

/* sifdev.h - libkernl's file calls on IOP devices (Sony sifdev.h), served through the file-server RPC,
 * and the IOP reset and module-loading calls Sony declares beside them. */
#ifndef DW4_SONY_SIFDEV_H
#define DW4_SONY_SIFDEV_H

#ifdef __cplusplus
extern "C" {
#endif

int sceOpen(const char *name, int flag, ...);
int sceClose(int fd);
int sceRead(int fd, void *buf, int size);
int sceWrite(int fd, const void *buf, int size);
int sceLseek(int fd, int offset, int whence);
long long sceLseek64(int fd, long long offset, int whence);
int sceIoctl(int fd, int cmd, void *arg);
int sceDopen(const char *name);
int sceDclose(int fd);
int sceDread(int fd, void *buf);
int sceGetstat(const char *name, void *stat);
int sceFsReset(void);

int sceSifLoadModule(const char *path, int arglen, const char *args);
int sceSifLoadFileReset(void);
int sceSifSyncIop(void);
int sceSifRebootIop(const char *arg);
int sceSifInitIopHeap(void);
int sceSifSearchModuleByName(const char *name);

/* IOP heap: carve a block out of the IOP's memory (0 when none is left) and give it back. */
void *sceSifAllocIopHeap(unsigned int size);
int sceSifFreeIopHeap(void *addr);

#ifdef __cplusplus
}
#endif

#endif

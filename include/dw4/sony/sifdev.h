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
int sceDopen(const char *name);
int sceDclose(int fd);
int sceDread(int fd, void *buf);
int sceGetstat(const char *name, void *stat);
int sceFsReset(void);

int sceSifLoadModule(const char *path, int arglen, const char *args);
int sceSifLoadFileReset(void);
int sceSifSyncIop(void);
int sceSifRebootIop(const char *arg);

#ifdef __cplusplus
}
#endif

#endif

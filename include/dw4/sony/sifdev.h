/* sifdev.h - libkernl's file calls on IOP devices (Sony sifdev.h), served through the file-server RPC. */
#ifndef DW4_SONY_SIFDEV_H
#define DW4_SONY_SIFDEV_H

#ifdef __cplusplus
extern "C" {
#endif

int sceOpen(const char *name, int flag, ...);
int sceClose(int fd);
int sceRead(int fd, void *buf, int size);
int sceWrite(int fd, const void *buf, int size);

#ifdef __cplusplus
}
#endif

#endif

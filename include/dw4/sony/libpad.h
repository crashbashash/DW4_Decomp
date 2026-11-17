/* libpad.h - Sony libpad: the controller ports padman.irx serves, their state, modes and actuators. */
#ifndef DW4_SONY_LIBPAD_H
#define DW4_SONY_LIBPAD_H

#ifdef __cplusplus
extern "C" {
#endif

int scePadInit(int mode);
int scePadPortOpen(int port, int slot, void *area);
int scePadPortClose(int port, int slot);
int scePadGetState(int port, int slot);
int scePadGetReqState(int port, int slot);
int scePadInfoComb(int port, int slot, int term, int offs);
int scePadInfoMode(int port, int slot, int term, int offs);
int scePadSetMainMode(int port, int slot, int offs, int lock);
int scePadSetActDirect(int port, int slot, const unsigned char *data);
int scePadSetActAlign(int port, int slot, const unsigned char *data);
int scePadInfoPressMode(int port, int slot);
int scePadEnterPressMode(int port, int slot);
int scePadExitPressMode(int port, int slot);

#ifdef __cplusplus
}
#endif

#endif

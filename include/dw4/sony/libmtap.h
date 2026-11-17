/* libmtap.h - libmtap's EE side (Sony libmtap.h): the multitap calls, each an RPC to mtapman. */
#ifndef DW4_SONY_LIBMTAP_H
#define DW4_SONY_LIBMTAP_H

#ifdef __cplusplus
extern "C" {
#endif

int sceMtapInit(void);
int sceMtapPortOpen(int port);
int sceMtapPortClose(int port);
int sceMtapGetConnection(int port);
int sceMtapChangeThreadPriority(int high_priority, int low_priority);
int sceMtapGetModVersion(void);

#ifdef __cplusplus
}
#endif

#endif

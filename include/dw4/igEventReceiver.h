#ifndef DW4_IGEVENTRECEIVER_H
#define DW4_IGEVENTRECEIVER_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igEventReceiver_metaObject;
void igEventReceiver_Register(void);

#ifdef __cplusplus
}
#endif

#endif

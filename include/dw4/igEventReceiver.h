#ifndef DW4_IGEVENTRECEIVER_H
#define DW4_IGEVENTRECEIVER_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igEventReceiver_metaObject;
struct CallbackArray *igEventReceiver_Register(void);
struct igMetaObject *igEventReceiver_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

#ifndef DW4_IGNONREFCOUNTEDOBJECTSTACK_H
#define DW4_IGNONREFCOUNTEDOBJECTSTACK_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igNonRefCountedObjectStack_metaObject;
struct CallbackArray *igNonRefCountedObjectStack_Register(void);

struct igMetaObject *igNonRefCountedObjectStack_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

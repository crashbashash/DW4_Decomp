#ifndef DW4_IGANIMATIONDATABASE_H
#define DW4_IGANIMATIONDATABASE_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igAnimationDatabase_metaObject;
struct igMetaObject *igAnimationDatabase_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

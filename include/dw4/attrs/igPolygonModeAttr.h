#ifndef DW4_IGPOLYGONMODEATTR_H
#define DW4_IGPOLYGONMODEATTR_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igPolygonModeAttr_EnsureRegistered(void);
struct igMetaObject *igPolygonModeAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

#ifndef DW4_IGVIEWMODE_H
#define DW4_IGVIEWMODE_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igViewMode_metaObject;
void igViewMode_Register(void);
struct igMetaObject *igViewMode_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

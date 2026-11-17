#ifndef DW4_BEMODELCTRLHITBOX_H
#define DW4_BEMODELCTRLHITBOX_H

struct beModelCtrlHITBOX;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beModelCtrlHITBOX *beModelCtrlHITBOX_Create(int allocator);

extern struct igMetaObject *g_beModelCtrlHITBOX_metaObject;

#ifdef __cplusplus
}
#endif

#endif

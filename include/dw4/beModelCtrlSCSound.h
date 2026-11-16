#ifndef DW4_BEMODELCTRLSCSOUND_H
#define DW4_BEMODELCTRLSCSOUND_H

struct beModelCtrlSCSound;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beModelCtrlSCSound *beModelCtrlSCSound_Create(int allocator);

extern struct igMetaObject *g_beModelCtrlSCSound_metaObject;

#ifdef __cplusplus
}
#endif

#endif

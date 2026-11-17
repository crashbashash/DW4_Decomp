#ifndef DW4_BEMODELCTRLSCHITBOX_H
#define DW4_BEMODELCTRLSCHITBOX_H

struct beModelCtrlSCHitBox;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beModelCtrlSCHitBox *beModelCtrlSCHitBox_Create(int allocator);

extern struct igMetaObject *g_beModelCtrlSCHitBox_metaObject;

#ifdef __cplusplus
}
#endif

#endif

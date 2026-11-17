#ifndef DW4_BELUASTATE_H
#define DW4_BELUASTATE_H

struct beLuaState;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beLuaState *beLuaState_Create(int allocator);

extern struct igMetaObject *g_beLuaState_metaObject;

#ifdef __cplusplus
}
#endif

#endif

#ifndef DW4_BELUA_H
#define DW4_BELUA_H

struct beLua;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beLua *beLua_CreateInstance(int allocator);
void beLua_EnsureRegistered(void);
struct igMetaObject *beLua_GetOrCreateMetaObject(void);
void beLua_ResetLuaState(struct beLua *self);
int beLua__RunNamedChunk(struct beLua *self, const char *name, const char *given);

extern struct igMetaObject *g_beLua_metaObject;

#ifdef __cplusplus
}
#endif

#endif

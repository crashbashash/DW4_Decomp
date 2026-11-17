#ifndef DW4_IGAUDIOCONTEXT_H
#define DW4_IGAUDIOCONTEXT_H

struct igMetaObject;
struct igAudioContext;

#ifdef __cplusplus
extern "C" {
#endif

void igAudioContext_EnsureRegistered(void);
struct igMetaObject *igAudioContext_GetOrCreateMetaObject(void);
struct igAudioContext *igAudioContext_CreateInstance(int allocator);

#ifdef __cplusplus
}
#endif

#endif

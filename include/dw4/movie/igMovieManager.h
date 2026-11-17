#ifndef DW4_IGMOVIEMANAGER_H
#define DW4_IGMOVIEMANAGER_H

struct igMetaObject;
struct igMovieManager;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igMovieManager_metaObject;
void igMovieManager_EnsureRegistered(void);
struct igMetaObject *igMovieManager_GetOrCreateMetaObject(void);
struct igMovieManager *igMovieManager_CreateInstance(int allocator);

#ifdef __cplusplus
}
#endif

#endif

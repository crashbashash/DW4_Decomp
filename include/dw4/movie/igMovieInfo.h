#ifndef DW4_IGMOVIEINFO_H
#define DW4_IGMOVIEINFO_H

struct igMetaObject;
struct igMovieInfo;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igMovieInfo_metaObject;
struct igMovieInfo *igMovieInfo_Create(int allocator);
int igMovieInfo_GetTiling(struct igMovieInfo *movie, int *tileWidth, int *tileHeight, int *tilesAcross, int *tilesDown);

#ifdef __cplusplus
}
#endif

#endif

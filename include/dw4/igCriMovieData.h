#ifndef DW4_IGCRIMOVIEDATA_H
#define DW4_IGCRIMOVIEDATA_H

struct igMetaObject;
struct igCriMovieData;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igCriMovieData_metaObject;
struct igCriMovieData *igCriMovieData_Create(int allocator);

#ifdef __cplusplus
}
#endif

#endif

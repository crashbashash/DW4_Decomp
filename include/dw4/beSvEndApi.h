#ifndef DW4_BESVENDAPI_H
#define DW4_BESVENDAPI_H

struct beSvEndApi;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSvEndApi *beSvEndApi_Create(int allocator);

extern struct igMetaObject *g_beSvEndApi_metaObject;

#ifdef __cplusplus
}
#endif

#endif

#ifndef DW4_BESVSTARTAPI_H
#define DW4_BESVSTARTAPI_H

struct beSvStartApi;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSvStartApi *beSvStartApi_Create(int allocator);

extern struct igMetaObject *g_beSvStartApi_metaObject;

#ifdef __cplusplus
}
#endif

#endif

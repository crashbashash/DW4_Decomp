#ifndef DW4_BESVFILEFINDAPI_H
#define DW4_BESVFILEFINDAPI_H

struct beSvFileFindApi;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSvFileFindApi *beSvFileFindApi_Create(int allocator);

extern struct igMetaObject *g_beSvFileFindApi_metaObject;

#ifdef __cplusplus
}
#endif

#endif

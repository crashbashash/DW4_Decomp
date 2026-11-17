#ifndef DW4_BESVUSECHECKAPI_H
#define DW4_BESVUSECHECKAPI_H

struct beSvUseCheckApi;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSvUseCheckApi *beSvUseCheckApi_Create(int allocator);

extern struct igMetaObject *g_beSvUseCheckApi_metaObject;

#ifdef __cplusplus
}
#endif

#endif

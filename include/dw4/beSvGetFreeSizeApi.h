#ifndef DW4_BESVGETFREESIZEAPI_H
#define DW4_BESVGETFREESIZEAPI_H

struct beSvGetFreeSizeApi;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSvGetFreeSizeApi *beSvGetFreeSizeApi_Create(int allocator);

extern struct igMetaObject *g_beSvGetFreeSizeApi_metaObject;

#ifdef __cplusplus
}
#endif

#endif

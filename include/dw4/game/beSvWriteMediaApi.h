#ifndef DW4_BESVWRITEMEDIAAPI_H
#define DW4_BESVWRITEMEDIAAPI_H

struct beSvWriteMediaApi;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSvWriteMediaApi *beSvWriteMediaApi_Create(int allocator);

extern struct igMetaObject *g_beSvWriteMediaApi_metaObject;

#ifdef __cplusplus
}
#endif

#endif

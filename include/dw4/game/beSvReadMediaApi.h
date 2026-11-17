#ifndef DW4_BESVREADMEDIAAPI_H
#define DW4_BESVREADMEDIAAPI_H

struct beSvReadMediaApi;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSvReadMediaApi *beSvReadMediaApi_Create(int allocator);

extern struct igMetaObject *g_beSvReadMediaApi_metaObject;

#ifdef __cplusplus
}
#endif

#endif

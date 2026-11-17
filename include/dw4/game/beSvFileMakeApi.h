#ifndef DW4_BESVFILEMAKEAPI_H
#define DW4_BESVFILEMAKEAPI_H

struct beSvFileMakeApi;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSvFileMakeApi *beSvFileMakeApi_Create(int allocator);

extern struct igMetaObject *g_beSvFileMakeApi_metaObject;

#ifdef __cplusplus
}
#endif

#endif

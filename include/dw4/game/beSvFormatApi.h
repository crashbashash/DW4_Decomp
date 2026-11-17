#ifndef DW4_BESVFORMATAPI_H
#define DW4_BESVFORMATAPI_H

struct beSvFormatApi;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSvFormatApi *beSvFormatApi_Create(int allocator);

extern struct igMetaObject *g_beSvFormatApi_metaObject;

#ifdef __cplusplus
}
#endif

#endif

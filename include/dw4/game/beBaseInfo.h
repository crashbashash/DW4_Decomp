#ifndef DW4_BEBASEINFO_H
#define DW4_BEBASEINFO_H

struct beBaseInfo;
struct CallbackArray;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void *beBaseInfo_Destroy(struct beBaseInfo *self, short delete_storage);
struct igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
struct CallbackArray *beBaseInfo_Register(void);

#ifdef __cplusplus
}
#endif

#endif

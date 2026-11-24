#ifndef DW4_BEBASEINFODATA_H
#define DW4_BEBASEINFODATA_H

struct beBaseInfoData;
struct CallbackArray;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beBaseInfoData *beBaseInfoData_Destroy(struct beBaseInfoData *self, short delete_storage);

#ifdef __cplusplus
}
#endif

#endif

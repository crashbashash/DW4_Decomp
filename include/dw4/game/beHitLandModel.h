#ifndef DW4_BEHITLANDMODEL_H
#define DW4_BEHITLANDMODEL_H

struct beHitLandModel;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beHitLandModel *beHitLandModel_CreateInstance(int allocator);
struct igMetaEnum *beHitLandModel_GetMessageEnum(void);

extern struct igMetaObject *g_beHitLandModel_metaObject;

#ifdef __cplusplus
}
#endif

#endif

#ifndef DW4_IGMODEL_H
#define DW4_IGMODEL_H

struct igModel;
struct igMetaField;
struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif
extern int g_igModel_vtable[4];

struct igModel *igModel_Destroy(struct igModel *self, short deleteFlag);

#ifdef __cplusplus
}
#endif

#endif

#ifndef DW4_IGGROUP_H
#define DW4_IGGROUP_H

struct CallbackArray;
struct igGroup;
struct igMetaObject;
struct igNode;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igGroup_metaObject;
int igGroup_AppendChild(struct igGroup *group, struct igNode *child);
struct igGroup *igGroup_CreateInstance(int allocator);
struct igGroup *igGroup_Destroy(struct igGroup *self, short deleteFlag);
struct igMetaObject *igGroup_GetOrCreateMetaObject(void);
struct CallbackArray *igGroup_Register(void);
unsigned int igGroup_RemoveChild(struct igGroup *group, struct igNode *child);

#ifdef __cplusplus
}
#endif

#endif

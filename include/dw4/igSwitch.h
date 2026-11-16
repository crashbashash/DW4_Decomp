#ifndef DW4_IGSWITCH_H
#define DW4_IGSWITCH_H

struct igMetaObject;
struct igNode;
struct igSwitch;

#ifdef __cplusplus
extern "C" {
#endif

int igSwitch_AppendChild(struct igSwitch *sw, struct igNode *child);
struct igSwitch *igSwitch_CreateInstance(int allocator);
void igSwitch_DisableAllChildren(struct igSwitch *sw);
void igSwitch_DisableChild(struct igSwitch *sw, unsigned int index);
void igSwitch_EnableAllChildren(struct igSwitch *sw);
void igSwitch_EnableChild(struct igSwitch *sw, unsigned int index);
struct igMetaObject *igSwitch_GetOrCreateMetaObject(void);
struct igNode *igSwitch_RemoveChildAt(struct igSwitch *sw, int index);

#ifdef __cplusplus
}
#endif

#endif

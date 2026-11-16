#ifndef DW4_IGATTRSTACKMANAGER_H
#define DW4_IGATTRSTACKMANAGER_H

struct igAttr;
struct igAttrStackManager;
struct igLightStateAttr;

#ifdef __cplusplus
extern "C" {
#endif

void igAttrStackManager_PopLightStateAttr(struct igAttrStackManager *manager, struct igLightStateAttr *attr, int isOverride);
void igAttrStackManager_PopOverrideAttr(struct igAttrStackManager *manager, struct igAttr *attr);
void igAttrStackManager_PushOverrideAttr(struct igAttrStackManager *manager, struct igAttr *attr);

#ifdef __cplusplus
}
#endif

#endif

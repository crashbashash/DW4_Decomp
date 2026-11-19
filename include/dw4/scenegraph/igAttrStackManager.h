#ifndef DW4_IGATTRSTACKMANAGER_H
#define DW4_IGATTRSTACKMANAGER_H

struct igAttr;
struct igAttrDefaultManager;
struct igAttrStack;
struct igAttrStackManager;
struct igLightStateAttr;
struct igMetaObject;
struct igVisualContextCapabilityManager;

#ifdef __cplusplus
extern "C" {
#endif

void igAttrStackManager_MarkStackChanged(struct igAttrStackManager *manager, struct igAttrStack *stack, int index);
void igAttrStackManager_PopLightStateAttr(struct igAttrStackManager *manager, struct igLightStateAttr *attr, int isOverride);
void igAttrStackManager_PopOverrideAttr(struct igAttrStackManager *manager, struct igAttr *attr);
void igAttrStackManager_PushOverrideAttr(struct igAttrStackManager *manager, struct igAttr *attr);
void FUN_001b06f0(struct igAttrStackManager *manager, struct igLightStateAttr *attr, int isOverride);
void FUN_001b0000(struct igAttrStackManager *manager, struct igMetaObject *meta,
                  struct igAttrDefaultManager *defaultManager, struct igVisualContextCapabilityManager *capabilityManager);

#ifdef __cplusplus
}
#endif

#endif

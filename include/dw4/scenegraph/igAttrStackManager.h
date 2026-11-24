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

#ifdef __cplusplus
}
#endif

#endif

#ifndef DW4_IGGUICOMPONENT_H
#define DW4_IGGUICOMPONENT_H

struct igMetaObject;
struct igGuiComponent;

#ifdef __cplusplus
extern "C" {
#endif

void igGuiComponent_AppendChild(struct igGuiComponent *parent, struct igGuiComponent *child);

#ifdef __cplusplus
}
#endif

#endif

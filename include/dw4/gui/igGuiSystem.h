#ifndef DW4_IGGUISYSTEM_H
#define DW4_IGGUISYSTEM_H

struct igGuiSystem;
struct igMouseCursor;
struct igGuiComponent;

#ifdef __cplusplus
extern "C" {
#endif

void igGuiSystem_RunStaticInit(void);
void igGuiSystem_SetMouseCursorVisible(struct igGuiSystem *gui, int visible);
void igGuiSystem_SetMouseCursor(struct igGuiSystem *gui, struct igMouseCursor *cursor);
void igGuiSystem_SetRootComponent(struct igGuiSystem *gui, struct igGuiComponent *root);

#ifdef __cplusplus
}
#endif

#endif

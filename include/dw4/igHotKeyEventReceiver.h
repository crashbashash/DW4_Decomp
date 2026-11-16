#ifndef DW4_IGHOTKEYEVENTRECEIVER_H
#define DW4_IGHOTKEYEVENTRECEIVER_H

struct igHotKeyEventReceiver;
struct igObject;

#ifdef __cplusplus
extern "C" {
#endif

void igHotKeyEventReceiver_RunStaticInit(void);
/* Binds `action` to a key or a button; 32 stands for no button. */
void igHotKeyEventReceiver_AddBinding(struct igHotKeyEventReceiver *receiver, int key, int button, struct igObject *action);
void igHotKeyEventReceiver_AddKey(struct igHotKeyEventReceiver *receiver, int key, struct igObject *action);
void igHotKeyEventReceiver_AddButton(struct igHotKeyEventReceiver *receiver, int button, struct igObject *action);
void igHotKeyEventReceiver_RemoveBinding(struct igHotKeyEventReceiver *receiver, int button);

#ifdef __cplusplus
}
#endif

#endif

#ifndef DW4_IGMESSENGER_H
#define DW4_IGMESSENGER_H

struct igMessenger;
struct igObject;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

/* Hands each message of `messageType` the messenger dispatches to `receiver`. */
void igMessenger_AddReceiver(struct igMessenger *messenger, struct igObject *receiver, struct igMetaObject *messageType);

#ifdef __cplusplus
}
#endif

#endif

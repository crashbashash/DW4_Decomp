#ifndef DW4_IGEVENTDISPATCHER_H
#define DW4_IGEVENTDISPATCHER_H

struct igEventDispatcher;
struct igObject;

#ifdef __cplusplus
extern "C" {
#endif

void igEventDispatcher_EnsureRegistered(void);
void igEventDispatcher_AddReceiver(struct igEventDispatcher *dispatcher, struct igObject *receiver);
void igEventDispatcher_RemoveReceiver(struct igEventDispatcher *dispatcher, struct igObject *receiver);
/* Makes `second` receive events after `first`. */
void igEventDispatcher_AddReceiverOrder(struct igEventDispatcher *dispatcher, struct igObject *first, struct igObject *second);
void igEventDispatcher_RemoveReceiverOrder(struct igEventDispatcher *dispatcher, struct igObject *first, struct igObject *second);

struct igMetaObject *igEventDispatcher_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

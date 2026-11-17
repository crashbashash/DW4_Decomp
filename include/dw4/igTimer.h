#ifndef DW4_IGTIMER_H
#define DW4_IGTIMER_H

struct igTimer;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igTimer *igTimer_Create(int allocator);
void igTimer_EnsureRegistered(void);
struct igMetaObject *igTimer_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

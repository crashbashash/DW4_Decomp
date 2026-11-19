#ifndef DW4_IGFIELDSYNCHRONIZER_H
#define DW4_IGFIELDSYNCHRONIZER_H

struct igFieldSynchronizer;
struct igMemoryPoolView;
struct igObject;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

struct igFieldSynchronizer *igFieldSynchronizer_Create(struct igMemoryPoolView *pool);
/* Keeps `field` of `model` in step with the synchronizer's other members: adds a field-change view on it. */
void igFieldSynchronizer_AddField(struct igFieldSynchronizer *self, struct igObject *model, struct igMetaField *field);

#ifdef __cplusplus
}
#endif

#endif

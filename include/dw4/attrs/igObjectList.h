#ifndef DW4_ATTRS_IGOBJECTLIST_H
#define DW4_ATTRS_IGOBJECTLIST_H

/* Object-list services the attrs library emits. */
struct igObject;
struct igObjectList;

#ifdef __cplusplus
extern "C" {
#endif

/* Where *key belongs in a list kept sorted by pointer value: the index of an equal entry, else the
 * index to insert at. */
int FUN_00142bb0(struct igObjectList *list, struct igObject *const *key);

#ifdef __cplusplus
}
#endif

#endif

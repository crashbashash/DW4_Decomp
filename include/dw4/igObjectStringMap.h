#ifndef DW4_IGOBJECTSTRINGMAP_H
#define DW4_IGOBJECTSTRINGMAP_H

struct igMetaObject;
struct igObjectStringMap;

#ifdef __cplusplus
extern "C" {
#endif
struct igMetaObject *igObjectStringMap_GetOrCreateMetaObject(void);
int igObjectStringMap_GetObject(void *self, const char *name);
void igObjectStringMap_Add(struct igObjectStringMap *self, const char *name, void *object);
int igObjectStringMap_GetCount(void *self);
int igObjectStringMap_GetObjectAt(void *self, int index);
int *igObjectStringMap_GetNameAt(void *self, int index);
int igObjectStringMap_GetIndexByName(struct igObjectStringMap *map, const char *name);
void igObjectStringMap_RemoveAt(struct igObjectStringMap *self, int index);
void igObjectStringMap_Clear(struct igObjectStringMap *o);
#ifdef __cplusplus
}
#endif

#endif

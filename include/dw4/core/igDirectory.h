#ifndef DW4_IGDIRECTORY_H
#define DW4_IGDIRECTORY_H

/* igDirectory: class registration. */
struct igDirectoryView;
struct igInfoView;
struct igMetaField;
struct igObject;
struct igResource;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igDirectory_GetOrCreateMetaObject(void);
void igDirectory_EnsureRegistered(void);
bool igDirectory_AddExternalInfoRef(struct igDirectoryView *directory, struct igInfoView *info, char *key, struct igObject *object);
int igDirectory_FindSortedInsertIndex(struct igDirectoryView *self, struct igMetaField *field, unsigned key);
int igDirectory_GetNthObjectOfType(struct igResource *resource, const char *name, const char *metaName, int wanted);
void *igDirectory_Create(int allocator);
int igDirectory_AddObjectRecursive(int directory, int object, int name, int);
void *igDirectory_GetEntry(int *directory, int index);
void igDirectory_RemoveInfoByName(void *directory, int name);
void igDirectory_AddInfo(void *directory, void *info);
void igDirectory_SetName(struct igDirectoryView *self, const char *name);

#ifdef __cplusplus
}
#endif

#endif

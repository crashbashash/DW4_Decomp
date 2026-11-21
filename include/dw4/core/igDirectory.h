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

bool igDirectory_AddExternalInfoRef(struct igDirectoryView *directory, struct igInfoView *info, char *key, struct igObject *object);
int igDirectory_GetNthObjectOfType(struct igResource *resource, const char *name, const char *metaName, int wanted);

#ifdef __cplusplus
}
#endif

#endif

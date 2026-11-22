#ifndef DW4_IGDIRECTORY_H
#define DW4_IGDIRECTORY_H

/* igDirectory: class registration. */
struct igMetaField;
struct igObject;
struct igResource;
struct igMetaObject;

#ifdef __cplusplus
namespace Gap {
namespace Core {
class igDirectory;
class igInfo;
class igObject;
}
}

extern "C" {
#endif

bool igDirectory_AddExternalInfoRef(Gap::Core::igDirectory *directory, Gap::Core::igInfo *info, const char *key, Gap::Core::igObject *object);
int igDirectory_GetNthObjectOfType(struct igResource *resource, const char *name, const char *metaName, int wanted);

#ifdef __cplusplus
}
#endif

#endif

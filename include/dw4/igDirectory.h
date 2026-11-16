#ifndef DW4_IGDIRECTORY_H
#define DW4_IGDIRECTORY_H

/* igDirectory: class registration. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igDirectory_GetOrCreateMetaObject(void);
void igDirectory_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif

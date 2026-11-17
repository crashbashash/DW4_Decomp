#ifndef DW4_IGFILE_H
#define DW4_IGFILE_H

/* igFile: the file class's registration, creation and file name. */
struct CallbackArray;
struct igFile;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igFile_metaObject;
void *igFile_Create(int allocator);
void *igFile_Destroy(struct igFile *file, short deleteFlag);
struct igMetaObject *igFile_GetPublishedMetaObject(void);
void igFile_GetMetaObjectFunction(void);
struct igMetaObject *igFile_GetOrCreateMetaObject(void);
void igFile_EnsureRegistered(void);
struct CallbackArray *igFile_Register(void);
void igFile_SetFileName(struct igFile *file, const char *name);
#ifdef __cplusplus
}
#endif

#endif

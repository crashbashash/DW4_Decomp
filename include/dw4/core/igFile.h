#ifndef DW4_IGFILE_H
#define DW4_IGFILE_H

/* igFile: the file class's registration, creation and file name. */
struct CallbackArray;
struct igFile;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
void *igFile_Destroy(struct igFile *file, short deleteFlag);
#ifdef __cplusplus
}
#endif

#endif

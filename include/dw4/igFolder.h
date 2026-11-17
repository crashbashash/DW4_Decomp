#ifndef DW4_IGFOLDER_H
#define DW4_IGFOLDER_H

struct igFolder;
struct igFolderView;

#ifdef __cplusplus
extern "C" {
#endif

struct igFolder *igFolder_Create(int allocator);
void igFolder_SetFolderName(struct igFolderView *self, const char *name);

#ifdef __cplusplus
}
#endif

#endif

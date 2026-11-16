#ifndef DW4_IGADXFILE_H
#define DW4_IGADXFILE_H

struct igMetaObject;
struct igAdxFile;

extern "C" {

extern struct igMetaObject *g_igAdxFile_metaObject;
struct igAdxFile *igAdxFile_Create(int allocator);
void igAdxFile_StaticInitialize(void);
void igAdxFile_StaticFinalize(void);
int igAdxFile_GetFileSize(struct igAdxFile *file);
void igAdxFile_SetUseBuffer(struct igAdxFile *file, bool useBuffer);
void igAdxFile_SetUseAsync(struct igAdxFile *file, bool useAsync);
int igAdxFile_WaitForReadEnd(struct igAdxFile *file);

}

#endif

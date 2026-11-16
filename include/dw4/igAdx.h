#ifndef DW4_IGADX_H
#define DW4_IGADX_H
#include "dw4/igSmartPointer.h"

struct igMetaObject;
struct igAdxAfsFileList;

extern "C" {

extern struct igMetaObject *g_igAdx_metaObject;
extern unsigned char g_adxIopReady;
extern int g_adxMediaMode;
extern int g_adxPartitionCount;
extern char g_adxUseFileInfoCache;
extern igSmartPointer<igAdxAfsFileList> g_adxAfsFileList;

void igAdx_CreateScratchString(void);
int igAdx_Initialize(int setupOptional);
void igAdx_Shutdown(void);
void igAdx_SetModulePath(const char *path);
void igAdx_SetHostRootPath(const char *path);
void igAdx_ExecVsync(void);
void igAdx_ExecServer(int);
void igAdx_SetPartitionCount(int count);
void igAdx_AddPartitionName(int partition, const char *name);
int igAdx_LoadPartition(int partition, const char *path, int mode, int length);
int igAdx_FindAfsFile(const char *name);
void igAdx_SetInsideFiles(struct igAdxAfsFileList *files);

}

#endif

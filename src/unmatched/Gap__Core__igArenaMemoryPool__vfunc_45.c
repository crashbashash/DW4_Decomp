#include "dw4/reflected.h"
struct PoolRequest { char pad0[60]; char *options; char pad64[4]; char *integrityCheck; char pad72[4]; char *messages; };
struct CoreGlobals { char pad0[48]; igArenaMemoryPool *defaultPool; };
char *strstr(const char *, const char *);
void FUN_002f0880(int *status);
void igArenaMemoryPool_SetPoolOptionFlags(igArenaMemoryPool *pool, int flags);
extern struct CoreGlobals *DAT_00586dc8[4];
extern char DAT_004fd2f8[];
extern char DAT_004fd300[];
extern char DAT_004fd308[];
extern char DAT_004fd318[];
extern char DAT_004fd328[];
extern char DAT_004fd340[];
extern char DAT_004fd358[];
extern char DAT_004fd368[];
extern char DAT_004fd378[];
extern char DAT_004fd388[];
extern char DAT_004fd3a0[];
extern char DAT_004fd3b8[];
extern char DAT_004fd3c8[];
extern char DAT_004fd3d8[];
extern char DAT_004fd3f0[];
extern char DAT_004fd400[];
void Gap__Core__igArenaMemoryPool__vfunc_45(int *out, igArenaMemoryPool *pool, struct PoolRequest *request) {
    char *options;
    int flags;
    char *integrityCheck;
    char *messages;
    int result;
    int status;
    FUN_002f0880(&status);
    result = status;
    options = request->options;
    integrityCheck = request->integrityCheck;
    messages = request->messages;
    if (options) {
        flags = 0;
        if (strstr(options, DAT_004fd2f8)) flags |= 2;
        if (strstr(options, DAT_004fd300)) flags |= 4;
        if (strstr(options, DAT_004fd308)) flags |= 1;
        if (strstr(options, DAT_004fd318)) flags |= 0x10;
        if (strstr(options, DAT_004fd328)) flags |= 8;
        if (strstr(options, DAT_004fd340)) flags |= 0x80;
        if (strstr(options, DAT_004fd358)) flags |= 0x40;
        if (strstr(options, DAT_004fd368)) flags |= 0x20;
        if (pool == DAT_00586dc8[0]->defaultPool && (flags & 1) != (pool->_poolOptionFlags & 1)) {
            flags ^= 1;
        }
        igArenaMemoryPool_SetPoolOptionFlags(pool, flags);
    }
    if (integrityCheck) {
        int level = pool->_heapIntegrityCheckLevel;
        if (strstr(integrityCheck, DAT_004fd378)) {
            level = 0;
        } else if (strstr(integrityCheck, DAT_004fd388)) {
            level = 1;
        } else if (strstr(integrityCheck, DAT_004fd3a0)) {
            level = 2;
        } else if (strstr(integrityCheck, DAT_004fd3b8)) {
            level = 3;
        }
        pool->_heapIntegrityCheckLevel = level;
    }
    if (messages) {
        int level = pool->_messageLevel;
        if (strstr(messages, DAT_004fd3c8)) {
            level = 0;
        } else if (strstr(messages, DAT_004fd3d8)) {
            level = 1;
        } else if (strstr(messages, DAT_004fd3f0)) {
            level = 2;
        } else if (strstr(messages, DAT_004fd400)) {
            level = 3;
        }
        pool->_messageLevel = level;
    }
    *out = result;
}

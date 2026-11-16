#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igFileDispatchView.h"
#include "dw4/beFileChkObj.h"
#include "dw4/beLuaState.h"
#include "dw4/igAdxFile.h"
#include "dw4/igMemory.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igObject.h"

extern "C" void igLuaState_RunString(void);
extern "C" int igLuaState_RunBuffer(...);
extern "C" void beLuaState_RunString(void);
extern "C" void beLuaState_RunBuffer(void);
extern "C" igMetaObject *beLuaState_GetMeta(void);
extern "C" int igLuaState_Close(beLuaState *);
extern "C" void beLuaState_userDestruct(beLuaState *self);
#pragma push
#pragma readonly_strings on

/* Owning stack reference to the script locator; released on scope exit (reference count in the low
 * 23 bits of _refCount). */

/* Owning stack reference to the script reader; released on scope exit. */
class ReaderRef {
public:
    igObject *p;
    ReaderRef(igObject *o) : p(o) {}
    ~ReaderRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" int beLuaState_RunFile(beLuaState *self, const char *fileName);

void beLuaState_userDestruct(beLuaState *self) {
    int allocator;

    if (self->_lp != 0) {
        allocator = (int)igObject_GetAllocator(self);
        allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        Memory_FreeBufferWithAllocator((void *)self->_lp, (igMemoryPoolView *)allocator);
    }
    igLuaState_Close(self);
}

void beLuaState_RunString(void)
{
    igLuaState_RunString();
}

int beLuaState_RunFile(beLuaState *self, const char *fileName) {
    int allocator;
    int fileSize;
    char *buffer;
    int length;
    bool found;
    allocator = (int)igObject_GetAllocator((igObject *)self);
    allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    igSmartPointer<igObject> locator(beFileChkObj_Create(allocator));
    if (beFileChkObj_FileExists((beFileChkObj *)locator.p, fileName) == 0) {
        return 2;
    }
    allocator = (int)igObject_GetAllocator(self);
    allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    ReaderRef reader(igAdxFile_Create(allocator));
    if (((igFileDispatchView *)reader.p)->OpenFile(fileName, "rb") == 0) {
        return -1;
    }
    fileSize = igAdxFile_GetFileSize((igAdxFile *)reader.p);
    if (self->_lp != 0) {
        allocator = (int)igObject_GetAllocator(self);
        allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        Memory_FreeBufferWithAllocator((void *)self->_lp, (igMemoryPoolView *)allocator);
    }
    allocator = (int)igObject_GetAllocator(self);
    allocator = (g_useOwnerAllocator != 0) ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    self->_lp = (int)Memory_AllocateAlignedWithAllocator(fileSize, 0x40, (igMemoryPoolView *)allocator);
    if (self->_lp == 0) {
        ((igFileDispatchView *)reader.p)->CloseFile();
        return -1;
    }
    igAdxFile_SetUseBuffer((igAdxFile *)reader.p, 0);
    igAdxFile_SetUseAsync((igAdxFile *)reader.p, 0);
    ((igFileDispatchView *)reader.p)->Read((void *)self->_lp, 1, fileSize);
    igAdxFile_WaitForReadEnd((igAdxFile *)reader.p);
    igAdxFile_SetUseBuffer((igAdxFile *)reader.p, 1);
    igAdxFile_SetUseAsync((igAdxFile *)reader.p, 1);
    ((igFileDispatchView *)reader.p)->CloseFile();
    buffer = (char *)self->_lp;
    found = false;
    length = 0;
    for (; length < fileSize; length++) {
        char *p = buffer + length;
        if (p[0] == 0x5B && p[1] == 0x45 && p[2] == 0x4F && p[3] == 0x46 && p[4] == 0x5D) {
            found = true;
            p[0] = 0x30;
            break;
        }
    }
    if (!found) {
        return -1;
    }
    fileSize = igLuaState_RunBuffer(self, buffer, length, fileName);
    return fileSize;
}

void beLuaState_RunBuffer(void)
{
    igLuaState_RunBuffer();
}

igMetaObject *beLuaState_GetMeta(void)
{
    return g_beLuaState_metaObject;
}

#pragma pop

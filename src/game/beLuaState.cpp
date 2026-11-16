#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igFileVirtuals.h"

extern "C" int Memory_FreeBufferWithAllocator(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void igLuaState_RunString(void);
extern "C" int igLuaState_RunBuffer(...);
extern "C" void beLuaState_RunString(void);
extern "C" void beLuaState_RunBuffer(void);
extern "C" int Memory_AllocateAlignedWithAllocator(int, int, int);
extern "C" int beLuaState_GetMeta(void);
extern "C" int igLuaState_Close(beLuaState *);
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" void beLuaState_userDestruct(beLuaState *self);
extern "C" igObject *beFileChkObj_Create(int);
extern "C" int beFileChkObj_FileExists(igObject *, int);
extern "C" igObject *igAdxFile_Create(int);
extern "C" int igAdxFile_GetFileSize(igObject *);
extern "C" int igAdxFile_SetUseBuffer(igObject *, int);
extern "C" int igAdxFile_SetUseAsync(igObject *, int);
extern "C" int igAdxFile_WaitForReadEnd(igObject *);
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
extern "C" int beLuaState_RunFile(beLuaState *self, int fileName);
extern "C" int g_beLuaState_metaObject[4];

void beLuaState_userDestruct(beLuaState *self) {
    int allocator;

    if (self->_lp != 0) {
        allocator = igObject_GetAllocator(self);
        allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        Memory_FreeBufferWithAllocator(self->_lp, allocator);
    }
    igLuaState_Close(self);
}

void beLuaState_RunString(void)
{
    igLuaState_RunString();
}

int beLuaState_RunFile(beLuaState *self, int fileName) {
    int allocator;
    int fileSize;
    char *buffer;
    int length;
    bool found;
    allocator = igObject_GetAllocator();
    allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
    igSmartPointer<igObject> locator(beFileChkObj_Create(allocator));
    if (beFileChkObj_FileExists(locator.p, fileName) == 0) {
        return 2;
    }
    allocator = igObject_GetAllocator(self);
    allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
    ReaderRef reader(igAdxFile_Create(allocator));
    if (((igFileVirtuals *)reader.p)->openFile(fileName, "rb") == 0) {
        return -1;
    }
    fileSize = igAdxFile_GetFileSize(reader.p);
    if (self->_lp != 0) {
        allocator = igObject_GetAllocator(self);
        allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        Memory_FreeBufferWithAllocator(self->_lp, allocator);
    }
    allocator = igObject_GetAllocator(self);
    allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
    self->_lp = (int)Memory_AllocateAlignedWithAllocator(fileSize, 0x40, allocator);
    if (self->_lp == 0) {
        ((igFileVirtuals *)reader.p)->closeFile();
        return -1;
    }
    igAdxFile_SetUseBuffer(reader.p, 0);
    igAdxFile_SetUseAsync(reader.p, 0);
    ((igFileVirtuals *)reader.p)->read(self->_lp, 1, fileSize);
    igAdxFile_WaitForReadEnd(reader.p);
    igAdxFile_SetUseBuffer(reader.p, 1);
    igAdxFile_SetUseAsync(reader.p, 1);
    ((igFileVirtuals *)reader.p)->closeFile();
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

int beLuaState_GetMeta(void)
{
    return g_beLuaState_metaObject[0];
}

#pragma pop

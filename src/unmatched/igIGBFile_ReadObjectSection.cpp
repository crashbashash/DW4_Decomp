#include "dw4/igSmartPointer.h"
struct Status {
    int code;
    Status() {}
    Status(const Status &o) { code = o.code; }
    bool operator==(const Status &o) const { return code == o.code; }
};
class SectionObject : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void setMemoryPool(int pool); virtual int memoryPoolIndex();
};
struct SectionPoolTable : public igObject {
    int pad8[2];
    int *_data;
};
struct IGBReader {
    char pad0[40];
    igObjectList *objects;
    char pad44[21];
    unsigned char remapPools;
    char pad66[14];
    int position;
    int consumed;
    int bufferEnd;
    char pad92[20];
    int objectCount;
    char pad116[8];
    int sectionSize;
    char pad128[132];
    int bufferSize;
    char pad264[12];
    unsigned char failed;
    char pad277[3];
    int pool;
    char pad284[20];
    SectionPoolTable *poolTable;
};
extern "C" {
igObjectList *FUN_002c72c0(int pool);
void ObjectList_ResizeRetained(igObjectList *list, int count);
Status FUN_002e7030(IGBReader *file);
igSmartPointer<SectionObject> igIGBFile_ReadObject(IGBReader *file);
extern Status g_statusSucceeded[2];
extern Status g_allocatorFailureStatus[2];
extern unsigned char g_useOwnerAllocator;
}

extern "C" Status igIGBFile_ReadObjectSection(IGBReader *file) {
    int pool;
    igObjectList *list;
    int i;
    file->position = file->bufferSize;
    file->consumed = 0;
    file->bufferEnd = file->sectionSize;
    list = file->objects;
    pool = file->pool;
    if (list != 0) {
        list->_refCount = list->_refCount - 1;
        if ((list->_refCount & 0x7FFFFF) == 0) igObject_Destroy(list);
    }
    file->objects = FUN_002c72c0(pool);
    ObjectList_ResizeRetained(file->objects, file->objectCount);
    if (FUN_002e7030(file) == g_allocatorFailureStatus[0]) {
        return g_allocatorFailureStatus[0];
    }
    for (i = 0; i < file->objectCount; i++) {
        igSmartPointer<SectionObject> object = igIGBFile_ReadObject(file);
        if (object.p == 0) {
            return g_allocatorFailureStatus[0];
        }
        if (file->remapPools != 0 && file->poolTable != 0 && g_useOwnerAllocator == 0) {
            int index = object->memoryPoolIndex();
            if (index > 0) {
                object->setMemoryPool(file->poolTable->_data[index]);
            }
        } else {
            object->setMemoryPool(-1);
        }
        SectionObject *entry = object.p;
        list = file->objects;
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        igObject *old = ((igObject **)list->_data)[i];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (list->_count != 0 && i >= 0 && i < list->_count) {
            ((SectionObject **)list->_data)[i] = entry;
        }
    }
    if (file->failed != 0) {
        return g_allocatorFailureStatus[0];
    }
    return g_statusSucceeded[0];
}

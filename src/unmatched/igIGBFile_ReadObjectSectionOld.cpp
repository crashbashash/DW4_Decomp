#include "dw4/igSmartPointer.h"
struct Status {
    int code;
    Status() {}
    Status(const Status &o) { code = o.code; }
    bool operator==(const Status &o) const { return code == o.code; }
};
struct IGBReader;
class SectionObject : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void setReferenceTarget(int target);
    virtual void d22(); virtual void d23();
    virtual SectionObject *resolve(IGBReader *file);
    virtual void setReferenceIndex(int index);
    virtual void d26();
    virtual void setMemoryPool(int pool);
    virtual int memoryPoolIndex();
    virtual void readFinished(IGBReader *file);
    int pad8;
    int index;
    char pad16[8];
    int referenceIndex;
};
struct SectionPoolTable : public igObject {
    int pad8[2];
    int *_data;
};
struct IndexList : public igObject {
    int _count;
    int _capacity;
    int *_data;
};
struct IGBReader : public igObject {
    int _count;
    int _capacity;
    SectionObject **_data;
    char pad20[16];
    unsigned char oldReferences;
    char pad37[7];
    IndexList *referenceIndices;
    char pad48[17];
    unsigned char remapPools;
    char pad66[14];
    int position;
    int consumed;
    int bufferEnd;
    igObject *resolved;
    char pad96[16];
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

    void set(int i, const igSmartPointer<SectionObject> &held) {
        SectionObject *entry = held.p;
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        igVirtualObject *old = _data[i];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && i >= 0 && i < _count) {
            _data[i] = entry;
        }
    }
    void setRaw(int i, SectionObject *entry) {
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        igVirtualObject *old = _data[i];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && i >= 0 && i < _count) {
            _data[i] = entry;
        }
    }
};
extern "C" {
IndexList *FUN_002c9130(int pool);
igObject *FUN_002bd680(int pool);
void List_Resize(void *list, int count, int elementSize);
void ObjectList_ResizeRetained(void *list, int count);
Status FUN_002e7030(IGBReader *file);
igSmartPointer<SectionObject> igIGBFile_ReadObject(IGBReader *file);
extern Status g_statusSucceeded[2];
extern Status g_allocatorFailureStatus[2];
extern unsigned char g_useOwnerAllocator;
}

extern "C" Status igIGBFile_ReadObjectSectionOld(IGBReader *file) {
    int pool;
    int i;
    file->position = file->bufferSize;
    file->consumed = 0;
    file->bufferEnd = file->sectionSize;
    if (file->oldReferences != 0) {
        IndexList *old = file->referenceIndices;
        pool = file->pool;
        igRelease((igObject *)old);
        file->referenceIndices = FUN_002c9130(pool);
        int count = file->objectCount;
        IndexList *indices = file->referenceIndices;
        if (count >= 0) {
            if (count <= indices->_capacity) {
                indices->_count = count;
            } else {
                List_Resize(indices, count, 4);
            }
        }
        igObject *previous = file->resolved;
        pool = file->pool;
        igRelease(previous);
        file->resolved = FUN_002bd680(pool);
    }
    if (FUN_002e7030(file) == g_allocatorFailureStatus[0]) {
        return g_allocatorFailureStatus[0];
    }
    ObjectList_ResizeRetained(file, file->objectCount);
    for (i = 0; i < file->objectCount; i++) {
        igSmartPointer<SectionObject> object = igIGBFile_ReadObject(file);
        if (object.p == 0) {
            return g_allocatorFailureStatus[0];
        }
        object->index = i;
        file->set(i, object);
        if (file->remapPools != 0 && file->poolTable != 0 && g_useOwnerAllocator == 0) {
            int index = object->memoryPoolIndex();
            if (index > 0) {
                object->setMemoryPool(file->poolTable->_data[index]);
            }
        } else {
            object->setMemoryPool(-1);
        }
        object->readFinished(file);
        if (file->oldReferences != 0) {
            int reference = object->referenceIndex;
            IndexList *indices = file->referenceIndices;
            if (indices->_count != 0 && i >= 0 && i < indices->_count) {
                indices->_data[i] = reference;
            }
            object->setReferenceIndex(object->referenceIndex);
            object->setReferenceTarget(0);
            object->index = i;
            file->setRaw(i, object->resolve(file));
        }
    }
    if (file->failed != 0) {
        return g_allocatorFailureStatus[0];
    }
    return g_statusSucceeded[0];
}

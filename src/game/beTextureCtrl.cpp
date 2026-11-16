#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igObjectVirtuals.h"
#include "dw4/igobject_release.h"

extern "C" void igObject_Destroy(void *);
extern "C" int beTextureCtrl_GetInfoMeta(void);
extern "C" int beTextureCtrl_GetMeta(void);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int ObjectList_RemoveFirstRetained(...);
extern "C" void beTextureCtrl_Prepare(beTextureCtrl *self);
extern "C" int g_beTextureCtrlInfo_metaObject[4];
extern "C" int g_beTextureCtrl_metaObject[4];
extern "C" beTextureCtrlWork *beTextureCtrlWork_Create(int allocator);
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" void beTextureCtrl_OnAddRam(beTextureCtrl *self, beBaseInfoRam *ram);
/* igTextureBindAttr seen through its vtable: slot 31 sets the bound texture. */
class NewObjectVirtual : public igVirtualObject {
public:
    DW4_SLOTS_20(s) DW4_SLOTS_5(t) DW4_SLOTS_5(u)
    virtual void setTexture(int texture);
};
/* A property record: the name it is found by and its value. */
struct PropertyRecord { int _vtable; unsigned int _refCount; int _name; int _value; };
extern "C" NewObjectVirtual *igTextureBindAttr_CreateInstance(...);
extern "C" PropertyRecord *igProperty_FindByName(...);
extern "C" int emptyString[4];
extern "C" int g_igTextureBindAttr_metaObject[4];
extern "C" int g_propertyNameField[4];
extern "C" void beTextureCtrl_UpdateRam(beTextureCtrl *self, beBaseInfoRam *ram);

void beTextureCtrl_Prepare(beTextureCtrl *self) {
    beTextureCtrlWork *work;

    self->_isFirstTime = 1;
    work = (beTextureCtrlWork *)self->_work;
    IG_OBJECT_RELEASE(work);
    self->_work = 0;
}

int beTextureCtrl_GetInfoMeta(void)
{
    return g_beTextureCtrlInfo_metaObject[0];
}

void beTextureCtrl_OnAddRam(beTextureCtrl *self, beBaseInfoRam *ram) {
    int count;
    int i;
    int offset;
    int allocator;
    igObject *old;
    beTextureCtrlInfo *info;

    if (self->_work == 0) {
        allocator = igObject_GetAllocator(self);
        if (g_useOwnerAllocator != 0) {
            allocator = (int)allocator;
        } else {
            allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        }
        old = (igObject *)self->_work;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)old);
            }
        }
        self->_work = (int)beTextureCtrlWork_Create(allocator);
    }
    ram = (beBaseInfoRam *)ram->_parentInfo;
    info = (beTextureCtrlInfo *)ram;
    if (info->_isTexture != 0) {
        count = ((igObjectList *)info->_dataList_)->_count;
        i = 0;
        if (0 < count) {
            offset = 0;
            do {
                ObjectList_AppendRetained(((beTextureCtrlWork *)self->_work)->_textureList, *(int *)((char *)((igObjectList *)info->_dataList_)->_data + offset));
                i += 1;
                offset += 4;
            } while (i < count);
        }
    } else {
        count = ((igObjectList *)info->_dataList_)->_count;
        i = 0;
        if (0 < count) {
            offset = 0;
            do {
                ObjectList_AppendRetained(((beTextureCtrlWork *)self->_work)->_attributeList, *(int *)((char *)((igObjectList *)info->_dataList_)->_data + offset));
                i += 1;
                offset += 4;
            } while (i < count);
        }
    }
}

/* Owning stack reference to the texture attribute object created per matching property; released
 * on scope exit, after the attribute set has retained it (reference count in the low 23 bits of
 * _refCount). */

void beTextureCtrl_UpdateRam(beTextureCtrl *self, beBaseInfoRam *ram) {
    /* matching construct: hand search — retail keeps the attribute count in a stack slot; the padding places it at +0xa0 */
    struct { int count; int pad[5]; } spilled;
    beTextureCtrlAttr *entry;
    int boundIndex;
    int offset;
    int *name;
    igAttrSet *attrSet;
    int allocator;
    beTextureCtrlWork *work;
    PropertyRecord *property;
    igObjectVirtuals *existing;
    int boundCount;
    int bindMeta;
    int attributeIndex;
    int boundOffset;
    if (self->_isFirstTime != 0) {
        if (((beTextureCtrlInfo *)ram->_parentInfo)->_isTexture == 0) {
            spilled.count = ((igObjectList *)((beTextureCtrlWork *)self->_work)->_attributeList)->_count;
            attributeIndex = 0;
            if (0 < spilled.count) {
                offset = 0;
                do {
                    work = (beTextureCtrlWork *)self->_work;
                    entry = (beTextureCtrlAttr *)*(int *)(((igObjectList *)work->_attributeList)->_data + offset);
                    name = (int *)entry->_name;
                    if (name != 0) {
                        name = (int *)name;
                    } else {
                        name = &emptyString[0];
                    }
                    property = igProperty_FindByName(work->_textureList, g_propertyNameField[0], name);
                    if (property != 0) {
                        allocator = igObject_GetAllocator(self);
                        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
                        igSmartPointer<NewObjectVirtual> attr(igTextureBindAttr_CreateInstance(allocator));
                        attr.p->setTexture(property->_value);
                        attrSet = (igAttrSet *)entry->_attrSet;
                        boundCount = ((igAttrList *)attrSet->_attributes)->_count;
                        boundIndex = 0;
                        if (0 < boundCount) {
                            boundOffset = 0;
                            do {
                                bindMeta = g_igTextureBindAttr_metaObject[0];
                                existing = (igObjectVirtuals *)*(int *)(((igAttrList *)attrSet->_attributes)->_data + boundOffset);
                                if (bindMeta == existing->getMeta()) {
                                    int removed; /* matching construct: the removal out-slot is declared after the holder so it lies below it (+0xb8 under +0xbc) as in retail */
                                    ObjectList_RemoveFirstRetained(&removed, attrSet->_attributes, existing, 0);
                                    break;
                                }
                                boundIndex++;
                                boundOffset += 4;
                            } while (boundIndex < boundCount);
                        }
                        ObjectList_AppendRetained(attrSet->_attributes, attr.p);
                    }
                    attributeIndex++;
                    offset += 4;
                } while (attributeIndex < spilled.count);
            }
        }
        self->_isFirstTime = 0;
    }
}

int beTextureCtrl_GetMeta(void)
{
    return g_beTextureCtrl_metaObject[0];
}

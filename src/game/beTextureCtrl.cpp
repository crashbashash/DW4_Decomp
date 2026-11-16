#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igTextureBindAttrDispatchView.h"
#include "dw4/igobject_release.h"
#include "dw4/beTextureCtrl.h"
#include "dw4/beTextureCtrlInfo.h"
#include "dw4/beTextureCtrlWork.h"
#include "dw4/igDataLists.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igNamedObject.h"
#include "dw4/igObject.h"
#include "dw4/igTextureBindAttr.h"

extern "C" igMetaObject *beTextureCtrl_GetInfoMeta(void);
extern "C" igMetaObject *beTextureCtrl_GetMeta(void);
/* kept local: the hidden igResult return slot is passed first; Core's copy is the only declaration */
extern "C" int ObjectList_RemoveFirstRetained(...);
extern "C" void beTextureCtrl_Prepare(beTextureCtrl *self);
extern "C" void beTextureCtrl_OnAddRam(beTextureCtrl *self, beBaseInfoRam *ram);
/* A property record: the name it is found by and its value. */
struct PropertyRecord { int _vtable; unsigned int _refCount; int _name; igObject *_value; };
extern "C" char emptyString[];
extern "C" void beTextureCtrl_UpdateRam(beTextureCtrl *self, beBaseInfoRam *ram);

void beTextureCtrl_Prepare(beTextureCtrl *self) {
    beTextureCtrlWork *work;

    self->_isFirstTime = 1;
    work = (beTextureCtrlWork *)self->_work;
    IG_OBJECT_RELEASE(work);
    self->_work = 0;
}

igMetaObject *beTextureCtrl_GetInfoMeta(void)
{
    return g_beTextureCtrlInfo_metaObject;
}

void beTextureCtrl_OnAddRam(beTextureCtrl *self, beBaseInfoRam *ram) {
    beTextureCtrlInfo *info;
    int count;
    int i;
    int offset;
    int allocator;
    igObject *old;

    if (self->_work == 0) {
        allocator = (int)igObject_GetAllocator(self);
        if (g_useOwnerAllocator != 0) {
            allocator = (int)allocator;
        } else {
            allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        old = (igObject *)self->_work;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        self->_work = (int)beTextureCtrlWork_Create(allocator);
    }
    info = (beTextureCtrlInfo *)ram->_parentInfo;
    if (info->_isTexture != 0) {
        count = ((igObjectList *)info->_dataList_)->_count;
        i = 0;
        if (0 < count) {
            offset = 0;
            do {
                ObjectList_AppendRetained((igObjectList *)((beTextureCtrlWork *)self->_work)->_textureList, *(igObject **)((char *)((igObjectList *)info->_dataList_)->_data + offset));
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
                ObjectList_AppendRetained((igObjectList *)((beTextureCtrlWork *)self->_work)->_attributeList, *(igObject **)((char *)((igObjectList *)info->_dataList_)->_data + offset));
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
    int attributeCount;
    beTextureCtrlAttr *entry;
    int boundIndex;
    int offset;
    int *name;
    igAttrSet *attrSet;
    int allocator;
    beTextureCtrlWork *work;
    PropertyRecord *property;
    igObjectDispatchView *existing;
    int boundCount;
    igMetaObject *bindMeta;
    int attributeIndex;
    int boundOffset;
    if (self->_isFirstTime != 0) {
        if (((beTextureCtrlInfo *)ram->_parentInfo)->_isTexture == 0) {
            attributeCount = ((igObjectList *)((beTextureCtrlWork *)self->_work)->_attributeList)->_count;
            attributeIndex = 0;
            if (0 < attributeCount) {
                offset = 0;
                do {
                    work = (beTextureCtrlWork *)self->_work;
                    entry = (beTextureCtrlAttr *)*(int *)(((igObjectList *)work->_attributeList)->_data + offset);
                    name = (int *)entry->_name;
                    if (name != 0) {
                        name = (int *)name;
                    } else {
                        name = (int *)emptyString;
                    }
                    property = (PropertyRecord *)igProperty_FindByName((igObjectList *)work->_textureList, g_propertyNameField, (const char *)name);
                    if (property != 0) {
                        allocator = (int)igObject_GetAllocator(self);
                        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                        igSmartPointer<igTextureBindAttrDispatchView> attr((igTextureBindAttrDispatchView *)igTextureBindAttr_CreateInstance(allocator));
                        attr.p->setTexture(property->_value);
                        attrSet = (igAttrSet *)entry->_attrSet;
                        boundCount = ((igAttrList *)attrSet->_attributes)->_count;
                        boundIndex = 0;
                        if (0 < boundCount) {
                            boundOffset = 0;
                            do {
                                bindMeta = g_igTextureBindAttr_metaObject;
                                existing = (igObjectDispatchView *)*(int *)(((igAttrList *)attrSet->_attributes)->_data + boundOffset);
                                if (bindMeta == existing->GetMeta()) {
                                    int removed; /* matching construct: the removal out-slot is declared after the holder so it lies below it (+0xb8 under +0xbc) as in retail */
                                    ObjectList_RemoveFirstRetained(&removed, attrSet->_attributes, existing, 0);
                                    break;
                                }
                                boundIndex++;
                                boundOffset += 4;
                            } while (boundIndex < boundCount);
                        }
                        ObjectList_AppendRetained((igObjectList *)attrSet->_attributes, (igObject *)attr.p);
                    }
                    attributeIndex++;
                    offset += 4;
                } while (attributeIndex < attributeCount);
            }
        }
        self->_isFirstTime = 0;
    }
}

igMetaObject *beTextureCtrl_GetMeta(void)
{
    return g_beTextureCtrl_metaObject;
}

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/attrs/igTextureBindAttrDispatchView.h"
#include "dw4/core/igobject_release.h"
#include "dw4/game/beTextureCtrl.h"
#include "dw4/game/beTextureCtrlInfo.h"
#include "dw4/game/beTextureCtrlWork.h"
#include "dw4/core/igDataLists.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include "dw4/attrs/igTextureBindAttr.h"
#include "dw4/support/emptyString.h"
#include "dw4/support/list-services.h"

extern "C" igMetaObject *beTextureCtrl_GetInfoMeta(void);
extern "C" igMetaObject *beTextureCtrl_GetMeta(void);
/* kept local: the hidden igResult return slot is passed first; Core's copy is the only declaration */
extern "C" void beTextureCtrl_Prepare(beTextureCtrl *self);
extern "C" void beTextureCtrl_OnAddRam(beTextureCtrl *self, beBaseInfoRam *ram);
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
        allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        if (g_useOwnerAllocator != 0) {
            allocator = (int)allocator;
        } else {
            allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        old = (igObject *)self->_work;
        igObject::release(old);
        self->_work = (int)beTextureCtrlWork_Create(allocator);
    }
    info = (beTextureCtrlInfo *)ram->_parentInfo;
    if (info->_isTexture != 0) {
        count = ((igObjectList *)info->_dataList_)->_count;
        i = 0;
        if (0 < count) {
            offset = 0;
            do {
                ((Gap::Core::igObjectList *)(((beTextureCtrlWork *)self->_work)->_textureList))->append((Gap::Core::igObject *)(*(igObject **)((char *)((igObjectList *)info->_dataList_)->_data + offset)));
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
                ((Gap::Core::igObjectList *)(((beTextureCtrlWork *)self->_work)->_attributeList))->append((Gap::Core::igObject *)(*(igObject **)((char *)((igObjectList *)info->_dataList_)->_data + offset)));
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
    beTextureCtrlData *property;
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
                    property = (beTextureCtrlData *)((Gap::Core::igObjectList *)work->_textureList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, (const char *)name);
                    if (property != 0) {
                        allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
                        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                        igSmartPointer<igTextureBindAttrDispatchView> attr((igTextureBindAttrDispatchView *)igTextureBindAttr_CreateInstance(allocator));
                        attr.p->setTexture((igObject *)property->_tex);
                        attrSet = (igAttrSet *)entry->_attrSet;
                        boundCount = ((igAttrList *)attrSet->_attributes)->_count;
                        boundIndex = 0;
                        if (0 < boundCount) {
                            boundOffset = 0;
                            do {
                                bindMeta = g_igTextureBindAttr_metaObject;
                                existing = (igObjectDispatchView *)*(int *)(((igAttrList *)attrSet->_attributes)->_data + boundOffset);
                                if (bindMeta == existing->GetMeta()) {
                                    ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)attrSet->_attributes))->removeByValue((Gap::Core::igObject *)existing, 0);
                                    break;
                                }
                                boundIndex++;
                                boundOffset += 4;
                            } while (boundIndex < boundCount);
                        }
                        ((Gap::Core::igObjectList *)attrSet->_attributes)->append((Gap::Core::igObject *)attr.p);
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

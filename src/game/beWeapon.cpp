#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igobject_release.h"
#include "dw4/game/beBaseInfoManagerDispatchView.h"
#include "dw4/scenegraph/igSkeletonDispatchView.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beWeapon.h"
#include "dw4/game/beWeaponAttachData.h"
#include "dw4/game/beWeaponAttachDataList.h"
#include "dw4/game/beWeaponInfo.h"
#include "dw4/game/beWeaponSeqData.h"
#include "dw4/scenegraph/igAppearance.h"
#include "dw4/core/igDataLists.h"
#include "dw4/scenegraph/igGroup.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/scenegraph/igModelViewMatrixBoneSelect.h"
#include "dw4/core/igObject.h"

#pragma push
#pragma readonly_strings on

#include "dw4/support/emptyString.h"
extern "C" {


void beWeapon_Prepare(beWeapon *self);
igMetaObject *beWeapon_GetInfoMeta(void);
void beWeapon_OnAddRam(beWeapon *self, beWeaponInfoRam *ram);
void beWeapon_UpdateRam(void);
int beWeapon_OnMessageText(beWeapon *self, beWeaponInfoRam *ram, const char *message);
igMetaObject *beWeapon_GetMeta(void);


}

static inline const char *nameOf(int name) { return name != 0 ? (const char *)name : emptyString; }

/* Releases every object of the list and empties it. */
static inline void ReleaseAll(igObjectList *list) {
    int count = list->_count;
    int i;
    for (i = 0; i < count; i++) {
        igObject::release(((igObject **)list->_data)[i]);
    }
    {
        int size = list->_count;
        int j;
        for (j = 0; j < size; j++) {
            ((igObject **)list->_data)[j] = 0;
        }
    }
    list->_count = 0;
}

void beWeapon_Prepare(beWeapon *self) {
    igObject *attachDataList;

    attachDataList = (igObject *)self->_attachDataList;
    IG_OBJECT_RELEASE(attachDataList);
    self->_attachDataList = 0;
}

igMetaObject *beWeapon_GetInfoMeta(void)
{
    return g_beWeaponInfo_metaObject;
}

class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; igObject::release(o); }
};

void beWeapon_OnAddRam(beWeapon *self, beWeaponInfoRam *ram) {
    int allocator;
    int attachIndex;
    igObject *retained;
    igObject *old;
    if (self->_attachDataList == 0) {
        allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igSmartPointer<igObject> list(beWeaponAttachDataList_Create(allocator));
        retained = list.p;
        igObject::ref(retained);
        old = (igObject *)self->_attachDataList;
        igObject::release(old);
        self->_attachDataList = (int)retained;
        for (attachIndex = 0; attachIndex < 4; attachIndex++) {
            allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
            allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
            ObjectRef data(beWeaponAttachData_Create(allocator));
            ((Gap::Core::igObjectList *)self->_attachDataList)->append((Gap::Core::igObject *)data.p);
        }
    }
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)ram, "PLAYERARMS");
}

void beWeapon_UpdateRam(void)
{
}

/* GENERATE attaches the weapon's nodes to the player's skeleton, REMOVE takes them off again and
 * GETINFONAME answers the info's name. */
int beWeapon_OnMessageText(beWeapon *self, beWeaponInfoRam *ram, const char *message) {
    beWeaponInfo *info = (beWeaponInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beWeaponSeqData_GetMsgActionEnum(), message)) {
    case 0: {
        ((beBaseInfoManagerDispatchView *)self)->OnMessageText((beBaseInfoRam *)ram, "REMOVE");
        beMessenger_SendRam((beMessenger *)self->_messenger, "PLAYER", ram->_ramNo, "GETINFONAME_RUN");
        if (beMessenger_GetStringCount((beMessenger *)self->_messenger) == 1) {
            const char *infoName = beMessenger_GetString((beMessenger *)self->_messenger, 0);
            beMessenger_SendNamed((beMessenger *)self->_messenger, "ACTION", infoName, ram->_ramNo, "GETAPPEARANCELIST");
            igObjectList *appearances = (igObjectList *)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
            igSkeletonDispatchView *skeleton = (igSkeletonDispatchView *)beMessenger_GetObject((beMessenger *)self->_messenger, 1);
            int seqCount = ((beWeaponSeqDataList *)info->_seqDataList)->_count;
            for (int i = 0; i < seqCount; i++) {
                beWeaponSeqData *seq = ((beWeaponSeqData **)((beWeaponSeqDataList *)info->_seqDataList)->_data)[i];
                beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", infoName, ram->_ramNo);
                beMessenger_AppendString((beMessenger *)self->_messenger, nameOf(seq->_name));
                beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)seq->_label);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETLABEL");
            }
            int nodeCount = ((igObjectList *)info->_nodeList)->_count;
            for (int j = 0; j < nodeCount; j++) {
                igNamedObject *boneName = ((igNamedObject **)((igObjectList *)info->_boneNameList)->_data)[j];
                int bone = skeleton->FindBoneIndex(nameOf(boneName->_name));
                if (bone >= 0) {
                    int allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
                    allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                    igSmartPointer<igModelViewMatrixBoneSelect> boneSelect(igModelViewMatrixBoneSelect_CreateInstance(allocator));
                    boneSelect.p->_matrixIndex = bone;
                    igGroup_AppendChild((igGroup *)boneSelect.p, (igNode *)(((igObject **)((igObjectList *)info->_nodeList)->_data)[j]));
                    int appearanceCount = appearances->_count;
                    for (int k = 0; k < appearanceCount; k++) {
                        igAppearance_AttachGraph((igAppearance *)(((igObject **)appearances->_data)[k]), (igNode *)boneSelect.p);
                    }
                    beWeaponAttachData *attach = ((beWeaponAttachData **)((beWeaponAttachDataList *)self->_attachDataList)->_data)[ram->_ramNo];
                    ((Gap::Core::igObjectList *)attach->_boneSelectList)->append((Gap::Core::igObject *)boneSelect.p);
                    ((Gap::Core::igObjectList *)attach->_appearanceListList)->append((Gap::Core::igObject *)appearances);
                }
            }
        }
        return 1;
    }
    case 1: {
        beWeaponAttachData *attach = ((beWeaponAttachData **)((beWeaponAttachDataList *)self->_attachDataList)->_data)[ram->_ramNo];
        int count = ((igObjectList *)attach->_boneSelectList)->_count;
        for (int i = 0; i < count; i++) {
            igObject *boneSelect = ((igObject **)((igObjectList *)attach->_boneSelectList)->_data)[i];
            if (boneSelect != 0) {
                igObjectList *appearances = ((igObjectList **)((igObjectList *)attach->_appearanceListList)->_data)[i];
                int appearanceCount = appearances->_count;
                for (int k = 0; k < appearanceCount; k++) {
                    igAppearance_DetachGraph((igAppearance *)(((igObject **)appearances->_data)[k]), (igNode *)boneSelect);
                }
            }
        }
        ReleaseAll((igObjectList *)attach->_boneSelectList);
        ReleaseAll((igObjectList *)attach->_appearanceListList);
        return 1;
    }
    case 2:
        beMessenger_AppendString((beMessenger *)self->_messenger, nameOf(info->_name));
        return 1;
    default:
        return 0;
    }
}

igMetaObject *beWeapon_GetMeta(void)
{
    return g_beWeapon_metaObject;
}

#pragma pop

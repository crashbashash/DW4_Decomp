#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

#pragma push
#pragma readonly_strings on

extern "C" {
igObject *beWeaponAttachDataList_Create(int);
igObject *beWeaponAttachData_Create(int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, igObject *);
int beMessenger_RegisterReceiverFromInfo(int, int, const char *);
int igObject_GetAllocator(...);

extern int kIGMemoryPoolHandleUser1[4];
extern unsigned char g_useOwnerAllocator;
extern int g_beWeaponInfo_metaObject[4];
extern int g_beWeapon_metaObject[4];

void beWeapon_Prepare(beWeapon *arg0);
int beWeapon_GetInfoMeta(void);
void beWeapon_OnAddRam(beWeapon *arg0, int arg1);
void beWeapon_UpdateRam(void);
int beWeapon_OnMessageText(beWeapon *self, beWeaponInfoRam *ram, const char *message);
int beWeapon_GetMeta(void);

igMetaEnum *beWeaponSeqData_GetMsgActionEnum(void);
igModelViewMatrixBoneSelect *igModelViewMatrixBoneSelect_CreateInstance(int allocator);
int FUN_001af7a0(igObject *appearance, igObject *graph);
int FUN_001af7b0(igObject *appearance, igObject *graph);
int igGroup_AppendChild(igObject *group, igObject *child);
int beMessenger_ResolveEnumValue(int messenger, igMetaEnum *values, const char *name);
void beMessenger_SendRam(int messenger, const char *category, int id, const char *selector);
int beMessenger_GetStringCount(int messenger);
const char *beMessenger_GetString(int messenger, int index);
void beMessenger_SendNamed(int messenger, const char *category, const char *name, int id, const char *selector);
igObject *beMessenger_GetObject(int messenger, int index);
void beMessenger_SelectReceivers(int messenger, const char *category, const char *name, int id);
void beMessenger_AppendString(int messenger, const char *text);
void beMessenger_DispatchSelected(int messenger, const char *selector);
void igObject_Destroy(void *object);

extern char emptyString[];
}

/* The beWeapon slot this file calls through the vtable: slot 33, the message handler. */
class beWeaponSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32();
    virtual int onMessage(beWeaponInfoRam *ram, const char *message);
};

/* The skeleton slot the weapon calls: slot 25 looks a bone up by name (-1 when it has none). */
class SkeletonSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual int findBoneIndex(const char *name);
};

static inline const char *nameOf(int name) { return name != 0 ? (const char *)name : emptyString; }

/* Releases every object of the list and empties it. */
static inline void ReleaseAll(igObjectList *list) {
    int count = list->_count;
    int i;
    for (i = 0; i < count; i++) {
        igRelease(((igObject **)list->_data)[i]);
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

void beWeapon_Prepare(beWeapon *arg0) {
    int *temp_a0;

    temp_a0 = (int *)arg0->_attachDataList;
    if (temp_a0 != 0) {
        temp_a0[1] = temp_a0[1] - 1;
        if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_attachDataList = 0;
}

int beWeapon_GetInfoMeta(void)
{
    return g_beWeaponInfo_metaObject[0];
}

class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

void beWeapon_OnAddRam(beWeapon *arg0, int arg1) {
    int var_v0;
    int var_s0;
    igObject *t;
    igObject *old;
    if (arg0->_attachDataList == 0) {
        var_v0 = igObject_GetAllocator();
        var_v0 = g_useOwnerAllocator ? var_v0 : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        igSmartPointer<igObject> list(beWeaponAttachDataList_Create(var_v0));
        t = list.p;
        if (t != 0) {
            t->_refCount = t->_refCount + 1;
        }
        old = (igObject *)arg0->_attachDataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(old);
            }
        }
        arg0->_attachDataList = (int)t;
        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            var_v0 = igObject_GetAllocator(arg0);
            var_v0 = g_useOwnerAllocator ? var_v0 : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
            ObjectRef data(beWeaponAttachData_Create(var_v0));
            ObjectList_AppendRetained(arg0->_attachDataList, data.p);
        }
    }
    beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, "PLAYERARMS");
}

void beWeapon_UpdateRam(void)
{
}

/* GENERATE attaches the weapon's nodes to the player's skeleton, REMOVE takes them off again and
 * GETINFONAME answers the info's name. */
int beWeapon_OnMessageText(beWeapon *self, beWeaponInfoRam *ram, const char *message) {
    beWeaponInfo *info = (beWeaponInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue(self->_messenger, beWeaponSeqData_GetMsgActionEnum(), message)) {
    case 0: {
        ((beWeaponSlots *)self)->onMessage(ram, "REMOVE");
        beMessenger_SendRam(self->_messenger, "PLAYER", ram->_ramNo, "GETINFONAME_RUN");
        if (beMessenger_GetStringCount(self->_messenger) == 1) {
            const char *infoName = beMessenger_GetString(self->_messenger, 0);
            beMessenger_SendNamed(self->_messenger, "ACTION", infoName, ram->_ramNo, "GETAPPEARANCELIST");
            igObjectList *appearances = (igObjectList *)beMessenger_GetObject(self->_messenger, 0);
            SkeletonSlots *skeleton = (SkeletonSlots *)beMessenger_GetObject(self->_messenger, 1);
            int seqCount = ((beWeaponSeqDataList *)info->_seqDataList)->_count;
            for (int i = 0; i < seqCount; i++) {
                beWeaponSeqData *seq = ((beWeaponSeqData **)((beWeaponSeqDataList *)info->_seqDataList)->_data)[i];
                beMessenger_SelectReceivers(self->_messenger, "MODELCTRL", infoName, ram->_ramNo);
                beMessenger_AppendString(self->_messenger, nameOf(seq->_name));
                beMessenger_AppendString(self->_messenger, (const char *)seq->_label);
                beMessenger_DispatchSelected(self->_messenger, "SETLABEL");
            }
            int nodeCount = ((igObjectList *)info->_nodeList)->_count;
            for (int j = 0; j < nodeCount; j++) {
                igNamedObject *boneName = ((igNamedObject **)((igObjectList *)info->_boneNameList)->_data)[j];
                int bone = skeleton->findBoneIndex(nameOf(boneName->_name));
                if (bone >= 0) {
                    int allocator = igObject_GetAllocator(self);
                    allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
                    igSmartPointer<igModelViewMatrixBoneSelect> boneSelect(igModelViewMatrixBoneSelect_CreateInstance(allocator));
                    boneSelect.p->_matrixIndex = bone;
                    igGroup_AppendChild(boneSelect.p, ((igObject **)((igObjectList *)info->_nodeList)->_data)[j]);
                    int appearanceCount = appearances->_count;
                    for (int k = 0; k < appearanceCount; k++) {
                        FUN_001af7a0(((igObject **)appearances->_data)[k], boneSelect.p);
                    }
                    beWeaponAttachData *attach = ((beWeaponAttachData **)((beWeaponAttachDataList *)self->_attachDataList)->_data)[ram->_ramNo];
                    ObjectList_AppendRetained(attach->_boneSelectList, boneSelect.p);
                    ObjectList_AppendRetained(attach->_appearanceListList, (igObject *)appearances);
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
                    FUN_001af7b0(((igObject **)appearances->_data)[k], boneSelect);
                }
            }
        }
        ReleaseAll((igObjectList *)attach->_boneSelectList);
        ReleaseAll((igObjectList *)attach->_appearanceListList);
        return 1;
    }
    case 2:
        beMessenger_AppendString(self->_messenger, nameOf(info->_name));
        return 1;
    default:
        return 0;
    }
}

int beWeapon_GetMeta(void)
{
    return g_beWeapon_metaObject[0];
}

#pragma pop

#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/beModelCtrlDispatchView.h"
#include "dw4/beNDMWItemBaseDispatchView.h"
#include "dw4/igVisualContextDispatchView.h"
#include "dw4/StringPool.h"
#include "dw4/be.h"
#include "dw4/beBaseInfoDataList.h"
#include "dw4/beBaseInfoManager.h"
#include "dw4/beBaseInfoRam.h"
#include "dw4/beMessenger.h"
#include "dw4/beModelCtrl.h"
#include "dw4/beNDMWItemAbilityChip.h"
#include "dw4/beNDMWItemBlueArmor.h"
#include "dw4/beNDMWItemDisk.h"
#include "dw4/beNDMWItemImportant.h"
#include "dw4/beNDMWItemInstant.h"
#include "dw4/beNDMWItemWeapon.h"
#include "dw4/beNDMWItemYellowArmor.h"
#include "dw4/beNDMWMdlItem.h"
#include "dw4/beNDMWMdlItemInfoWork.h"
#include "dw4/beTargetObj.h"
#include "dw4/igDataLists.h"
#include "dw4/igInsightCore.h"
#include "dw4/igMathConstants.h"
#include "dw4/igMatrix44f.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igNamedObject.h"
#include "dw4/igObject.h"
#include "dw4/igViewerSceneInfoManager.h"
#include <string.h>
#include "dw4/beDBManager.h"
#define HOLDER_BODY { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
#define ALLOC_OF(owner, a, sel) { a = igObject_GetAllocator(owner); a = g_useOwnerAllocator ? a : Memory_GetAllocatorBySelector(sel); }
#define ALLOC(a, sel) ALLOC_OF(self, a, sel)
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if ((rr->_refCount & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }
#define STORE_REF(slot, fresh) { igObject *held2 = fresh; if (held2 != 0) held2->_refCount = held2->_refCount + 1; REL((igObject *)slot) slot = (int)held2; }

extern "C" int beNDMWMdlItem_IsKind(int unused, int kind);
extern "C" int beNDMWMdlItem_GetMeta(void);
/* kept local: beNDMWItemBase.h is not included: its by-value GetRevisionColor moves the colour off retail's frame slot (load-bearing). */
extern "C" int beNDMWItemBase_IndexOfRecNo(igObjectList *items, int recNo);
/* Per instant item (recNo 1..25): the pickup panel model and the sequence it plays. */
struct ItemPickupSeq { const char *panel; const char *sequence; };
extern "C" ItemPickupSeq g_itemPickupSeqs[25];
extern "C" void beNDMWMdlItem_PlayPickupEffect(beNDMWMdlItem *self, int recNo, int playerNo);
extern "C" void beNDMWMdlItem_RegisterReceiver(beNDMWMdlItem *self, int info);
extern "C" void beNDMWMdlItem_Start(beNDMWMdlItem *self);
extern "C" void beNDMWMdlItem_Prepare(beNDMWMdlItem *self);
/* kept local: no include/dw4 home declares it yet. */
extern "C" char emptyString[];
struct ObjectRef { igObject *p; ObjectRef(igObject *o) : p(o) {} ~ObjectRef() HOLDER_BODY };
struct Store {
    static inline void assign(int &slot, igObject *fresh) {
        igObject *held2 = fresh;
        if (held2 != 0) held2->_refCount = held2->_refCount + 1;
        REL((igObject *)slot)
        slot = (int)held2;
    }
};
extern "C" void beNDMWMdlItem_OnGenerate(beNDMWMdlItem *self, beBaseInfoRam *info);
/* matching construct: inline release helper reproduces the retail inlined refcount release */
struct RefRelease { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void beNDMWMdlItem_OnErase(beNDMWMdlItem *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlItem_OnSequenceChange(beNDMWMdlItem *self, beBaseInfoRam *ram);
extern "C" { unsigned char g_flagFolderSetValue = 1; }
extern "C" void beNDMWMdlItem_OnAction1(beNDMWMdlItem *self, beNDMWGameRamInfoRam *ram);
extern "C" void beNDMWMdlItem_UpdateControl(beNDMWMdlItem *self, beBaseInfoRam *ram);
/* kept local: beNDMWItemBase.h is not included: its by-value GetRevisionColor moves the colour off retail's frame slot (load-bearing). */
extern "C" char *beNDMWItemBase_GetRecordString(int item, beNDMWMdlItem *ctrl, const char *field);
extern "C" void beNDMWItemBase_GetRevisionColor(float *color, int item);
/* kept local: no include/dw4 home declares it yet. */
extern "C" void igMatrix44f_Copy(float *matrix, void *source);
extern "C" void Vec3f_TransformProjective(float *out, float *v, float *m);
extern "C" { beBaseInfoRam *g_mdlEntity; }
extern "C" { float *g_mdlMatrix; }
#pragma push
#pragma readonly_strings on

extern "C" {
const char *g_itemFolderNames[10] = { "g_000bit", "g_000xdata1", "g_000xdata2", "g_000access", "g_000armor", "g_000boost1", "g_000item", "g_000key", "g_000penx", "g_000weapon" };
/* "font00".."font03": the item-name font of each player */
const char *g_itemNameFontNames[4] = { "font00", "font01", "font02", "font03" };
}

/* Plays the pickup effect of instant item recNo (1..25) on player playerNo. */
void beNDMWMdlItem_PlayPickupEffect(beNDMWMdlItem *self, int recNo, int playerNo) {
    float pos[4];
    int index;

    beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, "PLAYER", 0, playerNo);
    index = recNo - 1;
    beMessenger_AppendString((beMessenger *)self->_messenger, g_itemPickupSeqs[index].panel);
    beMessenger_AppendString((beMessenger *)self->_messenger, g_itemPickupSeqs[index].sequence);
    beMessenger_AppendFloat((beMessenger *)self->_messenger, 1.0f);
    pos[0] = g_vec3Zero[0];
    pos[1] = g_vec3Zero[1];
    pos[2] = g_vec3Zero[2];
    beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)pos);
    beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
    beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
    beMessenger_EnqueueSelected((beMessenger *)self->_messenger, "SETEFFECT", 1);
}

int beNDMWMdlItem_IsKind(int unused, int kind) {
    return strcmp((const char *)kind, "KIND_ITEM") == 0;
}

void beNDMWMdlItem_RegisterReceiver(beNDMWMdlItem *self, int info)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)info, "DROPITEM");
}

/* After the shared igObject slot 23 body, caches the viewer scene-info manager registered with the
 * insight core (_viewerSIManager), found by its class metaObject; the same binding step as the
 * other managers' slot 23. */
void beNDMWMdlItem_Start(beNDMWMdlItem *self) {
    beBaseInfoManager_Start((beBaseInfoManager *)self);
    self->_viewerSIManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_igViewerSceneInfoManager_metaObject);
}

void beNDMWMdlItem_Prepare(beNDMWMdlItem *self) {
    igDataList *l;
    int n;
    int i;
    igObject *r;
    int n2;
    int i2;
    l = (igDataList *)self->_lockRamList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        r = ((igObject **)l->_data)[i];
        if (r != 0) {
            --r->_refCount;
            if (((unsigned long long)(long long)r->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    n2 = l->_count;
    for (i2 = 0; i2 < n2; i2++) {
        ((igObject **)l->_data)[i2] = 0;
    }
    l->_count = 0;
}

template <class Ref> static inline void storeItem(const igSmartPointer<beNDMWMdlItemInfoWork> &work, const Ref &item) {
    igObject *held2 = item.p;
    beNDMWMdlItemInfoWork *w2 = work.p;
    if (held2 != 0) held2->_refCount = held2->_refCount + 1;
    REL((igObject *)w2->_itemObject)
    w2->_itemObject = (int)held2;
}

void beNDMWMdlItem_OnGenerate(beNDMWMdlItem *self, beBaseInfoRam *info) {
    beBaseInfo *parent = (beBaseInfo *)info->_parentInfo;
    igMemoryPoolView *alloc;
    beModelCtrlInfoRamData *prop;
    igObject *held;
    char *name;
    int i;
    int roll;

    if (info->_dataList == 0) {
        ALLOC_OF(info, alloc, kIGMemoryPoolHandleUser1)
        Store::assign(info->_dataList, ObjectRef(beBaseInfoDataList_Create((int)alloc)).p);
    }
    prop = (beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)info->_dataList, g_propertyNameField, "ONE");
    ALLOC(alloc, kIGMemoryPoolHandleUser1)
    {
    igSmartPointer<beNDMWMdlItemInfoWork> work((beNDMWMdlItemInfoWork *)beNDMWMdlItemInfoWork_Create((int)alloc));
    held = (igObject *)work.p;
    if (held != 0) held->_refCount = held->_refCount + 1;
    REL((igObject *)prop->_work)
    prop->_work = (int)held;
    if (beMessenger_GetIntCount((beMessenger *)self->_messenger) != 0) {
        work.p->_recNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        work.p->_dbId = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
    }
    i = 0;
    do {
        name = (char *)parent->_name;
        name = name != 0 ? name : emptyString;
        if (strcmp(name, g_itemFolderNames[i]) == 0) {
            work.p->_kind = i;
            break;
        }
        i += 1;
    } while (i < 10);
    {
        beNDMWMdlItemInfoWork *w = work.p;
        if (w->_kind < 3) {
            w->_isNamed = 0;
        } else {
            w->_isNamed = 1;
        }
    }
    switch ((unsigned int)work.p->_dbId) {
    case 0: {
        ALLOC(alloc, kIGMemoryPoolHandleUser0)
        igSmartPointer<beNDMWItemDisk> h((beNDMWItemDisk *)beNDMWItemDisk_Create((int)alloc));
        { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemDisk_Set(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 1: {
        ALLOC(alloc, kIGMemoryPoolHandleUser0)
        igSmartPointer<beNDMWItemInstant> h((beNDMWItemInstant *)beNDMWItemInstant_Create((int)alloc));
        { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemInstant_Set(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 2: {
        ALLOC(alloc, kIGMemoryPoolHandleUser0)
        igSmartPointer<beNDMWItemImportant> h((beNDMWItemImportant *)beNDMWItemImportant_Create((int)alloc));
        { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemImportant_Set(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 6: {
        ALLOC(alloc, kIGMemoryPoolHandleUser0)
        igSmartPointer<beNDMWItemAbilityChip> h((beNDMWItemAbilityChip *)beNDMWItemAbilityChip_Create((int)alloc));
        { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemAbilityChip_Set(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 3:
    case 4:
    case 5:
        beMessenger_PushArgContext((beMessenger *)self->_messenger);
        beMessenger_SendGroup((beMessenger *)self->_messenger, "GAMERAM", "GETPLAYER1");
        roll = igProperty_GetRecord(beMessenger_GetObject((beMessenger *)self->_messenger, 0), "LEVEL")->_data;
        switch ((unsigned int)work.p->_dbId) {
        case 3: {
            ALLOC(alloc, kIGMemoryPoolHandleUser0)
            igSmartPointer<beNDMWItemWeapon> h((beNDMWItemWeapon *)beNDMWItemWeapon_Create((int)alloc));
            { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemWeapon_SetRandom(h.p, w->_recNo, (beNDMWStatus *)self, roll); }
            storeItem(work, h);
            break;
        }
        case 4: {
            ALLOC(alloc, kIGMemoryPoolHandleUser0)
            igSmartPointer<beNDMWItemBlueArmor> h((beNDMWItemBlueArmor *)beNDMWItemBlueArmor_Create((int)alloc));
            { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemBlueArmor_SetRandom(h.p, w->_recNo, (beNDMWStatus *)self, roll); }
            storeItem(work, h);
            break;
        }
        case 5: {
            ALLOC(alloc, kIGMemoryPoolHandleUser0)
            igSmartPointer<beNDMWItemYellowArmor> h((beNDMWItemYellowArmor *)beNDMWItemYellowArmor_Create((int)alloc));
            { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemYellowArmor_SetRandom(h.p, w->_recNo, (beNDMWStatus *)self, roll); }
            storeItem(work, h);
            break;
        }
        }
        beMessenger_PopArgContext((beMessenger *)self->_messenger);
        break;
    }
    }
    beModelCtrl__OnGenerate((beModelCtrl *)self, info);
}

/* Squared distance between two points. */
static inline float DistanceSq(const float *a, const float *b) {
    return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2]) * (a[2] - b[2]);
}

/* Per frame: find the nearest player. A plain item (money, recovery) is used up by the first
 * player who comes near; a named item shows its name over itself in that player's font, locks
 * itself to the player, blinks the name colour and keeps the label on the item's screen position
 * until the player walks away (then the item is released through slot 45). */
void beNDMWMdlItem_UpdateControl(beNDMWMdlItem *self, beBaseInfoRam *ram) {
    beModelCtrlInfoRamData *ramData;
    beNDMWMdlItemInfoWork *work;
    igObjectList *locks;
    int i;
    bool isNear;
    int ramNo;
    int x, y, w, h;
    float color[3];
    float itemPos[3];
    float playerPos[3];
    float pos[3];
    float eye[3];
    float rgb[3];
    float label[3];
    float view[16];
    float projection[16];
    float playerMatrix[16];
    float distSq;
    if (ram->_dataList == 0) {
        int alloc = ((int)igObject_GetAllocator(ram));
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
        }
        ObjectRef created(beBaseInfoDataList_Create(a));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        RefRelease::go((igObject *)ram->_dataList);
        ram->_dataList = (int)s0;
    }
    ramData = (beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE");
    work = (beNDMWMdlItemInfoWork *)ramData->_work;
    if (((igObjectList *)self->_lockRamList)->_count == 0) {
        for (i = 0; i < 4; i++) {
            ObjectList_AppendRetained((igObjectList *)self->_lockRamList, 0);
        }
    }
    isNear = 0;
    ramNo = 0;
    if (beTargetObj_SelectTarget((float *)((char *)ramData->_node + 32), "PLAYER", "NEAR") != 0) {
        float distSq = beTargetObj_GetTargetDistanceSq();
        ramNo = beTargetObj_GetTargetRamNo();
        isNear = distSq < 64.0f;
    }
    if (work->_isNamed == 0) {
        if (isNear) {
            ((beNDMWItemBaseDispatchView *)work->_itemObject)->Use((igObject *)self, ramNo);
            {
                char *token;
                int *old;
                if (g_stringPool == 0) {
                    void *pool = StringPool_Allocate(0x10);
                    if (pool != 0) pool = StringPool_Construct((StringPool *)pool);
                    g_stringPool = (StringPool *)pool;
                }
                token = StringPool_Intern(g_stringPool, "SQ_DDMG");
                old = (int *)work->_keyEventName;
                if (old != 0) {
                    int *header = old - 2;
                    int refs = old[-1] - 1;
                    old[-1] = refs;
                    if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
                }
                work->_keyEventName = (int)token;
            }
            switch (((beNDMWItemInstant *)work->_itemObject)->_recNo) {
            case 0:
                g_mdlEntity = ram;
                g_mdlMatrix = (float *)((char *)ramData->_node + 32);
                FloatingNumber_Spawn(((beNDMWItemInstant *)work->_itemObject)->_value, 4);
                break;
            case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
            case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20:
            case 21: case 22: case 23: case 24: case 25:
                beNDMWMdlItem_PlayPickupEffect(self, ((beNDMWItemInstant *)work->_itemObject)->_recNo, ramNo);
                break;
            }
        }
    } else switch (ram->_st0) {
    case 0:
        if (isNear == 0) break;
        if (((igObject **)((igObjectList *)self->_lockRamList)->_data)[ramNo] == 0) {
            const char *font = g_itemNameFontNames[ramNo];
            char *name;
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "TEXTCTL");
            beMessenger_AppendString((beMessenger *)self->_messenger, "ITNAMEFONT");
            beMessenger_AppendString((beMessenger *)self->_messenger, font);
            beMessenger_AppendString((beMessenger *)self->_messenger, "CENTER");
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ALIGN");
            name = beNDMWItemBase_GetRecordString(work->_itemObject, self, "NAME");
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "TEXTCTL");
            beMessenger_AppendString((beMessenger *)self->_messenger, "ITNAMEFONT");
            beMessenger_AppendString((beMessenger *)self->_messenger, font);
            beMessenger_AppendString((beMessenger *)self->_messenger, name);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "TEXTSET");
            work->_isColorLight = 0;
            beBaseInfoRam_RemoveTimer(ram, "COLOR");
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "TEXTCTL");
            beMessenger_AppendString((beMessenger *)self->_messenger, "ITNAMEFONT");
            beMessenger_AppendString((beMessenger *)self->_messenger, font);
            beMessenger_AppendString((beMessenger *)self->_messenger, "SET");
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
            work->_isDispName = 1;
            {
                char *token;
                int *old;
                if (g_stringPool == 0) {
                    void *pool = StringPool_Allocate(0x10);
                    if (pool != 0) pool = StringPool_Construct((StringPool *)pool);
                    g_stringPool = (StringPool *)pool;
                }
                token = StringPool_Intern(g_stringPool, font);
                old = (int *)work->_fontType;
                if (old != 0) {
                    int *header = old - 2;
                    int refs = old[-1] - 1;
                    old[-1] = refs;
                    if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
                }
                work->_fontType = (int)token;
            }
            work->_dispPlayerRamNo = ramNo;
            locks = (igObjectList *)self->_lockRamList;
            if (ram != 0) ram->_refCount++;
            RefRelease::go(((igObject **)locks->_data)[ramNo]);
            {
                int count = locks->_count;
                if (count != 0 && ramNo >= 0 && ramNo < count) ((igObject **)locks->_data)[ramNo] = ram;
            }
            ram->_st0++;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
        }
        if (ram->_st0 == 0) break;
    case 1:
        if (beBaseInfoRam_IsTimerExpired(ram, "COLOR") != 0) {
            beNDMWItemBase_GetRevisionColor(color, work->_itemObject);
            if (work->_isColorLight != 0) {
                work->_isColorLight = 0;
                color[0] /= 3.0f;
                color[1] /= 3.0f;
                color[2] /= 3.0f;
            } else {
                work->_isColorLight = 1;
            }
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "TEXTCTL");
            beMessenger_AppendString((beMessenger *)self->_messenger, "ITNAMEFONT");
            beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)work->_fontType);
            rgb[0] = color[0];
            rgb[1] = color[1];
            rgb[2] = color[2];
            beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)rgb);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "COLOR");
            beBaseInfoRam_StartTimer(ram, "COLOR", 500000000);
        }
        igMatrix44f_GetTranslation((const float *)((char *)ramData->_node + 32), itemPos);
        beMessenger_SendNamed((beMessenger *)self->_messenger, "PLAYER", 0, work->_dispPlayerRamNo, "GETMATRIX");
        if (beMessenger_GetMatrixCount((beMessenger *)self->_messenger) != 0) {
            beMessenger_GetMatrix(playerMatrix, (beMessenger *)self->_messenger, 0);
            igMatrix44f_GetTranslation(playerMatrix, playerPos);
            distSq = DistanceSq(itemPos, playerPos);
        } else {
            distSq = 100.0f;
        }
        if (distSq < 64.0f) {
            float screenX, screenY;
            igViewerParameters *params;
            igMatrix44f_SetIdentity(view);
            igMatrix44f_SetIdentity(projection);
            params = (igViewerParameters *)((igViewerSceneInfoManager *)self->_viewerSIManager)->_parameters;
            igMatrix44f_Copy(view, params->_viewMatrix);
            params = (igViewerParameters *)((igViewerSceneInfoManager *)self->_viewerSIManager)->_parameters;
            igMatrix44f_Copy(projection, params->_projectionMatrix);
            igMatrix44f_GetTranslation((const float *)((char *)ramData->_node + 32), pos);
            pos[1] += 10.0f;
            Vec3f_TransformProjective(eye, pos, view);
            Vec3f_TransformProjective(pos, eye, projection);
            ((igVisualContextDispatchView *)((igInsightCore *)self->_insight)->_visualContext)->getViewport(&x, &y, &w, &h);
            screenX = x + ((1.0f + pos[0]) * w) / 2.0f;
            screenY = h - (y + ((1.0f + pos[1]) * h) / 2.0f);
            screenX -= w / 2;
            screenY = (h - screenY) - h / 2;
            screenX /= 100.0f;
            screenY /= 100.0f;
            screenX -= 0.7f;
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "TEXTCTL");
            beMessenger_AppendString((beMessenger *)self->_messenger, "ITNAMEFONT");
            beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)work->_fontType);
            label[0] = screenX;
            label[1] = screenY;
            label[2] = -5.0f;
            beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)label);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETPOSITION");
        } else {
            ((beModelCtrlDispatchView *)self)->OnErase(ram);
            ram->_st0 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
        }
        break;
    }
}

void beNDMWMdlItem_OnErase(beNDMWMdlItem *self, beBaseInfoRam *ram) {
    beModelCtrlInfoRamData *record;
    beNDMWMdlItemInfoWork *work;
    int idx;
    igObjectList *locks;
    int cnt, off;
    if (ram->_dataList == 0) {
        int alloc = ((int)igObject_GetAllocator(ram));
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
        }
        ObjectRef created(beBaseInfoDataList_Create(a));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        RefRelease::go((igObject *)ram->_dataList);
        ram->_dataList = (int)s0;
    }
    record = (beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE");
    work = (beNDMWMdlItemInfoWork *)record->_work;
    if (work->_isDispName != 0) {
        work->_isDispName = 0;
        locks = (igObjectList *)self->_lockRamList;
        idx = work->_dispPlayerRamNo;
        off = idx * 4;
        RefRelease::go(*(igObject **)((char *)locks->_data + off));
        cnt = locks->_count;
        if (cnt != 0 && idx >= 0 && idx < cnt) {
            *(igObject **)((char *)locks->_data + off) = 0;
        }
        work->_dispPlayerRamNo = -1;
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "TEXTCTL");
        beMessenger_AppendString((beMessenger *)self->_messenger, "ITNAMEFONT");
        beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)work->_fontType);
        beMessenger_AppendString((beMessenger *)self->_messenger, "CLR");
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
    }
}

static inline void setDataList(beBaseInfoRam *ram, const ObjectRef &list) {
    igObject *t = list.p;
    if (t != 0) t->_refCount = t->_refCount + 1;
    igRelease((igObject *)ram->_dataList);
    ram->_dataList = (int)t;
}

static inline void adoptDataList(beBaseInfoRam *ram, igObject *created) {
    ObjectRef list(created);
    setDataList(ram, list);
}

void beNDMWMdlItem_OnSequenceChange(beNDMWMdlItem *self, beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        void *a = igObject_GetAllocator(ram);
        void *al = g_useOwnerAllocator != 0 ? a : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igObject *created = (igObject *)((void *)beBaseInfoDataList_Create((int)al));
        adoptDataList(ram, created);
    }
    beModelCtrlInfoRamData *one = ((beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, ("ONE")));
    if (strcmp((const char *)((beModelCtrlInfoWork *)one->_work)->_seqCodeName, "SQ_EXIT") == 0)
        ((beModelCtrlDispatchView *)self)->OnErase(ram);
}

void beNDMWMdlItem_OnAction1(beNDMWMdlItem *self, beNDMWGameRamInfoRam *ram) {
    igObject *dataList;
    beNDMWMdlItemInfoWork *work;
    int playerNo;
    bool canTake;
    int player;
    if (ram->_dataList == 0) {
        int alloc = ((int)igObject_GetAllocator(ram));
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
        }
        ObjectRef ref(beBaseInfoDataList_Create(a));
        dataList = ref.p;
        if (dataList != 0) {
            dataList->_refCount++;
        }
        RefRelease::go((igObject *)ram->_dataList);
        ram->_dataList = (int)dataList;
    }
    work = (beNDMWMdlItemInfoWork *)((beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE"))->_work;
    if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) == 0 && work->_isNamed != 0 && work->_isDispName != 0) {
        playerNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        if (playerNo == work->_dispPlayerRamNo) {
            canTake = true;
            beMessenger_PushArgContext((beMessenger *)self->_messenger);
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
            beMessenger_AppendInt((beMessenger *)self->_messenger, playerNo);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GETPLAYER");
            player = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
            unsigned t1 = work->_kind - 3;
            switch (t1) {
            case 0:
            case 1:
            case 6:
                if (((igObjectList *)igProperty_GetRecordFolder((igObject *)player, "DEVICEFOLDER")->_data)->_count >= 36) {
                    canTake = false;
                }
                break;
            case 2:
            case 3:
            case 5: {
                igObjectList *l = (igObjectList *)igProperty_GetRecordFolder((igObject *)player, "DISKFOLDER")->_data;
                if (((beNDMWItemDisk **)l->_data)[beNDMWItemBase_IndexOfRecNo(l, work->_recNo)]->_kazu >= 9) {
                    canTake = false;
                }
                break;
            }
            }
            if (canTake) {
                igObjectList *a2 = (igObjectList *)igProperty_GetRecordFolder((igObject *)player, "DEVICEFOLDER")->_data;
                unsigned t2 = work->_kind - 3;
            switch (t2) {
                case 0:
                case 1:
                case 6:
                    ObjectList_AppendRetained(a2, (igObject *)work->_itemObject);
                    break;
                case 2:
                case 3:
                case 5: {
                    igObjectList *l = (igObjectList *)igProperty_GetRecordFolder((igObject *)player, "DISKFOLDER")->_data;
                    beNDMWItemDisk *it = ((beNDMWItemDisk **)l->_data)[beNDMWItemBase_IndexOfRecNo(l, work->_recNo)];
                    int v = it->_kazu;
                    if (v != 9) {
                        it->_kazu = v + 1;
                    }
                    break;
                }
                case 4: {
                    beMessenger_SendGroup((beMessenger *)self->_messenger, "GAMERAM", "GETCOMMON");
                    int o = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                    int idx = work->_recNo;
                    igUnsignedCharList *ar = (igUnsignedCharList *)igProperty_GetRecordArray((igObject *)o, "FLAGFOLDER")->_data;
                    int n = ar->_count;
                    if (n != 0 && idx >= 0 && idx < n) {
                        *(unsigned char *)(idx + (int)ar->_data) = g_flagFolderSetValue;
                    }
                    break;
                }
                }
                int ramNo = ram->_ramNo;
                beNDMWGameRamInfo *info = (beNDMWGameRamInfo *)ram->_parentInfo;
                int *name = info->_name ? (int *)info->_name : ((int *)emptyString);
                beMessenger_SendNamed((beMessenger *)self->_messenger, (const char *)((int *)"DROPITEM"), (const char *)name, ramNo, "SQ_DDMG");
                ((beModelCtrlDispatchView *)self)->OnErase((beBaseInfoRam *)ram);
            }
            beMessenger_PopArgContext((beMessenger *)self->_messenger);
            if (canTake) {
                beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
            }
        }
    }
}

int beNDMWMdlItem_GetMeta(void)
{
    return (int)g_beNDMWMdlItem_metaObject;
}

#pragma pop

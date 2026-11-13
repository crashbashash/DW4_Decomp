#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define HOLDER_BODY { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
#define ALLOC_OF(owner, a, sel) { a = igObject_GetAllocator(owner); a = g_useOwnerAllocator ? a : Memory_GetAllocatorBySelector(sel[0]); }
#define ALLOC(a, sel) ALLOC_OF(self, a, sel)
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if ((rr->_refCount & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }
#define STORE_REF(slot, fresh) { igObject *held2 = fresh; if (held2 != 0) held2->_refCount = held2->_refCount + 1; REL((igObject *)slot) slot = (int)held2; }

extern "C" int beMessenger_AppendBool(...);
extern "C" int beMessenger_AppendFloat(int, float);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_AppendVec3(int, float *);
extern "C" int beMessenger_EnqueueSelected(int, int *, int);
extern "C" int beMessenger_PrepareDelayedSelection(int, int *, int, int);
extern "C" int strcmp(...);
extern "C" int Gap__Bec__beNDMWMdlItem__vfunc_35(int dummy0, int arg1);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int igInsightCore_FindManager(int, int);
extern "C" int Gap__Core__igObject__vfunc_23(...);
extern "C" int Gap__Bec__beNDMWMdlItem__vfunc_20(void);
extern "C" int beNDMWItemWeapon_SetRandom(...);
extern "C" int beNDMWItemBlueArmor_SetRandom(...);
extern "C" int beNDMWItemYellowArmor_SetRandom(...);
extern "C" int beNDMWItemAbilityChip_Set(...);
extern "C" int beNDMWItemDisk_Set(...);
extern "C" int beNDMWItemInstant_Set(...);
extern "C" int beNDMWItemImportant_Set(...);
extern "C" int beModelCtrl__OnGenerate(...);
extern "C" void * Memory_GetAllocatorBySelector(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_GetObject(...);
extern "C" int beMessenger_PopArgContext(...);
extern "C" int beMessenger_PushArgContext(...);
extern "C" int beMessenger_SendGroup(...);
extern "C" void * igObject_GetAllocator(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int beMessenger_AppendMatrix(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beNDMWItemBase_IndexOfRecNo(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int DAT_004cfb40[4];
extern "C" int DAT_004cfb44[4];
extern "C" float g_vec3Zero[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
extern "C" int PLAYER_9[4];
extern "C" int SETEFFECT_4[4];
extern "C" void beNDMWMdlItem_PlayPickupEffect(beNDMWMdlItem *self, int recNo, int playerNo);
extern "C" int KIND_ITEM[4];
extern "C" char DROPITEM_2[];
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_37(beNDMWMdlItem *p0, int a1);
extern "C" int g_beNDMWMdlItem_metaObject[4];
extern "C" int g_igViewerSceneInfoManager_metaObject[4];
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_23(beNDMWMdlItem *self);
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_32(beNDMWMdlItem *arg0);
struct Prop { char pad[20]; igObject *f20; };
struct ParentInfo : public igObject { char *_name; };
struct Rec { int p[3]; int f12; };
extern "C" igObject * beBaseInfoDataList_Create(...);
extern "C" igObject *FUN_003c13f0(...);
extern "C" igObject *beNDMWItemDisk_Create(...);
extern "C" igObject *FUN_003c83c0(...);
extern "C" igObject *FUN_003c8240(...);
extern "C" igObject *beNDMWItemAbilityChip_Create(...);
extern "C" igObject *beNDMWItemWeapon_Create(...);
extern "C" igObject *beNDMWItemBlueArmor_Create(...);
extern "C" igObject *beNDMWItemYellowArmor_Create(...);
extern "C" Prop * igProperty_FindByName(...);
extern "C" Rec *igProperty_GetRecord(...);
extern "C" char *DAT_004cfc10[10];
extern "C" char emptyString[];
extern "C" int ONE_14[4];
extern "C" int GAMERAM_16[4];
extern "C" int GETPLAYER1_2[4];
extern "C" int LEVEL_9[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char g_useOwnerAllocator;
struct ObjectRef { igObject *p; ObjectRef(igObject *o) : p(o) {} ~ObjectRef() HOLDER_BODY };
struct ItemRef { igObject *p; ItemRef(igObject *o) : p(o) {} ~ItemRef() HOLDER_BODY };
struct ItemRefB { igObject *p; ItemRefB(igObject *o) : p(o) {} ~ItemRefB() HOLDER_BODY };
struct ItemRefC { igObject *p; ItemRefC(igObject *o) : p(o) {} ~ItemRefC() HOLDER_BODY };
template <int K> struct ItemRefK { igObject *p; ItemRefK(igObject *o) : p(o) {} ~ItemRefK() HOLDER_BODY };
struct Store {
    static inline void assign(int &slot, igObject *fresh) {
        igObject *held2 = fresh;
        if (held2 != 0) held2->_refCount = held2->_refCount + 1;
        REL((igObject *)slot)
        slot = (int)held2;
    }
};
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_36(beNDMWMdlItem *self, beBaseInfoRam *info);
struct PropertyValueObj { char p[252]; int f252; unsigned char f256; char p257[3]; int f260; };
struct PropertyEntry { char p[16]; int f16; PropertyValueObj *q; };
extern "C" int TEXTCTL_10[4];
extern "C" int ITNAMEFONT[4];
extern "C" int SWITCH_10[4];
extern "C" int CLR_6[4];
/* matching construct: inline release helper reproduces the retail inlined refcount release */
struct RefRelease { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_43(beNDMWMdlItem *arg0, beBaseInfoRam *arg1);
extern "C" char SQ_EXIT_2[];
class MdlItemVt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void exit(beBaseInfoRam *ram); };
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_44(beNDMWMdlItem *self, beBaseInfoRam *ram);
struct ItemRecord { char p[20]; int f20; };
struct PropertyFolder { char p[12]; igObjectList *f12; };
struct PropertyByteArrayHolder { char p[12]; igUnsignedCharList *f12; };
struct PropertyRecord { char p[20]; beNDMWMdlItemInfoWork *q; };
extern "C" PropertyFolder *igProperty_GetRecordFolder(...);
extern "C" PropertyByteArrayHolder *igProperty_GetRecordArray(...);
extern "C" int SQ_DDMG[16];
extern "C" int GETPLAYER_12[16];
extern "C" int DEVICEFOLDER_5[16];
extern "C" int DISKFOLDER_6[16];
extern "C" int GETCOMMON_11[16];
extern "C" int FLAGFOLDER_3[16];
extern "C" unsigned char GPR_00554a74;
/* matching construct: the inlined release of the previous data list is a static member so the compiler expands it as retail does */
struct ReleaseRefInline { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class MdlItemVirtual { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42();  virtual void vX(beNDMWGameRamInfoRam *); char p[16]; };
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_45(MdlItemVirtual *arg0, beNDMWGameRamInfoRam *arg1);
extern "C" void beNDMWMdlItem_Update(beNDMWMdlItem *self, beBaseInfoRam *ram);
extern "C" int beTargetObj_SelectTarget(void *, void *, void *);
extern "C" float beTargetObj_GetTargetDistanceSq(void);
extern "C" int beTargetObj_GetTargetRamNo(void);
extern "C" void *StringPool_Allocate(int);
extern "C" void *StringPool_Construct(void *);
extern "C" char *StringPool_Intern(void *, const void *);
extern "C" void StringChunk_ReleaseHeader(int, int *);
extern "C" void FloatingNumber_Spawn(int value, int style);
extern "C" char *beNDMWItemBase_GetRecordString(int item, beNDMWMdlItem *ctrl, void *field);
extern "C" void beNDMWItemBase_GetRevisionColor(float *color, int item);
extern "C" int beBaseInfoRam_IsTimerExpired(beBaseInfoRam *, void *);
extern "C" void beBaseInfoRam_RemoveTimer(beBaseInfoRam *, void *);
extern "C" void beBaseInfoRam_StartTimer(beBaseInfoRam *, void *, int);
extern "C" void Matrix44_GetTranslation(void *matrix, float *out);
extern "C" void Matrix44_Copy(float *matrix, void *source);
extern "C" void igMatrix44f_SetIdentity(float *matrix);
extern "C" void Vec3f_TransformProjective(float *out, float *v, float *m);
extern "C" int beMessenger_GetMatrixCount(int);
extern "C" void beMessenger_GetMatrix(float *out, int messenger, int index);
extern "C" void *g_stringPool[4];
extern "C" beBaseInfoRam *g_mdlEntity[4];
extern "C" void *g_mdlMatrix[4];
/* "font00".."font03": the item-name font of each player */
extern "C" char *g_itemNameFontNames[4];
extern "C" char NEAR_4[];
extern "C" char CENTER_6[];
extern "C" char ALIGN_6[];
extern "C" char NAME_8[];
extern "C" char TEXTSET_8[];
extern "C" char COLOR_6[];
extern "C" char SET_6[];
extern "C" char GETMATRIX_10[];
extern "C" char SETPOSITION[];

/* Plays the pickup effect of instant item recNo (1..25) on player playerNo. */
void beNDMWMdlItem_PlayPickupEffect(beNDMWMdlItem *self, int recNo, int playerNo) {
    float sp30[4];
    int temp_s1;

    beMessenger_PrepareDelayedSelection(self->_messenger, &PLAYER_9[0], 0, playerNo);
    temp_s1 = (recNo - 1) * 8;
    beMessenger_AppendString(self->_messenger, *(int *)((char *)DAT_004cfb40 + temp_s1));
    beMessenger_AppendString(self->_messenger, *(int *)((char *)DAT_004cfb44 + temp_s1));
    beMessenger_AppendFloat(self->_messenger, 1.0f);
    sp30[0] = g_vec3Zero[0];
    sp30[1] = DAT_004e105c[0];
    sp30[2] = DAT_004e1060[0];
    beMessenger_AppendVec3(self->_messenger, sp30);
    beMessenger_AppendBool(self->_messenger, 0);
    beMessenger_AppendBool(self->_messenger, 1);
    beMessenger_EnqueueSelected(self->_messenger, &SETEFFECT_4[0], 1);
}

int Gap__Bec__beNDMWMdlItem__vfunc_35(int dummy0, int arg1) {
    return strcmp(arg1, &KIND_ITEM[0]) == 0;
}

void Gap__Bec__beNDMWMdlItem__vfunc_37(beNDMWMdlItem *p0, int a1)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, a1, DROPITEM_2);
}

/* After the shared igObject slot 23 body, caches the viewer scene-info manager registered with the
 * insight core (_viewerSIManager), found by its class metaObject; the same binding step as the
 * other managers' slot 23. */
void Gap__Bec__beNDMWMdlItem__vfunc_23(beNDMWMdlItem *self) {
    Gap__Core__igObject__vfunc_23();
    self->_viewerSIManager = igInsightCore_FindManager(self->_insight, g_igViewerSceneInfoManager_metaObject[0]);
}

void Gap__Bec__beNDMWMdlItem__vfunc_32(beNDMWMdlItem *arg0) {
    igDataList *l;
    int n;
    int i;
    igObject *r;
    int n2;
    int i2;
    l = (igDataList *)arg0->_lockRamList;
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

void Gap__Bec__beNDMWMdlItem__vfunc_36(beNDMWMdlItem *self, beBaseInfoRam *info) {
    ParentInfo *parent = (ParentInfo *)info->_parentInfo;
    void *alloc;
    Prop *prop;
    igObject *held;
    char *name;
    int i;
    int roll;

    if (info->_dataList == 0) {
        ALLOC_OF(info, alloc, g_defaultAllocatorSelector)
        Store::assign(info->_dataList, ObjectRef(beBaseInfoDataList_Create(alloc)).p);
    }
    prop = igProperty_FindByName((void *)info->_dataList, g_propertyNameField[0], &ONE_14[0]);
    ALLOC(alloc, g_defaultAllocatorSelector)
    {
    igSmartPointer<beNDMWMdlItemInfoWork> work((beNDMWMdlItemInfoWork *)FUN_003c13f0(alloc));
    held = (igObject *)work.p;
    if (held != 0) held->_refCount = held->_refCount + 1;
    REL(prop->f20)
    prop->f20 = held;
    if (beMessenger_GetIntCount(self->_messenger) != 0) {
        work.p->_recNo = beMessenger_GetInt(self->_messenger, 0);
        work.p->_dbId = beMessenger_GetInt(self->_messenger, 1);
    }
    i = 0;
    do {
        name = parent->_name;
        name = name != 0 ? name : emptyString;
        if (strcmp(name, DAT_004cfc10[i]) == 0) {
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
        ALLOC(alloc, g_ndmwAllocatorSelector)
        ItemRef h(beNDMWItemDisk_Create(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemDisk_Set(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 1: {
        ALLOC(alloc, g_ndmwAllocatorSelector)
        ItemRefB h(FUN_003c83c0(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemInstant_Set(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 2: {
        ALLOC(alloc, g_ndmwAllocatorSelector)
        ItemRefC h(FUN_003c8240(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemImportant_Set(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 6: {
        ALLOC(alloc, g_ndmwAllocatorSelector)
        ItemRefK<4> h(beNDMWItemAbilityChip_Create(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemAbilityChip_Set(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 3:
    case 4:
    case 5:
        beMessenger_PushArgContext(self->_messenger);
        beMessenger_SendGroup(self->_messenger, &GAMERAM_16[0], &GETPLAYER1_2[0]);
        roll = igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), &LEVEL_9[0])->f12;
        switch ((unsigned int)work.p->_dbId) {
        case 3: {
            ALLOC(alloc, g_ndmwAllocatorSelector)
            ItemRefK<1> h(beNDMWItemWeapon_Create(alloc));
            { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemWeapon_SetRandom(h.p, w->_recNo, self, roll); }
            storeItem(work, h);
            break;
        }
        case 4: {
            ALLOC(alloc, g_ndmwAllocatorSelector)
            ItemRefK<2> h(beNDMWItemBlueArmor_Create(alloc));
            { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemBlueArmor_SetRandom(h.p, w->_recNo, self, roll); }
            storeItem(work, h);
            break;
        }
        case 5: {
            ALLOC(alloc, g_ndmwAllocatorSelector)
            ItemRefK<3> h(beNDMWItemYellowArmor_Create(alloc));
            { beNDMWMdlItemInfoWork *w = work.p; beNDMWItemYellowArmor_SetRandom(h.p, w->_recNo, self, roll); }
            storeItem(work, h);
            break;
        }
        }
        beMessenger_PopArgContext(self->_messenger);
        break;
    }
    }
    beModelCtrl__OnGenerate(self, info);
}

/* matching construct: dummy-virtual views supply the retail vtable slot offsets: the item's use
 * (+96) and the visual context's viewport query (+744). */
class ItemSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int use(beNDMWMdlItem *ctrl, int ramNo); };
#define VC_SLOTS10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();
class VisualContextSlots { public: VC_SLOTS10(a) VC_SLOTS10(b) VC_SLOTS10(c) VC_SLOTS10(d) VC_SLOTS10(e) VC_SLOTS10(f) VC_SLOTS10(g) VC_SLOTS10(h) VC_SLOTS10(i) VC_SLOTS10(j) VC_SLOTS10(k) VC_SLOTS10(l) VC_SLOTS10(m) VC_SLOTS10(n) VC_SLOTS10(o) VC_SLOTS10(p) VC_SLOTS10(q) VC_SLOTS10(r) virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void getViewport(int *x, int *y, int *w, int *h); };

/* Squared distance between two points. */
static inline float DistanceSq(const float *a, const float *b) {
    return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2]) * (a[2] - b[2]);
}

/* Per frame: find the nearest player. A plain item (money, recovery) is used up by the first
 * player who comes near; a named item shows its name over itself in that player's font, locks
 * itself to the player, blinks the name colour and keeps the label on the item's screen position
 * until the player walks away (then the item is released through slot 45). */
void beNDMWMdlItem_Update(beNDMWMdlItem *self, beBaseInfoRam *ram) {
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
            a = ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
        }
        ObjectRef created(beBaseInfoDataList_Create(a));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        RefRelease::go((igObject *)ram->_dataList);
        ram->_dataList = (int)s0;
    }
    ramData = (beModelCtrlInfoRamData *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ONE_14);
    work = (beNDMWMdlItemInfoWork *)ramData->_work;
    if (((igObjectList *)self->_lockRamList)->_count == 0) {
        for (i = 0; i < 4; i++) {
            ObjectList_AppendRetained(self->_lockRamList, 0);
        }
    }
    isNear = 0;
    ramNo = 0;
    if (beTargetObj_SelectTarget((char *)ramData->_node + 32, PLAYER_9, NEAR_4) != 0) {
        float distSq = beTargetObj_GetTargetDistanceSq();
        ramNo = beTargetObj_GetTargetRamNo();
        isNear = distSq < 64.0f;
    }
    if (work->_isNamed == 0) {
        if (isNear) {
            ((ItemSlots *)work->_itemObject)->use(self, ramNo);
            {
                char *token;
                int *old;
                if (g_stringPool[0] == 0) {
                    void *pool = StringPool_Allocate(0x10);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                token = StringPool_Intern(g_stringPool[0], SQ_DDMG);
                old = (int *)work->_keyEventName;
                if (old != 0) {
                    int *header = old - 2;
                    int refs = old[-1] - 1;
                    old[-1] = refs;
                    if (refs == 0) StringChunk_ReleaseHeader(*header, header);
                }
                work->_keyEventName = (int)token;
            }
            switch (((beNDMWItemInstant *)work->_itemObject)->_recNo) {
            case 0:
                g_mdlEntity[0] = ram;
                g_mdlMatrix[0] = (char *)ramData->_node + 32;
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
            char *font = g_itemNameFontNames[ramNo];
            char *name;
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_10);
            beMessenger_AppendString(self->_messenger, ITNAMEFONT);
            beMessenger_AppendString(self->_messenger, font);
            beMessenger_AppendString(self->_messenger, CENTER_6);
            beMessenger_DispatchSelected(self->_messenger, ALIGN_6);
            name = beNDMWItemBase_GetRecordString(work->_itemObject, self, NAME_8);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_10);
            beMessenger_AppendString(self->_messenger, ITNAMEFONT);
            beMessenger_AppendString(self->_messenger, font);
            beMessenger_AppendString(self->_messenger, name);
            beMessenger_DispatchSelected(self->_messenger, TEXTSET_8);
            work->_isColorLight = 0;
            beBaseInfoRam_RemoveTimer(ram, COLOR_6);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_10);
            beMessenger_AppendString(self->_messenger, ITNAMEFONT);
            beMessenger_AppendString(self->_messenger, font);
            beMessenger_AppendString(self->_messenger, SET_6);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_10);
            work->_isDispName = 1;
            {
                char *token;
                int *old;
                if (g_stringPool[0] == 0) {
                    void *pool = StringPool_Allocate(0x10);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                token = StringPool_Intern(g_stringPool[0], font);
                old = (int *)work->_fontType;
                if (old != 0) {
                    int *header = old - 2;
                    int refs = old[-1] - 1;
                    old[-1] = refs;
                    if (refs == 0) StringChunk_ReleaseHeader(*header, header);
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
        if (beBaseInfoRam_IsTimerExpired(ram, COLOR_6) != 0) {
            beNDMWItemBase_GetRevisionColor(color, work->_itemObject);
            if (work->_isColorLight != 0) {
                work->_isColorLight = 0;
                color[0] /= 3.0f;
                color[1] /= 3.0f;
                color[2] /= 3.0f;
            } else {
                work->_isColorLight = 1;
            }
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_10);
            beMessenger_AppendString(self->_messenger, ITNAMEFONT);
            beMessenger_AppendString(self->_messenger, work->_fontType);
            rgb[0] = color[0];
            rgb[1] = color[1];
            rgb[2] = color[2];
            beMessenger_AppendVec3(self->_messenger, rgb);
            beMessenger_DispatchSelected(self->_messenger, COLOR_6);
            beBaseInfoRam_StartTimer(ram, COLOR_6, 500000000);
        }
        Matrix44_GetTranslation((char *)ramData->_node + 32, itemPos);
        beMessenger_SendNamed(self->_messenger, PLAYER_9, 0, work->_dispPlayerRamNo, GETMATRIX_10);
        if (beMessenger_GetMatrixCount(self->_messenger) != 0) {
            beMessenger_GetMatrix(playerMatrix, self->_messenger, 0);
            Matrix44_GetTranslation(playerMatrix, playerPos);
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
            Matrix44_Copy(view, params->_viewMatrix);
            params = (igViewerParameters *)((igViewerSceneInfoManager *)self->_viewerSIManager)->_parameters;
            Matrix44_Copy(projection, params->_projectionMatrix);
            Matrix44_GetTranslation((char *)ramData->_node + 32, pos);
            pos[1] += 10.0f;
            Vec3f_TransformProjective(eye, pos, view);
            Vec3f_TransformProjective(pos, eye, projection);
            ((VisualContextSlots *)((igInsightCore *)self->_insight)->_visualContext)->getViewport(&x, &y, &w, &h);
            screenX = x + ((1.0f + pos[0]) * w) / 2.0f;
            screenY = h - (y + ((1.0f + pos[1]) * h) / 2.0f);
            screenX -= w / 2;
            screenY = (h - screenY) - h / 2;
            screenX /= 100.0f;
            screenY /= 100.0f;
            screenX -= 0.7f;
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_10);
            beMessenger_AppendString(self->_messenger, ITNAMEFONT);
            beMessenger_AppendString(self->_messenger, work->_fontType);
            label[0] = screenX;
            label[1] = screenY;
            label[2] = -5.0f;
            beMessenger_AppendVec3(self->_messenger, label);
            beMessenger_DispatchSelected(self->_messenger, SETPOSITION);
        } else {
            ((MdlItemVt *)self)->exit(ram);
            ram->_st0 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
        }
        break;
    }
}

void Gap__Bec__beNDMWMdlItem__vfunc_43(beNDMWMdlItem *arg0, beBaseInfoRam *arg1) {
    PropertyEntry *s3;
    PropertyValueObj *q;
    int idx;
    igObjectList *s2;
    int cnt, off;
    if (arg1->_dataList == 0) {
        int alloc = ((int)igObject_GetAllocator(arg1));
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
        }
        ObjectRef created(beBaseInfoDataList_Create(a));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        RefRelease::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)s0;
    }
    s3 = ((PropertyEntry *)igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], ONE_14));
    q = s3->q;
    if (q->f256 != 0) {
        q->f256 = 0;
        s2 = (igObjectList *)arg0->_lockRamList;
        idx = q->f252;
        off = idx * 4;
        RefRelease::go(*(igObject **)((char *)s2->_data + off));
        cnt = s2->_count;
        if (cnt != 0 && idx >= 0 && idx < cnt) {
            *(igObject **)((char *)s2->_data + off) = 0;
        }
        q->f252 = -1;
        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_10);
        beMessenger_AppendString(arg0->_messenger, ITNAMEFONT);
        beMessenger_AppendString(arg0->_messenger, q->f260);
        beMessenger_AppendString(arg0->_messenger, CLR_6);
        beMessenger_DispatchSelected(arg0->_messenger, SWITCH_10);
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

void Gap__Bec__beNDMWMdlItem__vfunc_44(beNDMWMdlItem *self, beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        void *a = igObject_GetAllocator(ram);
        void *al = g_useOwnerAllocator != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igObject *created = (igObject *)((void *)beBaseInfoDataList_Create(al));
        adoptDataList(ram, created);
    }
    beModelCtrlInfoRamData *one = ((beModelCtrlInfoRamData *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], ((char *)ONE_14)));
    if (strcmp((const char *)((beModelCtrlInfoWork *)one->_work)->_seqCodeName, SQ_EXIT_2) == 0)
        ((MdlItemVt *)self)->exit(ram);
}

void Gap__Bec__beNDMWMdlItem__vfunc_45(MdlItemVirtual *arg0, beNDMWGameRamInfoRam *arg1) {
    beNDMWMdlItem *self = (beNDMWMdlItem *)arg0;
    igObject *s0;
    beNDMWMdlItemInfoWork *s5;
    int s2;
    bool s4;
    int s3;
    if (arg1->_dataList == 0) {
        int alloc = ((int)igObject_GetAllocator(arg1));
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
        }
        ObjectRef ref(beBaseInfoDataList_Create(a));
        s0 = ref.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        ReleaseRefInline::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)s0;
    }
    s5 = ((PropertyRecord *)igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], ONE_14))->q;
    if (beMessenger_GetBoolCount(self->_messenger) == 0 && s5->_isNamed != 0 && s5->_isDispName != 0) {
        s2 = beMessenger_GetInt(self->_messenger, 0);
        if (s2 == s5->_dispPlayerRamNo) {
            s4 = true;
            beMessenger_PushArgContext(self->_messenger);
            beMessenger_SelectGroup(self->_messenger, GAMERAM_16);
            beMessenger_AppendInt(self->_messenger, s2);
            beMessenger_DispatchSelected(self->_messenger, GETPLAYER_12);
            s3 = beMessenger_GetObject(self->_messenger, 0);
            unsigned t1 = s5->_kind - 3;
            switch (t1) {
            case 0:
            case 1:
            case 6:
                if (igProperty_GetRecordFolder(s3, DEVICEFOLDER_5)->f12->_count >= 36) {
                    s4 = false;
                }
                break;
            case 2:
            case 3:
            case 5: {
                igObjectList *l = igProperty_GetRecordFolder(s3, DISKFOLDER_6)->f12;
                if (((ItemRecord **)l->_data)[beNDMWItemBase_IndexOfRecNo(l, s5->_recNo)]->f20 >= 9) {
                    s4 = false;
                }
                break;
            }
            }
            if (s4) {
                igObjectList *a2 = igProperty_GetRecordFolder(s3, DEVICEFOLDER_5)->f12;
                unsigned t2 = s5->_kind - 3;
            switch (t2) {
                case 0:
                case 1:
                case 6:
                    ObjectList_AppendRetained(a2, s5->_itemObject);
                    break;
                case 2:
                case 3:
                case 5: {
                    igObjectList *l = igProperty_GetRecordFolder(s3, DISKFOLDER_6)->f12;
                    ItemRecord *it = ((ItemRecord **)l->_data)[beNDMWItemBase_IndexOfRecNo(l, s5->_recNo)];
                    int v = it->f20;
                    if (v != 9) {
                        it->f20 = v + 1;
                    }
                    break;
                }
                case 4: {
                    beMessenger_SendGroup(self->_messenger, GAMERAM_16, GETCOMMON_11);
                    int o = beMessenger_GetObject(self->_messenger, 0);
                    int idx = s5->_recNo;
                    igUnsignedCharList *ar = igProperty_GetRecordArray(o, FLAGFOLDER_3)->f12;
                    int n = ar->_count;
                    if (n != 0 && idx >= 0 && idx < n) {
                        *(unsigned char *)(idx + (int)ar->_data) = GPR_00554a74;
                    }
                    break;
                }
                }
                int f8 = arg1->_ramNo;
                beNDMWGameRamInfo *info = (beNDMWGameRamInfo *)arg1->_parentInfo;
                int *name = info->_name ? (int *)info->_name : ((int *)emptyString);
                beMessenger_SendNamed(self->_messenger, ((int *)DROPITEM_2), name, f8, SQ_DDMG);
                arg0->vX(arg1);
            }
            beMessenger_PopArgContext(self->_messenger);
            if (s4) {
                beMessenger_AppendBool(self->_messenger, 1);
            }
        }
    }
}

int Gap__Bec__beNDMWMdlItem__vfunc_20(void)
{
    return g_beNDMWMdlItem_metaObject[0];
}


#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define HOLDER_BODY { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
#define ALLOC_OF(owner, a, sel) { a = igObject_GetAllocator(owner); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(sel[0]); }
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
extern "C" int FUN_00236f80(int, int);
extern "C" int Gap__Core__igObject__vfunc_23(...);
extern "C" int Gap__Bec__beNDMWMdlItem__vfunc_20(void);
extern "C" int FUN_004482e0(...);
extern "C" int FUN_00448430(...);
extern "C" int FUN_00448580(...);
extern "C" int FUN_00448660(...);
extern "C" int FUN_00448710(...);
extern "C" int FUN_00448ad0(...);
extern "C" int FUN_00448f00(...);
extern "C" int FUN_00396740(...);
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
extern "C" int FUN_00448050(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int DAT_004cfb40[4];
extern "C" int DAT_004cfb44[4];
extern "C" float DAT_004e1058[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
extern "C" int DAT_0051ce80[4];
extern "C" int DAT_0051ce88[4];
struct A0 { char pad[20]; int f20; };
extern "C" void FUN_004412c0(struct A0 *arg0, int arg1, int arg2);
extern "C" int DAT_0051ce98[4];
extern "C" char DAT_0051cea8[];
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
extern "C" igObject *FUN_003c85b0(...);
extern "C" igObject *FUN_003c83c0(...);
extern "C" igObject *FUN_003c8240(...);
extern "C" igObject *FUN_003c87f0(...);
extern "C" igObject *FUN_003c8c90(...);
extern "C" igObject *FUN_003c8b00(...);
extern "C" igObject *FUN_003c8970(...);
extern "C" Prop * igProperty_FindByName(...);
extern "C" Rec *igProperty_GetRecord(...);
extern "C" char *DAT_004cfc10[10];
extern "C" char DAT_004e0858[];
extern "C" int DAT_0051cf58[4];
extern "C" int DAT_0051cf60[4];
extern "C" int DAT_0051cf68[4];
extern "C" int DAT_0051cf78[4];
extern "C" int DAT_00585be0[4];
extern "C" int DAT_00587108[4];
extern "C" int DAT_00587110[4];
extern "C" unsigned char GPR_00554c14;
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
extern "C" int DAT_0051cfd0[4];
extern "C" int DAT_0051cfd8[4];
extern "C" int DAT_0051d018[4];
extern "C" int DAT_0051d0a8[4];
/* matching construct: inline release helper reproduces the retail inlined refcount release */
struct RefRelease { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_43(beNDMWMdlItem *arg0, beBaseInfoRam *arg1);
extern "C" char DAT_0051d0b0[];
class MdlItemVt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void exit(beBaseInfoRam *ram); };
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_44(beNDMWMdlItem *self, beBaseInfoRam *ram);
struct ItemRecord { char p[20]; int f20; };
struct PropertyFolder { char p[12]; igObjectList *f12; };
struct PropertyByteArrayHolder { char p[12]; igUnsignedCharList *f12; };
struct PropertyRecord { char p[20]; beNDMWMdlItemInfoWork *q; };
extern "C" PropertyFolder *igProperty_GetRecordFolder(...);
extern "C" PropertyByteArrayHolder *igProperty_GetRecordArray(...);
extern "C" int DAT_0051cfc8[16];
extern "C" int DAT_0051d0b8[16];
extern "C" int DAT_0051d0c8[16];
extern "C" int DAT_0051d0d8[16];
extern "C" int DAT_0051d0e8[16];
extern "C" int DAT_0051d0f8[16];
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

void FUN_004412c0(struct A0 *arg0, int arg1, int arg2) {
    float sp30[4];
    int temp_s1;

    beMessenger_PrepareDelayedSelection(arg0->f20, &DAT_0051ce80[0], 0, arg2);
    temp_s1 = (arg1 - 1) * 8;
    beMessenger_AppendString(arg0->f20, *(int *)((char *)DAT_004cfb40 + temp_s1));
    beMessenger_AppendString(arg0->f20, *(int *)((char *)DAT_004cfb44 + temp_s1));
    beMessenger_AppendFloat(arg0->f20, 1.0f);
    sp30[0] = DAT_004e1058[0];
    sp30[1] = DAT_004e105c[0];
    sp30[2] = DAT_004e1060[0];
    beMessenger_AppendVec3(arg0->f20, sp30);
    beMessenger_AppendBool(arg0->f20, 0);
    beMessenger_AppendBool(arg0->f20, 1);
    beMessenger_EnqueueSelected(arg0->f20, &DAT_0051ce88[0], 1);
}

int Gap__Bec__beNDMWMdlItem__vfunc_35(int dummy0, int arg1) {
    return strcmp(arg1, &DAT_0051ce98[0]) == 0;
}

void Gap__Bec__beNDMWMdlItem__vfunc_37(beNDMWMdlItem *p0, int a1)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, a1, DAT_0051cea8);
}

/* After the shared igObject slot 23 body, caches the viewer scene-info manager registered with the
 * insight core (_viewerSIManager), found by its class metaObject; the same binding step as the
 * other managers' slot 23. */
void Gap__Bec__beNDMWMdlItem__vfunc_23(beNDMWMdlItem *self) {
    Gap__Core__igObject__vfunc_23();
    self->_viewerSIManager = FUN_00236f80(self->_insight, g_igViewerSceneInfoManager_metaObject[0]);
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
        ALLOC_OF(info, alloc, DAT_00587110)
        Store::assign(info->_dataList, ObjectRef(beBaseInfoDataList_Create(alloc)).p);
    }
    prop = igProperty_FindByName((void *)info->_dataList, DAT_00585be0[0], &DAT_0051cf58[0]);
    ALLOC(alloc, DAT_00587110)
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
        name = name != 0 ? name : DAT_004e0858;
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
        ALLOC(alloc, DAT_00587108)
        ItemRef h(FUN_003c85b0(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; FUN_00448710(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 1: {
        ALLOC(alloc, DAT_00587108)
        ItemRefB h(FUN_003c83c0(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; FUN_00448ad0(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 2: {
        ALLOC(alloc, DAT_00587108)
        ItemRefC h(FUN_003c8240(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; FUN_00448f00(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 6: {
        ALLOC(alloc, DAT_00587108)
        ItemRefK<4> h(FUN_003c87f0(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; FUN_00448660(h.p, w->_recNo); }
        storeItem(work, h);
        break;
    }
    case 3:
    case 4:
    case 5:
        beMessenger_PushArgContext(self->_messenger);
        beMessenger_SendGroup(self->_messenger, &DAT_0051cf60[0], &DAT_0051cf68[0]);
        roll = igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), &DAT_0051cf78[0])->f12;
        switch ((unsigned int)work.p->_dbId) {
        case 3: {
            ALLOC(alloc, DAT_00587108)
            ItemRefK<1> h(FUN_003c8c90(alloc));
            { beNDMWMdlItemInfoWork *w = work.p; FUN_004482e0(h.p, w->_recNo, self, roll); }
            storeItem(work, h);
            break;
        }
        case 4: {
            ALLOC(alloc, DAT_00587108)
            ItemRefK<2> h(FUN_003c8b00(alloc));
            { beNDMWMdlItemInfoWork *w = work.p; FUN_00448430(h.p, w->_recNo, self, roll); }
            storeItem(work, h);
            break;
        }
        case 5: {
            ALLOC(alloc, DAT_00587108)
            ItemRefK<3> h(FUN_003c8970(alloc));
            { beNDMWMdlItemInfoWork *w = work.p; FUN_00448580(h.p, w->_recNo, self, roll); }
            storeItem(work, h);
            break;
        }
        }
        beMessenger_PopArgContext(self->_messenger);
        break;
    }
    }
    FUN_00396740(self, info);
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
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = ((int)Memory_GetAllocatorBySelector(DAT_00587110[0]));
        }
        ObjectRef created(beBaseInfoDataList_Create(a));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        RefRelease::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)s0;
    }
    s3 = ((PropertyEntry *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_0051cf58));
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
        beMessenger_SelectGroup(arg0->_messenger, DAT_0051cfd0);
        beMessenger_AppendString(arg0->_messenger, DAT_0051cfd8);
        beMessenger_AppendString(arg0->_messenger, q->f260);
        beMessenger_AppendString(arg0->_messenger, DAT_0051d0a8);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051d018);
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
        void *al = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igObject *created = (igObject *)((void *)beBaseInfoDataList_Create(al));
        adoptDataList(ram, created);
    }
    beModelCtrlInfoRamData *one = ((beModelCtrlInfoRamData *)igProperty_FindByName(ram->_dataList, DAT_00585be0[0], ((char *)DAT_0051cf58)));
    if (strcmp((const char *)((beModelCtrlInfoWork *)one->_work)->_seqCodeName, DAT_0051d0b0) == 0)
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
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = ((int)Memory_GetAllocatorBySelector(DAT_00587110[0]));
        }
        ObjectRef ref(beBaseInfoDataList_Create(a));
        s0 = ref.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        ReleaseRefInline::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)s0;
    }
    s5 = ((PropertyRecord *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_0051cf58))->q;
    if (beMessenger_GetBoolCount(self->_messenger) == 0 && s5->_isNamed != 0 && s5->_isDispName != 0) {
        s2 = beMessenger_GetInt(self->_messenger, 0);
        if (s2 == s5->_dispPlayerRamNo) {
            s4 = true;
            beMessenger_PushArgContext(self->_messenger);
            beMessenger_SelectGroup(self->_messenger, DAT_0051cf60);
            beMessenger_AppendInt(self->_messenger, s2);
            beMessenger_DispatchSelected(self->_messenger, DAT_0051d0b8);
            s3 = beMessenger_GetObject(self->_messenger, 0);
            unsigned t1 = s5->_kind - 3;
            switch (t1) {
            case 0:
            case 1:
            case 6:
                if (igProperty_GetRecordFolder(s3, DAT_0051d0c8)->f12->_count >= 36) {
                    s4 = false;
                }
                break;
            case 2:
            case 3:
            case 5: {
                igObjectList *l = igProperty_GetRecordFolder(s3, DAT_0051d0d8)->f12;
                if (((ItemRecord **)l->_data)[FUN_00448050(l, s5->_recNo)]->f20 >= 9) {
                    s4 = false;
                }
                break;
            }
            }
            if (s4) {
                igObjectList *a2 = igProperty_GetRecordFolder(s3, DAT_0051d0c8)->f12;
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
                    igObjectList *l = igProperty_GetRecordFolder(s3, DAT_0051d0d8)->f12;
                    ItemRecord *it = ((ItemRecord **)l->_data)[FUN_00448050(l, s5->_recNo)];
                    int v = it->f20;
                    if (v != 9) {
                        it->f20 = v + 1;
                    }
                    break;
                }
                case 4: {
                    beMessenger_SendGroup(self->_messenger, DAT_0051cf60, DAT_0051d0e8);
                    int o = beMessenger_GetObject(self->_messenger, 0);
                    int idx = s5->_recNo;
                    igUnsignedCharList *ar = igProperty_GetRecordArray(o, DAT_0051d0f8)->f12;
                    int n = ar->_count;
                    if (n != 0 && idx >= 0 && idx < n) {
                        *(unsigned char *)(idx + (int)ar->_data) = GPR_00554a74;
                    }
                    break;
                }
                }
                int f8 = arg1->_ramNo;
                beNDMWGameRamInfo *info = (beNDMWGameRamInfo *)arg1->_parentInfo;
                int *name = info->_name ? (int *)info->_name : ((int *)DAT_004e0858);
                beMessenger_SendNamed(self->_messenger, ((int *)DAT_0051cea8), name, f8, DAT_0051cfc8);
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


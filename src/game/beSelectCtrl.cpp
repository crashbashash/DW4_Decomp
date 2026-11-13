#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define REL(o) { igObject *rr = (igObject *)(o); if (rr != 0) { rr->_refCount = (int)rr->_refCount - 1; if ((rr->_refCount & 0x7FFFFF) == 0) igObject_Destroy(rr); } }

extern "C" int FUN_00236f80(int insight, int metaObject);
extern "C" int Gap__Bec__beSelectCtrl__vfunc_30(void);
extern "C" int Gap__Bec__beSelectCtrl__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, const char *);
extern "C" int sprintf(...);
extern "C" int FUN_002eb010(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" int *StringPool_Intern(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_AppendVec3(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int *bePadManager_GetPadForPlayer(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int igBoolList_Create(int);
extern "C" int FUN_00345680(int);
extern "C" int FUN_003459a0(...);
extern "C" int beMessenger_AppendBool(int, int);
extern "C" int beMessenger_AppendInt(int, int);
extern "C" int beMessenger_GetBoolCount(int);
extern "C" int beMessenger_GetInt(int, int);
extern "C" int beMessenger_GetIntCount(int);
extern "C" int beMessenger_GetString(int, int);
extern "C" int beMessenger_GetStringCount(int);
extern "C" int beMessenger_GetVec3(float *, int, int);
extern "C" int beMessenger_GetVec3Count(int);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, int);
extern "C" int strcmp(int, int *);
extern "C" int g_beSelectCtrlInfo_metaObject[4];
extern "C" int g_beSelectCtrl_metaObject[4];
extern "C" int D_00588518[];
extern "C" void beSelectCtrl_EnsurePadManager(beSelectCtrl *self);
extern "C" char D_0050f7f0[];
extern "C" void beSelectCtrl_RegisterReceiver(beSelectCtrl *self, int info);
extern "C" char DAT_0050f8b0[];
extern "C" igObject * beBaseInfoDataList_Create(...);
extern "C" beSelectCtrlInfoRamData * igProperty_FindByName(...);
extern "C" int emptyString[4];
extern "C" int DAT_0050f800[4];
extern "C" int DAT_0050f808[4];
extern "C" int DAT_0050f818[4];
extern "C" int DAT_0050f820[4];
extern "C" int DAT_0050f830[4];
extern "C" int DAT_0050f840[4];
extern "C" int DAT_0050f850[4];
extern "C" int DAT_0050f860[4];
extern "C" int DAT_0050f870[4];
extern "C" int DAT_0050f878[4];
extern "C" int DAT_0050f888[4];
extern "C" int DAT_0050f890[4];
extern "C" int DAT_0050f8a0[4];
extern "C" int DAT_0050f8c0[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_stringPool[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
typedef struct DecideList { char pad[16]; unsigned char *data; } DecideList;
extern "C" void Gap__Bec__beSelectCtrl__vfunc_31(beSelectCtrl *self, beBaseInfoRam *ram);
extern "C" int List_Resize(igBoolList *, int, int);
extern "C" float g_vec3Zero[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
extern "C" int DAT_0050f8d0[4];
/* Owning stack reference to the freshly created property data list, released at the end of the
 * full expression that stores it (reference count in the low 23 bits of _refCount). */

/* Owning stack reference to the select work created on start, released on scope exit. */
class WorkRef {
public:
    beSelectCtrlInfoWork *p;
    WorkRef(beSelectCtrlInfoWork *o) : p(o) {}
    ~WorkRef() { beSelectCtrlInfoWork *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to a new decide list while it is filled, released on scope exit. */
class BoolListRef {
public:
    igObject *p;
    BoolListRef(igObject *o) : p(o) {}
    ~BoolListRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Store a freshly created data list in the ram, taking the ram's share and dropping the previous list;
 * the caller passes the list as a temporary holder that gives up the creating share at the end of the
 * full expression (matching construct: a temporary takes its frame slot after the named locals). */
struct DataList { static inline void store(beBaseInfoRam *ram, const igSmartPointer<igObject> &list) {
    igObject *created = list.p;
    if (created != 0) created->_refCount = (int)created->_refCount + 1;
    REL(ram->_dataList)
    ram->_dataList = (int)created;
}
static inline void create(beBaseInfoRam *ram, int a) { igSmartPointer<igObject> list((igObject *)((int)beBaseInfoDataList_Create(a))); store(ram, list); }
};
extern "C" int Gap__Bec__beSelectCtrl__vfunc_33(beSelectCtrl *arg0, beBaseInfoRam *arg1, int arg2);

void beSelectCtrl_EnsurePadManager(beSelectCtrl *self)
{
    if (self->_padManager == 0) {
        self->_padManager = FUN_00236f80(self->_insight, D_00588518[0]);
    }
}

int Gap__Bec__beSelectCtrl__vfunc_30(void)
{
    return g_beSelectCtrlInfo_metaObject[0];
}

void beSelectCtrl_RegisterReceiver(beSelectCtrl *self, int info)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, D_0050f7f0);
}

#define NAME (info->_name ? info->_name : (int)&emptyString[0])
/* Bool flags use daddiu, ram->_ramNo and ram->_svSeqName are hoisted into locals before the NAME
 * ternary, switch(st3) has case 0 and default, info is declared first, the on-demand data list is held by an igSmartPointer<igObject>, and the decide-list
 * byte test uses an unsigned index. */

static inline int st2Of(const beBaseInfoRam *r) { return r->_st2; }

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

void Gap__Bec__beSelectCtrl__vfunc_31(beSelectCtrl *self, beBaseInfoRam *ram) {
    beBaseInfo *info;
    float vec[3];
    char buf1[16];
    char buf2[16];
    char buf3[16];
    char buf4[16];
    int hold;
    beSelectCtrlInfoRamData *rd;
    int trig;
    int *old;
    int state;
    bool moved;
    beSelectCtrlInfoWork *wk;
    int *pad;
    bool up;
    int allocator;
    bool down;
    int v;
    int cur;
    int cnt;
    unsigned input;
    int *hd;
    bool left;
    bool right;
    int *s;

    if (ram->_isRun == 0) return;
    info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        igObject *s3;
        igObject *o;
        allocator = igObject_GetAllocator(ram);
        allocator = GPR_00554c14 != 0 ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<igObject> ref(beBaseInfoDataList_Create(allocator));
        s3 = ref.p;
        if (s3 != 0) s3->_refCount = s3->_refCount + 1;
        o = (igObject *)ram->_dataList;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
        ram->_dataList = (int)s3;
    }
    rd = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], &DAT_0050f800[0]);
    wk = (beSelectCtrlInfoWork *)rd->_work;
    pad = bePadManager_GetPadForPlayer(self->_padManager, ram->_ramNo);
    state = ram->_st0;
    input = pad[18];
    trig = pad[9];
    hold = pad[17] & 0xF0;
    switch (state) {
    case 0:
        switch (ram->_st1) {
        case 0:
            { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
            vec[0] = *(float *)&wk->_offsetPos[0];
            vec[1] = *(float *)&wk->_offsetPos[1];
            vec[2] = *(float *)&wk->_offsetPos[2];
            beMessenger_AppendVec3(self->_messenger, vec);
            beMessenger_AppendString(self->_messenger, &DAT_0050f818[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0050f820[0]);
            ram->_st1 = ram->_st1 + 1;
            ram->_st3 = 0;
            ram->_st2 = 0;
            return;
        case 1:
            { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
            beMessenger_AppendString(self->_messenger, &DAT_0050f818[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0050f830[0]);
            if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                sprintf(buf1, &DAT_0050f840[0], rd->_selectNo);
                { int rn = ram->_ramNo; beMessenger_SendNamed(self->_messenger, &DAT_0050f808[0], NAME, rn, buf1); }
                ram->_st0 = ram->_st0 + 1;
                ram->_st3 = 0;
                ram->_st2 = 0;
                ram->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 1:
        switch (ram->_st1) {
        case 0:
            if (trig != 0 || hold != 0) {
                switch (ram->_st3) {
                case 0:
                    cur = rd->_selectNo;
                    moved = false;
                    up = true;
                    if (!(trig & 8) && !(hold & 0x80)) up = false;
                    down = true;
                    if (!(trig & 2) && !(hold & 0x20)) down = false;
                    left = true;
                    if (!(trig & 1) && !(hold & 0x10)) left = false;
                    right = true;
                    if (!(trig & 4) && !(hold & 0x40)) right = false;
                    v = rd->_isTateSelect;
                    if ((v != 0 && left) || (v == 0 && up)) {
                        if (cur != 0) {
                            cur = cur - 1;
                            moved = true;
                            sprintf(buf2, &DAT_0050f850[0], cur);
                            if (g_stringPool[0] == 0) {
                                v = FUN_002eb010(0x10);
                                if (v != 0) v = StringPool_Construct(v);
                                g_stringPool[0] = v;
                            }
                            s = StringPool_Intern(g_stringPool[0], buf2);
                            old = (int *)wk->_svSeqName;
                            if (old != 0) {
                                hd = old - 2;
                                v = old[-1] - 1;
                                old[-1] = v;
                                if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
                            }
                            wk->_svSeqName = (int)s;
                        }
                    } else if (((v != 0 && right) || (v == 0 && down)) && cur != wk->_selectMax - 1) {
                        cur = cur + 1;
                        moved = true;
                        sprintf(buf3, &DAT_0050f860[0], cur);
                        if (g_stringPool[0] == 0) {
                            v = FUN_002eb010(0x10);
                            if (v != 0) v = StringPool_Construct(v);
                            g_stringPool[0] = v;
                        }
                        s = StringPool_Intern(g_stringPool[0], buf3);
                        old = (int *)wk->_svSeqName;
                        if (old != 0) {
                            hd = old - 2;
                            v = old[-1] - 1;
                            old[-1] = v;
                            if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
                        }
                        wk->_svSeqName = (int)s;
                    }
                    if (moved) {
                        rd->_selectNo = cur;
                        { int sq = wk->_svSeqName; int rn = ram->_ramNo; beMessenger_SendNamed(self->_messenger, &DAT_0050f808[0], NAME, rn, sq); }
                        ram->_st3 = ram->_st3 + 1;
                    }
                    break;
                default:
                    { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
                    beMessenger_AppendString(self->_messenger, wk->_svSeqName);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0050f830[0]);
                    if (beMessenger_GetBool(self->_messenger, 0) == 0) ram->_st3 = 0;
                }
            }
            if (input & 0x2000) {
                if (wk->_isCancel != 0) {
                    rd->_selectNo = -1;
                    ram->_st0 = ram->_st0 + 1;
                    ram->_st3 = 0;
                    ram->_st2 = 0;
                    ram->_st1 = 0;
                    return;
                }
                beMessenger_SelectGroup(self->_messenger, &DAT_0050f870[0]);
                beMessenger_AppendString(self->_messenger, &DAT_0050f878[0]);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0050f888[0]);
                ram->_st1 = 2;
                ram->_st3 = 0;
                ram->_st2 = 0;
                return;
            }
            if (input & 0x4000) {
                DecideList *dl = (DecideList *)wk->_decideList;
                if (dl != 0 && ((unsigned char *)dl->data)[(unsigned)rd->_selectNo] == 0) {
                    beMessenger_SelectGroup(self->_messenger, &DAT_0050f870[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0050f878[0]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0050f888[0]);
                    ram->_st1 = 2;
                    ram->_st3 = 0;
                    ram->_st2 = 0;
                    return;
                }
                sprintf(buf4, &DAT_0050f890[0], rd->_selectNo);
                if (g_stringPool[0] == 0) {
                    v = FUN_002eb010(0x10);
                    if (v != 0) v = StringPool_Construct(v);
                    g_stringPool[0] = v;
                }
                s = StringPool_Intern(g_stringPool[0], buf4);
                old = (int *)wk->_svSeqName;
                if (old != 0) {
                    hd = old - 2;
                    v = old[-1] - 1;
                    old[-1] = v;
                    if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
                }
                wk->_svSeqName = (int)s;
                { int sq = wk->_svSeqName; int rn = ram->_ramNo; beMessenger_SendNamed(self->_messenger, &DAT_0050f808[0], NAME, rn, sq); }
                ram->_st1 = ram->_st1 + 1;
                ram->_st3 = 0;
                ram->_st2 = 0;
                return;
            }
            break;
        case 1:
            { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
            beMessenger_AppendString(self->_messenger, wk->_svSeqName);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0050f830[0]);
            if (beMessenger_GetBool(self->_messenger, 0) == 0) {
                ram->_st0 = ram->_st0 + 1;
                ram->_st3 = 0;
                ram->_st2 = 0;
                ram->_st1 = 0;
                return;
            }
            break;
        case 2:
            if (st2Of(ram) < 0x10) {
                ram->_st2 = ram->_st2 + 1;
                ram->_st3 = 0;
                return;
            }
            ram->_st1 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            return;
        }
        break;
    case 2:
        switch (ram->_st1) {
        case 0:
            if (rd->_selectNo != -1) s = (int *)&DAT_0050f8a0[0];
            else s = (int *)DAT_0050f8b0;
            if (g_stringPool[0] == 0) {
                v = FUN_002eb010(0x10);
                if (v != 0) v = StringPool_Construct(v);
                g_stringPool[0] = v;
            }
            hd = StringPool_Intern(g_stringPool[0], s);
            old = (int *)wk->_svSeqName;
            if (old != 0) {
                int *h2 = old - 2;
                v = old[-1] - 1;
                old[-1] = v;
                if (v == 0) StringChunk_ReleaseHeader(*h2, h2);
            }
            wk->_svSeqName = (int)hd;
            { int sq = wk->_svSeqName; int rn = ram->_ramNo; beMessenger_SendNamed(self->_messenger, &DAT_0050f808[0], NAME, rn, sq); }
            ram->_st1 = ram->_st1 + 1;
            ram->_st3 = 0;
            ram->_st2 = 0;
            return;
        case 1:
            { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
            beMessenger_AppendString(self->_messenger, wk->_svSeqName);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0050f830[0]);
            if (beMessenger_GetBool(self->_messenger, 0) == 0) {
                ram->_st0 = ram->_st0 + 1;
                ram->_st3 = 0;
                ram->_st2 = 0;
                ram->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 10:
        switch (ram->_st1) {
        case 0:
            { int rn = ram->_ramNo; beMessenger_SendNamed(self->_messenger, &DAT_0050f808[0], NAME, rn, &DAT_0050f8c0[0]); }
            ram->_st1 = ram->_st1 + 1;
            ram->_st3 = 0;
            ram->_st2 = 0;
            return;
        case 1:
            { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
            beMessenger_AppendString(self->_messenger, &DAT_0050f8c0[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0050f830[0]);
            if (beMessenger_GetBool(self->_messenger, 0) == 0) {
                ram->_st0 = 1;
                ram->_st3 = 0;
                ram->_st2 = 0;
                ram->_st1 = 0;
                return;
            }
            break;
        }
        break;
    default:
        ram->_isRun = 0;
        {
            igObject *o = (igObject *)rd->_work;
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
            }
        }
        rd->_work = 0;
        break;
    }
}

#undef NAME

int Gap__Bec__beSelectCtrl__vfunc_33(beSelectCtrl *arg0, beBaseInfoRam *arg1, int arg2) {
    float sp80[3];
    int n;
    int i;
    int a;
    beSelectCtrlInfoRamData *s3;
    beSelectCtrlInfoWork *s2;
    int i2;
    int v;
    beSelectCtrlInfoWork *u;
    int v2;
    int b2;
    igBoolList *l2;
    int b;
    igObject *t;
    igBoolList *l;
    if (arg1->_dataList == 0) {
        a = igObject_GetAllocator(arg1);
        a = (GPR_00554c14 != 0) ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        DataList::create(arg1, a);
    }
    s3 = (beSelectCtrlInfoRamData *)((int)igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], DAT_0050f800));
    s2 = (beSelectCtrlInfoWork *)s3->_work;
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003459a0(), arg2)) {
    case 0:
        arg1->_isRun = 1;
        arg1->_st0 = 0;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
        a = igObject_GetAllocator(arg0);
        a = (GPR_00554c14 != 0) ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        {
            WorkRef work((beSelectCtrlInfoWork *)FUN_00345680(a));
            t = (igObject *)work.p;
            if (t != 0) t->_refCount = (int)t->_refCount + 1;
            REL(s3->_work)
            s3->_work = (int)t;
            u = work.p;
        }
        s3->_selectNo = 0;
        if (beMessenger_GetIntCount(arg0->_messenger) != 0) {
            u->_selectMax = beMessenger_GetInt(arg0->_messenger, 0);
            if (beMessenger_GetIntCount(arg0->_messenger) == 2) {
                s3->_selectNo = beMessenger_GetInt(arg0->_messenger, 1);
            }
        } else {
            u->_selectMax = s3->_maxSelect;
        }
        if (beMessenger_GetVec3Count(arg0->_messenger) != 0) {
            beMessenger_GetVec3(sp80, arg0->_messenger, 0);
            ((float *)u->_offsetPos)[0] = sp80[0];
            ((float *)u->_offsetPos)[1] = sp80[1];
            ((float *)u->_offsetPos)[2] = sp80[2];
        } else {
            ((float *)u->_offsetPos)[0] = g_vec3Zero[0];
            ((float *)u->_offsetPos)[1] = DAT_004e105c[0];
            ((float *)u->_offsetPos)[2] = DAT_004e1060[0];
        }
        if (beMessenger_GetStringCount(arg0->_messenger) != 0) {
            if (strcmp(beMessenger_GetString(arg0->_messenger, 0), DAT_0050f8d0) == 0) {
                u->_isCancel = 0;
            }
        }
        n = beMessenger_GetBoolCount(arg0->_messenger);
        if (n != 0 && n == u->_selectMax) {
            a = igObject_GetAllocator(arg0);
            a = (GPR_00554c14 != 0) ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            BoolListRef decide((igObject *)igBoolList_Create(a));
            t = decide.p;
            if (t != 0) t->_refCount = (int)t->_refCount + 1;
            REL(u->_decideList)
            u->_decideList = (int)t;
            i = 0;
            if (0 < n) {
                do {
                    v = beMessenger_GetBool(arg0->_messenger, i) & 0xFF;
                    l = (igBoolList *)decide.p;
                    b = l->_count;
                    if (b < l->_capacity) {
                        l->_count = b + 1;
                    } else {
                        List_Resize(l, b + 1, 1);
                    }
                    i += 1;
                    ((unsigned char *)l->_data)[b] = v;
                } while (i < n);
            }
        }
        return 1;
    case 3:
        if (arg1->_isRun != 0) {
            if (arg1->_st0 == 2 || arg1->_st0 == 3) {
                beMessenger_AppendBool(arg0->_messenger, 0);
            } else {
                beMessenger_AppendBool(arg0->_messenger, 1);
            }
        } else {
            beMessenger_AppendBool(arg0->_messenger, 0);
        }
        return 1;
    case 1:
        if (arg1->_isRun != 0) {
            beMessenger_AppendBool(arg0->_messenger, 0);
        } else {
            beMessenger_AppendBool(arg0->_messenger, 1);
        }
        return 1;
    case 2:
        beMessenger_AppendInt(arg0->_messenger, s3->_selectNo);
        return 1;
    case 5:
        if (arg1->_st0 == 1 && arg1->_st1 == 0) {
            beMessenger_AppendBool(arg0->_messenger, 0);
        } else {
            beMessenger_AppendBool(arg0->_messenger, 1);
        }
        return 1;
    case 4:
        if (arg1->_st0 == 1 && arg1->_st1 == 0) {
            s3->_selectNo = 0;
            if (beMessenger_GetIntCount(arg0->_messenger) > 0) {
                s2->_selectMax = beMessenger_GetInt(arg0->_messenger, 0);
                n = beMessenger_GetBoolCount(arg0->_messenger);
                if (n != 0 && n == s2->_selectMax) {
                    a = igObject_GetAllocator(arg0);
                    a = (GPR_00554c14 != 0) ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    BoolListRef decide((igObject *)igBoolList_Create(a));
                    t = decide.p;
                    if (t != 0) t->_refCount = (int)t->_refCount + 1;
                    REL(s2->_decideList)
                    s2->_decideList = (int)t;
                    i2 = 0;
                    if (0 < n) {
                        do {
                            v2 = beMessenger_GetBool(arg0->_messenger, i2) & 0xFF;
                            l2 = (igBoolList *)decide.p;
                            b2 = l2->_count;
                            if (b2 < l2->_capacity) {
                                l2->_count = b2 + 1;
                            } else {
                                List_Resize(l2, b2 + 1, 1);
                            }
                            i2 += 1;
                            ((unsigned char *)l2->_data)[b2] = v2;
                        } while (i2 < n);
                    }
                }
            }
            arg1->_st0 = 0xA;
            arg1->_st3 = 0;
            arg1->_st2 = 0;
            arg1->_st1 = 0;
            beMessenger_AppendBool(arg0->_messenger, 1);
        } else {
            beMessenger_AppendBool(arg0->_messenger, 0);
        }
        return 1;
    case 6:
        s3->_selectNo = -1;
        arg1->_st0 = 2;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
    default:
        return 0;
    }
}

int Gap__Bec__beSelectCtrl__vfunc_20(void)
{
    return g_beSelectCtrl_metaObject[0];
}

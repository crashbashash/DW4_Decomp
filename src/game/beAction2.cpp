#include "dw4/reflected.h"
#include "dw4/igobject_release.h"
#define REL(o) { Rc *rr = (o); if (rr != 0) { rr->references = rr->references - 1; if (((unsigned long long)((long long)rr->references << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define LDATA(l) ((int *)(l)->_data)
#define BITCLR(n) { unsigned int w = (n) >> 5; int bit = 1 << ((n) & 0x1F); int *pw = LDATA(sw) + w; int cnt = sw->_count; int cur = *pw; int nv = ~bit & cur; if (cnt != 0 && (int)w >= 0 && (int)w < cnt) { *pw = nv; } }
#define BITSET(n) { unsigned int w = (n) >> 5; int bit = 1 << ((n) & 0x1F); int *pw = LDATA(sw) + w; int cnt = sw->_count; int cur = *pw; int nv = bit | cur; if (cnt != 0 && (int)w >= 0 && (int)w < cnt) { *pw = nv; } }

extern "C" void Gap__Bec__beAction2__vfunc_32(void);
extern "C" int Gap__Bec__beAction2__vfunc_30(void);
extern "C" int Gap__Bec__beAction2__vfunc_20(void);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, char *, int *);
extern "C" int FUN_003a7e90(...);
extern "C" int FUN_003a8580(...);
extern "C" int ObjectList_RemoveFirstRetained(...);
extern "C" int igObject_Destroy(...);
extern "C" int FUN_00193540(...);
extern "C" void *FUN_00131390(...);
extern "C" void *FUN_00135e20(...);
extern "C" void *FUN_00138ee0(...);
extern "C" int FUN_003a7a20(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int igObject_GetAllocator(...);
extern "C" long long FUN_00398e80(int, long long);
extern "C" int FUN_001dd4b0(long long, long long, long long *);
extern "C" void FUN_001af510(void *, long long);
extern "C" long long __fixsfdi(float);
extern "C" float FUN_003a8140(...);
extern "C" void *FUN_00139600(...);
extern "C" int FUN_001ac140(...);
extern "C" void * igProperty_FindByName(...);
extern "C" int FUN_001ae660(void *, void *, int, int, int, int *, int, long long, float, float, int);
extern "C" int FUN_001ae780(...);
extern "C" int igObject_IsKindOf(...);
extern "C" void beAction2_StartComponents(int manager, void *info);
extern "C" int FUN_0036dcd0(...);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, void *);
extern "C" void beMessenger_AppendBool(int, unsigned char);
extern "C" int beMessenger_AppendObject(int, int);
extern "C" int beMessenger_AppendMatrix(int, int);
extern "C" int beMessenger_AppendString(int, void *);
extern "C" int beMessenger_GetString(int, int);
extern "C" int FUN_003a84a0(void *, float);
extern "C" int strcmp(void *, void *);
extern "C" int List_Reserve(void *, int, int);
extern "C" int FUN_003a8760(void *);
extern "C" int FUN_001adf70(int);
extern "C" void *igMetaObject_FindFieldByName(int, void *);
extern "C" void Memory_FreeBuffer(int);
extern "C" void *FUN_0036c2a0(void *);
extern "C" int FUN_00239070(void *, void *);
extern "C" int FUN_001ae750(void *, int, int, int, int);
extern "C" int beMessenger_SendNamed(int, void *, void *, int, void *);
extern "C" void Gap__Core__igObject__vfunc_28(void);
extern "C" int Gap__Core__igObject__vfunc_34(void);
extern "C" int g_beAction2Info_metaObject[4];
extern "C" int g_beAction2_metaObject[4];
extern "C" int DAT_0050dfc8[4];
extern "C" int DAT_005626e0[4];
extern "C" void Gap__Bec__beAction2__vfunc_29(beAction2 *arg0, char *arg1);
/* The info's _node target: only its list handle at +136 is read. */

typedef struct Action2NodeList136 { char pad[136]; int list; } Action2NodeList136;
extern "C" int DAT_0050dfd0[4];
extern "C" void beAction2FLASHSET_Update(void *arg0, beAction2InfoRam *arg1);
/* matching construct: dummy-virtual class so ->vX() dispatches through the attribute object's vtable slot */
struct AttrObjView { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(void *); char pad[24]; int f28; };
extern "C" int DAT_00587110[4];
extern "C" unsigned char GPR_00554c14;
extern "C" int beAction2FLASHSET_Start(int arg0, beAction2InfoRam *arg1, beAction2FLASHSET *arg2);
extern "C" int DAT_0050dfd8[4];
struct WcClock { char p[80]; long long time; };
extern "C" void beAction2WAITCHECK_Update(beAction2 *arg0, beAction2InfoRam *arg1);
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class RandomSourceVirtual {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual unsigned Query();
};
extern "C" float DAT_0058a348[4];
extern "C" int beAction2WAITCHECK_Start(beAction2 *mgr, beAction2InfoRam *act, beAction2WAITCHECK *comp);
struct RefCountedObject { int vt; int rc; };
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 128 */
struct DummyVirtualComponent { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(void *); char pad[24]; int f28; };
struct FadeColor { int x, y, z; float w; };
extern "C" int DAT_0050dfe0[4];
extern "C" void beAction2FADESET_Update(void *arg0, beAction2InfoRam *arg1);
struct Action2SwitchBits { char pad32[32]; igUnsignedIntList *f32; };
extern "C" int DAT_004e0858[4];
/* Owning stack reference to the freshly created attribute (colour 0, blend state 1, lighting state
 * 2, texture state 3); one class per kind so each gets its own out-of-line destructor. */
template <int kind> struct Ref {
    igObject *p;
    Ref(igObject *o) : p(o) {}
    ~Ref() {
        igObject *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
extern "C" int beAction2FADESET_Start(int arg0, beAction2InfoRam *arg1, beAction2FADESET *arg2);
typedef struct Clock { char p[80]; long long time; } Clock;
typedef struct Node { char p[120]; float scale; char q[4]; long long bias; } Node;
typedef struct Work { char p[28]; int state; long long start; long long end; char isEnd; } Work;
typedef struct Owner { char p[12]; Clock *clock; } Owner;
typedef struct Act { char p[44]; Node *node; char q[8]; Work *work; } Act;
extern "C" void beAction2JOINTSET_Update(Owner *arg0, Act *arg1);
extern "C" int beAction2JOINTSET_Start(Owner *arg0, beAction2InfoRam *arg1, beAction2JOINTSET *arg2);
typedef struct Node_377090 { char p[120]; float scale; } Node_377090;
typedef struct Work_377090 { char p[20]; int state; } Work_377090;
typedef struct Piece { char p[28]; char flag; char q[27]; float rate; char r[4]; long long pos; } Piece;
typedef struct Pieces { char p[8]; int count; char q[4]; Piece **items; } Pieces;
typedef struct Track { char p[56]; Pieces *pieces; } Track;
typedef struct Tracks { char p[16]; Track **items; } Tracks;
typedef struct Sys { char p[36]; Tracks *tracks; } Sys;
typedef struct Ctx { char p[32]; Sys *sys; } Ctx;
typedef struct Act_377090 { char p[8]; int index; Ctx *ctx; char q[28]; Node_377090 *node; char r[8]; Work_377090 *work; } Act_377090;
extern "C" void beAction2MOTIONSET_Update(Owner *arg0, Act_377090 *arg1);
extern "C" int DAT_00561b48[4];
extern "C" int DAT_00585be0[4];
extern "C" int beAction2MOTIONSET_Start(beAction2 *arg0, beAction2InfoRam *arg1, beAction2MOTIONSET *arg2);
extern "C" int g_beAction2FLASHSET_metaObject[4];
extern "C" int g_beAction2WAITCHECK_metaObject[4];
extern "C" int g_beAction2FADESET_metaObject[4];
extern "C" int g_beAction2JOINTSET_metaObject[4];
extern "C" int g_beAction2MOTIONSET_metaObject[4];
/* matching construct: igObjectList-shaped component list with a pointer-typed buffer; reflected
 * igObjectList._data (int) changes retail register allocation */
struct Action2ComponentList {
    char _pad0[8];
    int _count;
    int _capacity;
    struct Action2Component **_data;
};
/* matching construct: dummy-virtual component class; only slot 20 (GetMetaObject) is called */
class Action2Component {
public:
    virtual void vfunc_00();
    virtual void vfunc_01();
    virtual void vfunc_02();
    virtual void vfunc_03();
    virtual void vfunc_04();
    virtual void vfunc_05();
    virtual void vfunc_06();
    virtual void vfunc_07();
    virtual void vfunc_08();
    virtual void vfunc_09();
    virtual void vfunc_10();
    virtual void vfunc_11();
    virtual void vfunc_12();
    virtual void vfunc_13();
    virtual void vfunc_14();
    virtual void vfunc_15();
    virtual void vfunc_16();
    virtual void vfunc_17();
    virtual void vfunc_18();
    virtual void vfunc_19();
    virtual int GetMetaObject();
};
/* matching construct: the guard reads the list through its own view, so its load stays apart from
 * the loads in the loop. */
struct Action2DataGuardView : beAction2Data {};
extern "C" void Gap__Bec__beAction2__vfunc_31(void *self, beAction2InfoRam *info);
extern "C" int DAT_0050dfe8[4];
extern "C" int DAT_0050dff0[4];
extern "C" int DAT_0050e010[4];
extern "C" int DAT_0050e030[4];
/* Owning reference held in the frame; its release is inlined at each return. */
struct Rc { int w0; int references; };
struct RP { Rc *p; inline ~RP(); };
/* matching construct: dummy virtual slots so the calls dispatch through the retail vtable offsets */
struct V {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19();
    virtual int v22();
    virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();
    virtual int v27(int);
    virtual int v28(int);
};
extern "C" int Gap__Bec__beAction2__vfunc_33(beAction2 *arg0, beAction2InfoRam *arg1, void *arg2);

void Gap__Bec__beAction2__vfunc_32(void)
{
}

int Gap__Bec__beAction2__vfunc_30(void)
{
    return g_beAction2Info_metaObject[0];
}

void Gap__Bec__beAction2__vfunc_29(beAction2 *arg0, char *arg1) {
    beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050dfc8[0]);
    arg1[20] = 0;
    DAT_005626e0[0] = 0xBD088889;
}

void beAction2FLASHSET_Update(void *arg0, beAction2InfoRam *arg1) {
    int sp4C;
    int sp48;
    int sp44;
    beAction2InfoWork *s1;
    int s0;
    igObject *a0;
    s1 = (beAction2InfoWork *)arg1->_work;
    switch (s1->_flashSt0) {
    case 0:
        break;
    case 1:
        if (FUN_003a7e90(arg1, &DAT_0050dfd0[0]) != 0) {
            s0 = ((Action2NodeList136 *)arg1->_node)->list;
            if (s1->_blendStateAttr == 0) {
                ObjectList_RemoveFirstRetained(&sp4C, s0, s1->_colorAttr, 0);
                a0 = (igObject *)s1->_colorAttr;
                if (a0 != 0) {
                    a0->_refCount = (int)a0->_refCount - 1;
                    if (((unsigned long long)((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(a0);
                    }
                }
                s1->_colorAttr = 0;
                ObjectList_RemoveFirstRetained(&sp48, s0, s1->_lightingStateAttr, 0);
                a0 = (igObject *)s1->_lightingStateAttr;
                if (a0 != 0) {
                    a0->_refCount = (int)a0->_refCount - 1;
                    if (((unsigned long long)((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(a0);
                    }
                }
                s1->_lightingStateAttr = 0;
            }
            ObjectList_RemoveFirstRetained(&sp44, s0, s1->_textureStateAttr, 0);
            a0 = (igObject *)s1->_textureStateAttr;
            if (a0 != 0) {
                a0->_refCount = (int)a0->_refCount - 1;
                if (((unsigned long long)((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(a0);
                }
            }
            s1->_textureStateAttr = 0;
            FUN_003a8580(arg1, &DAT_0050dfd0[0]);
            s1->_flashSt0 = 0;
        }
    }
}

int beAction2FLASHSET_Start(int arg0, beAction2InfoRam *arg1, beAction2FLASHSET *arg2) {
    beAction2InfoWork *c = (beAction2InfoWork *)arg1->_work;
    int list = ((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList;
    if (c->_colorAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
        Ref<0> r((igObject *)FUN_00138ee0(a));
        igObject *o;
        igObject *old;
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)c->_colorAttr;
        IG_OBJECT_RELEASE(old);
        c->_colorAttr = (int)o;
    }
    if (c->_textureStateAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
        Ref<3> r((igObject *)FUN_00131390(a));
        igObject *o;
        igObject *old;
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)c->_textureStateAttr;
        IG_OBJECT_RELEASE(old);
        c->_textureStateAttr = (int)o;
    }
    if (c->_lightingStateAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
        Ref<2> r((igObject *)FUN_00135e20(a));
        igObject *o;
        igObject *old;
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)c->_lightingStateAttr;
        IG_OBJECT_RELEASE(old);
        c->_lightingStateAttr = (int)o;
    }
    struct { int x, y, z, w; } v3;
    FUN_00193540(&v3, 1, ((AttrObjView *)c->_colorAttr)->f28);
    v3.y = 0x3F800000;
    v3.x = 0x3F800000;
    ((AttrObjView *)c->_colorAttr)->vX(&v3);
    ((AttrObjView *)c->_textureStateAttr)->vX(0);
    ((AttrObjView *)c->_lightingStateAttr)->vX(0);
    c->_flashSt0 = 1;
    FUN_003a7a20(arg1, &DAT_0050dfd0[0], 0x03F940AC);
    return 1;
}

/* matching construct: the reflected reference fields are 4-byte ints; the casts give the typed views (no layout effect) */
void beAction2WAITCHECK_Update(beAction2 *arg0, beAction2InfoRam *arg1) {
    unsigned long long b;
    beAction2InfoWork *work;
    igAnimationState *obj;
    long long a;
    long long d;
    igAnimation *info;
    beAction2Info *ctx;
    igAnimationStateList *ew;
    work = (beAction2InfoWork *)arg1->_work;
    ctx = (beAction2Info *)arg1->_parentInfo;
    switch (work->_waitSt0) {
    case 1:
        if (FUN_003a7e90(arg1, &DAT_0050dfd8[0]) != 0) {
            work->_waitSt0 = 0;
            beAction2_StartComponents((int)arg0, arg1);
        }
        break;
    case 2:
        ew = (igAnimationStateList *)((igAnimationCombiner *)((int *)((igObjectList *)((igAnimationDatabase *)ctx->_animationDatabase)->_combinerList)->_data)[arg1->_ramNo])->_animationStateList;
        if (ew->_count == 1) {
            obj = (igAnimationState *)((int *)ew->_data)[0];
            info = (igAnimation *)obj->_animation;
            d = obj->_localTime - info->_keyFrameTimeOffset;
            b = info->_duration;
            a = info->_startTime;
            if (b != 0) {
                long long t;
                FUN_001dd4b0(d - a, b, &t);
                t += a;
            }
            FUN_001af510(obj, FUN_00398e80(arg1->_node, ((WcClock *)arg0->_insight)->time));
            if (b <= obj->_localTime) {
                work->_waitSt0 = 0;
                beAction2_StartComponents((int)arg0, arg1);
            }
        }
        break;
    case 3:
        if (work->_jointIsEnd != 0) {
            work->_waitSt0 = 0;
            beAction2_StartComponents((int)arg0, arg1);
        }
        break;
    }
}

int beAction2WAITCHECK_Start(beAction2 *mgr, beAction2InfoRam *act, beAction2WAITCHECK *comp) {
    beAction2InfoWork *w = (beAction2InfoWork *)act->_work;
    const char *name = (const char *)comp->_name;
    float secs = comp->_waitTime;
    const char *s = name ? name : ((char *)DAT_004e0858);
    switch (*s) {
    case 'R': {
        const char *s2 = name ? name : ((char *)DAT_004e0858);
        unsigned r, d;
        if (s2[3] == 'S') {
            DAT_0058a348[0] = secs;
            return 1;
        }
        d = (int)(100.0f * secs - 100.0f * DAT_0058a348[0]);
        r = ((RandomSourceVirtual *)((beSystem *)mgr->_system)->_random)->Query() % d;
        secs = DAT_0058a348[0] + (float)r / 100.0f;
    }
    case 'F':
        FUN_003a7a20(act, DAT_0050dfd8, __fixsfdi(1e9f * secs / 60.0f));
        w->_waitSt0 = 1;
        break;
    case 'M':
        w->_waitSt0 = 2;
        break;
    case 'J':
        w->_waitSt0 = 3;
        break;
    default:
        break;
    }
    return 0;
}

void beAction2FADESET_Update(void *arg0, beAction2InfoRam *arg1) {
    beAction2InfoWork *c = (beAction2InfoWork *)arg1->_work;
    switch (c->_fadeSt0) {
    case 1: {
        float lim;
        float dt;
        FadeColor v;
        float *pw;
        int list;
        int s1, s2, s3;
        RefCountedObject *a0;
        dt = FUN_003a8140(arg1, &DAT_0050dfe0[0]);
        if (dt != 0.0f) {
            FUN_00193540(&v, 1, ((DummyVirtualComponent *)c->_colorAttr)->f28);
            pw = &v.w;
            *pw = c->_fadeValue + dt * c->_fadeAddValue;
            ((DummyVirtualComponent *)c->_colorAttr)->vX(&v);
            c->_fadeValue = *pw;
            lim = *(float *)&c->_fadeLimitValue;
            if (!(*pw < lim)) {
                list = ((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList;
                if (c->_textureStateAttr == 0) {
                    ObjectList_RemoveFirstRetained(&s1, list, c->_colorAttr, 0);
                    a0 = (RefCountedObject *)c->_colorAttr;
                    if (a0 != 0) {
                        a0->rc = a0->rc - 1;
                        if (((unsigned long long)((long long)a0->rc << 0x29) >> 0x29) == 0) igObject_Destroy(a0);
                    }
                    c->_colorAttr = 0;
                    ObjectList_RemoveFirstRetained(&s2, list, c->_lightingStateAttr, 0);
                    a0 = (RefCountedObject *)c->_lightingStateAttr;
                    if (a0 != 0) {
                        a0->rc = a0->rc - 1;
                        if (((unsigned long long)((long long)a0->rc << 0x29) >> 0x29) == 0) igObject_Destroy(a0);
                    }
                    c->_lightingStateAttr = 0;
                }
                ObjectList_RemoveFirstRetained(&s3, list, c->_blendStateAttr, 0);
                a0 = (RefCountedObject *)c->_blendStateAttr;
                if (a0 != 0) {
                    a0->rc = a0->rc - 1;
                    if (((unsigned long long)((long long)a0->rc << 0x29) >> 0x29) == 0) igObject_Destroy(a0);
                }
                c->_blendStateAttr = 0;
                FUN_003a8580(arg1, &DAT_0050dfe0[0]);
                c->_fadeSt0 = 3;
            }
        }
        break;
    }
    case 2: {
        float dt;
        FadeColor v;
        float *pw;
        float nv;
        dt = FUN_003a8140(arg1, &DAT_0050dfe0[0]);
        if (dt != 0.0f) {
            FUN_00193540(&v, 1, ((DummyVirtualComponent *)c->_colorAttr)->f28);
            nv = c->_fadeValue - dt * c->_fadeAddValue;
            pw = &v.w;
            *pw = nv;
            if (nv < 0.0f) *pw = 0.0f;
            ((DummyVirtualComponent *)c->_colorAttr)->vX(&v);
            c->_fadeValue = *pw;
            if (*pw <= 0.0f) {
                FUN_003a8580(arg1, &DAT_0050dfe0[0]);
                c->_fadeSt0 = 3;
            }
        }
        break;
    }
    }
}

/* matching construct: the (igObject *)/(int) casts on _colorAttr/_blendStateAttr/_lightingStateAttr stand in for 4-byte reference fields */
int beAction2FADESET_Start(int arg0, beAction2InfoRam *arg1, beAction2FADESET *arg2) {
    beAction2InfoWork *c = (beAction2InfoWork *)arg1->_work;
    int list = ((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList;
    char *nm = (char *)arg2->_name;
    nm = nm != 0 ? nm : (char *)DAT_004e0858;
    if (*nm == 0x48) {
        unsigned bit;
        unsigned i;
        igUnsignedIntList *l;
        unsigned *p;
        int cnt;
        int v;
        int m;
        /* matching construct: cast from the 4-byte reference field (int) to the typed pointer; no layout effect */
        beAction2Info *pi = (beAction2Info *)arg1->_parentInfo;
        l = ((Action2SwitchBits *)pi->_switch)->f32;
        bit = arg1->_ramNo;
        i = bit >> 5;
        m = 1 << (bit & 0x1F);
        p = (unsigned *)l->_data + i;
        cnt = l->_count;
        v = ~m & *p;
        if (cnt != 0 && (int)i >= 0 && (int)i < cnt) {
            *p = v;
        }
    } else {
    if (c->_colorAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                igObject *o;
        igObject *old;
        Ref<0> r((igObject *)FUN_00138ee0(a));
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)c->_colorAttr;
        IG_OBJECT_RELEASE(old);
        c->_colorAttr = (int)o;
    }
    if (c->_blendStateAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                igObject *o;
        igObject *old;
        Ref<1> r((igObject *)FUN_00139600(a));
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)c->_blendStateAttr;
        IG_OBJECT_RELEASE(old);
        c->_blendStateAttr = (int)o;
    }
    if (c->_lightingStateAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                igObject *o;
        igObject *old;
        Ref<2> r((igObject *)FUN_00135e20(a));
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)c->_lightingStateAttr;
        IG_OBJECT_RELEASE(old);
        c->_lightingStateAttr = (int)o;
    }
        char *nm2 = (char *)arg2->_name;
        nm2 = nm2 != 0 ? nm2 : (char *)DAT_004e0858;
        if (*nm2 == 0x49) {
            struct { int x, y, z, w; } v3;
            FUN_00193540(&v3, 1, ((igColorAttr *)c->_colorAttr)->_colorPacked);
            v3.w = 0;
            ((DummyVirtualComponent *)c->_colorAttr)->vX(&v3);
            ((DummyVirtualComponent *)c->_blendStateAttr)->vX((void *)1);
            ((DummyVirtualComponent *)c->_lightingStateAttr)->vX((void *)0);
            c->_fadeValue = 0.0f;
            c->_fadeLimitValue = arg2->_fadeValue;
            c->_fadeAddValue = arg2->_fadeValue / arg2->_fadeTime;
            c->_fadeSt0 = 1;
        } else {
            struct { int x, y, z; float w; } v3;
            FUN_00193540(&v3, 1, ((igColorAttr *)c->_colorAttr)->_colorPacked);
            v3.w = arg2->_fadeValue;
            ((DummyVirtualComponent *)c->_colorAttr)->vX(&v3);
            ((DummyVirtualComponent *)c->_blendStateAttr)->vX((void *)1);
            ((DummyVirtualComponent *)c->_lightingStateAttr)->vX((void *)0);
            c->_fadeValue = arg2->_fadeValue;
            c->_fadeLimitValue = arg2->_fadeValue;
            c->_fadeAddValue = arg2->_fadeValue / arg2->_fadeTime;
            c->_fadeSt0 = 2;
        }
        FUN_003a7a20(arg1, &DAT_0050dfe0[0], 0);
    }
    return 1;
}

void beAction2JOINTSET_Update(Owner *arg0, Act *arg1) {
    Work *work;
    long long now;
    long long end;
    bool changed;
    int state;
    long long t;
    Node *node;
    float f;

    work = arg1->work;
    state = work->state;
    if (state == 2) goto body;
    if (state == 1) goto body;
    if (state == 0) return;
    return;
    body:
    {
        now = FUN_00398e80((int)arg1->node, arg0->clock->time);
        end = work->end;
        changed = false;
        if (end < now) {
            state = work->state;
            do {
                switch (state) {
                case 1:
                    changed = true;
                    now += work->start - end;
                    break;
                case 2:
                    now = end;
                    changed = true;
                    break;
                }
            } while (now > end);
        }
        if (changed) {
            node = arg1->node;
            f = (float)(unsigned int)(int)(arg0->clock->time >> 18);
            f = f * node->scale;
            node->bias = now - (__fixsfdi(f) << 18);
            work->isEnd = 1;
        }
    }
}

/* matching construct: _work/_node/_loopMode are 4-byte reference fields in the reflected structs; the casts give the typed views (no layout effect) */
int beAction2JOINTSET_Start(Owner *arg0, beAction2InfoRam *arg1, beAction2JOINTSET *arg2) {
    long long start;
    Work *work;
    Node *node;
    long long t;
    float f;

    work = (Work *)arg1->_work;
    if (*(char *)arg2->_loopMode == 0x4C) {
        work->state = 1;
    } else {
        work->state = 2;
    }
    float m = arg2->_startTime;
    float n = 1e9f * m;
    work->start = __fixsfdi(n / 60.0f);
    m = arg2->_endTime;
    n = 1e9f * m;
    m = n / 60.0f;
    work->end = __fixsfdi(m);
    t = (int)(arg0->clock->time >> 18);
    node = (Node *)arg1->_node;
    f = (float)(unsigned int)(int)t;
    f = f * node->scale;
    start = work->start;
    node->bias = start - (__fixsfdi(f) << 18);
    work->isEnd = 0;
    return 1;
}

void beAction2MOTIONSET_Update(Owner *arg0, Act_377090 *arg1) {
    Track *track;
    int n;
    int i;
    Work_377090 *work;
    Pieces *pieces;
    Piece *first;
    float f;
    float rate;
    Node_377090 *node;
    long long v;
    long long d;
    long p; /* matching construct: decomp-permuter — the saved time bias is a `long` (igLong, 64-bit under mwccps2), not `long long` */

    work = arg1->work;
    switch (work->state) {
    case 1:
        work->state = 2;
        return;
    case 2:
        track = arg1->ctx->sys->tracks->items[arg1->index];
        pieces = track->pieces;
        if (pieces->count != 1) {
            v = FUN_00398e80((int)arg1->node, arg0->clock->time);
            FUN_001ac140((int)track, v);
            n = track->pieces->count;
            i = 0;
            while (i < n) {
                track->pieces->items[i]->flag = 0;
                i++;
            }
        }
        if (pieces->count == 1) {
            if (pieces->items[0]->rate != arg1->node->scale) {
                v = FUN_00398e80((int)arg1->node, arg0->clock->time);
                node = arg1->node;
                rate = node->scale;
                first = pieces->items[0];
                f = (float)(unsigned int)(int)(v >> 18);
                d = __fixsfdi(f * first->rate);
                p = first->pos;
                first->pos = (d << 18) + p;
                first->pos = first->pos - (__fixsfdi(f * rate) << 18);
                first->rate = rate;
            }
            work->state = 0;
        }
        break;
    }
}

int beAction2MOTIONSET_Start(beAction2 *arg0, beAction2InfoRam *arg1, beAction2MOTIONSET *arg2) {
    beAction2Info *info = (beAction2Info *)arg1->_parentInfo;
    beAction2InfoWork *work = (beAction2InfoWork *)arg1->_work;
    int names = ((igAnimationDatabase *)info->_animationDatabase)->_animationList;
    int name = arg2->_name;
    int nameOrEmpty;
    if (name != 0) nameOrEmpty = name; else nameOrEmpty = (int)DAT_004e0858;
    igAnimation *res = (igAnimation *)igProperty_FindByName(names, DAT_00585be0[0], nameOrEmpty);
    igAnimationCombiner *anim = ((igAnimationCombiner **)((igAnimationCombinerList *)((igAnimationDatabase *)info->_animationDatabase)->_combinerList)->_data)[arg1->_ramNo];
    long biasOld; /* matching construct: decomp-permuter (found on beAction2MOTIONSET_Update) — the saved time bias is a `long` (igLong, 64-bit under mwccps2), not `long long` */
    float zero = 0.0f;
    float blend;
    long long hokanTicks;
    if (work->_isNoHokan != 0 || arg2->_hokanTime == 0.0f) {
        blend = 1.0f;
        work->_isNoHokan = 0;
        hokanTicks = 1;
    } else {
        hokanTicks = __fixsfdi(1e9f * arg2->_hokanTime / 60.0f);
        blend = 0.0f;
    }
    if (((igAnimationStateList *)anim->_animationStateList)->_count >= 2) FUN_001ae780(anim, 0);
    int value = res->_priority;
    FUN_001ae660(anim, res, 1, 1, 1, &value, 0, hokanTicks, blend, 1.0f, 0);
    long long cur = FUN_00398e80(arg1->_node, ((igInsightCore *)arg0->_insight)->_worldTime);
    FUN_001ac140(anim, cur);
    if (((char *)arg2->_hokanMode)[0] == 'S') {
        igAnimationState *tr = ((igAnimationState **)((igAnimationStateList *)anim->_animationStateList)->_data)[0];
        float f = (float)(unsigned int)(int)(((igInsightCore *)arg0->_insight)->_worldTime >> 18);
        long long ticks = __fixsfdi(f * tr->_timeScale);
        biasOld = tr->_timeBias;
        tr->_timeBias = (ticks << 18) + biasOld;
        tr->_timeBias -= __fixsfdi(f * zero) << 18;
        tr->_timeScale = zero;
    }
    if (((char *)arg2->_hokanMode)[1] == 'S') {
        igAnimationStateList *sl = (igAnimationStateList *)anim->_animationStateList;
        int idx = sl->_count - 1;
        igAnimationState *tr = ((igAnimationState **)sl->_data)[idx];
        float f = (float)(unsigned int)(int)(((igInsightCore *)arg0->_insight)->_worldTime >> 18);
        long long ticks = __fixsfdi(f * tr->_timeScale);
        biasOld = tr->_timeBias;
        tr->_timeBias = (ticks << 18) + biasOld;
        tr->_timeBias -= __fixsfdi(f * zero) << 18;
        tr->_timeScale = zero;
    }
    igAnimationTrackList *bl = (igAnimationTrackList *)res->_trackList;
    int isLoop = ((char *)arg2->_loopMode)[0] == 'L';
    int j;
    for (j = 0; j < bl->_count; j++) {
        void *tg = (void *)((igAnimationTrack **)bl->_data)[j]->_source;
        if (tg != 0) {
            if (igObject_IsKindOf(tg, DAT_00561b48[0]) != 0) {
                igEnbayaAnimationSource *m = (igEnbayaAnimationSource *)((igEnbayaTransformSource *)tg)->_enbayaAnimationSource;
                if (isLoop) m->_playMode = 0; else m->_playMode = 4;
                break;
            } else if (isLoop) {
                igCompressedAnimationSequenceQS *sq = (igCompressedAnimationSequenceQS *)tg;
                if (sq->_playMode == 3) break;
                sq->_playMode = 3;
            } else {
                igCompressedAnimationSequenceQS *sq = (igCompressedAnimationSequenceQS *)tg;
                if (sq->_playMode == 1) break;
                sq->_playMode = 1;
            }
        }
    }
    work->_motionSt0 = 1;
    work->_isMotion = 1;
    return 1;
}

/* Resumes at work._comIndex and starts components until one handler returns false or the list is
 * exhausted, then saves the position back into work._comIndex. The component kind is identified by
 * comparing its virtual GetMetaObject() result with the published metadata handle of each *_Start
 * handler's class. */
void beAction2_StartComponents(int manager, void *info)
{
    beAction2Data *data;
    beAction2InfoWork *work;
    int index;
    unsigned char keepGoing;
    Action2Component *component;

    work = (beAction2InfoWork *)((beAction2InfoRam *)info)->_work;
    data = (beAction2Data *)work->_comData;
    index = work->_comIndex;
    if (index != ((Action2ComponentList *)((Action2DataGuardView *)data)->_comList)->_count) {
        do {
            keepGoing = true;
            component = (((Action2ComponentList *)data->_comList)->_data)[index];
            if (g_beAction2MOTIONSET_metaObject[0] == component->GetMetaObject()) {
                keepGoing = beAction2MOTIONSET_Start((beAction2 *)manager, (beAction2InfoRam *)info, (beAction2MOTIONSET *)component) & 0xFF;
                index += 1;
            } else if (g_beAction2JOINTSET_metaObject[0] == component->GetMetaObject()) {
                keepGoing = beAction2JOINTSET_Start((Owner *)manager, (beAction2InfoRam *)info, (beAction2JOINTSET *)component) & 0xFF;
                index += 1;
            } else if (g_beAction2FADESET_metaObject[0] == component->GetMetaObject()) {
                keepGoing = beAction2FADESET_Start(manager, (beAction2InfoRam *)info, (beAction2FADESET *)component) & 0xFF;
                index += 1;
            } else if (g_beAction2WAITCHECK_metaObject[0] == component->GetMetaObject()) {
                keepGoing = beAction2WAITCHECK_Start((beAction2 *)manager, (beAction2InfoRam *)info, (beAction2WAITCHECK *)component) & 0xFF;
                index += 1;
            } else if (g_beAction2FLASHSET_metaObject[0] == component->GetMetaObject()) {
                keepGoing = beAction2FLASHSET_Start(manager, (beAction2InfoRam *)info, (beAction2FLASHSET *)component) & 0xFF;
                index += 1;
            }
        } while ((keepGoing & 0xFF) && index != ((Action2ComponentList *)data->_comList)->_count);
    }
    work->_comIndex = index;
}

void Gap__Bec__beAction2__vfunc_31(void *self, beAction2InfoRam *info) {
    beAction2InfoWork *work;

    if (info->_isRun == 0) {
        return;
    }
    work = (beAction2InfoWork *)info->_work;
    if (work->_isFreeze != 0) {
        return;
    }
    if (work->_motionSt0 != 0) {
        beAction2MOTIONSET_Update((Owner *)self, (Act_377090 *)info);
    }
    if (work->_jointSt0 != 0) {
        beAction2JOINTSET_Update((Owner *)self, (Act *)info);
    }
    if (work->_fadeSt0 != 0) {
        beAction2FADESET_Update(self, (beAction2InfoRam *)info);
    }
    if (work->_waitSt0 != 0) {
        beAction2WAITCHECK_Update((beAction2 *)self, (beAction2InfoRam *)info);
    }
    if (work->_flashSt0 != 0) {
        beAction2FLASHSET_Update(self, (beAction2InfoRam *)info);
    }
}

inline RP::~RP() { Rc *rr = p; if (rr != 0) { rr->references = rr->references - 1; if ((rr->references & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }

/* the object lists hold 4-byte arena handles: _data is a memory ref */





int Gap__Bec__beAction2__vfunc_33(beAction2 *arg0, beAction2InfoRam *arg1, void *arg2)
{
    RP spBC;
    beAction2Info *info;
    unsigned int ramNo;
    igBitMask *sw;
    beAction2InfoWork *w;

    spBC.p = (Rc *)arg1->_work;
    if (spBC.p != 0) {
        spBC.p->references = spBC.p->references + 1;
    }
    info = (beAction2Info *)arg1->_parentInfo;
    ramNo = arg1->_ramNo;
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0036dcd0(), arg2)) {
    case 1:
        beMessenger_AppendBool(arg0->_messenger, arg1->_isRun);
        break;
    case 0: {
        beAction2InfoWork *ww = (beAction2InfoWork *)spBC.p;
        beAction2Data *cd = (beAction2Data *)ww->_comData;
        int ci = ww->_comIndex;
        if (ww->_waitSt0 == 0 && ci == ((igObjectList *)cd->_comList)->_count) {
            beMessenger_AppendBool(arg0->_messenger, 1);
        } else {
            beMessenger_AppendBool(arg0->_messenger, 0);
        }
        break;
    }
    case 3:
        if (arg1->_isRun != 0) {
            beMessenger_AppendObject(arg0->_messenger, arg1->_appearanceList);
            beMessenger_AppendObject(arg0->_messenger, LDATA((igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_skeletonList)[0]);
        }
        break;
    case 4:
        if (arg1->_isRun != 0) {
            int nm = beMessenger_GetString(arg0->_messenger, 0);
            igActor *a = (igActor *)LDATA((igObjectList *)arg1->_actorList)[0];
            int idx = ((V *)((int *)a->_animationSystem)[3])->v27(nm);
            int m;
            if (a->_actorCacheUsed != 0) {
                m = a->_boneMatrixCacheArray + (idx << 6);
            } else {
                m = ((V *)a->_animationSystem)->v28(idx);
            }
            beMessenger_AppendMatrix(arg0->_messenger, m);
        }
        break;
    case 2: {
        igObjectList *l = (igObjectList *)info->_dataList_;
        int n = l->_count;
        int i;
        for (i = 0; i < n; i++) {
            void *nm = (void *)((int *)LDATA(l)[i])[2];
            void *nm2;
            if (nm != 0) nm2 = nm; else nm2 = &DAT_004e0858[0];
            beMessenger_AppendString(arg0->_messenger, nm2);
        }
        break;
    }
    case 5:
        if (spBC.p != 0) {
            beModelCtrlNode2 *nd;
            float f20;
            int tt;
            float k = 0.0f;
            FUN_003a84a0(arg1, k);
            tt = (int)(((igInsightCore *)arg0->_insight)->_worldTime >> 0x12);
            nd = (beModelCtrlNode2 *)arg1->_node;
            f20 = (float)(unsigned int)tt;
            {
                long long bias = __fixsfdi(f20 * nd->_timeScale);
                bias <<= 18;
                bias += nd->_timeBias;
                nd->_timeBias = bias;
            }
            nd->_timeBias -= __fixsfdi(f20 * k) << 18;
            nd->_timeScale = k;
            ((beAction2InfoWork *)spBC.p)->_isFreeze = 1;
        }
        break;
    case 6:
        if (spBC.p != 0) {
            beModelCtrlNode2 *nd;
            float f20;
            int tt;
            float k = 1.0f;
            FUN_003a84a0(arg1, k);
            tt = (int)(((igInsightCore *)arg0->_insight)->_worldTime >> 0x12);
            nd = (beModelCtrlNode2 *)arg1->_node;
            f20 = (float)(unsigned int)tt;
            {
                long long bias = __fixsfdi(f20 * nd->_timeScale);
                bias <<= 18;
                bias += nd->_timeBias;
                nd->_timeBias = bias;
            }
            nd->_timeBias -= __fixsfdi(f20 * k) << 18;
            nd->_timeScale = k;
            ((beAction2InfoWork *)spBC.p)->_isFreeze = 0;
        }
        break;
    default:
        sw = (igBitMask *)((int *)info->_switch)[8];
        if (strcmp(arg2, &DAT_0050dfe8[0]) == 0) {
            igObjectList *l = (igObjectList *)((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList;
            int n = l->_count;
            int i;
            int n2;
            int j;
            for (i = 0; i < n; i++) {
                Rc *o = (Rc *)LDATA(l)[i];
                REL(o)
            }
            j = 0;
            n2 = l->_count;
            for (; j < n2; j++) {
                LDATA(l)[j] = 0;
            }
            l->_count = 0;
            int pos = ((igObjectList *)((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList)->_count > 0;
            if (!pos) {
                List_Reserve((void *)((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList, 0, 4);
            }
            BITCLR(ramNo)
            { Rc *o = (Rc *)arg1->_work; REL(o) }
            arg1->_work = 0;
            FUN_003a8760(arg1);
            arg1->_isRun = 0;
            if (info->_animationDatabase != 0) {
                igObjectList *dl = (igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_combinerList;
                int an;
                int k;
                igMetaField *fl;
                igMetaField *fl2;
                V *ac;
                int pv;
                int pv2;
                if (dl != 0) {
                    FUN_001adf70(LDATA(dl)[arg1->_ramNo]);
                }
                an = ((igObjectList *)arg1->_actorList)->_count;
                for (k = 0; k < an; k++) {
                    ac = (V *)LDATA((igObjectList *)arg1->_actorList)[k];
                    fl = (igMetaField *)igMetaObject_FindFieldByName(ac->v22(), &DAT_0050dff0[0]);
                    pv = *(int *)((char *)ac + fl->_offset);
                    if (pv != 0) {
                        Memory_FreeBuffer(pv);
                        *(int *)((char *)ac + fl->_offset) = 0;
                    }
                    fl2 = (igMetaField *)igMetaObject_FindFieldByName(ac->v22(), &DAT_0050e010[0]);
                    pv2 = *(int *)((char *)ac + fl2->_offset);
                    if (pv2 != 0) {
                        Memory_FreeBuffer(pv2);
                        *(int *)((char *)ac + fl2->_offset) = 0;
                    }
                }
            }
            return 1;
        }
        if (spBC.p == 0) {
            void *alloc = ((void *)igObject_GetAllocator(arg0));
            Rc *t;
            alloc = GPR_00554c14 ? alloc : ((void *)Memory_GetAllocatorBySelector(DAT_00587110[0]));
            { Rc *o = spBC.p; REL(o) }
            spBC.p = (Rc *)FUN_0036c2a0(alloc);
            t = spBC.p;
            if (t != 0) t->references = t->references + 1;
            { Rc *o = (Rc *)arg1->_work; REL(o) }
            arg1->_work = (int)t;
        }
        if (arg1->_isRun == 0) {
            beAction2InfoWork *ww;
            arg1->_isRun = 1;
            ww = (beAction2InfoWork *)spBC.p; ww->_motionSt0 = 0;
            ww = (beAction2InfoWork *)spBC.p; ww->_fadeSt0 = 0;
            ww = (beAction2InfoWork *)spBC.p; ww->_waitSt0 = 0;
            BITSET(ramNo)
            ((beAction2InfoWork *)spBC.p)->_isNoHokan = 1;
            if (info->_animationDatabase != 0) {
                igObjectList *dl = (igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_combinerList;
                if (dl != 0) {
                    igAnimationCombiner *s5 = (igAnimationCombiner *)LDATA(dl)[arg1->_ramNo];
                    int an;
                    int k;
                    s5->_animationStateTime = 0x05F5E100;
                    an = ((igObjectList *)arg1->_actorList)->_count;
                    for (k = 0; k < an; k++) {
                        igActor *ac = (igActor *)LDATA((igObjectList *)arg1->_actorList)[k];
                        int nz = ac->_boneMatrixCacheArray != 0;
                        if (nz) break;
                        FUN_00239070(ac, s5);
                    }
                    FUN_001ae750(s5, LDATA((igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_animationList)[0], 0, 4, 0);
                }
            }
        } else {
            BITSET(ramNo)
            ((beAction2InfoWork *)spBC.p)->_isNoHokan = 0;
        }
        {
            int prop = (int)igProperty_FindByName(info->_dataList_, DAT_00585be0[0], arg2);
            beAction2InfoWork *cur = (beAction2InfoWork *)spBC.p;
            if (cur->_comData != prop) {
                if (prop != 0) ((Rc *)prop)->references = ((Rc *)prop)->references + 1;
                { Rc *o = (Rc *)cur->_comData; REL(o) }
                cur->_comData = prop;
                ((beAction2InfoWork *)spBC.p)->_comIndex = 0;
                beAction2_StartComponents((int)arg0, arg1);
                int rn = arg1->_ramNo;
                void *pn;
                if (info->_name != 0) pn = (void *)info->_name; else pn = &DAT_004e0858[0];
                beMessenger_SendNamed(arg0->_messenger, &DAT_0050e030[0], pn, rn, arg2);
            }
        }
        break;
    }
    return 1;
}

int Gap__Bec__beAction2__vfunc_20(void)
{
    return g_beAction2_metaObject[0];
}

/* Shared default virtual slots that almost every class inherits, so most are empty or return a
 * constant. The slot number is the only name evidence, so the bodies are documented by what they
 * do. */

/* Slot 28 default: empty. */
void Gap__Core__igObject__vfunc_28(void)
{
}

/* Slot 34 default: always 0. */
int Gap__Core__igObject__vfunc_34(void) {
    return 0;
}

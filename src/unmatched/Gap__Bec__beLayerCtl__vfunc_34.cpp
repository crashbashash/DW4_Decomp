/* Message handler dispatching on an enum value name read from the message: 0 builds the layer
 * switch from the layer info record, 1 sets or toggles a named layer, 2 selects one, 3 lists the
 * names, 4 looks one up and returns it. Class names below are readable labels (the layer switch is
 * an igSwitch, the group elements igGroups). */
#include "dw4/reflected.h"
extern "C" {
void *FUN_001968f0(void *);
void *FUN_0019f1d0(void *);
int FUN_001c5d10(void *, void *);
int FUN_001c6050(void *, void *);
int FUN_001dc820(void *, int);
int FUN_001dc870(void *);
int FUN_001dc880(void *, int);
int FUN_001dc8d0(void *);
int FUN_001dc8e0(void *, void *);
int FUN_001dc9a0(void *, int);
void *FUN_00236f80(int, int);
int FUN_0035c9e0();
int FUN_0035ca40();
void *Memory_GetAllocatorBySelector(int);
int beMessenger_AppendBool(int, int);
int beMessenger_AppendObject(int, void *);
int beMessenger_AppendString(int, char *);
int beMessenger_ClearObjects(int);
char *beMessenger_GetString(int, int);
int beMessenger_GetStringCount(int);
unsigned int beMessenger_ResolveEnumValue(int, int, void *);
void igNamedObject_SetName(void *, char *);
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
int strcmp(char *, char *);
extern int DAT_004e0858[4];
extern int DAT_0050ebd0[4];
extern int DAT_0050ebe0[4];
extern int DAT_0050ebf0[4];
extern int DAT_0050ebf8[4];
extern int DAT_0050ec08[4];
extern int DAT_005618d8[4];
extern int DAT_00587108[4];
extern int DAT_00587110[4];
extern int DAT_0058c790[4];
extern unsigned char GPR_00554c14;
int Gap__Bec__beLayerCtl__vfunc_34(beLayerCtl *arg0, beLayerInfoRam *arg1, beMessengerWork *arg2);
}
/* matching construct: dummy-virtual class so e->v22() compiles to the retail jalr through vtable slot 22 (a scene-graph node's class-id virtual) */
class NodeVt {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v22();
};
/* matching construct: stack holder released through the refcount (the 23-bit count mask) in its destructor, emitted as __dt__3RefFv; the constructor takes the factory result so the exception table protects the holder from its first use (retail copy 0x00229350) */
struct Ref {
    igNamedObject *p;
    Ref(igNamedObject *o) : p(o) {}
    ~Ref() {
        igNamedObject *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct InsightRec { char pad[20]; beLayerInfoRam *cur; };
/* The receiver's _groups is a beLayerGroupList whose elements are scene-graph groups (igGroup:
 * name from igNamedObject, _childList at +28). */
#define GROUPS(i) ((beLayerGroupList *)(i)->_groups)
#define KIDS(g) ((igNodeList *)(g)->_childList)
#define SWT(a) ((igSwitch *)(a)->_layerSwt)
#define ELEM(l, i) ((igGroup *)((int *)(l)->_data)[i])
#define NAME(n) ((n)->_name ? (char *)(n)->_name : (char *)&DAT_004e0858[0])
#define LCOUNT(l) ((l) != 0 ? (l)->_count : 0)
#define RELEASE(o) if (o) { --(o)->_refCount; if (((unsigned long long)((long long)(int)(o)->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o); }
int Gap__Bec__beLayerCtl__vfunc_34(beLayerCtl *arg0, beLayerInfoRam *arg1, beMessengerWork *arg2) {
    unsigned v;
    beLayerInfo *msg = (beLayerInfo *)arg1->_parentInfo;
    v = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0035ca40(), (void *)arg2->_message);
    switch (v) {
    case 0: {
        beLayerInfo *srcl = (beLayerInfo *)((InsightRec *)FUN_00236f80(arg0->_insight, DAT_0058c790[0]))->cur->_parentInfo;
        if (arg0->_isOrdered == 0) {
            void *al = igObject_GetAllocator(arg0);
            al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587108[0]);
            igNamedObject *old = (igNamedObject *)arg0->_layerSwt;
            RELEASE(old)
            arg0->_layerSwt = (int)FUN_001968f0(al);
            igNamedObject_SetName((void *)arg0->_layerSwt, (char *)&DAT_0050ebd0[0]);
            igGroup *found = 0;
            int i;
            for (i = 0; i < LCOUNT(GROUPS(srcl)); i++) {
                igGroup *e = ELEM(GROUPS(srcl), i);
                int k = DAT_005618d8[0];
                if (k == ((NodeVt *)e)->v22()) found = e;
            }
            if (found == 0) return 0;
            igGroup *sw = 0;
            int j;
            for (j = 0; j < LCOUNT(KIDS(found)); j++) {
                igGroup *e2 = ELEM(KIDS(found), j);
                if (NAME(e2) != 0 && strcmp((char *)&DAT_0050ebe0[0], NAME(e2)) == 0) { sw = e2; break; }
            }
            if (sw != 0) FUN_001c5d10(sw, (void *)arg0->_layerSwt);
            else FUN_001c5d10(found, (void *)arg0->_layerSwt);
            arg0->_isOrdered = 1;
        }
        beLayerGroupList *ml = GROUPS(msg);
        if (ml == 0) return 1;
        int n;
        for (n = 0; n < ml->_count; n++) {
            void *al = igObject_GetAllocator(arg0);
            al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            Ref held((igNamedObject *)FUN_0019f1d0(al));
            igNamedObject_SetName(held.p, NAME(ELEM(ml, n)));
            FUN_001dc8e0((void *)arg0->_layerSwt, held.p);
        }
        void *al2 = igObject_GetAllocator(arg0);
        al2 = GPR_00554c14 ? al2 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        Ref held2((igNamedObject *)FUN_0019f1d0(al2));
        igNamedObject_SetName(held2.p, (char *)&DAT_0050ebf0[0]);
        FUN_001dc8e0((void *)arg0->_layerSwt, held2.p);
        int idx;
        igGroup *e3;
        igGroup *hit;
        char *nm;
        int q;
        igGroup *el;
        idx = 0;
        while (idx < LCOUNT(GROUPS(srcl))) {
            el = ELEM(GROUPS(srcl), idx);
            if (NAME(el) == 0) igNamedObject_SetName(el, (char *)&DAT_0050ebf0[0]);
            if (strcmp((char *)&DAT_0050ebf8[0], NAME(el)) == 0 || DAT_005618d8[0] == ((NodeVt *)el)->v22()) {
                idx += 1;
            } else {
                nm = NAME(el);
                hit = 0;
                for (q = 0; q < LCOUNT(KIDS(SWT(arg0))); q++) {
                    e3 = ELEM(KIDS(SWT(arg0)), q);
                    if (strcmp(nm, NAME(e3)) == 0) { hit = e3; break; }
                }
                if (hit != 0) FUN_001c5d10(hit, el);
                else FUN_001c5d10(held2.p, el);
                FUN_001c6050(srcl, el);
            }
        }
        beMessenger_AppendBool(arg0->_messenger, 1);
        break;
    }
    case 1: {
        if (beMessenger_GetStringCount(arg0->_messenger) < 2) return 0;
        char *a = beMessenger_GetString(arg0->_messenger, 0);
        char *b = beMessenger_GetString(arg0->_messenger, 1);
        if (strcmp(a, (char *)&DAT_0050ec08[0]) == 0) {
            switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0035c9e0(), b)) {
            case 0: FUN_001dc8d0((void *)arg0->_layerSwt); break;
            case 1: FUN_001dc870((void *)arg0->_layerSwt); break;
            case 2: break;
            }
        } else {
            int i;
            for (i = 0; i < LCOUNT(KIDS(SWT(arg0))); i++) {
                if (strcmp(NAME(ELEM(KIDS(SWT(arg0)), i)), a) == 0) {
                    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0035c9e0(), b)) {
                    case 0: FUN_001dc880((void *)arg0->_layerSwt, i); break;
                    case 1: FUN_001dc820((void *)arg0->_layerSwt, i); break;
                    case 2: {
                        igSwitch *l = SWT(arg0);
                        if ((1 << (i & 31)) & ((unsigned *)((igBitMask *)l->_childMask)->_data)[(unsigned)i >> 5]) FUN_001dc880(l, i);
                        else FUN_001dc820(l, i);
                        break; }
                    }
                    break;
                }
            }
        }
        break;
    }
    case 2: {
        if (beMessenger_GetStringCount(arg0->_messenger) <= 0) return 0;
        char *a = beMessenger_GetString(arg0->_messenger, 0);
        int i;
        for (i = 0; i < LCOUNT(KIDS(SWT(arg0))); i++) {
            if (strcmp(NAME(ELEM(KIDS(SWT(arg0)), i)), a) == 0) {
                FUN_001dc9a0((void *)arg0->_layerSwt, i);
                break;
            }
        }
        break;
    }
    case 3: {
        int i;
        for (i = 0; i < LCOUNT(KIDS(SWT(arg0))); i++)
            beMessenger_AppendString(arg0->_messenger, NAME(ELEM(KIDS(SWT(arg0)), i)));
        break;
    }
    case 4: {
        if (beMessenger_GetStringCount(arg0->_messenger) <= 0) return 0;
        char *a = beMessenger_GetString(arg0->_messenger, 0);
        int found = -1;
        int i;
        for (i = 0; i < LCOUNT(KIDS(SWT(arg0))); i++) {
            if (strcmp(NAME(ELEM(KIDS(SWT(arg0)), i)), a) == 0) { found = i; break; }
        }
        if (found != -1) {
            beMessenger_ClearObjects(arg0->_messenger);
            beMessenger_AppendObject(arg0->_messenger, ELEM(KIDS(SWT(arg0)), found));
            beMessenger_AppendBool(arg0->_messenger, 1);
        }
        break;
    }
    case 5:
    default:
        break;
    }
    return 1;
}

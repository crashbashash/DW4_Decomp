#include "dw4/reflected.h"
struct Prop { char pad16[16]; char *f16; };
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 88 */
struct Msg {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX();
};
extern "C" {
int FUN_002eb010(...);
int FUN_003a7d80(...);
int FUN_003a7a20(...);
void *beBaseInfoDataList_Create(...);
void *FUN_00352940(...);
float FUN_00123640(float, float);
int FUN_00192f50(...);
int FUN_00392d20(beModelCtrlMoveObject *, int, float, float, float);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(...);
void *StringPool_Intern(int, void *);
int beMessenger_GetObject(...);
int beMessenger_GetObjectCount(...);
int beMessenger_SendNamed(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
Prop *igProperty_FindByName(...);
int igStrCmp(void *, void *);
extern int DAT_004e0858[4];
extern int DAT_004e1098[4];
extern int DAT_0050ef18[4];
extern int DAT_0050ef60[4];
extern int DAT_0050f0b8[4];
extern int DAT_0050f0c8[4];
extern int DAT_0050f0d0[4];
extern int DAT_0050f0d8[4];
extern int DAT_0050f0e0[4];
extern int DAT_0050f0e8[4];
extern int DAT_0050f0f0[4];
extern int DAT_0050f0f8[4];
extern int DAT_0050f100[4];
extern int DAT_00585be0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_00588da0[4];
extern int DAT_00588dd8[4];
extern unsigned char GPR_00554c14;
unsigned char FUN_00393260(beModelCtrl *arg0, beBaseInfoRam *arg1, beModelCtrlInfoWork *arg2, Msg *arg3);
}


/* Owning references live across calls (retail exception table 0x543a8c): DataListRef is the ObjectRef copy at
 * 0x33e9c0 (slot 152), MoveRef the copy emitted behind this function at 0x393aa0 (slot 156).
 * matching construct: `volatile` pointer members keep the reference in its frame slot (retail stores and reloads
 * it around each use) and keep the allocator/`p` registers in retail's order. */
struct DataListRef {
    igObject *volatile p;
    DataListRef(igObject *x) { p = x; }
    ~DataListRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct MoveRef {
    igObject *volatile p;
    MoveRef() { p = 0; }
    ~MoveRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* matching construct: the code reads the refcount as a signed int, the header declares it unsigned */
#define RC(x) (*(int *)&(x)->_refCount)
#define MOVES(c) ((beModelCtrlMoveObject **)((beModelCtrlMoveObjectList *)(c)->_moveObjectList)->_data)
#define ALLOC(var, arg) { int base_ = igObject_GetAllocator(arg); if (GPR_00554c14 != 0) var = base_; else var = Memory_GetAllocatorBySelector(DAT_00587110[0]); }

/* matching construct: the data-list holder (slot 152) must sit below the move-object holder (slot 156), so it is
 * a local of a static inline member (allocated after the caller's); inline_depth(8) keeps its destructor inline.
 * al/p/old stay the caller's locals so the register order matches. Found by trial (no permuter). */
struct Locals {
    static inline void CreateDataList(beBaseInfoRam *arg1, int &al, igObject *&p, igObject *&old) {
        ALLOC(al, arg1);
        {
            DataListRef sp98((igObject *)beBaseInfoDataList_Create(al));
            p = sp98.p;
            if (p != 0) RC(p) = RC(p) + 1;
            old = (igObject *)arg1->_dataList;
            if (old != 0) {
                RC(old) = RC(old) - 1;
                if (((unsigned long long)((long long)RC(old) << 0x29) >> 0x29) == 0) igObject_Destroy(old);
            }
            arg1->_dataList = (int)p;
        }
    }
};
extern "C" unsigned char FUN_00393260(beModelCtrl *arg0, beBaseInfoRam *arg1, beModelCtrlInfoWork *arg2, Msg *arg3)
{
    float sp88[3];
    int k;
    if (!(FUN_003a7d80(arg1, &DAT_0050f0b8[0]) & 0xFF)) {
        FUN_003a7a20(arg1, &DAT_0050f0b8[0], 0);
    }
    if (arg2->_isPosLock != 0) {
        arg2->_isPosLock = 0;
        if (arg1->_dataList == 0) {
            int al;
            igObject *p, *old;
            Locals::CreateDataList(arg1, al, p, old);
        }
        FUN_00192f50(&sp88[0], &DAT_004e1098[0], igProperty_FindByName((igObject *)arg1->_dataList, DAT_00585be0[0], &DAT_0050ef60[0])->f16 + 32);
        {
            float r = FUN_00123640(sp88[0], sp88[2]);
            *(float *)&arg2->_direction[1] = r;
            *(float *)&arg2->_targetDirection[1] = r;
        }
    }
    if (((beModelCtrlMoveObjectList *)arg2->_moveObjectList)->_count == 0) {
        int al;
        igObject *o;
        MoveRef sp9C;
        ALLOC(al, arg0);
        o = sp9C.p;
        if (o != 0) { RC(o) = RC(o) - 1; if (((unsigned long long)((long long)RC(o) << 0x29) >> 0x29) == 0) igObject_Destroy(o); }
        sp9C.p = (igObject *)FUN_00352940(al);
        { igObject *q_ = sp9C.p; beModelCtrlMoveObjectList *l_ = *(beModelCtrlMoveObjectList *volatile *)&arg2->_moveObjectList; ObjectList_AppendRetained(l_, q_); }
        ALLOC(al, arg0);
        o = sp9C.p;
        if (o != 0) { RC(o) = RC(o) - 1; if (((unsigned long long)((long long)RC(o) << 0x29) >> 0x29) == 0) igObject_Destroy(o); }
        sp9C.p = (igObject *)FUN_00352940(al);
        { igObject *q_ = sp9C.p; beModelCtrlMoveObjectList *l_ = *(beModelCtrlMoveObjectList *volatile *)&arg2->_moveObjectList; ObjectList_AppendRetained(l_, q_); }
        ALLOC(al, arg0);
        o = sp9C.p;
        if (o != 0) { RC(o) = RC(o) - 1; if (((unsigned long long)((long long)RC(o) << 0x29) >> 0x29) == 0) igObject_Destroy(o); }
        sp9C.p = (igObject *)FUN_00352940(al);
        { igObject *q_ = sp9C.p; beModelCtrlMoveObjectList *l_ = *(beModelCtrlMoveObjectList *volatile *)&arg2->_moveObjectList; ObjectList_AppendRetained(l_, q_); }
        ALLOC(al, arg0);
        o = sp9C.p;
        if (o != 0) { RC(o) = RC(o) - 1; if (((unsigned long long)((long long)RC(o) << 0x29) >> 0x29) == 0) igObject_Destroy(o); }
        sp9C.p = (igObject *)FUN_00352940(al);
        { igObject *q_ = sp9C.p; beModelCtrlMoveObjectList *l_ = *(beModelCtrlMoveObjectList *volatile *)&arg2->_moveObjectList; ObjectList_AppendRetained(l_, q_); }
    }
    k = DAT_00588dd8[0];
    if (k == arg3->vX()) {
        char *nm;
        float fa, fb;
        beModelCtrlMOVE *m = (beModelCtrlMOVE *)arg3;
        nm = m->_name ? (char *)m->_name : (char *)&DAT_004e0858[0];
        fa = m->_value;
        fb = m->_frame;
        if (igStrCmp(nm, &DAT_0050f0c8[0]) == 0) {
            FUN_00392d20(MOVES(arg2)[2], 2, fa, fb, 0.0f);
        } else if (igStrCmp(nm, &DAT_0050f0d0[0]) == 0) {
            FUN_00392d20(MOVES(arg2)[2], 0, fa, fb, 0.0f);
        } else if (igStrCmp(nm, &DAT_0050f0d8[0]) == 0) {
            FUN_00392d20(MOVES(arg2)[2], 4, fa, fb, 0.0f);
        } else if (igStrCmp(nm, &DAT_0050f0e0[0]) == 0) {
            FUN_00392d20(MOVES(arg2)[2], 5, fa, fb, 0.0f);
        } else if (igStrCmp(nm, &DAT_0050f0e8[0]) == 0) {
            FUN_00392d20(MOVES(arg2)[1], 4, fa, fb, 0.0f);
        } else if (igStrCmp(nm, &DAT_0050f0f0[0]) == 0) {
            FUN_00392d20(MOVES(arg2)[1], 1, fa, fb, 0.0f);
        }
    } else {
        k = DAT_00588da0[0];
        if (k == arg3->vX()) {
            char *s;
            int idx, mode, off;
            unsigned char cb;
            float fa, fb, fc, fd, fe;
            beModelCtrlMoveObject *obj;
            beModelCtrlMOVEEX *m = (beModelCtrlMOVEEX *)arg3;
            s = m->_name ? (char *)m->_name : (char *)&DAT_004e0858[0];
            fa = m->_value;
            fb = m->_frame;
            fc = m->_playTime;
            cb = m->_isSeqStop;
            fd = m->_stopValue;
            fe = m->_stopFrame;
            off = (s[0] == 0x54) ? 0 : 2;
            idx = s[1] - 0x58 + off;
            switch (s[3]) {
            case 0x41: mode = 0; break;
            case 0x44: mode = 2; break;
            case 0x54: mode = 4; break;
            }
            if (s[2] == 0x4d) mode += 1;
            obj = MOVES(arg2)[idx];
            FUN_00392d20(obj, mode, fa, fb, fc);
            obj->_isSeqStop = cb;
            obj->_stopValue = fd;
            obj->_stopFrame = fe;
        } else {
            char *s;
            beModelCtrlMOVERL *m = (beModelCtrlMOVERL *)arg3;
            s = m->_name ? (char *)m->_name : (char *)&DAT_004e0858[0];
            if (igStrCmp(s, &DAT_0050f0f8[0]) == 0) {
                igObject *ob, *old;
                beMessenger_SendNamed(arg0->_messenger, &DAT_0050ef18[0], (char *)m->_modelName, arg1->_ramNo, &DAT_0050f100[0]);
                if (beMessenger_GetObjectCount(arg0->_messenger) == 1) {
                    arg2->_isPosLock = 1;
                    ob = (igObject *)beMessenger_GetObject(arg0->_messenger, 0);
                    if (ob != 0) RC(ob) = RC(ob) + 1;
                    old = (igObject *)arg2->_posLockTrc;
                    if (old != 0) {
                        RC(old) = RC(old) - 1;
                        if (((unsigned long long)((long long)RC(old) << 0x29) >> 0x29) == 0) igObject_Destroy(old);
                    }
                    arg2->_posLockTrc = (int)ob;
                }
            } else {
                char *n1, *n2;
                char *old1, *old2;
                n1 = (char *)m->_modelName;
                if (DAT_00586f20[0] == 0) {
                    int p = FUN_002eb010(16);
                    if (p != 0) p = StringPool_Construct(p);
                    DAT_00586f20[0] = p;
                }
                n1 = (char *)StringPool_Intern(DAT_00586f20[0], n1);
                old1 = (char *)arg2->_posLockModelName;
                if (old1 != 0) {
                    int *h = (int *)(old1 - 8);
                    int r = *(int *)(old1 - 4) - 1;
                    *(int *)(old1 - 4) = r;
                    if (r == 0) StringChunk_ReleaseHeader(*h, h);
                }
                arg2->_posLockModelName = (int)n1;
                n2 = (char *)m->_boneName;
                if (DAT_00586f20[0] == 0) {
                    int p = FUN_002eb010(16);
                    if (p != 0) p = StringPool_Construct(p);
                    DAT_00586f20[0] = p;
                }
                n2 = (char *)StringPool_Intern(DAT_00586f20[0], n2);
                old2 = (char *)arg2->_posLockBoneName;
                if (old2 != 0) {
                    int *h = (int *)(old2 - 8);
                    int r = *(int *)(old2 - 4) - 1;
                    *(int *)(old2 - 4) = r;
                    if (r == 0) StringChunk_ReleaseHeader(*h, h);
                }
                arg2->_posLockBoneName = (int)n2;
                arg2->_isPosLock = 1;
            }
        }
    }
    return 1;
}

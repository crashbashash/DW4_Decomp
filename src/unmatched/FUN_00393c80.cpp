#include "dw4/reflected.h"
/* The smart-pointer slots RP are destructor holders. */
extern "C" {
int FUN_001cafc0(igStringRefList *, int *, int);
int FUN_001ca620(igStringRefList *, int *);
void *FUN_002b90e0(int);
void *FUN_002caa70(int);
int FUN_002eb010(int);
int List_Resize(igIntList *, int, int);
int Memory_GetAllocatorBySelector(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int igObject_Destroy(igObject *);
int igObject_GetAllocator(int);
extern int DAT_004c8fa8[4];
extern int DAT_004c8fb0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
struct RPA { igObject *p; RPA() { p = 0; } ~RPA() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };
struct RPB { igObject *p; RPB() { p = 0; } ~RPB() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };
/* Interned-string holder: count at p[-1], header at p[-2]. */
struct StringRef { int p; StringRef(int x) { p = x; } ~StringRef() { int s = p; if (s != 0) { int *hd = (int *)(s - 8); int c = *(int *)(s - 4) - 1; *(int *)(s - 4) = c; if (c == 0) StringChunk_ReleaseHeader(*hd, hd); } } };

extern "C" void FUN_00393c80(int a0, int a1, beModelCtrlInfoWork *a2, int name, int val) {
    igStringRefList *l36, *l40;
    igIntList *l44;
    int al0, al, v, idx, c, n, k;
    igObject *o, *s0;
    int *hd, *slot;
    int s, old;

    l36 = (igStringRefList *)a2->_labelSeqList;
    l40 = (igStringRefList *)a2->_labelNameList;
    l44 = (igIntList *)a2->_labelOffsetList;
    if (l36 == 0) {
        RPB sp9C;
        RPA sp98;
        al0 = igObject_GetAllocator(a0);
        if (GPR_00554c14 != 0) {
            al = al0;
        } else {
            al = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        o = sp9C.p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
        sp9C.p = (igObject *)FUN_002b90e0(al);
        s0 = sp9C.p;
        if (s0 != 0) s0->_refCount = s0->_refCount + 1;
        o = (igObject *)a2->_labelSeqList;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
        a2->_labelSeqList = (int)s0;
        l36 = (igStringRefList *)sp9C.p;

        al0 = igObject_GetAllocator(a0);
        if (GPR_00554c14 != 0) {
            al = al0;
        } else {
            al = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        o = sp9C.p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
        sp9C.p = (igObject *)FUN_002b90e0(al);
        s0 = sp9C.p;
        if (s0 != 0) s0->_refCount = s0->_refCount + 1;
        o = (igObject *)a2->_labelNameList;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
        a2->_labelNameList = (int)s0;
        l40 = (igStringRefList *)sp9C.p;

        al0 = igObject_GetAllocator(a0);
        if (GPR_00554c14 != 0) {
            al = al0;
        } else {
            al = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        o = sp98.p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
        sp98.p = (igObject *)FUN_002caa70(al);
        s0 = sp98.p;
        if (s0 != 0) s0->_refCount = s0->_refCount + 1;
        o = (igObject *)a2->_labelOffsetList;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
        a2->_labelOffsetList = (int)s0;
        l44 = (igIntList *)sp98.p;
    }
    if (name == 0) {
        v = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            c = FUN_002eb010(16);
            if (c != 0) c = StringPool_Construct(c);
            DAT_00586f20[0] = c;
        }
        v = StringPool_Intern(DAT_00586f20[0], name);
    }
    {
        StringRef sp94(v);
        idx = FUN_001cafc0(l36, &sp94.p, 0);
    }
    if (idx != -1) {
        if (name == 0) {
            v = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                c = FUN_002eb010(16);
                if (c != 0) c = StringPool_Construct(c);
                DAT_00586f20[0] = c;
            }
            v = StringPool_Intern(DAT_00586f20[0], name);
        }
        {
        StringRef sp90(v);
        n = *(volatile int *)&l36->_count;
        if (n != 0 && idx >= 0 && idx < n) {
            slot = &((int *)l36->_data)[idx];
            s = sp90.p;
            if (s != 0) *(int *)(s - 4) = *(int *)(s - 4) + 1;
            old = *slot;
            if (old != 0) {
                hd = (int *)(old - 8);
                c = *(int *)(old - 4) - 1;
                *(int *)(old - 4) = c;
                if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
            }
            *slot = sp90.p;
        }
        }
        if (val == 0) {
            v = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                c = FUN_002eb010(16);
                if (c != 0) c = StringPool_Construct(c);
                DAT_00586f20[0] = c;
            }
            v = StringPool_Intern(DAT_00586f20[0], val);
        }
        {
        StringRef sp8C(v);
        n = *(volatile int *)&l40->_count;
        if (n != 0 && idx >= 0 && idx < n) {
            slot = &((int *)l40->_data)[idx];
            s = sp8C.p;
            if (s != 0) *(int *)(s - 4) = *(int *)(s - 4) + 1;
            old = *slot;
            if (old != 0) {
                hd = (int *)(old - 8);
                c = *(int *)(old - 4) - 1;
                *(int *)(old - 4) = c;
                if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
            }
            *slot = sp8C.p;
        }
        }
        n = *(volatile int *)&l44->_count;
        if (n != 0 && idx >= 0 && idx < n) {
            ((int *)l44->_data)[idx] = DAT_004c8fa8[0];
        }
    } else {
        if (name == 0) {
            v = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                c = FUN_002eb010(16);
                if (c != 0) c = StringPool_Construct(c);
                DAT_00586f20[0] = c;
            }
            v = StringPool_Intern(DAT_00586f20[0], name);
        }
        {
            StringRef sp88(v);
            FUN_001ca620(l36, &sp88.p);
        }
        if (val == 0) {
            v = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                c = FUN_002eb010(16);
                if (c != 0) c = StringPool_Construct(c);
                DAT_00586f20[0] = c;
            }
            v = StringPool_Intern(DAT_00586f20[0], val);
        }
        {
            StringRef sp84(v);
            FUN_001ca620(l40, &sp84.p);
        }
        k = *(volatile int *)&l44->_count;
        if (k < l44->_capacity) {
            *(volatile int *)&l44->_count = *(volatile int *)&l44->_count + 1;
        } else {
            List_Resize(l44, k + 1, 4);
        }
        ((int *)l44->_data)[k] = DAT_004c8fb0[0];
    }
}

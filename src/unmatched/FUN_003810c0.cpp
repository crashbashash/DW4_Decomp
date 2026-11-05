#include "dw4/reflected.h"
extern "C" {
int igInsightCore_AddInfo(...);
int FUN_002eb010(...);
int igObject_IsKindOf(...);
int FUN_003092f0(...);
int FUN_00309740(...);
int FUN_00309750(...);
int List_InsertWords(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_004e0858[4];
extern int DAT_0050e6c8[4];
extern int DAT_005615e0[4];
extern int DAT_00586dd0[4];
extern int DAT_00586f20[4];
extern int DAT_00587108[4];
extern int DAT_00587110[4];
extern int DAT_005891c0[4];
extern unsigned char GPR_00554c14;
int FUN_003810c0(beFileListInfoManager *arg0, igStringRefList *arg1);
}
struct VO {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int vX();
};
/* Owning stack reference to a pooled string token (count at p[-1], chunk header at p[-2]); the out-of-line copy the
 * exception table names is retail 0x00130720 (duplicate __dt__9StringRefFv). */
struct StringRef { int *p; StringRef() {} StringRef(const StringRef &o) : p(o.p) {} ~StringRef() { int *s = p; if (s != 0) { int *h = s - 2; int r = s[-1] - 1; s[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } } };
/* Returns its pooled string through the hidden result pointer (a0), so the copy is owned from the call on. */
extern "C" StringRef StringList_CopyRetained(igStringRefList *list, int index);
/* A read-info insert passes the info through a one-word stack temporary whose address List_InsertWords receives. */
struct InfoWord { int *p; InfoWord(int *x) : p(x) {} };
struct ReadInfoInsert { static inline void go(beFileListInfoManager *m, int idx, const InfoWord &w) {
    const InfoWord *pw = (const InfoWord *)(int)&w; /* matching construct: manual - the int round trip keeps the temporary addressed through memory */
    int *v = pw->p;
    int lst = m->_readInfoList;
    if (v != 0) v[1] = v[1] + 1;
    List_InsertWords(lst, idx, 1, pw);
} };

int FUN_003810c0(beFileListInfoManager *arg0, igStringRefList *arg1) {
    igDirectory *d;
    igInfoList *kids;
    int off;
    int i;
    int idx;
    int j;
    VO *o;
    int t;
    int *nm;
    igDirectoryList *dirs;
    int ld;
    int cn;
    cn = *(volatile int *)&arg1->_count;
    ld = *(volatile int *)&arg0->_loaded;
    int rr = ld < cn;
    if (rr == 0) {
        return 1;
    }
    dirs = (igDirectoryList *)arg0->_dirList;
    if (dirs->_count != 0) {
        d = ((igDirectory **)dirs->_data)[0];
        if (FUN_00309740(DAT_00586dd0[0], d) != 0) {
            if ((char *)&DAT_0050e6c8[0] == 0) {
                nm = 0;
            } else {
                if (DAT_00586f20[0] == 0) {
                    int pv = FUN_002eb010(0x10);
                    if (pv != 0) { pv = StringPool_Construct(pv); }
                    DAT_00586f20[0] = pv;
                }
                nm = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050e6c8[0]);
            }
            StringRef sp172;
            sp172.p = nm;
            kids = (igInfoList *)d->_infoList;
            i = 0;
            if (i < kids->_count) {
                off = 0;
                do {
                    t = DAT_005891c0[0];
                    o = *(VO **)(kids->_data + off);
                    if (t == o->vX()) {
                        igInsightCore_AddInfo(arg0->_insight, o);
                    } else {
                        t = DAT_005615e0[0];
                        if (t == o->vX()) {
                            igSceneInfo *a;
                            if (o != 0 && igObject_IsKindOf(o, DAT_005615e0[0]) != 0) {
                                a = (igSceneInfo *)o;
                            } else {
                                a = 0;
                            }
                            if (a->_cameras != 0 && ((igObjectList *)a->_cameras)->_count > 0) {
                                ObjectList_AppendRetained(arg0->_importantInfoList, o);
                            } else {
                                int *s0 = (int *)((igInfo *)a->_sceneGraph)->_name;
                                int *s = s0 ? s0 : (int *)&DAT_004e0858[0];
                                if (s == sp172.p) {
                                    ObjectList_AppendRetained(arg0->_importantInfoList, o);
                                } else {
                                    ObjectList_AppendRetained(arg0->_infoList, o);
                                }
                            }
                        } else {
                            idx = -1;
                            j = 0;
                            if (j < ((igInfoList *)arg0->_readInfoList)->_count) {
                                do {
                                    int u = DAT_005615e0[0];
                                    if (u == o->vX()) {
                                        idx = j;
                                        break;
                                    }
                                    j += 1;
                                } while (j < ((igInfoList *)arg0->_readInfoList)->_count);
                            }
                            if (idx == -1) {
                                ObjectList_AppendRetained(arg0->_readInfoList, o);
                            } else {
                                ReadInfoInsert::go(arg0, idx, InfoWord((int *)o));
                            }
                        }
                    }
                    i += 1;
                    off += 4;
                } while (i < kids->_count);
            }
            FUN_00309750(DAT_00586dd0[0], d->_name);
            {
                igDirectoryList *l = (igDirectoryList *)arg0->_dirList;
                int n = l->_count;
                int a;
                int m;
                int j;
                for (a = 0; a < n; a++) {
                    igObject *e = ((igObject **)l->_data)[a];
                    if (e != 0) {
                        e->_refCount = e->_refCount - 1;
                        if (((unsigned long long)((long long)(int)e->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(e);
                    }
                }
                m = l->_count;
                for (j = 0; j < m; j++) {
                    ((int *)l->_data)[j] = 0;
                }
                l->_count = 0;
            }
            arg0->_loaded = arg0->_loaded + 1;
        }
    } else {
        int cnt = arg0->_onetimeCount;
        if (cnt > -1) {
            if (cnt == 2) {
                igResource *sy;
                int a;
                int base = igObject_GetAllocator();
                igObject *old;
                if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587108[0]); }
                sy = (igResource *)DAT_00586dd0[0];
                if (a != 0) ((igObject *)a)->_refCount = ((igObject *)a)->_refCount + 1;
                old = (igObject *)sy->_objectMemoryPool;
                if (old != 0) {
                    old->_refCount = old->_refCount - 1;
                    if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old);
                }
                sy->_objectMemoryPool = a;
                {
                igResource *sy2;
                int a2;
                int base2 = igObject_GetAllocator(arg0);
                igObject *old2;
                if (GPR_00554c14 != 0) { a2 = base2; } else { a2 = Memory_GetAllocatorBySelector(DAT_00587108[0]); }
                sy2 = (igResource *)DAT_00586dd0[0];
                if (a2 != 0) ((igObject *)a2)->_refCount = ((igObject *)a2)->_refCount + 1;
                old2 = (igObject *)sy2->_dataMemoryPool;
                if (old2 != 0) {
                    old2->_refCount = old2->_refCount - 1;
                    if (((unsigned long long)((long long)(int)old2->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old2);
                }
                sy2->_dataMemoryPool = a2;
                }
            } else if (cnt == 0) {
                igResource *sy;
                int a;
                int base = igObject_GetAllocator();
                igObject *old;
                if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                sy = (igResource *)DAT_00586dd0[0];
                if (a != 0) ((igObject *)a)->_refCount = ((igObject *)a)->_refCount + 1;
                old = (igObject *)sy->_objectMemoryPool;
                if (old != 0) {
                    old->_refCount = old->_refCount - 1;
                    if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old);
                }
                sy->_objectMemoryPool = a;
                {
                igResource *sy2;
                int a2;
                int base2 = igObject_GetAllocator(arg0);
                igObject *old2;
                if (GPR_00554c14 != 0) { a2 = base2; } else { a2 = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                sy2 = (igResource *)DAT_00586dd0[0];
                if (a2 != 0) ((igObject *)a2)->_refCount = ((igObject *)a2)->_refCount + 1;
                old2 = (igObject *)sy2->_dataMemoryPool;
                if (old2 != 0) {
                    old2->_refCount = old2->_refCount - 1;
                    if (((unsigned long long)((long long)(int)old2->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old2);
                }
                sy2->_dataMemoryPool = a2;
                }
            }
            arg0->_onetimeCount = arg0->_onetimeCount - 1;
        }
        StringRef sp168(StringList_CopyRetained(arg1, arg0->_loaded));
        ObjectList_AppendRetained(arg0->_dirList, FUN_003092f0(DAT_00586dd0[0], sp168.p));
    }
    return 0;
}

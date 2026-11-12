#include "dw4/igSmartPointer.h"
extern "C" int sprintf(...);
extern "C" int strlen(...);
extern "C" int FUN_001c5d10(...);
extern "C" int FUN_00236f80(...);
extern "C" int igInsightCore_AddInfo(...);
extern "C" int FUN_002eb010(...);
extern "C" int igObject_IsKindOf(...);
extern "C" int FUN_00308c80(...);
extern "C" int FUN_00308e00(...);
extern "C" int FUN_003092f0(...);
extern "C" int FUN_00309740(...);
extern "C" int FUN_00309750(...);
extern "C" int FUN_0030b3c0(...);
extern "C" int FUN_0030b460(...);
extern "C" int FUN_0030bbf0(...);
extern "C" int FUN_003810c0(...);
extern "C" int FUN_003817d0(...);
extern "C" int beLua__RunNamedChunk(...);
extern "C" int FUN_0038a2d0(...);
extern "C" int beLoadingNode_Lock(...);
extern "C" int beLoadingNode_IsPastPlayLimit(...);
extern "C" int List_RemoveWordAt(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" void StringChunk_ReleaseHeader(int, void *);
extern "C" int StringPool_Construct(...);
extern "C" int StringPool_Intern(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" int beMessenger_GetObject(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SendGroup(...);
extern int DAT_004c22f0[4];
extern int DAT_004e0858[4];
extern int DAT_0050e560[4];
extern int DAT_0050e570[4];
extern int DAT_0050e578[4];
extern int DAT_0050e580[4];
extern int DAT_0050e590[4];
extern int DAT_0050e5a0[4];
extern int DAT_0050e5b8[4];
extern int DAT_0050e5c0[4];
extern int DAT_0050e5c8[4];
extern int DAT_0050e5d8[4];
extern int DAT_0050e5e8[4];
extern int DAT_0050e5f0[4];
extern int DAT_0050e600[4];
extern int DAT_0050e610[4];
extern int DAT_0050e620[4];
extern int DAT_0050e628[4];
extern int DAT_0050e630[4];
extern int DAT_0050e638[4];
extern int DAT_0050e640[4];
extern int DAT_0050e650[4];
extern int DAT_0050e658[4];
extern int DAT_0050e668[4];
extern int DAT_0050e678[4];
extern int DAT_0050e688[4];
extern int DAT_0050e698[4];
extern int DAT_0050e6a8[4];
extern int DAT_0050e6b8[4];
extern int DAT_005615e0[4];
extern int DAT_00586dd0[4];
extern int DAT_00586f20[4];
extern int DAT_005886e8[4];
extern int DAT_00589208[4];

struct VO {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual int vX();
};

/* Retained interned-string share. The stage-name object share (cases 0 and 1) and the interned
 * file-name shares (cases 1, 102, 9) are RAII locals. The copy constructor takes the extra share
 * that StringList_AppendRetained hands to the list. */
struct StringRef {
    char *p;
    StringRef(char *s) : p(s) {}
    StringRef(const StringRef &o) : p(o.p) { if (p != 0) ((int *)p)[-1] = ((int *)p)[-1] + 1; }
    ~StringRef() { char *s = p; if (s != 0) { int *hd = (int *)s - 2; int cnt = ((int *)s)[-1] - 1; ((int *)s)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
};
/* Retained share of the stage-name string object. */

extern "C" int StringList_AppendRetained(void *, const StringRef &);

#define EMPTY ((int *)&DAT_004e0858[0])
#define REL_STR(p) { \
    int *q = (int *)(p); \
    if (q != 0) { \
        int *h = q - 2; \
        int r = q[-1] - 1; \
        q[-1] = r; \
        if (r == 0) StringChunk_ReleaseHeader(*h, h); \
    } }
#define REL_OBJ(o) { \
    int *q = (int *)(o); \
    if (q != 0) { \
        ((igObject *)q)->_refCount = (int)((igObject *)q)->_refCount - 1; \
        if (((unsigned long long)((long long)(int)((igObject *)q)->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(q); \
    } }
#define POOL() { \
    if (DAT_00586f20[0] == 0) { \
        int pv = FUN_002eb010(0x10); \
        if (pv != 0) { pv = StringPool_Construct(pv); } \
        DAT_00586f20[0] = pv; \
    } }
#define CLEAR(T, src) { \
    T *l = (T *)(src); \
    int n = l->_count; \
    int i; \
    int m; \
    int j; \
    int *o; \
    for (i = 0; i < n; i++) { \
        o = ((int **)l->_data)[i]; \
        REL_OBJ(o) \
    } \
    m = l->_count; \
    for (j = 0; j < m; j++) { \
        ((int *)l->_data)[j] = 0; \
    } \
    l->_count = 0; }

extern "C" void Gap__Bec__beFileListInfoManager__vfunc_27(beFileListInfoManager *arg0) {
    beSystem *sys;
    int spC0[8];
    int spA0[8];
    int sp80[8];

    sys = (beSystem *)arg0->_system;
    if (sys->_execDvdErr <= 0) {
        switch (arg0->_proc) {
        default:
            arg0->_proc = -1;
            break;
        case -1:
            break;
        case 0: {
            int *t0;
            int *v;
            int *s1;
            int x0;
            beFileListInfo *info;
            beSystem *s0;
            if (((igInfoList *)arg0->_infoList)->_count <= 0) {
                arg0->_proc = -1;
                break;
            }
            sys->_isActive = 0;
            info = ((beFileListInfo **)((igInfoList *)arg0->_infoList)->_data)[0];
            s1 = (int *)info->_name;
            if (s1 != 0) { v = s1; } else { v = EMPTY; }
            if (v != 0) {
                int *nw;
                int *old;
                s1 = s1 ? s1 : EMPTY;
                s0 = (beSystem *)arg0->_system;
                POOL()
                nw = (int *)StringPool_Intern(DAT_00586f20[0], s1);
                old = (int *)s0->_stageName;
                REL_STR(old)
                s0->_stageName = (int)nw;
            } else {
                int *old;
                int *nw;
                s0 = (beSystem *)arg0->_system;
                POOL()
                nw = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050e560[0]);
                old = (int *)s0->_stageName;
                REL_STR(old)
                s0->_stageName = (int)nw;
            }
            FUN_00308c80(DAT_00586dd0[0]);
            {
            igSmartPointer<igObject> stageObj((igObject *)((beSystem *)arg0->_system)->_globalStrObj, kRetainReference);
            FUN_0030b3c0(stageObj.p, ((beSystem *)arg0->_system)->_stageName);
            FUN_0030bbf0(stageObj.p, 0, 2);
            t0 = (int *)stageObj.p; FUN_0030b460(t0, &DAT_0050e570[0], 0, strlen(&DAT_0050e570[0]));
            { int *ta = (int *)stageObj.p; int xa = ta[3]; FUN_0030b460(ta, &DAT_0050e578[0], xa, strlen(&DAT_0050e578[0])); }
            t0 = (int *)stageObj.p; FUN_0030b460(t0, &DAT_0050e580[0], 0, strlen(&DAT_0050e580[0]));
            {
                int a1 = ((int *)stageObj.p)[2];
                int r;
                int a2;
                if (a1 == 0) { a2 = DAT_004c22f0[0]; } else { a2 = a1; }
                r = FUN_003092f0(DAT_00586dd0[0], a2);
                ObjectList_AppendRetained(arg0->_dirList, r);
            }
            }
            arg0->_proc = 1;
            break;
        }
        case 1: {
            unsigned char found;
            igObjectList *s4;
            int i;
            int idx;
            int k;
            int *s1;
            int j;
            igObjectList *s5;
            s1 = ((int **)((igDirectoryList *)arg0->_dirList)->_data)[0];
            if ((FUN_00309740(DAT_00586dd0[0], s1) & 0xFF) == 0) {
                break;
            }
            s4 = (igObjectList *)s1[7];
            for (k = 0; k < s4->_count; k++) {
                igInsightCore_AddInfo(arg0->_insight, ((int *)s4->_data)[k]);
            }
            FUN_00309750(DAT_00586dd0[0], s1[5]);
            CLEAR(igDirectoryList, arg0->_dirList)
            s5 = (igObjectList *)((beFileListInfo **)((igInfoList *)arg0->_infoList)->_data)[0]->_fnames;
            if (arg0->_isReadOnetime == 0) {
                int *v;
                if ((char *)&DAT_0050e590[0] == 0) { v = 0; } else {
                    POOL()
                    v = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050e590[0]);
                }
                StringRef firstName((char *)v);
                StringList_AppendRetained((void *)arg0->_fnames, StringRef(firstName));
                if ((char *)&DAT_0050e5a0[0] == 0) { v = 0; } else {
                    POOL()
                    v = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050e5a0[0]);
                }
                StringRef secondName((char *)v);
                StringList_AppendRetained((void *)arg0->_fnames, StringRef(secondName));
                arg0->_isReadOnetime = 1;
                arg0->_onetimeCount = 2;
            }
            igSmartPointer<igObject> stageObj((igObject *)((beSystem *)arg0->_system)->_globalStrObj, kRetainReference);
            found = 0;
            i = 0;
            if (0 < s5->_count) {
                do {
                    unsigned int lim;
                    int *tmp;
                    int *s4n;
                    int *base;
                    s4n = (int *)((beFileListInfo **)s5->_data)[i]->_name;
                    s4n = s4n ? s4n : EMPTY;
                    if (s4n == 0) { tmp = 0; } else {
                        POOL()
                        tmp = (int *)StringPool_Intern(DAT_00586f20[0], s4n);
                    }
                    {
                    StringRef entryName((char *)tmp);
                    idx = -1;
                    FUN_0030b3c0(stageObj.p, entryName.p);
                    {
                        volatile int *t = (int *)stageObj.p;
                        j = 0;
                        if ((unsigned int)j < (unsigned int)t[3]) {
                            do {
                                base = (int *)t[2];
                                if (base == 0) { base = (int *)DAT_004c22f0[0]; }
                                if (*((char *)base + (int)j) == 0x2F) {
                                    idx = j;
                                    break;
                                }
                                j += 1;
                            } while ((unsigned int)j < (unsigned int)t[3]);
                        }
                    }
                    if (idx == -1) { idx = 0; }
                    { int *t10 = (int *)entryName.p;
                    if (((char *)t10)[idx + 1] == 0x73) {
                        StringList_AppendRetained((void *)arg0->_fnames, StringRef(entryName));
                        {
                            int *o = ((int **)s5->_data)[i];
                            found = 1;
                            REL_OBJ(o)
                        }
                        List_RemoveWordAt(s5, i);
                        i -= 1;
                        ((int *)s5->_data)[s5->_count] = 0;
                    } }
                    }
                    i += 1;
                } while (i < s5->_count);
            }
            if (found) { arg0->_proc = 100; } else { arg0->_proc = 102; }
            break;
        }
        case 100: {
            igStringRefList *s6;
            int n;
            int k;
            if (FUN_003810c0(arg0, arg0->_fnames) == 0) {
                break;
            }
            FUN_003817d0(arg0);
            CLEAR(igInfoList, arg0->_readInfoList)
            arg0->_loaded = 0;
            s6 = (igStringRefList *)arg0->_fnames;
            n = s6->_count;
            k = 0;
            if (0 < n) {
                int **slot;
                int *old;
                int *nw;
                int off;
                off = 0;
                do {
                    slot = (int **)((char *)s6->_data + off);
                    POOL()
                    nw = (int *)StringPool_Intern(DAT_00586f20[0], 0);
                    old = *slot;
                    REL_STR(old)
                    k += 1;
                    *slot = nw;
                    off += 4;
                } while (k < n);
            }
            s6->_count = 0;
            beMessenger_SendGroup(arg0->_messenger, &DAT_0050e5b8[0], &DAT_0050e5c0[0]);
            if (beMessenger_GetBool(arg0->_messenger, 0) != 0) {
                arg0->_proc = 0x65;
                beMessenger_SendGroup(arg0->_messenger, &DAT_0050e5b8[0], &DAT_0050e5c8[0]);
                break;
            }
            arg0->_proc = 0x66;
            break;
        }
        case 101:
            beMessenger_SendGroup(arg0->_messenger, &DAT_0050e5b8[0], &DAT_0050e5d8[0]);
            if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) == 1) {
                arg0->_proc = 0x66;
                break;
            }
            break;
        case 102: {
            igObjectList *s3;
            int i;
            s3 = (igObjectList *)((beFileListInfo **)((igInfoList *)arg0->_infoList)->_data)[0]->_fnames;
            i = 0;
            if (0 < s3->_count) {
                do {
                    int *s4n;
                    int *tmp;
                    s4n = (int *)((beFileListInfo **)s3->_data)[i]->_name;
                    s4n = s4n ? s4n : EMPTY;
                    if (s4n == 0) { tmp = 0; } else {
                        POOL()
                        tmp = (int *)StringPool_Intern(DAT_00586f20[0], s4n);
                    }
                    {
                    StringRef entryName((char *)tmp);
                    StringList_AppendRetained((void *)arg0->_fnames, StringRef(entryName));
                    }
                    i += 1;
                } while (i < s3->_count);
            }
            arg0->_proc = 2;
            break;
        }
        case 2:
            if (FUN_003810c0(arg0, arg0->_fnames) != 0) {
                arg0->_loaded = 0;
                arg0->_proc = 3;
                break;
            }
            break;
        case 3: {
            int s0 = FUN_00236f80(arg0->_insight, DAT_00589208[0]);
            if (s0 != 0) {
                sprintf(spC0, &DAT_0050e5e8[0], ((beSystem *)arg0->_system)->_stageName);
                FUN_0038a2d0(s0);
                beLua__RunNamedChunk(s0, &DAT_0050e5f0[0], spC0);
                beLua__RunNamedChunk(s0, &DAT_0050e600[0], spC0);
            }
            arg0->_proc = 4;
            break;
        }
        case 4: {
            int cnt;
            int s1;
            int s0;
            int *lst;
            int li;
            unsigned char s3;
            int v1;
            s0 = sys->_readFileList;
            lst = (int *)*(int *)(*(int *)(*(int *)(arg0->_sceneInfoManager + 20) + 12) + 28);
            s1 = 0;
            if (lst != 0) { cnt = ((igInfoList *)lst)->_count; } else { cnt = 0; }
            li = (int)lst;
            if (cnt > 0) {
                igInfoList *il = (igInfoList *)li; int *ob = *(int **)il->_data;
                if (ob != 0 && igObject_IsKindOf(ob, DAT_005886e8[0]) != 0) { s1 = (int)ob; } else { s1 = 0; }
                if (s1 != 0) { s3 = beLoadingNode_IsPastPlayLimit(s1) & 0xFF; } else { s3 = 1; }
            } else {
                s3 = 1;
            }
            v1 = FUN_003810c0(arg0, s0) & 0xFF;
            if (s3 && v1) {
                arg0->_loaded = 0;
                arg0->_proc = 0x14;
                if (s1 != 0) {
                    beLoadingNode_Lock(s1);
                }
                while (((igInfoList *)arg0->_importantInfoList)->_count > 0) {
                    igInfoList *l;
                    int *o;
                    l = (igInfoList *)arg0->_importantInfoList;
                    ObjectList_AppendRetained(arg0->_readInfoList, *(int *)l->_data);
                    l = (igInfoList *)arg0->_importantInfoList;
                    o = *(int **)l->_data;
                    REL_OBJ(o)
                    List_RemoveWordAt(l, 0);
                    ((int *)l->_data)[l->_count] = 0;
                }
                FUN_00308e00(DAT_00586dd0[0]);
                break;
            }
            break;
        }
        case 20:
            arg0->_proc = 0x15;
            break;
        case 21:
            arg0->_proc = 5;
            break;
        case 5:
            if (FUN_003817d0(arg0) != 0) {
                CLEAR(igInfoList, arg0->_readInfoList)
                arg0->_proc = 6;
                break;
            }
            break;
        case 6: {
            int i;
            igInfoList *il;
            beMessenger_SendGroup(arg0->_messenger, &DAT_0050e610[0], &DAT_0050e620[0]);
            if (beMessenger_GetBoolCount(arg0->_messenger) > 0) {
                beMessenger_SelectGroup(arg0->_messenger, &DAT_0050e610[0]);
                beMessenger_AppendString(arg0->_messenger, &DAT_0050e628[0]);
                beMessenger_AppendString(arg0->_messenger, &DAT_0050e630[0]);
                beMessenger_DispatchSelected(arg0->_messenger, &DAT_0050e638[0]);
                if (((igInfoList *)arg0->_infoList)->_count > 1) {
                    for (i = 1; i < ((igInfoList *)arg0->_infoList)->_count; i++) {
                        int *obj;
                        int *s4;
                        int s3v;
                        int *nm;
                        s3v = DAT_005615e0[0];
                        s4 = ((int **)((igInfoList *)arg0->_infoList)->_data)[i];
                        if (s3v == ((VO *)s4)->vX()) {
                            obj = (int *)s4[5];
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_0050e610[0]);
                            nm = (int *)obj[2];
                            nm = nm ? nm : EMPTY;
                            beMessenger_AppendString(arg0->_messenger, nm);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0050e640[0]);
                            if (beMessenger_GetObjectCount(arg0->_messenger) > 0) {
                                FUN_001c5d10(beMessenger_GetObject(arg0->_messenger, 0), obj);
                            }
                        }
                    }
                }
            }
            arg0->_proc = 7;
            break;
        }
        case 7: {
            int s0;
            beMessenger_SendGroup(arg0->_messenger, &DAT_0050e650[0], &DAT_0050e658[0]);
            s0 = FUN_00236f80(arg0->_insight, DAT_00589208[0]);
            if (s0 != 0) {
                sprintf(spA0, &DAT_0050e5e8[0], ((beSystem *)arg0->_system)->_stageName);
                beLua__RunNamedChunk(s0, &DAT_0050e668[0], spA0);
            }
            arg0->_proc = 8;
            break;
        }
        case 8:
            sys->_isActive = 1;
            arg0->_proc = 9;
            break;
        case 9: {
            int s0 = FUN_00236f80(arg0->_insight, DAT_00589208[0]);
            int *nm;
            int *rv;
            if (s0 != 0) {
                sprintf(sp80, &DAT_0050e5e8[0], ((beSystem *)arg0->_system)->_stageName);
                beLua__RunNamedChunk(s0, &DAT_0050e678[0], sp80);
            }
            arg0->_proc = -1;
            if ((char *)&DAT_0050e688[0] == 0) { rv = 0; } else {
                POOL()
                rv = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050e688[0]);
            }
            StringRef resetName0((char *)rv);
            if ((char *)&DAT_0050e698[0] == 0) { rv = 0; } else {
                POOL()
                rv = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050e698[0]);
            }
            StringRef resetName1((char *)rv);
            if ((char *)&DAT_0050e6a8[0] == 0) { rv = 0; } else {
                POOL()
                rv = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050e6a8[0]);
            }
            StringRef resetName2((char *)rv);
            if ((char *)&DAT_0050e6b8[0] == 0) { rv = 0; } else {
                POOL()
                rv = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050e6b8[0]);
            }
            StringRef resetName3((char *)rv);
            nm = (int *)((beSystem *)arg0->_system)->_stageName;
            if (nm == 0) { rv = 0; } else {
                POOL()
                rv = (int *)StringPool_Intern(DAT_00586f20[0], nm);
            }
            StringRef curName((char *)rv);
            {
                int *c = (int *)curName.p;
                if ((c != (int *)resetName0.p) && (c != (int *)resetName1.p) && (c != (int *)resetName2.p) && (c != (int *)resetName3.p)) {
                    ((beSystem *)arg0->_system)->_isSResetEnable = 1;
                }
            }
            break;
        }
        }
    }
}

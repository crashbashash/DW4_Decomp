#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" int List_Reserve(...);
extern "C" void igObject_Destroy(void *);
extern "C" int FUN_002eb010(...);
extern "C" int strcmp(...);
extern "C" int beCri_SetSndfVolume(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" char * StringPool_Intern(...);
extern "C" int Gap__Bec__beSound__vfunc_30(void);
extern "C" int Gap__Bec__beSound__vfunc_20(void);
extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" int List_RemoveWordAt(...);
extern "C" int beCri_SetFx(...);
extern "C" int ObjectList_RemoveFirstRetained(...);
extern "C" void *FUN_002b90e0(...);
extern "C" int FUN_0030b3c0(...);
extern "C" int FUN_0030b5c0(...);
extern "C" int FUN_0030b8a0(...);
extern "C" int FUN_0030ba20(...);
extern "C" int FUN_0030bbf0(...);
extern "C" int FUN_00344250(...);
extern "C" void *FUN_003447c0(...);
extern "C" int beCri_PlayStream(...);
extern "C" int beCri_PlayEffect(...);
extern "C" int beCri_StopByID(...);
extern "C" int beCri_StopGroup(...);
extern "C" int beCri_UnpauseByName(...);
extern "C" int beCri_FadeByName(int, char *, float, float, float);
extern "C" int beCri_FadeByID(int, int, float, float, float);
extern "C" int beCri_SetFreezeAudible(...);
extern "C" int beCri_StartSfpTransfers(...);
extern "C" int beCri_FreeSfpData(...);
extern "C" int beCri_IsTransferDone(...);
extern "C" int beCri_IsReady(...);
extern "C" void *Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int beMessenger_AppendBool(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendLong(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_EnqueueSelected(...);
extern "C" float beMessenger_GetFloat(...);
extern "C" int beMessenger_GetFloatCount(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetLong(...);
extern "C" int beMessenger_GetLongCount(...);
extern "C" char *beMessenger_GetString(...);
extern "C" int beMessenger_GetStringCount(...);
extern "C" int beMessenger_PrepareDelayedGroup(...);
extern "C" unsigned int beMessenger_ResolveEnumValue(...);
extern "C" void *igObject_GetAllocator(...);
extern "C" int g_beCri_metaObject[4];
extern "C" igObject *FUN_00236f80(int, int);
extern "C" void Gap__Bec__beSound__vfunc_32(beSound *arg0);
typedef struct K { char pad[52]; int f52; char pad2[8]; int f64; } K;
/* matching construct: pointer-typed view of beBaseInfoRam._parentInfo (+12) and beSoundInfo._dataType (+32); the matching compiler
 * schedules differently when those two fields are int handles.  The shorts at +36/+38 are read through beSoundInfo. */
typedef struct SoundInfoPointerView { char pad0[12]; struct SoundInfoPointerView *f12; char pad[16]; int *f32; } SoundInfoPointerView;
extern "C" int beMessenger_RegisterReceiver(int, SoundInfoPointerView *, int *, int, int);
extern "C" int g_stringPool[4];
extern "C" int DAT_0050f9a0[4];
extern "C" int DAT_0050f9a8[4];
extern "C" void Gap__Bec__beSound__vfunc_29(beSound *arg0, SoundInfoPointerView *arg1);
extern "C" int g_beSoundInfo_metaObject[4];
extern "C" int g_beSound_metaObject[4];
extern "C" igObjectList * beMessenger_GetObject(...);
extern "C" char emptyString[];
extern "C" int DAT_0050f9b0[4];
extern "C" int DAT_0050f9c0[4];
extern "C" int DAT_0050f9d0[4];
extern "C" int DAT_0050f9d8[4];
struct RP { int *p; };
typedef struct SE { int p[2]; int _name; int p2[2]; igDataList *_list; } SE;
extern "C" void Gap__Bec__beSound__vfunc_31(beSound *self, beBaseInfoRam *arg1);
extern "C" char *DAT_004c22f0[];
extern "C" int DAT_0050f9e0[4];
extern "C" int DAT_0050f9e8[4];
extern "C" int DAT_0050f9f0[4];
extern "C" int DAT_0050f9f8[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
struct Arg2 { int p[5]; int f20; };
struct SubE { int p[5]; igObjectList *f20; };
struct NameListRef {
    igObject *p;
    NameListRef(igObject *o) : p(o) {}
    ~NameListRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct GlobalStrRef {
    igObject *p;
    GlobalStrRef(igObject *o) : p(o) { if (p != 0) p->_refCount = p->_refCount + 1; }
    ~GlobalStrRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct StringRef {
    char *p;
    StringRef() {}
    StringRef(char *s) : p(s) { if (p != 0) ((int *)p)[-1] = ((int *)p)[-1] + 1; }
    ~StringRef() { char *s = p; if (s != 0) { int *hd = (int *)s - 2; int cnt = ((int *)s)[-1] - 1; ((int *)s)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
};
extern "C" int StringList_AppendRetained(void *list, const StringRef &text);
extern "C" StringRef StringList_CopyRetained(void *list, int index);
struct FloatBits { unsigned mantissa : 31; unsigned sign : 1; };
struct U { static inline char *Intern(char *text) {
    if (g_stringPool[0] == 0) {
        int pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    return StringPool_Intern(g_stringPool[0], text);
} };
extern "C" int Gap__Bec__beSound__vfunc_34(beSound *self, beBaseInfoRam *arg1, Arg2 *arg2);
extern "C" int FUN_0039fb60(void *arg0, beBaseInfoRam *arg1, int arg2);

void Gap__Bec__beSound__vfunc_32(beSound *arg0) {
    igDataList *l;
    int n;
    int i;
    igObject *o;
    igDataList *l2;
    if (arg0->_cri == 0) {
        igObject *t = FUN_00236f80(arg0->_insight, g_beCri_metaObject[0]);
        igObject *old;
        if (t != 0) {
            t->_refCount = (int)t->_refCount + 1;
        }
        old = (igObject *)arg0->_cri;
        if (old != 0) {
            old->_refCount = (int)old->_refCount - 1;
            if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)old);
            }
        }
        arg0->_cri = (int)t;
    }
    l = (igDataList *)arg0->_playSEs;
    n = l->_count;
    for (i = 0; i < n; i++) {
        o = ((igObject **)l->_data)[i];
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)o);
            }
        }
    }
    {
        int m = l->_count;
        int j;
        for (j = 0; j < m; j++) {
            ((igObject **)l->_data)[j] = 0;
        }
    }
    l->_count = 0;
    l2 = (igDataList *)arg0->_playSEs;
    if (0 < l2->_count) {
    } else {
        List_Reserve(l2, 0, 4);
    }
}

void Gap__Bec__beSound__vfunc_29(beSound *arg0, SoundInfoPointerView *arg1) {
    int *s2;
    int *old;
    int *a1;
    int v1;
    int var_v0;
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_0050f9a0[0], 0, -1);
    arg1 = arg1->f12;
    ((K *)arg0->_cri)->f52 = ((beSoundInfo *)arg1)->_baseVolume;
    beCri_SetSndfVolume(arg0->_cri, ((beSoundInfo *)arg1)->_sndfVolume);
    if (arg1->f32 == 0) {
        if (g_stringPool[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            g_stringPool[0] = var_v0;
        }
        s2 = (int *)StringPool_Intern(g_stringPool[0], &DAT_0050f9a8[0]);
        old = arg1->f32;
        if (old != 0) {
            a1 = old - 2;
            v1 = old[-1] - 1;
            old[-1] = v1;
            if (v1 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        arg1->f32 = s2;
    }
    if (strcmp(arg1->f32, &DAT_0050f9a8[0]) == 0) {
        ((K *)arg0->_cri)->f64 = 0;
    } else {
        ((K *)arg0->_cri)->f64 = 1;
    }
}

int Gap__Bec__beSound__vfunc_30(void)
{
    return g_beSoundInfo_metaObject[0];
}

#define NM(e) ((e)->_name ? (char *)(e)->_name : emptyString)
#define REL(o) { igObject *rr = (igObject *)(o); if (rr != 0) { rr->_refCount = (int)rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
void Gap__Bec__beSound__vfunc_31(beSound *self, beBaseInfoRam *arg1) {
    igDataList *objs;
    long long now;
    SE *e;
    igDataList *l;
    int n;
    int i;
    int m;
    int j2;
    RP sp;
    int k;
    int j;
    switch (arg1->_st0) {
    case 0:
        beMessenger_SendGroup(self->_messenger, &DAT_0050f9b0[0], &DAT_0050f9c0[0]);
        if (beMessenger_GetObjectCount(self->_messenger) <= 0) break;
            objs = (igDataList *)beMessenger_GetObject(self->_messenger, 0);
            i = 0;
            if (0 < objs->_count) do {
                e = ((SE **)objs->_data)[i];
                if (NM(e) == 0) { i++; continue; }
                if (strcmp(NM(e), &DAT_0050f9d0[0]) == 0) { i++; continue; }
                l = e->_list;
                n = l->_count;
                for (j = 0; j < n; j++) {
                    REL(((igObject **)l->_data)[j]);
                }
                m = l->_count;
                for (j2 = 0; j2 < m; j2++) {
                    ((int *)l->_data)[j2] = 0;
                }
                l->_count = 0;
                if (0 < e->_list->_count) {
                } else {
                    List_Reserve(e->_list, 0, 4);
                }
                REL(((igObject **)objs->_data)[i]);
                List_RemoveWordAt(objs, i);
                ((int *)objs->_data)[objs->_count] = 0;
            } while (i < objs->_count);
        beCri_SetFx(self->_cri, &DAT_0050f9d8[0]);
        arg1->_st0 = arg1->_st0 + 1;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
    case 1:
        now = ((igInsightCore *)self->_insight)->_worldTime;
        l = (igDataList *)self->_playSEs;
        k = 0;
        if (0 < l->_count) do {
            bePlaySE *s = ((bePlaySE **)l->_data)[k];
            if (s->_time < now) {
                ObjectList_RemoveFirstRetained(&sp, l, s, k);
                k--;
            }
            l = (igDataList *)self->_playSEs;
            k++;
        } while (k < l->_count);
    }
}

#undef REL
#undef NM

#define SREL(s) { char *ss = (s); if (ss != 0) { int *hd = (int *)ss - 2; int cnt = ((int *)ss)[-1] - 1; ((int *)ss)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
#define ALLOC(a, self) { a = igObject_GetAllocator(self); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
static inline float Abs(float value) {
    ((FloatBits *)&value)->sign = 0;
    return value;
}

int Gap__Bec__beSound__vfunc_34(beSound *self, beBaseInfoRam *arg1, Arg2 *arg2) {
    igObjectList *spCC;
    beSoundInfo *info;
    igNamedObject *ne;
    igObjectList *fl20;
    char *nm;
    char *bn;
    char *s1;
    char *s2;
    char *old;
    float fa, fb, fc;
    int idx;
    int r0;
    int cri;
    int k;
    int ia;
    int ib;
    char *nmb;
    unsigned char fb1;
    int jb;
    unsigned char fa1;
    int ja;
    int nb;
    char *iv;
    char *dt;
    beSoundData *e;
    void *alloc;
    igObjectList *l9;
    int n9;
    int i9;
    bePlaySE *dse;
    int offv;
    bePlaySEList *pl;
    bePlaySEList *pl2;
    long long now;
    int i;
    char *bn2;

    info = (beSoundInfo *)arg1->_parentInfo;
    switch (beMessenger_ResolveEnumValue(self->_messenger, FUN_00344250(), arg2->f20)) {
    case 1:
        if (beMessenger_GetLongCount(self->_messenger) == 0) return 0;
        beCri_StopByID(self->_cri, beMessenger_GetLong(self->_messenger, 0));
        break;
    case 3:
        ((beCri *)self->_cri)->_pauseOnetime = 1;
    case 2:
        if ((r0 = FUN_0039fb60((void *)self, arg1, (int)(beMessenger_GetString(self->_messenger, 0)))) == -1) return 0;
        idx = r0;
        e = ((beSoundData **)((igObjectList *)info->_dataList)->_data)[idx];
        switch (e->_type) {
        case 1:
            if (self->_currentBGM != 0) {
                nm = e->_name ? (char *)e->_name : emptyString;
                if (strcmp(nm, self->_currentBGM) == 0) return 1;
            }
            if (beCri_PlayStream(self->_cri, info->_fnameList, e) == 0) {
                beMessenger_PrepareDelayedGroup(self->_messenger, &DAT_0050f9a0[0]);
                nm = e->_name ? (char *)e->_name : emptyString;
                beMessenger_AppendString(self->_messenger, nm);
                beMessenger_EnqueueSelected(self->_messenger, &DAT_0050f9e0[0], 0xB);
            } else {
                nm = e->_name ? (char *)e->_name : emptyString;
                s1 = U::Intern(nm);
                old = (char *)self->_currentBGM;
                SREL(old)
                self->_currentBGM = (int)s1;
            }
            break;
        case 2:
            if (beCri_PlayStream(self->_cri, info->_fnameList, e) == 0) {
                beMessenger_PrepareDelayedGroup(self->_messenger, &DAT_0050f9a0[0]);
                nm = e->_name ? (char *)e->_name : emptyString;
                beMessenger_AppendString(self->_messenger, nm);
                beMessenger_EnqueueSelected(self->_messenger, &DAT_0050f9e0[0], 0xB);
            }
            break;
        default:
            now = ((igInsightCore *)self->_insight)->_worldTime;
            pl = (bePlaySEList *)self->_playSEs;
            i = 0;
            pl2 = pl;
            if (0 < *(int *)&pl->_count) {
                offv = 0;
                do {
                    dse = *(bePlaySE **)((char *)pl2->_data + offv);
                    if (dse->_id == idx && now < dse->_time) {
                        beMessenger_AppendInt(self->_messenger, 0);
                        beMessenger_AppendLong(self->_messenger, 0);
                        return 1;
                    }
                    i += 1;
                    offv += 4;
                    pl2 = pl;
                } while (i < pl->_count);
            }
            k = beCri_PlayEffect(self->_cri, info->_fnameList, e, i);
            beMessenger_AppendInt(self->_messenger, e->_type);
            beMessenger_AppendLong(self->_messenger, k);
            if (k > 0) {
                ALLOC(alloc, self)
                igSmartPointer<igObject> playSE((igObject *)FUN_003447c0(alloc));
                ((bePlaySE *)playSE.p)->_id = idx;
                ((bePlaySE *)playSE.p)->_time = now + 0x2FAF07E;
                ObjectList_AppendRetained(self->_playSEs, playSE.p);
            }
            break;
        }
        break;
    case 4:
        cri = self->_cri;
        beCri_UnpauseByName(cri, beMessenger_GetString(self->_messenger, 0));
        break;
    case 5:
        s1 = beMessenger_GetString(self->_messenger, 0);
        if (beMessenger_GetLongCount(self->_messenger) > 0) {
            if (strcmp(s1, &DAT_0050f9e8[0]) == 0) {
                cri = self->_cri;
                beCri_FadeByID(cri, beMessenger_GetLong(self->_messenger, 0), 0.0f, 1.0f, 10.0f);
            } else if (strcmp(s1, &DAT_0050f9f0[0]) == 0) {
                cri = self->_cri;
                beCri_FadeByID(cri, beMessenger_GetLong(self->_messenger, 0), 1.0f, 0.0f, 10.0f);
            }
            break;
        }
        if (beMessenger_GetStringCount(self->_messenger) <= 1) break;
        s2 = beMessenger_GetString(self->_messenger, 1);
        if (strcmp(s1, &DAT_0050f9e8[0]) == 0) {
            beCri_FadeByName(self->_cri, s2, 0.0f, 1.0f, 10.0f);
        } else if (strcmp(s1, &DAT_0050f9f0[0]) == 0) {
            beCri_FadeByName(self->_cri, s2, 1.0f, 0.0f, 10.0f);
        }
        if (self->_currentBGM != 0 && strcmp(s2, self->_currentBGM) == 0) {
            s1 = U::Intern(0);
            old = (char *)self->_currentBGM;
            SREL(old)
            self->_currentBGM = (int)s1;
        }
        break;
    case 10:
        if (beMessenger_GetStringCount(self->_messenger) <= 0) return 0;
        if (beMessenger_GetFloatCount(self->_messenger) < 3) return 0;
        s1 = beMessenger_GetString(self->_messenger, 0);
        fa = beMessenger_GetFloat(self->_messenger, 0);
        fb = beMessenger_GetFloat(self->_messenger, 1);
        fc = beMessenger_GetFloat(self->_messenger, 2);
        Abs(fa - fb);
        beCri_FadeByName(self->_cri, s1, fa, fb, fc);
        break;
    case 6:
        beCri_StopGroup(self->_cri, 1);
        s1 = U::Intern(0);
        old = (char *)self->_currentBGM;
        SREL(old)
        self->_currentBGM = (int)s1;
        break;
    case 7:
        beCri_StopGroup(self->_cri, 2);
        break;
    case 8:
        beCri_StopGroup(self->_cri, 4);
        break;
    case 11:
        beCri_SetFx(self->_cri, beMessenger_GetString(self->_messenger, 0));
        break;
    case 9:
        l9 = (igObjectList *)info->_dataList;
        n9 = l9->_count;
        i9 = 0;
        if (0 < n9) {
            do {
                nm = ((beSoundData **)l9->_data)[i9]->_name ? (char *)((beSoundData **)l9->_data)[i9]->_name : emptyString;
                beMessenger_AppendString(self->_messenger, nm);
                i9 += 1;
            } while (i9 < n9);
        }
        break;
    case 12:
    case 15:
        if (beMessenger_GetStringCount(self->_messenger) <= 0) {
            s1 = (char *)&DAT_0050f9f8[0];
        } else {
            s1 = beMessenger_GetString(self->_messenger, 0);
        }
        beMessenger_AppendBool(self->_messenger, beCri_IsReady(self->_cri, s1) & 0xFF);
        break;
    case 13:
        nm = ((beCriHandle *)((beCri *)self->_cri)->_hdBGM)->_name ? (char *)((beCriHandle *)((beCri *)self->_cri)->_hdBGM)->_name : emptyString;
        beMessenger_AppendBool(self->_messenger, beCri_IsReady(self->_cri, nm) & 0xFF);
        break;
    case 14:
        nm = ((beCriHandle *)((beCri *)self->_cri)->_hdENV)->_name ? (char *)((beCriHandle *)((beCri *)self->_cri)->_hdENV)->_name : emptyString;
        beMessenger_AppendBool(self->_messenger, beCri_IsReady(self->_cri, nm) & 0xFF);
        break;
    case 17:
        beCri_SetSndfVolume(self->_cri, beMessenger_GetInt(self->_messenger, 0));
        break;
    case 19:
        beCri_SetFreezeAudible(self->_cri, 0);
        break;
    case 18:
        beCri_SetFreezeAudible(self->_cri, 1);
        break;
    case 20:
        if (info->_dataType == 0) return 0;
        beMessenger_SendGroup(self->_messenger, &DAT_0050f9b0[0], &DAT_0050f9c0[0]);
        if (beMessenger_GetObjectCount(self->_messenger) <= 0) return 0;
        spCC = (igObjectList *)beMessenger_GetObject(self->_messenger, 0);
        fl20 = (igObjectList *)info->_fnameList;
        ALLOC(alloc, self)
        {
        NameListRef names((igObject *)FUN_002b90e0(alloc));
        GlobalStrRef scratch((igObject *)((beSystem *)self->_system)->_globalStrObj);
        ia = 0;
        if (0 < fl20->_count) {
            do {
                nm = ((igNamedObject **)fl20->_data)[ia]->_name ? (char *)((igNamedObject **)fl20->_data)[ia]->_name : emptyString;
                FUN_0030b3c0(scratch.p, nm);
                FUN_0030b8a0(scratch.p);
                FUN_0030bbf0(scratch.p, 0, 1);
                dt = (char *)info->_dataType;
                bn = (char *)((igStringObj *)scratch.p)->_buffer;
                if (bn == 0) bn2 = DAT_004c22f0[0]; else bn2 = bn;
                if (strcmp(dt, bn2) == 0) {
                    nm = ((igNamedObject **)fl20->_data)[ia]->_name ? (char *)((igNamedObject **)fl20->_data)[ia]->_name : emptyString;
                    FUN_0030b3c0(scratch.p, nm);
                    FUN_0030ba20(scratch.p);
                    FUN_0030b5c0(scratch.p);
                    s2 = (char *)((igStringObj *)scratch.p)->_buffer;
                    fa1 = 0;
                    if (s2 == 0) s2 = DAT_004c22f0[0];
                    if (s2 == 0) iv = 0; else iv = U::Intern(s2);
                    StringRef held;
                    held.p = iv;
                    ja = 0;
                    if (0 < ((igStringRefList *)names.p)->_count) {
                        do {
                            int eq;
                            eq = strcmp(held.p, StringList_CopyRetained(names.p, ja).p) == 0;
                            if (eq) { fa1 = 1; break; }
                            ja += 1;
                        } while (ja < ((igStringRefList *)names.p)->_count);
                    }
                    if (!(fa1 & 0xFF)) {
                        StringList_AppendRetained(names.p, StringRef(held.p));
                    }
                }
                ia += 1;
            } while (ia < fl20->_count);
        }
        ib = 0;
        if (0 < ((igStringRefList *)names.p)->_count) {
            do {
                nmb = StringList_CopyRetained(names.p, ib).p;
                fb1 = 0;
                jb = 0;
                if (0 < spCC->_count) {
                    do {
                        igObjectList *sub = ((SubE *)((igObject **)spCC->_data)[jb])->f20;
                        nb = 0;
                        if (0 < sub->_count) {
                            do {
                                ne = ((igNamedObject **)sub->_data)[nb];
                                nm = ne->_name ? (char *)ne->_name : emptyString;
                                if (strcmp(nm, nmb) == 0) {
                                    ObjectList_AppendRetained(((beCri *)self->_cri)->_lsBinObjs, ne);
                                    fb1 = 1;
                                    break;
                                }
                                nb += 1;
                            } while (nb < sub->_count);
                        }
                        if (fb1) break;
                        jb += 1;
                    } while (jb < spCC->_count);
                }
                ib += 1;
            } while (ib < ((igStringRefList *)names.p)->_count);
        }
        }
        beCri_StartSfpTransfers(self->_cri);
        break;
    case 21:
        beMessenger_AppendBool(self->_messenger, beCri_IsTransferDone(self->_cri) & 0xFF);
        break;
    case 22:
        if (((beCri *)self->_cri)->_dataType == 1) {
            beCri_FreeSfpData(self->_cri, 1);
        }
        break;
    default:
        return 0;
    }
    return 1;
}

#undef ALLOC
#undef SREL

int FUN_0039fb60(void *arg0, beBaseInfoRam *arg1, int arg2) {
    int i;
    igObjectList *t;
    int n;
    int *p;

    t = (igObjectList *)((beSoundInfo *)arg1->_parentInfo)->_dataList;
    n = t->_count;
    for (i = 0; i < n; i++) {
        p = (int *)((beSoundData **)t->_data)[i]->_name;
        p = p ? p : &((int *)emptyString)[0];
        if (strcmp(arg2, p) == 0) {
            return i;
        }
    }
    return -1;
}

int Gap__Bec__beSound__vfunc_20(void)
{
    return g_beSound_metaObject[0];
}

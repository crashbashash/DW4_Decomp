/* Message handler of the sound manager: resolves the message selector against the class enum and
 * dispatches over commands 1..22; the default entry returns 0, every other path returns 1.
 * Commands 2 and 3 look a sound entry up in the parent info's data list and play it (entry types 1
 * and 2 go through the delayed message queue, other types register an expiring record in the
 * playing-SE list); command 20 gathers the sound names of the stage record into a string list. The
 * playing-SE search loop keeps separate index / byte-offset inductions and the hoisted data
 * pointer only through the loop-carried re-read `pl2 = pl` and the explicit `offv`; a direct
 * `list->data[i]` is turned into one pointer induction by this compiler. The list count is
 * volatile like the engine's other list classes. Null fallbacks: a ternary for the constant
 * default; `if (bn == 0) bn2 = G; else bn2 = bn;` with a separate variable for the global default
 * (the empty else arm and the deleted jump keep the join unpadded). The first compare argument
 * (info->_dataType) is read before the test. Counts are compared as `> 1` (slti at) and `0 < n`
 * (slt at,zero); the declaration order of the locals decides the s-register colouring. The union
 * at spD0 is a volatile float / sign-bit pair: the otherwise dead difference of the first two
 * floats of command 10 is stored into that slot with the sign bit cleared before the call. */
#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
void *FUN_002b90e0(...);
int FUN_0030b3c0(...);
int FUN_0030b5c0(...);
int FUN_0030b8a0(...);
int FUN_0030ba20(...);
int FUN_0030bbf0(...);
int FUN_00344250(...);
void *FUN_003447c0(...);
int FUN_0037c2c0(...);
int FUN_0037c4c0(...);
int FUN_0037cb80(...);
int FUN_0037cc50(...);
int FUN_0037cd90(...);
int FUN_0037cf30(int, char *, float, float, float);
int FUN_0037d160(int, int, float, float, float);
int FUN_0037d570(...);
int FUN_0037d780(...);
int FUN_0037d870(...);
int FUN_0037daf0(...);
int FUN_0037dc60(...);
int FUN_0037dd10(...);
int FUN_0037e020(...);
int FUN_0039fb60(...);
void *Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
int beMessenger_AppendBool(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendLong(...);
int beMessenger_AppendString(...);
int beMessenger_EnqueueSelected(...);
float beMessenger_GetFloat(...);
int beMessenger_GetFloatCount(...);
int beMessenger_GetInt(...);
int beMessenger_GetLong(...);
int beMessenger_GetLongCount(...);
int beMessenger_GetObject(...);
int beMessenger_GetObjectCount(...);
char *beMessenger_GetString(...);
int beMessenger_GetStringCount(...);
int beMessenger_PrepareDelayedGroup(...);
unsigned int beMessenger_ResolveEnumValue(...);
int beMessenger_SendGroup(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
int strcmp(...);
extern char DAT_004e0858[];
extern char *DAT_004c22f0[];
extern int DAT_0050f9a0[4];
extern int DAT_0050f9b0[4];
extern int DAT_0050f9c0[4];
extern int DAT_0050f9e0[4];
extern int DAT_0050f9e8[4];
extern int DAT_0050f9f0[4];
extern int DAT_0050f9f8[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int Gap__Bec__beSound__vfunc_34(beSound *self, beBaseInfoRam *arg1, struct Arg2 *arg2);
}
struct Arg2 { int p[5]; int f20; };
struct SubE { int p[5]; igObjectList *f20; };
/* Owning stack references of the sound manager's message handler. PlaySERef holds a freshly
 * created playing-SE record while it is listed, NameListRef the string list built by command 20,
 * GlobalStrRef a retained share of the system's global string object and StringRef a share of an
 * interned text. */
struct PlaySERef {
    igObject *p;
    PlaySERef(igObject *o) : p(o) {}
    ~PlaySERef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
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
/* the list hands out a retained share of entry `index` by value (hidden result pointer) */
extern "C" int StringList_AppendRetained(void *list, const StringRef &text);
extern "C" StringRef StringList_CopyRetained(void *list, int index);

/* matching construct: retail stores the (otherwise dead) difference of the first two floats of command 10 into a stack slot with the sign bit cleared;
 * kept as an inline function so the slot is allocated after the references above. */
struct Dead { static inline void Difference(float a, float b) {
    volatile union { float f; struct { unsigned m : 31; unsigned s : 1; } b; } slot;
    slot.f = a - b;
    slot.b.s = 0;
} };
struct U { static inline char *Intern(char *text) {
    if (DAT_00586f20[0] == 0) {
        int pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    return StringPool_Intern(DAT_00586f20[0], text);
} };
#define SREL(s) { char *ss = (s); if (ss != 0) { int *hd = (int *)ss - 2; int cnt = ((int *)ss)[-1] - 1; ((int *)ss)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
#define ALLOC(a, self) { a = igObject_GetAllocator(self); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); }

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
        FUN_0037cb80(self->_cri, beMessenger_GetLong(self->_messenger, 0));
        break;
    case 3:
        ((beCri *)self->_cri)->_pauseOnetime = 1;
    case 2:
        if ((r0 = FUN_0039fb60(self, arg1, beMessenger_GetString(self->_messenger, 0))) == -1) return 0;
        idx = r0;
        e = ((beSoundData **)((igObjectList *)info->_dataList)->_data)[idx];
        switch (e->_type) {
        case 1:
            if (self->_currentBGM != 0) {
                nm = e->_name ? (char *)e->_name : DAT_004e0858;
                if (strcmp(nm, self->_currentBGM) == 0) return 1;
            }
            if (FUN_0037c2c0(self->_cri, info->_fnameList, e) == 0) {
                beMessenger_PrepareDelayedGroup(self->_messenger, &DAT_0050f9a0[0]);
                nm = e->_name ? (char *)e->_name : DAT_004e0858;
                beMessenger_AppendString(self->_messenger, nm);
                beMessenger_EnqueueSelected(self->_messenger, &DAT_0050f9e0[0], 0xB);
            } else {
                nm = e->_name ? (char *)e->_name : DAT_004e0858;
                s1 = U::Intern(nm);
                old = (char *)self->_currentBGM;
                SREL(old)
                self->_currentBGM = (int)s1;
            }
            break;
        case 2:
            if (FUN_0037c2c0(self->_cri, info->_fnameList, e) == 0) {
                beMessenger_PrepareDelayedGroup(self->_messenger, &DAT_0050f9a0[0]);
                nm = e->_name ? (char *)e->_name : DAT_004e0858;
                beMessenger_AppendString(self->_messenger, nm);
                beMessenger_EnqueueSelected(self->_messenger, &DAT_0050f9e0[0], 0xB);
            }
            break;
        default:
            now = ((igInsightCore *)self->_insight)->_worldTime;
            pl = (bePlaySEList *)self->_playSEs;
            i = 0;
            pl2 = pl;
            if (0 < *(volatile int *)&pl->_count) {
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
                } while (i < *(volatile int *)&pl->_count);
            }
            k = FUN_0037c4c0(self->_cri, info->_fnameList, e, i);
            beMessenger_AppendInt(self->_messenger, e->_type);
            beMessenger_AppendLong(self->_messenger, k);
            if (k > 0) {
                ALLOC(alloc, self)
                PlaySERef playSE((igObject *)FUN_003447c0(alloc));
                ((bePlaySE *)playSE.p)->_id = idx;
                ((bePlaySE *)playSE.p)->_time = now + 0x2FAF07E;
                ObjectList_AppendRetained(self->_playSEs, playSE.p);
            }
            break;
        }
        break;
    case 4:
        cri = self->_cri;
        FUN_0037cd90(cri, beMessenger_GetString(self->_messenger, 0));
        break;
    case 5:
        s1 = beMessenger_GetString(self->_messenger, 0);
        if (beMessenger_GetLongCount(self->_messenger) > 0) {
            if (strcmp(s1, &DAT_0050f9e8[0]) == 0) {
                cri = self->_cri;
                FUN_0037d160(cri, beMessenger_GetLong(self->_messenger, 0), 0.0f, 1.0f, 10.0f);
            } else if (strcmp(s1, &DAT_0050f9f0[0]) == 0) {
                cri = self->_cri;
                FUN_0037d160(cri, beMessenger_GetLong(self->_messenger, 0), 1.0f, 0.0f, 10.0f);
            }
            break;
        }
        if (beMessenger_GetStringCount(self->_messenger) <= 1) break;
        s2 = beMessenger_GetString(self->_messenger, 1);
        if (strcmp(s1, &DAT_0050f9e8[0]) == 0) {
            FUN_0037cf30(self->_cri, s2, 0.0f, 1.0f, 10.0f);
        } else if (strcmp(s1, &DAT_0050f9f0[0]) == 0) {
            FUN_0037cf30(self->_cri, s2, 1.0f, 0.0f, 10.0f);
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
        Dead::Difference(fa, fb);
        FUN_0037cf30(self->_cri, s1, fa, fb, fc);
        break;
    case 6:
        FUN_0037cc50(self->_cri, 1);
        s1 = U::Intern(0);
        old = (char *)self->_currentBGM;
        SREL(old)
        self->_currentBGM = (int)s1;
        break;
    case 7:
        FUN_0037cc50(self->_cri, 2);
        break;
    case 8:
        FUN_0037cc50(self->_cri, 4);
        break;
    case 11:
        FUN_0037dc60(self->_cri, beMessenger_GetString(self->_messenger, 0));
        break;
    case 9:
        l9 = (igObjectList *)info->_dataList;
        n9 = l9->_count;
        i9 = 0;
        if (0 < n9) {
            do {
                nm = ((beSoundData **)l9->_data)[i9]->_name ? (char *)((beSoundData **)l9->_data)[i9]->_name : DAT_004e0858;
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
        beMessenger_AppendBool(self->_messenger, FUN_0037dd10(self->_cri, s1) & 0xFF);
        break;
    case 13:
        nm = ((beCriHandle *)((beCri *)self->_cri)->_hdBGM)->_name ? (char *)((beCriHandle *)((beCri *)self->_cri)->_hdBGM)->_name : DAT_004e0858;
        beMessenger_AppendBool(self->_messenger, FUN_0037dd10(self->_cri, nm) & 0xFF);
        break;
    case 14:
        nm = ((beCriHandle *)((beCri *)self->_cri)->_hdENV)->_name ? (char *)((beCriHandle *)((beCri *)self->_cri)->_hdENV)->_name : DAT_004e0858;
        beMessenger_AppendBool(self->_messenger, FUN_0037dd10(self->_cri, nm) & 0xFF);
        break;
    case 17:
        FUN_0037e020(self->_cri, beMessenger_GetInt(self->_messenger, 0));
        break;
    case 19:
        FUN_0037d570(self->_cri, 0);
        break;
    case 18:
        FUN_0037d570(self->_cri, 1);
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
                nm = ((igNamedObject **)fl20->_data)[ia]->_name ? (char *)((igNamedObject **)fl20->_data)[ia]->_name : DAT_004e0858;
                FUN_0030b3c0(scratch.p, nm);
                FUN_0030b8a0(scratch.p);
                FUN_0030bbf0(scratch.p, 0, 1);
                dt = (char *)info->_dataType;
                bn = (char *)((igStringObj *)scratch.p)->_buffer;
                if (bn == 0) bn2 = DAT_004c22f0[0]; else bn2 = bn;
                if (strcmp(dt, bn2) == 0) {
                    nm = ((igNamedObject **)fl20->_data)[ia]->_name ? (char *)((igNamedObject **)fl20->_data)[ia]->_name : DAT_004e0858;
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
                                nm = ne->_name ? (char *)ne->_name : DAT_004e0858;
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
        FUN_0037d780(self->_cri);
        break;
    case 21:
        beMessenger_AppendBool(self->_messenger, FUN_0037daf0(self->_cri) & 0xFF);
        break;
    case 22:
        if (((beCri *)self->_cri)->_dataType == 1) {
            FUN_0037d870(self->_cri, 1);
        }
        break;
    default:
        return 0;
    }
    return 1;
}

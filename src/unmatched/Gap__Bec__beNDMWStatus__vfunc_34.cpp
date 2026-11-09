/* Message handler of the status screen (enum-dispatched). Every DAT_ string is declared int[4] on
 * purpose: a small object (<= 8 bytes) is addressed gp-relative, which makes gp a live physical
 * neighbour of every node and shifts the whole s-register colouring. The block-local order `int
 * idx; int v = ...; { igIntList *lst = ...; idx = ...; }` gives the per-row nodes the ids idx < v
 * < lst, the push order needed (colours idx s5, v s4, lst s3). beMessenger_AppendBool takes an
 * unsigned char and beMessenger_AppendObject a pointer: the argument type decides which of the two
 * argument loads lands in the delay slot. The 5 and 2 byte copies are the compiler's __memcpy
 * intrinsic (alternate compiler only; the default compiler crashes on it). */
#include "dw4/reflected.h"

extern "C" {
int sprintf(...);
int FUN_003b1d70(void);
int FUN_003bb730(void);
int FUN_003d8740(...);
int List_Resize(void *, int, int);
int *beDataBase_GetRecordString(int, int, const void *);
void beMessenger_AppendBool(int, unsigned char);
void beMessenger_AppendInt(int, int);
void beMessenger_AppendObject(int, void *);
void beMessenger_AppendString(int, const void *);
void beMessenger_AppendVec3(int, const void *);
void beMessenger_DispatchSelected(int, const void *);
int beMessenger_GetInt(int, int);
int beMessenger_GetObject(int, int);
int beMessenger_GetString(int, int);
unsigned int beMessenger_ResolveEnumValue(int, int, int);
void beMessenger_SelectGroup(int, const void *);
void beMessenger_SendDelayedGroup(int, const void *, const void *, int);
void beMessenger_SendGroup(int, const void *, const void *);
void beMessenger_SendNamed(int, const void *, const void *, int, const void *);
void beMessenger_SetFreezeTime(int, int);
void igObject_Destroy(void *);
int *igProperty_GetRecord(int, const void *);

struct Folder { int pad[3]; igObjectList *list; };
Folder *igProperty_GetRecordFolder(int, const void *);
}

extern "C" {
extern int DAT_00516788[4];
extern int DAT_005167e8[4];
extern int DAT_00516828[4];
extern int DAT_00516838[4];
extern int DAT_00516848[4];
extern int DAT_00516850[4];
extern int DAT_00516910[4];
extern int DAT_00516920[4];
extern int DAT_00516928[4];
extern int DAT_00516938[4];
extern int DAT_00516940[4];
extern int DAT_00516950[4];
extern int DAT_00516958[4];
extern int DAT_00516960[4];
extern int DAT_00516968[4];
extern int DAT_00516970[4];
extern int DAT_00516980[4];
extern int DAT_00516990[4];
extern int DAT_00516998[4];
extern int DAT_005169a8[4];
extern int DAT_005169b8[4];
extern int DAT_005169c0[4];
extern int DAT_005169c8[4];
extern int DAT_005169d0[4];
extern int DAT_005169e0[4];
extern int DAT_005169e8[4];
extern int DAT_005169f0[4];
extern int DAT_005169f8[4];
extern int DAT_00516a00[4];
extern int DAT_00516a08[4];
extern int DAT_00516a10[4];
extern int DAT_00516a18[4];
extern int DAT_00516a20[4];
extern int DAT_00516a28[4];
extern int DAT_00516a38[4];
extern int DAT_00516a40[4];
extern int DAT_00516a48[4];
extern int DAT_00516a50[4];
extern int DAT_00516a60[4];
extern int DAT_00516a68[4];
extern int DAT_00516a78[4];
extern int DAT_00516a80[4];
extern int DAT_00516a90[4];
extern int DAT_00516a98[4];
extern int DAT_00516aa8[4];
extern int DAT_00516ab0[4];
extern int DAT_00516ac0[4];
extern int DAT_00516ac8[4];
extern int DAT_00516ad0[4];
extern int DAT_00516ad8[4];
extern int DAT_00516ae0[4];
extern int DAT_00516ae8[4];
extern int DAT_00516af0[4];
extern int DAT_00516af8[4];
extern int DAT_00516b00[4];
extern int DAT_00516b08[4];
extern int DAT_00516b10[4];
extern int DAT_00516b18[4];
}

/* Owning stack reference to the first record of the selected folder: constructed from the object
 * (then retained) and released on scope exit (reference count in the low 23 bits of _refCount). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct MsgArg { int pad[5]; int f20; };

#define RELEASE_REF(q) { igObject *rr = (igObject *)(q); if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }
#if __MWERKS__ >= 0x3000
#define COPY_BYTES(d, s, n) __memcpy(d, s, n)
#else
#define COPY_BYTES(d, s, n) { char *cd_ = (char *)(d); const char *cs_ = (const char *)(s); int k_; for (k_ = 0; k_ < (n); k_++) cd_[k_] = cs_[k_]; }
#endif
#define M (arg0->_messenger)
#define SEL(g) beMessenger_SelectGroup(M, g)
#define APS(s) beMessenger_AppendString(M, s)
#define DSP(d) beMessenger_DispatchSelected(M, d)
#define REC(o, s) (igProperty_GetRecord(o, &s[0])[3])
#define APPENDL(val) { igIntList *lst = (igIntList *)work->_parameter; idx = lst->_count; if (idx < lst->_capacity) lst->_count = *(const int *)&lst->_count + 1; else List_Resize(lst, idx + 1, 4); ((int *)lst->_data)[idx] = (val); }
#define APPEND(val) { int idx; igIntList *lst = (igIntList *)work->_parameter; idx = lst->_count; if (idx < lst->_capacity) lst->_count = *(const int *)&lst->_count + 1; else List_Resize(lst, idx + 1, 4); ((int *)lst->_data)[idx] = (val); }
#define LISTDATA(i) (((int *)((igIntList *)work->_parameter)->_data)[i])
#define COLOR(a, ref) { if (a == ref) { r = 0.9f; g = 0.9f; b = 0.9f; } else if (a < ref) { r = 0.94f; g = 0.4f; b = 0.25f; } else { g = 0.96f; b = 1.0f; r = 0.0f; } }

extern "C" int Gap__Bec__beNDMWStatus__vfunc_34(beNDMWStatus *arg0, beNDMWStatusInfoRam *arg1, MsgArg *arg2);
int Gap__Bec__beNDMWStatus__vfunc_34(beNDMWStatus *arg0, beNDMWStatusInfoRam *arg1, MsgArg *arg2) {
    unsigned int kind = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003bb730(), arg2->f20);
    float v0[3];
    float v1[3];
    float v2[3];
    float v3[3];
    float v4[3];
    float v5[3];
    float v6[3];
    float v7[3];
    float v8[3];
    float v9[3];
    float v10[3];
    char b2[16];
    char b4[16];
    char b5[16];
    int s3;
    int cnt;
    int s7;
    int s8;
    beNDMWStatusInfoWork *work;
    int obj;
    switch (kind) {
    case 6:
        beMessenger_AppendBool(M, arg1->_isRun);
        return 1;
    case 0:
        if (arg1->_isRun == 0) {
            int a = beMessenger_GetInt(M, 0);
            int b = beMessenger_GetString(M, 0);
            unsigned int c = beMessenger_ResolveEnumValue(M, FUN_003b1d70(), b);
            arg1->_isRun = 1;
            arg1->_st0 = 0;
            arg1->_st3 = 0;
            arg1->_st2 = 0;
            arg1->_st1 = 0;
            arg0->_subWndNo = c;
            arg0->_whoGenerate = a;
            beMessenger_SendGroup(M, &DAT_00516838[0], &DAT_00516910[0]);
            beMessenger_SendGroup(M, &DAT_00516828[0], &DAT_00516910[0]);
            beMessenger_SetFreezeTime(M, 1);
            beMessenger_SendGroup(M, &DAT_005167e8[0], &DAT_00516910[0]);
        }
        return 1;
    case 1:
        if (arg1->_isRun == 1) {
            beNDMWWindow *wp = (beNDMWWindow *)arg0->_windowPro;
            if (wp != 0) {
                wp->_st0 = 2;
                wp->_st3 = 0;
                wp->_st2 = 0;
                wp->_st1 = 0;
            } else {
                beMessenger_SetFreezeTime(M, 0);
                beMessenger_SendDelayedGroup(M, &DAT_00516788[0], &DAT_00516920[0], 1);
            }
        }
        return 1;
    case 2: {
        work = (beNDMWStatusInfoWork *)arg1->_work;
        s3 = beMessenger_GetInt(M, 0);
        if (work == 0) {
            FUN_003d8740(arg0, arg1);
            work = (beNDMWStatusInfoWork *)arg1->_work;
        }
        ((igIntList *)work->_parameter)->_count = 0;
        SEL(&DAT_00516848[0]);
        beMessenger_AppendInt(M, s3);
        DSP(&DAT_00516850[0]);
        obj = beMessenger_GetObject(M, 0);
        ObjectRef ref(((igObject **)igProperty_GetRecordFolder(obj, &DAT_00516928[0])->list->_data)[0]);
        if (ref.p != 0) ref.p->_refCount = ref.p->_refCount + 1;
        SEL(&DAT_00516938[0]);
        APS(&DAT_00516940[0]);
        APS(&DAT_00516950[0]);
        beMessenger_AppendObject(M, ref.p);
        DSP(&DAT_00516958[0]);
        cnt = REC(obj, DAT_00516960);
        if (cnt > 999) cnt = 999;
        sprintf(b2, &DAT_00516968[0], cnt);
        SEL(&DAT_00516938[0]);
        APS(&DAT_00516970[0]);
        APS(&DAT_00516950[0]);
        APS(b2);
        DSP(&DAT_00516958[0]);
        beMessenger_SendNamed(M, &DAT_00516980[0], &DAT_00516990[0], 0, &DAT_00516998[0]);
        {
            int db = beMessenger_GetObject(M, 0);
            int *str = beDataBase_GetRecordString(db, REC(obj, DAT_005169a8), &DAT_005169b8[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_00516970[0]);
            APS(&DAT_005169c0[0]);
            APS(str);
            DSP(&DAT_00516958[0]);
        }
        s7 = REC(obj, DAT_005169c8);
        sprintf(b2, &DAT_00516968[0], s7);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516950[0]);
        APS(b2);
        DSP(&DAT_00516958[0]);
        s8 = REC(obj, DAT_005169e0);
        sprintf(b2, &DAT_00516968[0], s8);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_005169c0[0]);
        APS(b2);
        DSP(&DAT_00516958[0]);
        {
            int idx; int v = REC(obj, DAT_005169e8);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_005169f0[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_005169f8);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a00[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a08);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a10[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a18);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a20[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a28);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a38[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a40);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a48[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a50);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a60[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a68);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a78[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a80);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a90[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a98);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516aa8[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516ab0);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516ac0[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516ac8);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516ad0[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
        }
        {
            int idx; int v = REC(obj, DAT_00516ad8);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516ae0[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
        }
        {
            int lo = REC(obj, DAT_00516ae8);
            int diff = REC(obj, DAT_00516af0) - lo;
            if (cnt >= 999) {
                COPY_BYTES(b2, DAT_00516af8, 5);
            } else if (diff < 0) {
                COPY_BYTES(b2, DAT_00516b00, 2);
            } else {
                sprintf(b2, &DAT_00516968[0], diff);
            }
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516b08[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
        }
        APPEND(s7);
        APPEND(s8);
        return 1;
    }
    case 4: {
        int s1;
        int obj;
        beNDMWStatusInfoWork *work = (beNDMWStatusInfoWork *)arg1->_work;
        s1 = beMessenger_GetInt(M, 0);
        float r, g, b;
        SEL(&DAT_00516848[0]);
        beMessenger_AppendInt(M, s1);
        DSP(&DAT_00516850[0]);
        obj = beMessenger_GetObject(M, 0);
        {
            int a2 = REC(obj, DAT_005169e8);
            int ref = LISTDATA(0);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_005169f0[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_005169f0[0]);
            v0[0] = r; v0[1] = g; v0[2] = b;
            beMessenger_AppendVec3(M, v0);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_005169f8);
            int ref = LISTDATA(1);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a00[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a00[0]);
            v1[0] = r; v1[1] = g; v1[2] = b;
            beMessenger_AppendVec3(M, v1);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a08);
            int ref = LISTDATA(2);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a10[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a10[0]);
            v2[0] = r; v2[1] = g; v2[2] = b;
            beMessenger_AppendVec3(M, v2);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a18);
            int ref = LISTDATA(3);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a20[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a20[0]);
            v3[0] = r; v3[1] = g; v3[2] = b;
            beMessenger_AppendVec3(M, v3);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a28);
            int ref = LISTDATA(4);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a38[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a38[0]);
            v4[0] = r; v4[1] = g; v4[2] = b;
            beMessenger_AppendVec3(M, v4);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a40);
            int ref = LISTDATA(5);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a48[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a48[0]);
            v5[0] = r; v5[1] = g; v5[2] = b;
            beMessenger_AppendVec3(M, v5);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a50);
            int ref = LISTDATA(6);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a60[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a60[0]);
            v6[0] = r; v6[1] = g; v6[2] = b;
            beMessenger_AppendVec3(M, v6);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a68);
            int ref = LISTDATA(7);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a78[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a78[0]);
            v7[0] = r; v7[1] = g; v7[2] = b;
            beMessenger_AppendVec3(M, v7);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a80);
            int ref = LISTDATA(8);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a90[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a90[0]);
            v8[0] = r; v8[1] = g; v8[2] = b;
            beMessenger_AppendVec3(M, v8);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a98);
            int ref = LISTDATA(9);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516aa8[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516aa8[0]);
            v9[0] = r; v9[1] = g; v9[2] = b;
            beMessenger_AppendVec3(M, v9);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516ab0);
            int ref = LISTDATA(10);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516ac0[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516ac0[0]);
            v10[0] = r; v10[1] = g; v10[2] = b;
            beMessenger_AppendVec3(M, v10);
            DSP(&DAT_00516b10[0]);
        }
        return 1;
    }
    case 5: {
        int s1;
        beNDMWStatusInfoWork *work = (beNDMWStatusInfoWork *)arg1->_work;
        s1 = beMessenger_GetInt(M, 0);
        int *pv;
        int s4, s3, obj;
        sprintf(b5, &DAT_00516968[0], LISTDATA(0));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_005169f0[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_005169f0[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(1));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a00[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a00[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(2));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a10[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a10[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(3));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a20[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a20[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(4));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a38[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a38[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(5));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a48[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a48[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(6));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a60[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a60[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(7));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a78[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a78[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(8));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a90[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a90[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(9));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516aa8[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516aa8[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(10));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516ac0[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516ac0[0]);
        DSP(&DAT_00516b18[0]);
        pv = (int *)((igIntList *)work->_parameter)->_data;
        s4 = pv[11];
        s3 = pv[12];
        SEL(&DAT_00516848[0]);
        beMessenger_AppendInt(M, s1);
        DSP(&DAT_00516850[0]);
        obj = beMessenger_GetObject(M, 0);
        REC(obj, DAT_005169c8) = s4;
        REC(obj, DAT_005169e0) = s3;
        return 1;
    }
    case 3: {
        beNDMWStatusInfoWork *work = (beNDMWStatusInfoWork *)arg1->_work;
        int what = beMessenger_GetInt(M, 0);
                switch (what) {
        case 6:
            beMessenger_AppendObject(M, (void *)work->_weaponSalesList);
            break;
        case 7:
            beMessenger_AppendObject(M, (void *)work->_armorSalesList);
            break;
        case 8:
            beMessenger_AppendObject(M, (void *)work->_chipSalesList);
            break;
        case 9:
            beMessenger_AppendObject(M, (void *)work->_junkSalesList);
            beMessenger_AppendInt(M, work->_junkGift);
            break;
        }
        return 1;
    }
    default:
        return 0;
    }
}

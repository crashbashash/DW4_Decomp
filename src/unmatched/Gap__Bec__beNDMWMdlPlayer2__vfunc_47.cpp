extern "C" {
#include "dw4/reflected.h"

typedef struct Ref { int vt; unsigned rc; } Ref;
typedef struct Msg {
    char _pad0[8];
    int number;            /* +8  */
    char _pad12[8];
    unsigned char flag;    /* +20 */
    char _pad21[19];
    Ref *cache;            /* +40 */
} Msg;
typedef struct IntVec { char _p[8]; int count; char _q[4]; int *data; } IntVec;
typedef struct StrVec { char _p[8]; int count; char _q[4]; int *data; } StrVec;
typedef struct F3Vec { char _p[8]; int count; char _q[4]; float *data; } F3Vec;
typedef struct RecInt { char _p[12]; int v; } RecInt;
typedef struct RecIv { char _p[12]; IntVec *v; } RecIv;
typedef struct RecSl { char _p[12]; StrVec *v; } RecSl;
typedef struct RecFl { char _p[12]; F3Vec *v; } RecFl;
typedef struct RecStr { char _p[12]; char *v; } RecStr;

int igStrCmp(const char *, const char *);
void *igObject_GetAllocator(Msg *);
void *Memory_GetAllocatorBySelector(int);
Ref *beBaseInfoDataList_Create(void *);
void igObject_Destroy(Ref *);
char *igProperty_FindByName(Ref *, int, const char *);
RecInt *igProperty_GetRecord(int, const char *);
RecIv *FUN_003a9250(int, const char *);
RecStr *FUN_003a92e0(int, const char *);
RecSl *FUN_003a9310(int, const char *);
RecFl *FUN_003a9370(int, const char *);
void StringList_CopyRetained(int *, StrVec *, int);
void StringChunk_ReleaseHeader(int, void *);
void beMessenger_SendGroup(int, const char *, const char *);
int beMessenger_GetObject(int, int);
void beMessenger_PrepareDelayedSelection(int, const char *, const char *, int);
void beMessenger_AppendVec3(int, float *);
void sprintf(char *, const char *, int);
void beMessenger_AppendString(int, const char *);
void beMessenger_EnqueueSelected(int, const char *, int);
void beMessenger_GetMatrix(float *, int, int);
int beMessenger_GetInt(int, int);
void beMessenger_SendNamed(int, const char *, int, int, const char *);
int beMessenger_GetBoolCount(int);
int beMessenger_GetBool(int, int);
void beMessenger_SelectGroup(int, const char *);
void beMessenger_AppendInt(int, int);
void beMessenger_DispatchSelected(int, const char *);
void beMessenger_SelectReceivers(int, const char *, const char *, int);
void beMessenger_AppendMatrix(int, float *);
void beMessenger_SendDelayedNamed(int, const char *, int, int, const char *, int);

extern unsigned char GPR_00554c14;
extern char DAT_005165c0[], DAT_005165c8[], DAT_005165d0[], DAT_005165d8[], DAT_005165e8[], DAT_005165f8[];
extern char DAT_00516608[], DAT_00516648[], DAT_00516658[], DAT_00516660[], DAT_00516670[], DAT_00516680[];
extern char DAT_00516690[], DAT_005166a0[], DAT_005166a8[], DAT_005166b0[], DAT_005166c0[], DAT_005166c8[];
extern char DAT_005166d8[], DAT_005166e8[], DAT_005166f0[], DAT_00516700[], DAT_00516708[], DAT_00516718[], DAT_00516720[];
extern int DAT_004cc820[4], DAT_004cc828[4], DAT_00587110[4], DAT_00585be0[4];

}
/* matching construct: dummy-virtual receiver; only slot 33 (beNDMWMdlPlayer2::vfunc_33, vtable +0x08 + 4*33) is called.
 * The k-th declared virtual dispatches slot k, so the names count from vfunc_00 (scripts/check_vtable_slots.py). */
struct Msg;
class Player2Virt {
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
    virtual void vfunc_20();
    virtual void vfunc_21();
    virtual void vfunc_22();
    virtual void vfunc_23();
    virtual void vfunc_24();
    virtual void vfunc_25();
    virtual void vfunc_26();
    virtual void vfunc_27();
    virtual void vfunc_28();
    virtual void vfunc_29();
    virtual void vfunc_30();
    virtual void vfunc_31();
    virtual void vfunc_32();
    virtual void vfunc_33(Msg *, const char *);
};
#define STR_RELEASE(r) if (r) { int *h_ = (int *)((r) - 8); int c_ = *(int *)((r) - 4) - 1; *(int *)((r) - 4) = c_; if (!c_) StringChunk_ReleaseHeader(*h_, h_); }
#define OBJ_RELEASE(q) if (q) { (q)->rc--; if (((q)->rc & 0x7fffff) == 0) igObject_Destroy(q); }
extern "C" int Gap__Bec__beNDMWMdlPlayer2__vfunc_47(beNDMWMdlPlayer2 *self, Msg *msg, const char *name)
{
    int a, b, s, didb;
    volatile int empty;
    Ref *volatile t;
    if (igStrCmp(name, DAT_00516648) == 0) {
        if (msg->flag != 0)
            ((Player2Virt *)self)->vfunc_33(msg, DAT_00516658);
    } else if (igStrCmp(name, DAT_00516660) == 0) {
        beMessenger_SendGroup(self->_messenger, DAT_005165d0, DAT_005165d8);
        int obj = beMessenger_GetObject(self->_messenger, 0);
        StrVec *names = FUN_003a9310(obj, DAT_005165e8)->v;
        F3Vec *pos = FUN_003a9370(obj, DAT_005165f8)->v;
        int idx = msg->number;
        bool match;
        StringList_CopyRetained(&a, names, idx);
        didb = 0;
        match = false;
        if (a != 0) {
            StringList_CopyRetained(&b, names, idx);
            didb = 1;
            if (igStrCmp((const char *)((beSystem *)self->_system)->_stageName, (const char *)b) == 0)
                match = true;
        }
        if (didb) { STR_RELEASE(b) }
        STR_RELEASE(a)
        if (match) {
            float *d = pos->data;
            float x = *(float *)((char *)d + idx * 3 * 4); float y = *(float *)((char *)d + (idx * 3 + 1) * 4); float z = *(float *)((char *)d + (idx * 3 + 2) * 4);
            float v[3];
            char buf[16];
            beMessenger_PrepareDelayedSelection(self->_messenger, DAT_00516670, DAT_00516680, msg->number);
            v[0] = x; v[1] = y; v[2] = z;
            beMessenger_AppendVec3(self->_messenger, v);
            sprintf(buf, DAT_00516690, msg->number + 1);
            beMessenger_AppendString(self->_messenger, buf);
            beMessenger_EnqueueSelected(self->_messenger, DAT_00516648, 1);
        }
        return 1;
    } else if (igStrCmp(name, DAT_005166a0) == 0) {
        if (msg->cache == 0) {
            void *al = igObject_GetAllocator((Msg *)msg);
            void *al2;
            if (GPR_00554c14 != 0) {
                al2 = al;
            } else {
                al2 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
            }
            t = beBaseInfoDataList_Create(al2);
            Ref *r = t;
            if (r) r->rc++;
            Ref *old = msg->cache;
            OBJ_RELEASE(old)
            msg->cache = r;
            Ref *t2 = t;
            OBJ_RELEASE(t2)
        }
        beNDMWMdlPlayer2InfoWork *info = *(beNDMWMdlPlayer2InfoWork **)(igProperty_FindByName(msg->cache, DAT_00585be0[0], DAT_005165c8) + 20);
        if (info->_timerCount < 10)
            return 1;
        float mat[16];
        beMessenger_GetMatrix(mat, self->_messenger, 0);
        int pct = beMessenger_GetInt(self->_messenger, 0);
        int val = beMessenger_GetInt(self->_messenger, 1);
        unsigned char found = 0;
        beMessenger_SendNamed(self->_messenger, DAT_00516608, 0, msg->number, DAT_005166a8);
        int n = beMessenger_GetBoolCount(self->_messenger);
        for (int i = 0; i < n; i++) {
            if ((beMessenger_GetBool(self->_messenger, i) & 0xff) == 1) {
                found = 1;
                break;
            }
        }
        beMessenger_SelectGroup(self->_messenger, DAT_005165d0);
        beMessenger_AppendInt(self->_messenger, msg->number);
        beMessenger_DispatchSelected(self->_messenger, DAT_005166b0);
        int o = beMessenger_GetObject(self->_messenger, 0);
        if (!found) {
            igProperty_GetRecord(o, DAT_005166c0)->v = val;
            char *who = FUN_003a92e0(o, DAT_005166c8)->v;
            if (*who == 0) who = DAT_005166d8;
            beMessenger_SelectReceivers(self->_messenger, DAT_00516670, who, msg->number);
            beMessenger_AppendMatrix(self->_messenger, mat);
            beMessenger_AppendString(self->_messenger, DAT_005166e8);
            beMessenger_DispatchSelected(self->_messenger, DAT_00516648);
        }
        beMessenger_SendGroup(self->_messenger, DAT_005165d0, DAT_005165d8);
        int obj = beMessenger_GetObject(self->_messenger, 0);
        int i2 = msg->number * 2;
        int *dp = FUN_003a9250(obj, DAT_005166f0)->v->data;
        int d = dp[i2];
        d += igProperty_GetRecord(o, DAT_00516700)->v; igProperty_GetRecord(o, DAT_00516700)->v = d;
        {
            IntVec *vec = FUN_003a9250(obj, DAT_005166f0)->v;
            if (vec->count != 0 && i2 >= 0 && i2 < vec->count)
                vec->data[i2] = DAT_004cc820[0];
        }
        char *cur = FUN_003a92e0(o, DAT_005166c8)->v;
        val = msg->number;
        {
            StringList_CopyRetained(&s, FUN_003a9310(obj, DAT_00516708)->v, val);
            char *sp = (char *)s;
            STR_RELEASE(sp)
            if (igStrCmp(cur, sp) == 0) {
                int i3 = msg->number * 2 + 1;
                int *dp3 = FUN_003a9250(obj, DAT_005166f0)->v->data;
                int e3 = dp3[i3]; int d3 = (e3 * pct) / 100;
                d3 += igProperty_GetRecord(o, DAT_00516718)->v; igProperty_GetRecord(o, DAT_00516718)->v = d3;
                IntVec *vec = FUN_003a9250(obj, DAT_005166f0)->v;
                if (vec->count != 0 && i3 >= 0 && i3 < vec->count)
                    vec->data[i3] = DAT_004cc828[0];
            }
        }
        beMessenger_SendDelayedNamed(self->_messenger, DAT_005165c0, 0, msg->number, DAT_00516720, 0);
        beMessenger_SendGroup(self->_messenger, DAT_005165d0, DAT_005165d8);
        int obj2 = beMessenger_GetObject(self->_messenger, 0);
        empty = 0;
        int k = msg->number;
        StrVec *lst = FUN_003a9310(obj2, DAT_005165e8)->v;
        if (lst->count != 0 && k >= 0 && k < lst->count) {
            int *slot = lst->data + k;
            int e1 = empty;
            if (e1) *(int *)(e1 - 4) += 1;
            int old = *slot;
            STR_RELEASE(old)
            *slot = empty;
        }
        int e3 = empty;
        STR_RELEASE(e3)
        return 1;
    }
    return 0;
}

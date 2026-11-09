#include "dw4/reflected.h"
struct igResult { int w0; bool operator==(const igResult &o) const { return w0 == o.w0; } };
typedef struct List { int w0; int references; int size; int cap; int *data; } List;
typedef struct BList { int w0; int references; int size; int cap; unsigned char *data; } BList;
typedef struct OList { int w0; int references; int size; int cap; beModelCtrlMoveObject **data; } OList;
typedef struct Param { int w0; int references; int pad8; int value; } Param;
typedef struct Entry { int w0, w1, w2, w3, w4; beNDMWMdlPEBaseInfoWork *work; } Entry;
typedef struct Model { int w0; int references; int id; char pad12[28]; List *props; } Model;
extern "C" {
extern int igObject_GetAllocator(...);
extern int Memory_GetAllocatorBySelector(...);
extern void *beBaseInfoDataList_Create(...);
extern void igObject_Destroy(List *);
extern Entry *igProperty_FindByName(...);
extern Param *igProperty_GetRecord(...);
extern int beMessenger_GetObject(...);
extern int beMessenger_SendNamed(...);
extern int FUN_003a7a20(...);
extern int FUN_003a7e90(...);
extern int FUN_003a8580(...);
extern long long __divdi3(...);
extern int FUN_003c03e0(...);
extern igResult igMetaEnum_GetValueByName(...);
extern int FUN_00445c60(...);
extern int FUN_00443900(void *, void *, int, int, int, bool);
extern int strcmp(...);
extern int beMessenger_SelectReceivers(...);
extern int beMessenger_SelectGroup(...);
extern int beMessenger_AppendFloat(int, float);
extern int beMessenger_AppendInt(...);
extern int beMessenger_DispatchSelected(...);
extern int DAT_004cfc50[4];
extern int DAT_004cfcb8[4];
extern int DAT_004cfcc0[4];
extern int DAT_004cfcc8[4];
extern int DAT_004cfcd0[4];
extern int DAT_004cfcd8[4];
extern int DAT_004cfce0[4];
extern int DAT_004cfce8[4];
extern int DAT_004cfcf0[4];
extern int DAT_004cfcf8[4];
extern int DAT_004cfd00[4];
extern int DAT_004cfd08[4];
extern int DAT_004cfd10[4];
extern int DAT_004cfd18[4];
extern int DAT_004cfd20[4];
extern int DAT_004cfd28[4];
extern int DAT_004cfd30[4];
extern int DAT_004cfd38[4];
extern int DAT_004cfd40[4];
extern int DAT_004cfd48[4];
extern int DAT_004cfd50[4];
extern int DAT_004cfd58[4];
extern int DAT_004cfd60[4];
extern int DAT_004cfd68[4];
extern int DAT_004cfd70[4];
extern int DAT_004cfd78[4];
extern int DAT_004cfd80[4];
extern int DAT_004cfd88[4];
extern int DAT_004cfd90[4];
extern int DAT_004cfd98[4];
extern int DAT_004cfda0[4];
extern int DAT_004cfda8[4];
extern int DAT_004cfdb0[4];
extern igResult DAT_004fb410;
extern int DAT_00587110[4];
extern int DAT_00585be0[4];
extern int DAT_0051d3a0[4];
extern int DAT_0051d3a8[4];
extern int DAT_0051d3e8[4];
extern int DAT_0051d3f0[4];
extern int DAT_0051d3f8[4];
extern int DAT_0051d408[4];
extern int DAT_0051d410[4];
extern int DAT_0051d420[4];
extern int DAT_0051d430[4];
extern int DAT_0051d438[4];
extern int DAT_0051d448[4];
extern int DAT_0051d450[4];
extern int DAT_0051d458[4];
extern int DAT_0051d460[4];
extern int DAT_0051d468[4];
extern int DAT_0051d470[4];
extern int DAT_0051d478[4];
extern int DAT_0051d480[4];
extern int DAT_0051d488[4];
extern int DAT_0051d490[4];
extern int DAT_0051d498[4];
extern int DAT_0051d4a0[4];
extern int DAT_0051d4a8[4];
extern int DAT_0051d4b0[4];
extern int DAT_0051d4b8[4];
extern int DAT_0051d4c8[4];
extern unsigned char GPR_00554a78, GPR_00554a7c, GPR_00554a80, GPR_00554a84, GPR_00554a88, GPR_00554a8c, GPR_00554a90, GPR_00554a94, GPR_00554a98, GPR_00554a9c, GPR_00554c14;

}
/* Owning stack reference to the freshly created property list; released on scope exit (reference
 * count in the low 23 bits of references). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->references; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class VC140 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void vX(Model *, void *); };

#define W(f) ((List *)w->f)
#define SETI(L, I, V) if (((List *)(L))->size != 0 && (I) >= 0 && (I) < ((List *)(L))->size) ((List *)(L))->data[I] = (V);
#define SETB(L, I, V) if (((BList *)(L))->size != 0 && (I) >= 0 && (I) < ((BList *)(L))->size) ((BList *)(L))->data[I] = (V);
#define MS(t) __divdi3((long long)(t) * 1000000000, 60)
#define CALLV(name) ((VC140 *)self)->vX(obj, name)
#define RELEASE(o) if ((o) != 0) { (o)->references = (o)->references - 1; if (((unsigned long long)((long long)(o)->references << 0x29) >> 0x29) == 0) igObject_Destroy(o); }

static inline void ensureProps(Model *obj)
{
    if (obj->props == 0) {
        int allocator = igObject_GetAllocator(obj);
        igSmartPointer<List> holder((List *)beBaseInfoDataList_Create(GPR_00554c14 != 0 ? allocator : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        List *created = holder.p;
        if (created != 0) created->references = created->references + 1;
        List *old = obj->props;
        RELEASE(old)
        obj->props = created;
    }
}

extern "C" void Gap__Bec__beNDMWMdlPEBase__vfunc_46(beNDMWMdlPEBase *self, Model *obj);
extern "C" void Gap__Bec__beNDMWMdlPEBase__vfunc_46(beNDMWMdlPEBase *self, Model *obj) {
    beNDMWMdlPEBaseInfoWork *w;
    List *l;
    int n;
    int *d;
    int j;
    int enumExtra;
    ensureProps(obj);
    w = igProperty_FindByName(obj->props, DAT_00585be0[0], &DAT_0051d3a0[0])->work;
    if (w->_timerList != 0) {
        if (((Param *)w->_hp)->value == 0) {
            int i = 0;
            int off = 0;
            int *p = &DAT_004cfc50[0];
            do {
                int v = *(int *)&((BList *)w->_dispRamNoList)->data[off];
                if (v != -1) beMessenger_SendNamed(self->_messenger, &DAT_0051d3a8[0], *p, v, &DAT_0051d3e8[0]);
                i++;
                off += 4;
                p += 1;
            } while (i < 12);
            { List *l1 = W(_timerList); int n1 = l1->size; int *d1 = l1->data; int j1;
              for (j1 = 0; j1 < n1; j1++) { d1[j1] = DAT_004cfcb8[0]; } }
            { List *l2 = W(_dispRamNoList); int n2 = l2->size; int *d2 = l2->data; int j2;
              for (j2 = 0; j2 < n2; j2++) { d2[j2] = DAT_004cfcc0[0]; } }
            return;
        }
        if (w->_messenger == 0) w->_messenger = self->_messenger;
        if (w->_isOnCtrl != 0 && W(_timerList)->data[0] != 0) {
            if (((BList *)w->_isFirstList)->data[0] != 0) {
                FUN_003a7a20(obj, &DAT_0051d3f0[0], 2000000000);
                { int v_ = W(_timerList)->data[0] - 1; SETI(w->_timerList, 0, v_) }
                SETB(w->_isFirstList, 0, GPR_00554a78)
            }
            if (FUN_003a7e90(obj, &DAT_0051d3f0[0]) != 0) {
                Param *hp = (Param *)w->_hp;
                int v = hp->value - w->_poisonDamage;
                if (v >= 0) { v = (int)v; } else { v = 0; } hp->value = v;
                if (w->_isPlayer != 0) {
                    beMessenger_SelectReceivers(self->_messenger, &DAT_0051d3f8[0], &DAT_0051d408[0], obj->id);
                    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)((Param *)w->_hp)->value / (float)((Param *)w->_mHp)->value);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051d410[0]);
                    beMessenger_SelectReceivers(self->_messenger, &DAT_0051d420[0], &DAT_0051d430[0], obj->id);
                    beMessenger_AppendInt(self->_messenger, ((Param *)w->_hp)->value);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051d438[0]);
                }
                hp = (Param *)w->_hp;
                if (hp->value <= 0) {
                    if (w->_isPlayer != 0) {
                        CALLV(&DAT_0051d448[0]);
                        FUN_003a8580(obj, &DAT_0051d3f0[0]);
                        SETI(w->_timerList, 0, DAT_004cfcc8[0])
                    } else {
                        hp->value = 1;
                        FUN_003a8580(obj, &DAT_0051d3f0[0]);
                        SETI(w->_timerList, 0, DAT_004cfcd0[0])
                    }
                } else {
                    { int v_ = W(_timerList)->data[0] - 1; SETI(w->_timerList, 0, v_) }
                    if (W(_timerList)->data[0] <= 0) {
                        FUN_003a8580(obj, &DAT_0051d3f0[0]);
                        SETI(w->_timerList, 0, DAT_004cfcd8[0])
                    } else {
                        FUN_003a7a20(obj, &DAT_0051d3f0[0], 2000000000);
                    }
                }
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[8] != 0) {
            if (((BList *)w->_isFirstList)->data[8] != 0) {
                FUN_003a7a20(obj, &DAT_0051d450[0], MS(W(_timerList)->data[8]));
                if (strcmp(w->_seqCodeName, &DAT_0051d458[0]) != 0) CALLV(&DAT_0051d458[0]);
                SETB(w->_isFirstList, 8, GPR_00554a7c)
            }
            if (FUN_003a7e90(obj, &DAT_0051d450[0]) != 0) {
                CALLV(&DAT_0051d460[0]);
                FUN_003a8580(obj, &DAT_0051d450[0]);
                SETI(w->_timerList, 8, DAT_004cfce0[0])
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[9] != 0 && strcmp(w->_seqCodeName, &DAT_0051d468[0]) == 0) {
            if (((BList *)w->_isFirstList)->data[9] != 0) {
                FUN_003a7a20(obj, &DAT_0051d470[0], MS(W(_timerList)->data[9]));
                SETB(w->_isFirstList, 9, GPR_00554a80)
            }
            if (FUN_003a7e90(obj, &DAT_0051d470[0]) != 0) {
                SETI(w->_timerList, 9, DAT_004cfce8[0])
                FUN_003a8580(obj, &DAT_0051d470[0]);
                CALLV(&DAT_0051d460[0]);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[3] != 0) {
            if (((BList *)w->_isFirstList)->data[3] != 0) {
                FUN_003a7a20(obj, &DAT_0051d478[0], MS(W(_timerList)->data[3]));
                SETB(w->_isFirstList, 3, GPR_00554a84)
            }
            if (FUN_003a7e90(obj, &DAT_0051d478[0]) != 0) {
                FUN_003a8580(obj, &DAT_0051d478[0]);
                SETI(w->_timerList, 3, DAT_004cfcf0[0])
                CALLV(&DAT_0051d460[0]);
            } else {
                if (!(igMetaEnum_GetValueByName(FUN_003c03e0(), w->_seqCodeName, &enumExtra) == DAT_004fb410)) {
                    OList *moves = (OList *)w->_moveObjectList;
                    int n = moves->size;
                    int i;
                    for (i = 0; i < n; i++) {
                        if (i != 1) {
                            beModelCtrlMoveObject *o = moves->data[i];
                            o->_isRun = 0;
                            o->_speed = 0;
                        }
                    }
                }
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[1] != 0) {
            if (((BList *)w->_isFirstList)->data[1] != 0) {
                FUN_003a7a20(obj, &DAT_0051d480[0], MS(W(_timerList)->data[1]));
                SETB(w->_isFirstList, 1, GPR_00554a88)
            }
            if (FUN_003a7e90(obj, &DAT_0051d480[0]) != 0) {
                FUN_003a8580(obj, &DAT_0051d480[0]);
                SETI(w->_timerList, 1, DAT_004cfcf8[0])
                SETI(w->_downDataList, 0, DAT_004cfd00[0])
                SETI(w->_downDataList, 1, DAT_004cfd08[0])
                SETI(w->_downDataList, 2, DAT_004cfd10[0])
                SETI(w->_downDataList, 3, DAT_004cfd18[0])
                FUN_00445c60(self, obj, w);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[2] != 0) {
            if (((BList *)w->_isFirstList)->data[2] != 0) {
                FUN_003a7a20(obj, &DAT_0051d488[0], MS(W(_timerList)->data[2]));
                SETB(w->_isFirstList, 2, GPR_00554a8c)
            }
            if (FUN_003a7e90(obj, &DAT_0051d488[0]) != 0) {
                FUN_003a8580(obj, &DAT_0051d488[0]);
                SETI(w->_timerList, 2, DAT_004cfd20[0])
                SETI(w->_downDataList, 4, DAT_004cfd28[0])
                SETI(w->_downDataList, 5, DAT_004cfd30[0])
                FUN_00445c60(self, obj, w);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[5] != 0) {
            if (((BList *)w->_isFirstList)->data[5] != 0) {
                FUN_003a7a20(obj, &DAT_0051d490[0], MS(W(_timerList)->data[5]));
                SETB(w->_isFirstList, 5, GPR_00554a90)
            }
            if (FUN_003a7e90(obj, &DAT_0051d490[0]) != 0) {
                FUN_003a8580(obj, &DAT_0051d490[0]);
                SETI(w->_timerList, 5, DAT_004cfd38[0])
                SETI(w->_upDataList, 0, DAT_004cfd40[0])
                SETI(w->_upDataList, 1, DAT_004cfd48[0])
                SETI(w->_upDataList, 2, DAT_004cfd50[0])
                SETI(w->_upDataList, 3, DAT_004cfd58[0])
                FUN_00445c60(self, obj, w);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[6] != 0) {
            if (((BList *)w->_isFirstList)->data[6] != 0) {
                FUN_003a7a20(obj, &DAT_0051d498[0], MS(W(_timerList)->data[6]));
                SETB(w->_isFirstList, 6, GPR_00554a94)
            }
            if (FUN_003a7e90(obj, &DAT_0051d498[0]) != 0) {
                FUN_003a8580(obj, &DAT_0051d498[0]);
                SETI(w->_timerList, 6, DAT_004cfd60[0])
                SETI(w->_upDataList, 4, DAT_004cfd68[0])
                SETI(w->_upDataList, 5, DAT_004cfd70[0])
                SETI(w->_upDataList, 6, DAT_004cfd78[0])
                FUN_00445c60(self, obj, w);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[4] != 0) {
            if (((BList *)w->_isFirstList)->data[4] != 0) {
                FUN_003a7a20(obj, &DAT_0051d4a0[0], MS(W(_timerList)->data[4]));
                SETB(w->_isFirstList, 4, GPR_00554a98)
            }
            if (FUN_003a7e90(obj, &DAT_0051d4a0[0]) != 0) {
                FUN_003a8580(obj, &DAT_0051d4a0[0]);
                SETI(w->_timerList, 4, DAT_004cfd80[0])
                SETI(w->_upDataList, 7, DAT_004cfd88[0])
                SETI(w->_upDataList, 8, DAT_004cfd90[0])
                SETI(w->_upDataList, 9, DAT_004cfd98[0])
                SETI(w->_upDataList, 10, DAT_004cfda0[0])
                FUN_00445c60(self, obj, w);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[7] != 0) {
            if (((BList *)w->_isFirstList)->data[7] != 0) {
                SETI(w->_downDataList, 6, DAT_004cfda8[0])
                FUN_003a7a20(obj, &DAT_0051d4a8[0], 0);
                SETB(w->_isFirstList, 7, GPR_00554a9c)
            }
            if (FUN_003a7e90(obj, &DAT_0051d4a8[0]) != 0) {
                int t120;
                { List *L_ = W(_downDataList); int v_ = L_->data[6] + 4; SETI(L_, 6, v_) }
                beMessenger_SelectGroup(self->_messenger, &DAT_0051d4b0[0]);
                beMessenger_AppendInt(self->_messenger, obj->id);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051d4b8[0]);
                t120 = igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), &DAT_0051d4c8[0])->value * 120;
                FUN_003a7a20(obj, &DAT_0051d4a8[0], MS(t120));
                FUN_00445c60(self, obj, w);
            }
        }
        {
            bool flag = false;
            int count = 0;
            int i = 0;
            do {
                int r;
                if (i == 11) { int fv = flag; SETI(w->_timerList, i, fv) }
                if (W(_timerList)->data[i] != 0) {
                    if (i < 8) {
                        bool changed = false;
                        if (count != W(_dispPosNoList)->data[i]) {
                            SETI(w->_dispPosNoList, i, count)
                            changed = true;
                        }
                        r = FUN_00443900(self, obj, DAT_004cfc50[i], W(_dispRamNoList)->data[i], count, changed);
                        count++;
                    } else if (i != 10) {
                        r = FUN_00443900(self, obj, DAT_004cfc50[i], W(_dispRamNoList)->data[i], 0, 0);
                    } else {
                        r = FUN_00443900(self, obj, DAT_004cfc50[i], W(_dispRamNoList)->data[i], W(_timerList)->data[10] - 1, 0);
                    }
                    SETI(w->_dispRamNoList, i, r)
                    if (i < 8) flag = true;
                } else {
                    int v = W(_dispRamNoList)->data[i];
                    if (v != -1) {
                        beMessenger_SendNamed(self->_messenger, &DAT_0051d3a8[0], DAT_004cfc50[i], v, &DAT_0051d3e8[0]);
                        SETI(w->_dispRamNoList, i, DAT_004cfdb0[0])
                    }
                }
                i++;
            } while (i < 12);
        }
    }
}

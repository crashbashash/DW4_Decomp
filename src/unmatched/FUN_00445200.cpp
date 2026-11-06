#include "dw4/reflected.h"
/* matching construct: MessengerVirt carries 33 dummy virtuals so vX() dispatches through the same vtable slot as retail; the receiver is reached as a beNDMWMdlPEBase and cast only for that one call */
extern "C" {
igObject *beBaseInfoDataList_Create(...);
int FUN_003a8580(...);
void *Memory_GetAllocatorBySelector(...);
int beMessenger_SendNamed(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
void *igProperty_FindByName(...);
int igStrCmp(...);
extern int DAT_004cfc50[4];
extern int DAT_004cfc74[4];
extern int DAT_004cfdb8[4];
extern int DAT_004cfdc0[4];
extern int DAT_004cfdc8[4];
extern int DAT_004cfdd0[4];
extern int DAT_0051d3a0[4];
extern int DAT_0051d3a8[4];
extern int DAT_0051d3e8[4];
extern int DAT_0051d450[4];
extern int DAT_0051d458[4];
extern int DAT_0051d460[4];
extern int DAT_0051d468[4];
extern int DAT_0051d470[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554aa0;
extern unsigned char GPR_00554aa4;
extern unsigned char GPR_00554c14;
}
struct HpWord { char pad[12]; int f12; };
class MessengerVirt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(void *, void *); };

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

#define SETI(L, I, V) if ((L)->_count != 0 && (I) >= 0 && (I) < (L)->_count) ((int *)(L)->_data)[I] = (V);
#define SETB(L, I, V) if ((L)->_count != 0 && (I) >= 0 && (I) < (L)->_count) ((unsigned char *)(L)->_data)[I] = (V);
extern "C" void FUN_00445200(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1) {
    void *al;
    beNDMWMdlPEBaseInfoWork *st;
    igObject *s1;
    igObject *old;
    if (arg1->_dataList == 0) {
        al = igObject_GetAllocator(arg1);
        if (GPR_00554c14 != 0) {
            al = (void *)(int)al;
        } else {
            al = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        ObjectRef ref(beBaseInfoDataList_Create(al));
        s1 = ref.p;
        if (s1 != 0) s1->_refCount = s1->_refCount + 1;
        old = (igObject *)arg1->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        arg1->_dataList = (int)s1;
    }
    st = *(beNDMWMdlPEBaseInfoWork **)((char *)igProperty_FindByName((igObject *)arg1->_dataList, DAT_00585be0[0], &DAT_0051d3a0[0]) + 20);
    if (st->_dispRamNoList != 0) {
        if (((igIntList *)st->_dispRamNoList)->_count != 0 && ((HpWord *)st->_hp)->f12 == 0) {
            int i;
            for (i = 0; i < 12; i++) {
                int v = ((int *)((igIntList *)st->_dispRamNoList)->_data)[i];
                if (v != -1) beMessenger_SendNamed(arg0->_messenger, &DAT_0051d3a8[0], DAT_004cfc50[i], v, &DAT_0051d3e8[0]);
            }
            {
                igIntList *l = (igIntList *)st->_timerList;
                int n = l->_count;
                int *q = (int *)l->_data;
                int j;
                for (j = 0; j < n; j++) q[j] = DAT_004cfdb8[0];
            }
            {
                igIntList *l2 = (igIntList *)st->_dispRamNoList;
                int n2 = l2->_count;
                int *q2 = (int *)l2->_data;
                int k;
                for (k = 0; k < n2; k++) q2[k] = DAT_004cfdc0[0];
            }
            return;
        }
        if (((igIntList *)st->_timerList)->_count != 0) {
            if (((int *)((igIntList *)st->_timerList)->_data)[8] != 0 && igStrCmp((char *)st->_seqCodeName, &DAT_0051d458[0]) != 0) {
                FUN_003a8580(arg1, &DAT_0051d450[0]);
                SETB((igUnsignedCharList *)st->_isFirstList, 8, GPR_00554aa0)
                SETI((igIntList *)st->_timerList, 8, DAT_004cfdc8[0])
            }
            if (((int *)((igIntList *)st->_timerList)->_data)[9] != 0) {
                if (igStrCmp((char *)st->_seqCodeName, &DAT_0051d460[0]) == 0) {
                    ((MessengerVirt *)arg0)->vX(arg1, &DAT_0051d468[0]);
                    return;
                }
                if (igStrCmp((char *)st->_seqCodeName, &DAT_0051d468[0]) != 0) {
                    FUN_003a8580(arg1, &DAT_0051d470[0]);
                    SETB((igUnsignedCharList *)st->_isFirstList, 9, GPR_00554aa4)
                    SETI((igIntList *)st->_timerList, 9, DAT_004cfdd0[0])
                    beMessenger_SendNamed(arg0->_messenger, &DAT_0051d3a8[0], DAT_004cfc74[0], ((int *)((igIntList *)st->_dispRamNoList)->_data)[9], &DAT_0051d3e8[0]);
                }
            }
        }
    }
}

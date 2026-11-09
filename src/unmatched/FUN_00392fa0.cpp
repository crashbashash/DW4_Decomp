/* matching construct: PropV carries 35 dummy virtuals so vX() dispatches through vtable offset 148 (lw t9,0(a0); lw t9,148(t9); jalr t9); the (int) self-assignment of var_v0 keeps the GPR_00554c14 select shape */
#include "dw4/igSmartPointer.h"
struct PropV { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void vX(void *); };
typedef beModelCtrlMoveObject *MoveObjRef;
#define MOVES(w) ((MoveObjRef *)((beModelCtrlMoveObjectList *)(w)->_moveObjectList)->_data)
extern "C" {
igObject *beBaseInfoDataList_Create(...);
float FUN_00392e10(void *, float);
int FUN_003956e0(...);
int FUN_00396940(...);
float FUN_003a8140(...);
int Matrix44_Copy(...);
int Matrix44_TranslateLocal(...);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
beModelCtrlInfoRamData *igProperty_FindByName(...);
extern int DAT_0050ef60[4];
extern int DAT_0050f0b8[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */

extern "C" void FUN_00392fa0(beModelCtrl *arg0, int arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3);
void FUN_00392fa0(beModelCtrl *arg0, int arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3) {
    float vec[3];
    int sp70[16];
    float f20;
    float f3;
    int var_v0;
    beModelCtrlMoveObjectList *info;
    MoveObjRef *lst;
    beModelCtrlInfoRamData *prop;
    igObject *s1;
    igObject *t;
    void *a2;

    info = (beModelCtrlMoveObjectList *)arg3->_moveObjectList;
    arg3->_isHitCheck = 0;
    if (info->_count != 0) {
        f20 = FUN_003a8140(arg2, &DAT_0050f0b8[0]);
        if (((MoveObjRef *)info->_data)[3]->_isRun != 0) {
            f3 = 0.017453292f * FUN_00392e10(MOVES(arg3)[3], f20);
            *(float *)&arg3->_targetDirection[1] = *(float *)&arg3->_targetDirection[1] + f3;
            if (f3 < 0.0f) {
                f3 = -f3;
            }
            *(float *)&arg3->_directionLimiter[1] = 1.25f * f3;
        }
        FUN_003956e0(arg0, arg1, arg2, arg3, 0);
        lst = (MoveObjRef *)info->_data;
        if (lst[0]->_isRun != 0 || lst[1]->_isRun != 0 || lst[2]->_isRun != 0) {
            if (arg2->_dataList == 0) {
                var_v0 = igObject_GetAllocator(arg2);
                if (GPR_00554c14 != 0) {
                    var_v0 = (int)var_v0;
                } else {
                    var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                }
                {
                    igSmartPointer<igObject> r(beBaseInfoDataList_Create(var_v0));
                    s1 = r.p;
                    if (s1 != 0) {
                        s1->_refCount = s1->_refCount + 1;
                    }
                    t = (igObject *)arg2->_dataList;
                    if (t != 0) {
                        t->_refCount = t->_refCount - 1;
                        if ((t->_refCount & 0x7FFFFF) == 0) {
                            igObject_Destroy(t);
                        }
                    }
                    arg2->_dataList = (int)s1;
                }
            }
            prop = igProperty_FindByName((igObject *)arg2->_dataList, DAT_00585be0[0], &DAT_0050ef60[0]);
            Matrix44_Copy(sp70, (char *)prop->_node + 0x20);
            vec[0] = FUN_00392e10(MOVES(arg3)[0], f20);
            vec[1] = FUN_00392e10(MOVES(arg3)[1], f20);
            vec[2] = FUN_00392e10(MOVES(arg3)[2], f20);
            Matrix44_TranslateLocal(sp70, vec);
            ((PropV *)prop->_node)->vX(sp70);
            arg3->_isHitCheck = 1;
            a2 = (void *)arg3->_baseAABox;
            if (a2 != 0) {
                FUN_00396940(arg0, (PropV *)prop->_node, a2);
            }
        }
    }
}

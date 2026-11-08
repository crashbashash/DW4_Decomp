#include "dw4/reflected.h"
struct MsgView {
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual int v33(beBaseInfoRam *, int *);
};
struct UpdView {
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual int v46(beBaseInfoRam *);
};
struct NodeView {
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual int v35(int *);
};
struct RideView {
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
    virtual void d20();
    virtual int v21(int *);
};
extern "C" {
int igMatrix44f_SetIdentity(...);
int FUN_001904f0(...);
int FUN_001906d0(...);
int FUN_00191f30(...);
int FUN_002eb010(...);
igObject *beBaseInfoDataList_Create(...);
int FUN_00391cf0(...);
int FUN_003926d0(...);
int FUN_00392fa0(...);
int FUN_00394bf0(...);
int FUN_003951e0(...);
int FUN_00396940(...);
int FUN_00399e20(...);
int FUN_003a8580(...);
int Matrix44_Copy(...);
int Matrix44_GetTranslation(...);
int Matrix44_SetTranslation(...);
int Matrix44_TranslateLocal(...);
int Memory_GetAllocatorBySelector(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetMatrix(...);
int beMessenger_GetMatrixCount(...);
int beMessenger_SelectReceivers(...);
int beMessenger_SendNamed(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
void *igProperty_FindByName(...);
int strcmp(...);
extern float DAT_004e1058[4];
extern int DAT_0050ef18[4];
extern int DAT_0050ef60[4];
extern int DAT_0050ef68[4];
extern int DAT_0050efe8[4];
extern int DAT_0050eff8[4];
extern int DAT_0050f000[4];
extern int DAT_0050f1b8[4];
extern int DAT_0050f1c0[4];
extern int DAT_0050f1c8[4];
extern void * DAT_00561288[4];
extern int DAT_00585be0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Core__igObject__vfunc_31(beModelCtrl *arg0, beBaseInfoRam *arg1);
}
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void Gap__Core__igObject__vfunc_31(beModelCtrl *arg0, beBaseInfoRam *arg1) {
    int sp27C;
    float sp268[3];
    float sp258[3];
    float sp248[3];
    float sp238[3];
    int sp1F0[16];
    int sp1B0[16];
    int sp170[16];
    int sp130[16];
    int spF0[16];
    int spB0[16];
    int sp70[16];
    int s2 = arg1->_parentInfo;
    if (arg1->_dataList == 0) {
        int base = igObject_GetAllocator(arg1);
        int a;
        igObject *o;
        igObject *old;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
        ObjectRef ref(beBaseInfoDataList_Create(a));
        o = ref.p;
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)arg1->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        arg1->_dataList = (int)o;
    }
    beModelCtrlInfoRamData *prop = (beModelCtrlInfoRamData *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_0050ef60[0]);
    beModelCtrlInfoWork *q = (beModelCtrlInfoWork *)prop->_work;
    if (arg1->_isRun != 0 && q->_isOnFreeze == 0) {
        int t;
        int posNode;
        beModelCtrlInfoRideOn4 *p;
        if (strcmp(q->_seqCodeName, &DAT_0050f1b8[0]) == 0) {
            ((MsgView *)arg0)->v33(arg1, &DAT_0050f1c0[0]);
            return;
        }
        q->_keyInput = 0;
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        t = StringPool_Intern(DAT_00586f20[0], &DAT_0050efe8[0]);
        if (q->_keyEventName != 0) {
            int *hdr = (int *)(q->_keyEventName - 8);
            int c = *(int *)(q->_keyEventName - 4) - 1;
            *(int *)(q->_keyEventName - 4) = c;
            if (c == 0) StringChunk_ReleaseHeader(*hdr, hdr);
        }
        q->_keyEventName = t;
        if (q->_ctrlSt0 != 0) {
            FUN_00391cf0(arg0, s2, arg1, q);
        } else if (q->_aI != 0) {
            FUN_003a8580(arg1, &DAT_0050ef68[0]);
        }
        ((UpdView *)arg0)->v46(arg1);
        if (q->_isPosLock == 0) {
            FUN_00392fa0(arg0, s2, arg1, q);
        } else {
            if (q->_posLockNode != 0) {
                Matrix44_Copy(sp1F0, q->_posLockNode + 32);
                Matrix44_TranslateLocal(sp1F0, &q->_posLockOffset[0]);
                ((NodeView *)prop->_node)->v35(sp1F0);
            } else if (q->_posLockTrc != 0) {
                ((NodeView *)prop->_node)->v35((int *)(*(int *)(q->_posLockTrc + 16) + *(int *)((char *)DAT_00561288[0] + 8)));
            } else if (q->_posLockModelName != 0) {
                beMessenger_SelectReceivers(arg0->_messenger, &DAT_0050eff8[0], q->_posLockModelName, arg1->_ramNo);
                beMessenger_AppendString(arg0->_messenger, q->_posLockBoneName);
                beMessenger_DispatchSelected(arg0->_messenger, &DAT_0050f1c8[0]);
                if (beMessenger_GetMatrixCount(arg0->_messenger) == 1) {
                    beMessenger_GetMatrix(sp1B0, arg0->_messenger, 0);
                    beMessenger_SendNamed(arg0->_messenger, &DAT_0050ef18[0], q->_posLockModelName, arg1->_ramNo, &DAT_0050f000[0]);
                    if (beMessenger_GetMatrixCount(arg0->_messenger) == 1) {
                        beMessenger_GetMatrix(sp170, arg0->_messenger, 0);
                        FUN_001906d0(sp170, sp1B0);
                        ((NodeView *)prop->_node)->v35(sp170);
                    }
                }
            }
            if (q->_baseAABox != 0) FUN_00396940(arg0, prop->_node, q->_baseAABox);
        }
        p = (beModelCtrlInfoRideOn4 *)q->_rideOnData;
        if (p != 0) {
            ((RideView *)p)->v21((int *)(prop->_node + 32));
            Matrix44_GetTranslation(p->_oldMatrix, sp268);
            Matrix44_GetTranslation(prop->_node + 32, sp258);
            sp248[0] = sp258[0] - sp268[0];
            sp248[1] = sp258[1] - sp268[1];
            sp248[2] = sp258[2] - sp268[2];
            Matrix44_Copy(sp130, p->_oldMatrix);
            Matrix44_Copy(spF0, prop->_node + 32);
            Matrix44_SetTranslation(sp130, &DAT_004e1058[0]);
            FUN_00191f30(&sp27C, sp130, sp130);
            Matrix44_SetTranslation(spF0, sp248);
            igMatrix44f_SetIdentity(spB0);
            FUN_001904f0(spB0, spF0, sp130);
            igMatrix44f_SetIdentity(sp70);
            FUN_001904f0(sp70, spB0, p->_modelNode + 32);
            ((NodeView *)prop->_node)->v35(sp70);
            Matrix44_Copy(p->_oldMatrix, p->_modelNode + 32);
            q->_isHitCheck = 1;
        }
        if (q->_wCheckName != 0) FUN_00394bf0(arg0, s2, arg1, q);
        FUN_003951e0(arg0, arg1, q);
        FUN_00399e20(q->_subCommand, arg1);
        if (q->_isHitCheck != 0) FUN_003926d0(arg0, s2, arg1, q);
        p = (beModelCtrlInfoRideOn4 *)q->_rideOnData;
        if (p != 0 && p->_modelRamNo == 0x68) {
            Matrix44_GetTranslation(prop->_node + 32, sp238);
            ((float *)&p->_oldPlayerPos[0])[0] = sp238[0];
            ((float *)&p->_oldPlayerPos[0])[1] = sp238[1];
            ((float *)&p->_oldPlayerPos[0])[2] = sp238[2];
        }
    }
}

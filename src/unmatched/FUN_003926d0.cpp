#include "dw4/reflected.h"
extern "C" {
void *FUN_00351e20(...);
int FUN_00392050(...);
int FUN_003921a0(...);
int FUN_00392be0(...);
int FUN_00394400(...);
int Memory_GetAllocatorBySelector(...);
int beMessenger_GetBool(...);
int beMessenger_GetBoolCount(...);
int beMessenger_GetInt(...);
int beMessenger_GetString(...);
int beMessenger_GetStringCount(...);
int beMessenger_SendNamed(...);
int igObject_GetAllocator(...);
int igStrCmp(...);
void igObject_Destroy(...);
extern int DAT_004e0858[4];
extern int DAT_0050f010[4];
extern int DAT_0050f018[4];
extern int DAT_0050f028[4];
extern int DAT_0050f038[4];
extern int DAT_0050f040[4];
extern int DAT_0050f050[4];
extern int DAT_0050f058[4];
extern int DAT_0050f068[4];
extern int DAT_0050f070[4];
extern int DAT_0050f078[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
class VO { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(void *, void *); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void vX(void *); };
struct Slot { beModelCtrlInfoRideOn4 *p; void set(beModelCtrlInfoRideOn4 *n) { beModelCtrlInfoRideOn4 *o = p; if (o) { --o->_refCount; if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } p = n; } };
/* Scope holder for the freshly built ride-on record; retail keeps its out-of-line destructor at 0x350d90. The
 * constructor takes the allocation result, so the protected range starts after the allocation call. */
struct RideOnRef { beModelCtrlInfoRideOn4 *p; RideOnRef(beModelCtrlInfoRideOn4 *x) { p = x; } ~RideOnRef() { beModelCtrlInfoRideOn4 *o = p; if (o) { --o->_refCount; if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } } };
extern "C" void FUN_003926d0(beModelCtrl *arg0, beBaseInfoRam *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3);
void FUN_003926d0(beModelCtrl *arg0, beBaseInfoRam *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3) {
    unsigned char b0;
    bool s8;
    int s7;
    int s6;
    int s5;
    int s0;
    s8 = false;
    if (arg3->_isWallCheck) {
        int *t0;
        int a2, a3;
        if (arg3->_rideOnData == 0) t0 = DAT_0050f010; else t0 = DAT_0050f018;
        a2 = arg1->_ramNo;
        a3 = arg2->_ramNo;
        a2 = a2 ? a2 : (int)DAT_004e0858;
        beMessenger_SendNamed(arg0->_messenger, DAT_0050f028, a2, a3, t0);
        if (arg3->_luaWHit != 0 && beMessenger_GetBool(arg0->_messenger, 1) != 0) {
            int s = arg1->_ramNo;
            s = s ? s : (int)DAT_004e0858;
            FUN_00394400(arg0, arg2, arg3->_luaWHit, DAT_0050f038, s, 0, 0, 0, 0, 0);
        }
    }
    if (arg3->_isFloorCheck) {
        if (FUN_00392be0(arg0, arg2, arg3, 3)) return;
        {
            int a2 = arg1->_ramNo;
            int a3 = arg2->_ramNo;
            a2 = a2 ? a2 : (int)DAT_004e0858;
            beMessenger_SendNamed(arg0->_messenger, DAT_0050f028, a2, a3, DAT_0050f040);
        }
        if (beMessenger_GetBoolCount(arg0->_messenger) == 0) return;
        s0 = 0;
        s6 = beMessenger_GetStringCount(arg0->_messenger);
        if (s6 != 0) {
            s0 = beMessenger_GetString(arg0->_messenger, 0);
            if (igStrCmp(s0, DAT_0050f050) != 0) {
                s5 = beMessenger_GetInt(arg0->_messenger, 0);
            } else {
                s6 = 0;
            }
        }
        b0 = beMessenger_GetBool(arg0->_messenger, 0);
        s7 = beMessenger_GetBool(arg0->_messenger, 1) & 0xFF;
        s8 = false;
        if (arg3->_isFallCheck) {
            if (FUN_00392be0(arg0, arg2, arg3, 4)) {
                if (s7 != 0) {
                    int a2 = arg1->_ramNo;
                    int a3 = arg2->_ramNo;
                    a2 = a2 ? a2 : (int)DAT_004e0858;
                    beMessenger_SendNamed(arg0->_messenger, DAT_0050f028, a2, a3, DAT_0050f058);
                    FUN_00392be0(arg0, arg2, arg3, 5);
                    s8 = true;
                }
            } else if (b0) {
                int a2 = arg1->_ramNo;
                int a3 = arg2->_ramNo;
                a2 = a2 ? a2 : (int)DAT_004e0858;
                beMessenger_SendNamed(arg0->_messenger, DAT_0050f028, a2, a3, DAT_0050f058);
                FUN_00392be0(arg0, arg2, arg3, 5);
                return;
            } else {
                if (igStrCmp(arg3->_seqCodeName, DAT_0050f068) == 0) return;
                ((VO *)arg0)->d33(arg2, DAT_0050f070);
                return;
            }
        }
        if (arg3->_luaFHit != 0 && s7 != 0) {
            int s = arg1->_ramNo;
            s = s ? s : (int)DAT_004e0858;
            FUN_00394400(arg0, arg2, arg3->_luaFHit, DAT_0050f078, s, 0, 0, 0, 0, 0);
        }
        if (s8) {
            beModelCtrlInfoRideOn4 *a0 = (beModelCtrlInfoRideOn4 *)arg3->_rideOnData;
            if (a0 == 0 || a0->_modelRamNo < 100) {
                if (s6 == 0) {
                    if (a0 != 0) {
                        ((Slot *)&arg3->_rideOnData)->set(0);
                    }
                } else if (a0 == 0) {
                    int alloc = igObject_GetAllocator(arg0);
                    int a;
                    beModelCtrlInfoRideOn4 *n;
                    if (GPR_00554c14 != 0) a = alloc; else a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    RideOnRef holder((beModelCtrlInfoRideOn4 *)FUN_00351e20(a));
                    FUN_00392050(holder.p, s0, s5, arg0->_messenger);
                    n = holder.p;
                    if (n != 0) n->_refCount++;
                    ((Slot *)&arg3->_rideOnData)->set(n);
                } else if (!(FUN_003921a0(a0, s0, s5) & 0xFF)) {
                    FUN_00392050((beModelCtrlInfoRideOn4 *)arg3->_rideOnData, s0, s5, arg0->_messenger);
                }
            }
        }
    }
}

#include "dw4/reflected.h"

extern "C" void Gap__Bec__beMeterCtrl__vfunc_32(void);
extern "C" int Gap__Bec__beMeterCtrl__vfunc_30(void);
extern "C" int Gap__Bec__beMeterCtrl__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int FUN_00357600(...);
extern "C" int FUN_0038f9b0(...);
extern "C" int beMessenger_AppendFloat(int, float);
extern "C" float beMessenger_GetFloat(int, int);
extern "C" int beMessenger_GetInt(int, int);
extern "C" void *beMessenger_GetObject(int, int);
extern "C" int beMessenger_GetString(int, int);
extern "C" int beMessenger_PopArgContext(int);
extern "C" int beMessenger_PushArgContext(int);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, int);
extern "C" int beMessenger_SendNamed(int, void *, int, int, void *);
extern "C" int igObject_Destroy(...);
extern "C" int g_beMeterCtrlInfo_metaObject[4];
extern "C" int g_beMeterCtrl_metaObject[4];
extern "C" char METERCTRL_3[];
extern "C" void Gap__Bec__beMeterCtrl__vfunc_29(beMeterCtrl * p0, int p1, char * p2);
extern "C" int MODELCTRL_11[4];
extern "C" int GETHP_2[4];
extern "C" int Gap__Bec__beMeterCtrl__vfunc_33(beMeterCtrl *arg0, beBaseInfoRam *arg1, int arg2);

void Gap__Bec__beMeterCtrl__vfunc_32(void)
{
}

int Gap__Bec__beMeterCtrl__vfunc_30(void)
{
    return g_beMeterCtrlInfo_metaObject[0];
}

void Gap__Bec__beMeterCtrl__vfunc_29(beMeterCtrl * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, METERCTRL_3);
}

int Gap__Bec__beMeterCtrl__vfunc_33(beMeterCtrl *arg0, beBaseInfoRam *arg1, int arg2) {
    beMeterCtrlOneData *s1;
    igObjectList *l;
    float f0, f2, f3, v;
    unsigned char zero;
    int s3, s0;
    igObject *o;
    l = (igObjectList *)((beMeterCtrlInfo *)arg1->_parentInfo)->_oneDataList;
    s1 = ((beMeterCtrlOneData **)l->_data)[arg1->_ramNo];
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_00357600(l), arg2)) {
    case 0:
        beMessenger_AppendFloat(arg0->_messenger, s1->_nowValueF);
        return 1;
    case 1:
        f0 = beMessenger_GetFloat(arg0->_messenger, 0);
        s1->_nowValueF = f0;
        s1->_dspValueF = f0;
        s1->_isChange = 1;
        return 1;
    case 2:
        v = beMessenger_GetFloat(arg0->_messenger, 0);
        v += s1->_nowValueF;
        if (v > s1->_maxValueF) v = s1->_maxValueF; else if (v < 0.0f) v = 0.0f;
        s1->_nowValueF = v;
        return 1;
    case 3:
        beMessenger_AppendFloat(arg0->_messenger, s1->_nowValueF / s1->_maxValueF);
        return 1;
    case 4:
        if (s1->_hp == 0) {
            f0 = beMessenger_GetFloat(arg0->_messenger, 0);
            zero = (f0 != 0.0f);
            v = (f0 * s1->_maxValueF) / 100.0f;
            if (v < 1.0f && zero) v = 1.0f;
            s1->_nowValueF = v;
        }
        return 1;
    case 5:
        f2 = s1->_maxValueF;
        v = beMessenger_GetFloat(arg0->_messenger, 0); v = (v * f2) / 100.0f;
        v += s1->_nowValueF;
        if (v > s1->_maxValueF) v = s1->_maxValueF; else if (v < 0.0f) v = 0.0f;
        s1->_nowValueF = v;
        return 1;
    case 6:
        s1->_maxValueF = beMessenger_GetFloat(arg0->_messenger, 0);
        FUN_0038f9b0(arg0, s1);
        return 1;
    case 7:
        s3 = beMessenger_GetString(arg0->_messenger, 0);
        s0 = beMessenger_GetInt(arg0->_messenger, 0);
        beMessenger_PushArgContext(arg0->_messenger);
        beMessenger_SendNamed(arg0->_messenger, &MODELCTRL_11[0], s3, s0, &GETHP_2[0]);
        o = (igObject *)beMessenger_GetObject(arg0->_messenger, 0);
        if (o != 0) o->_refCount = o->_refCount + 1;
        {
            igObject *old = (igObject *)s1->_hp;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        s1->_hp = (int)o;
        o = (igObject *)beMessenger_GetObject(arg0->_messenger, 1);
        if (o != 0) o->_refCount = o->_refCount + 1;
        {
            igObject *old = (igObject *)s1->_mHp;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        s1->_mHp = (int)o;
        beMessenger_PopArgContext(arg0->_messenger);
        return 1;
    default:
        return 0;
    }
}

int Gap__Bec__beMeterCtrl__vfunc_20(void)
{
    return g_beMeterCtrl_metaObject[0];
}

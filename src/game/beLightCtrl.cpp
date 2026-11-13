#include "dw4/reflected.h"

extern "C" void Gap__Bec__beLightCtrl__vfunc_32(void);
extern "C" int Gap__Bec__beLightCtrl__vfunc_30(void);
extern "C" void Gap__Bec__beLightCtrl__vfunc_31(void);
extern "C" int Gap__Bec__beLightCtrl__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int FUN_0035bfb0(...);
extern "C" int beMessenger_GetString(int, int);
extern "C" void beMessenger_GetVec3(void *, int, int);
extern "C" int beMessenger_ResolveEnumValue(int, int, int);
extern "C" void *igProperty_FindByName(int, int, int);
extern "C" int g_beLightCtrlInfo_metaObject[4];
extern "C" int g_beLightCtrl_metaObject[4];
extern "C" char LIGHTCTRL[];
extern "C" void Gap__Bec__beLightCtrl__vfunc_29(beLightCtrl * p0, int p1, char * p2);
extern "C" int g_propertyNameField[4];
struct Light {
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
    virtual void f30(void *);
    virtual void f31(void *);
    virtual void f32(void *);
};
struct V3 { float x; float y; float z; };
struct V4 { float x; float y; float z; int w; };
extern "C" int Gap__Bec__beLightCtrl__vfunc_33(beLightCtrl *arg0, beBaseInfoRam *arg1, int arg2);

void Gap__Bec__beLightCtrl__vfunc_32(void)
{
}

int Gap__Bec__beLightCtrl__vfunc_30(void)
{
    return g_beLightCtrlInfo_metaObject[0];
}

void Gap__Bec__beLightCtrl__vfunc_29(beLightCtrl * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, LIGHTCTRL);
}

void Gap__Bec__beLightCtrl__vfunc_31(void)
{
}

int Gap__Bec__beLightCtrl__vfunc_33(beLightCtrl *arg0, beBaseInfoRam *arg1, int arg2) {
    beLightCtrlInfo *s1;
    V3 a;
    Light *l;
    Light **lp;
    V3 b;
    V3 c;
    int name;
    igLightSet *r;
    V4 v;
    s1 = (beLightCtrlInfo *)arg1->_parentInfo;
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0035bfb0(), arg2)) {
    case 0:
    name = beMessenger_GetString(arg0->_messenger, 0);
        beMessenger_GetVec3(&a, arg0->_messenger, 0);
        beMessenger_GetVec3(&b, arg0->_messenger, 1);
        beMessenger_GetVec3(&c, arg0->_messenger, 2);
        r = (igLightSet *)igProperty_FindByName(s1->_lightSetList, g_propertyNameField[0], name);
        if (r != 0) {
            lp = (Light **)((igLightList *)r->_lights)->_data;
            l = *lp;
            v.w = 0x3F800000;
            v.x = a.x; v.y = a.y; v.z = a.z;
            l->f31(&v);
            v.x = b.x; v.y = b.y; v.z = b.z;
            l->f30(&v);
            v.x = c.x; v.y = c.y; v.z = c.z;
            l->f32(&v);
        }
        return 1;
    default:
        return 0;
    }
}

int Gap__Bec__beLightCtrl__vfunc_20(void)
{
    return g_beLightCtrl_metaObject[0];
}

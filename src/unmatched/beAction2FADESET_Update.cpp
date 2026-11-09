#include "dw4/reflected.h"
struct RefCountedObject { int vt; int rc; };
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 128 */
struct DummyVirtualComponent { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(void *); char pad[24]; int f28; };
struct FadeColor { int x, y, z; float w; };
extern "C" {
int FUN_00193540(...);
float FUN_003a8140(...);
int FUN_003a8580(...);
int ObjectList_RemoveFirstRetained(...);
int igObject_Destroy(...);
extern int DAT_0050dfe0[4];
void beAction2FADESET_Update(void *arg0, beAction2InfoRam *arg1);
}
void beAction2FADESET_Update(void *arg0, beAction2InfoRam *arg1) {
    beAction2InfoWork *c = (beAction2InfoWork *)arg1->_work;
    switch (c->_fadeSt0) {
    case 1: {
        float lim;
        float dt;
        FadeColor v;
        float *pw;
        int list;
        int s1, s2, s3;
        RefCountedObject *a0;
        dt = FUN_003a8140(arg1, &DAT_0050dfe0[0]);
        if (dt != 0.0f) {
            FUN_00193540(&v, 1, ((DummyVirtualComponent *)c->_colorAttr)->f28);
            pw = &v.w;
            *pw = c->_fadeValue + dt * c->_fadeAddValue;
            ((DummyVirtualComponent *)c->_colorAttr)->vX(&v);
            c->_fadeValue = *pw;
            lim = *(float *)&c->_fadeLimitValue;
            if (!(*pw < lim)) {
                list = ((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList;
                if (c->_textureStateAttr == 0) {
                    ObjectList_RemoveFirstRetained(&s1, list, c->_colorAttr, 0);
                    a0 = (RefCountedObject *)c->_colorAttr;
                    if (a0 != 0) {
                        a0->rc = a0->rc - 1;
                        if (((unsigned long long)((long long)a0->rc << 0x29) >> 0x29) == 0) igObject_Destroy(a0);
                    }
                    c->_colorAttr = 0;
                    ObjectList_RemoveFirstRetained(&s2, list, c->_lightingStateAttr, 0);
                    a0 = (RefCountedObject *)c->_lightingStateAttr;
                    if (a0 != 0) {
                        a0->rc = a0->rc - 1;
                        if (((unsigned long long)((long long)a0->rc << 0x29) >> 0x29) == 0) igObject_Destroy(a0);
                    }
                    c->_lightingStateAttr = 0;
                }
                ObjectList_RemoveFirstRetained(&s3, list, c->_blendStateAttr, 0);
                a0 = (RefCountedObject *)c->_blendStateAttr;
                if (a0 != 0) {
                    a0->rc = a0->rc - 1;
                    if (((unsigned long long)((long long)a0->rc << 0x29) >> 0x29) == 0) igObject_Destroy(a0);
                }
                c->_blendStateAttr = 0;
                FUN_003a8580(arg1, &DAT_0050dfe0[0]);
                c->_fadeSt0 = 3;
            }
        }
        break;
    }
    case 2: {
        float dt;
        FadeColor v;
        float *pw;
        float nv;
        dt = FUN_003a8140(arg1, &DAT_0050dfe0[0]);
        if (dt != 0.0f) {
            FUN_00193540(&v, 1, ((DummyVirtualComponent *)c->_colorAttr)->f28);
            nv = c->_fadeValue - dt * c->_fadeAddValue;
            pw = &v.w;
            *pw = nv;
            if (nv < 0.0f) *pw = 0.0f;
            ((DummyVirtualComponent *)c->_colorAttr)->vX(&v);
            c->_fadeValue = *pw;
            if (*pw <= 0.0f) {
                FUN_003a8580(arg1, &DAT_0050dfe0[0]);
                c->_fadeSt0 = 3;
            }
        }
        break;
    }
    }
}

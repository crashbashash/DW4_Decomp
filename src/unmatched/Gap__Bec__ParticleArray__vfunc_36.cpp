#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(...);
void Gap__Bec__ParticleArray__vfunc_36(ParticleArray *arg0);
}
/* matching construct: dummy-virtual class so vX() dispatches through vtable slot 57 of the vertex-array object */
class DW4VC_236 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void vX(); };
struct PointSpriteView { char pad[24]; igObject *f24; };
void Gap__Bec__ParticleArray__vfunc_36(ParticleArray *arg0) {
    igObject *t;
    PointSpriteView *s0;

    t = (igObject *)arg0->_context;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if ((t->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_context = 0;
    s0 = (PointSpriteView *)arg0->_pointSpriteInterface;
    if (s0 != 0) {
        if ((DW4VC_236 *)s0->f24 == (DW4VC_236 *)arg0->_internalVertexArray) {
            /* matching construct: volatile re-read of the reference before its release */
            t = *(igObject * volatile *)&s0->f24;
            if (t != 0) {
                t->_refCount = t->_refCount - 1;
                if ((t->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(t);
                }
            }
            s0->f24 = 0;
        }
        t = (igObject *)arg0->_pointSpriteInterface;
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if ((t->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->_pointSpriteInterface = 0;
    }
    if (arg0->_internalVertexArray != 0) {
        ((DW4VC_236 *)arg0->_internalVertexArray)->vX();
    }
}

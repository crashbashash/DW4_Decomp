/* Class-membership test: ask `object` for its metaobject (virtual slot 20, the metaobject
 * accessor, e.g. Gap__Bec__ParticleInfo__vfunc_20) and walk the metaobject's `_parent` chain
 * looking for `kind`. Returns 1 when `kind` is the object's own class or one of its ancestors,
 * else 0. The accessor is called with `kind` still in the second argument register (the retail
 * call sequence passes it through; slot 20 has no use for it in the bodies seen). */
#include "dw4/reflected.h"
extern "C" { int igObject_IsKindOf(void *object, igMetaObject *kind); }
/* Stand-in for the object's vtable: vX is slot 20, the metaobject accessor. */
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(int); };
int igObject_IsKindOf(void *object, igMetaObject *kind) {
    igMetaObject *meta = (igMetaObject *)((VC *)object)->vX((int)kind);
    while (meta != 0) {
        if (meta == kind) return 1;
        meta = (igMetaObject *)meta->_parent;
    }
    return 0;
}

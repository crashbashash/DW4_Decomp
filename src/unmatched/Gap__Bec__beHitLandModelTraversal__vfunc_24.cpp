#include "dw4/reflected.h"
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
struct TimeSourceVirtual { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();  virtual long long v24(); };
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
struct TraversalVirtual { virtual void t0(); int pad[3]; long long val; unsigned char flag; };
extern TimeSourceVirtual *DAT_005871d8[4];
extern "C" { long long Gap__Bec__beHitLandModelTraversal__vfunc_24(TraversalVirtual *); }
long long Gap__Bec__beHitLandModelTraversal__vfunc_24(TraversalVirtual *t) {
    if (((beHitLandModelTraversal *)t)->_userTimeState) return ((beHitLandModelTraversal *)t)->_timeLong;
    return DAT_005871d8[0]->v24();
}

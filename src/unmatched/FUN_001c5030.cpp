#include "dw4/reflected.h"
/* matching construct: dummy virtual slots so the type-test call dispatches through the retail vtable offset 88 */
struct BoundVolume { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int ty(); };
struct TraversalFunctionTable { char pad[16]; void (**fn)(void *, void *); };
extern "C" {
extern int DAT_005610e0[4];
extern TraversalFunctionTable *DAT_00562640[4];
int FUN_00190060(void *, void *);
void *FUN_001c4ac0(igFrustCullTraversal *, void *);
int FUN_001c4c20(igFrustCullTraversal *, igNode *, void *);
void FUN_001c5030(igFrustCullTraversal *arg0, igNode *arg1) {
    if (arg0->_modeMask & 0x200) {
        BoundVolume *o = (BoundVolume *)arg1->_bound;
        void *var = o;
        if (o != 0) {
            int t = DAT_005610e0[0];
            if (t == o->ty()) {
                var = o;
            } else {
                igAABox *x = (igAABox *)arg0->_boundingBox;
                var = x;
                float *mn = (float *)x->_min;
                float *mx = (float *)&x->_max;
                mn[0] = mn[1] = mn[2] = 3.4028235e38f;
                mx[0] = mx[1] = mx[2] = -3.4028235e38f;
                FUN_00190060(x, o);
            }
            FUN_001c4c20(arg0, arg1, FUN_001c4ac0(arg0, var));
            return;
        }
    }
    unsigned sel = arg1->_handle;
    DAT_00562640[0]->fn[sel](arg0, arg1);
}
}

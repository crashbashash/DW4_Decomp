/* 0x001c5030 - FUN_001c5030. C++ virtual type test; float constants loaded once into locals in use order; empty then-arm assigns var=o; unsigned selector index */
#include "dw4/reflected.h"
/* matching construct: dummy virtual slots so the type-test call dispatches through the retail vtable offset 88 */
struct Obj { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int ty(); };
/* hypothesis: handle 0x562640 is not in data/reflection.json; its +16 slot is a table of node-handler functions */
struct Tb { char pad[16]; void (**fn)(void *, void *); };
extern "C" {
extern int DAT_005610e0[4];
extern Tb *DAT_00562640[4];
extern float GPR_0055490c;
extern float GPR_00554910;
int FUN_00190060(void *, void *);
void *FUN_001c4ac0(igFrustCullTraversal *, void *);
int FUN_001c4c20(igFrustCullTraversal *, igNode *, void *);
void FUN_001c5030(igFrustCullTraversal *arg0, igNode *arg1) {
    if (arg0->_modeMask & 0x200) {
        Obj *o = (Obj *)arg1->_bound;
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
                float z = GPR_0055490c;
                mn[2] = z;
                mn[1] = z;
                mn[0] = z;
                float w = GPR_00554910;
                mx[2] = w;
                mx[1] = w;
                mx[0] = w;
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

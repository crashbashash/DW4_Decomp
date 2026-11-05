#include "dw4/reflected.h"
extern "C" {
struct RC { int p0; unsigned refs; char p8[8]; char f16; };
typedef igObjectList OL;
int ObjectList_AppendRetained(OL *, RC *);
int igObject_Destroy(igObject *);
void FUN_0043a450(void *arg0, OL *arg1, OL *arg2, OL *arg3, OL *arg4) {
    int i2;
    int off2;
    igObject *r;
    int i;
    RC *o;
    int off;
    i = 0;
    goto guard1;
body1:
    o = ((RC **)(arg1->_data + off))[0];
    ObjectList_AppendRetained(arg2, o);
    if (o != 0) o->f16 = 0;
    r = ((igObject **)(arg1->_data + off))[0];
    if (r != 0) {
        r->_refCount--;
        if (!(r->_refCount & 0x7fffff)) igObject_Destroy(r);
    }
    if (arg1->_count != 0 && i >= 0 && i < arg1->_count) {
        ((RC **)(arg1->_data + off))[0] = 0;
    }
    off += 4;
    i++;
cond1:
    if (i < arg1->_count) goto body1;
after1:
    if (arg3 != 0) {
        if (arg4 != 0) {
            i2 = 0;
            goto guard2;
body2:
            o = ((RC **)(arg3->_data + off2))[0];
            ObjectList_AppendRetained(arg4, o);
            if (o != 0) o->f16 = 0;
            r = ((igObject **)(arg3->_data + off2))[0];
            if (r != 0) {
                r->_refCount--;
                if (!(r->_refCount & 0x7fffff)) igObject_Destroy(r);
            }
            if (arg3->_count != 0 && i2 >= 0 && i2 < arg3->_count) {
                ((RC **)(arg3->_data + off2))[0] = 0;
            }
            off2 += 4;
            i2++;
cond2:
            if (i2 < arg3->_count) goto body2;
        }
    }
done:
    return;
guard2:
    if (0 < arg3->_count) { off2 = 0; goto cond2; }
    goto done;
guard1:
    if (0 < arg1->_count) { off = 0; goto cond1; }
    goto after1;
}
}

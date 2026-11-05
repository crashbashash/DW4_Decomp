#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(igObject *);
void FUN_0043a660(void *arg0, igDataList *arg1, igDataList *arg2, igDataList *arg3, igDataList *arg4) {
    int i2;
    igObject *o2;
    int i;
    igObject *r2;
    igObject *r;
    igObject *o;
    i = 0;
    goto guard1;
body1:
    o = ((igObject **)arg2->_data)[i];
    if (o != 0) o->_refCount++;
    r = ((igObject **)arg1->_data)[i];
    if (r != 0) {
        r->_refCount--;
        if (!(r->_refCount & 0x7fffff)) igObject_Destroy(r);
    }
    if (arg1->_count != 0 && i >= 0 && i < arg1->_count) {
        ((igObject **)arg1->_data)[i] = o;
    }
    if (o != 0) *((char *)o + 16) = 1;
    r = ((igObject **)arg2->_data)[i];
    if (r != 0) {
        r->_refCount--;
        if (!(r->_refCount & 0x7fffff)) igObject_Destroy(r);
    }
    if (arg2->_count != 0 && i >= 0 && i < arg2->_count) {
        ((igObject **)arg2->_data)[i] = 0;
    }
    i++;
cond1:
    if (i < arg2->_count) goto body1;
after1:
    if (arg3 != 0) {
        if (arg4 != 0) {
            i2 = 0;
            goto guard2;
body2:
            o2 = ((igObject **)arg4->_data)[i2];
            if (o2 != 0) o2->_refCount++;
            r2 = ((igObject **)arg3->_data)[i2];
            if (r2 != 0) {
                r2->_refCount--;
                if (!(r2->_refCount & 0x7fffff)) igObject_Destroy(r2);
            }
            if (arg3->_count != 0 && i2 >= 0 && i2 < arg3->_count) {
                ((igObject **)arg3->_data)[i2] = o2;
            }
            if (o2 != 0) *((char *)o2 + 16) = 1;
            r2 = ((igObject **)arg4->_data)[i2];
            if (r2 != 0) {
                r2->_refCount--;
                if (!(r2->_refCount & 0x7fffff)) igObject_Destroy(r2);
            }
            if (arg4->_count != 0 && i2 >= 0 && i2 < arg4->_count) {
                ((igObject **)arg4->_data)[i2] = 0;
            }
                    i2++;
cond2:
            if (i2 < arg4->_count) goto body2;
        }
    }
done:
    return;
guard2:
    if (0 < arg4->_count) goto cond2;
    goto done;
guard1:
    if (0 < arg2->_count) goto cond1;
    goto after1;
}
}

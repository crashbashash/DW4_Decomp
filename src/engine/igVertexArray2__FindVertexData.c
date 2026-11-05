#include "dw4/typecast.h"
extern int DAT_0055fa58[4];
typedef struct L { char p[8]; int n; int pad; int *data; } L;
typedef struct A { char p[16]; L *l; } A;
typedef struct O { char p[16]; int k0; int k1; } O;
void *igVertexArray2__FindVertexData(A *arg0, int arg1, int arg2) {
    void *res;
    int i;
    O *o;
    int n;
    res = 0;
    n = arg0->l->n;
    for (i = 0; i < n; i++) {
        o = (O *)dw4_cast_or_null((char *)arg0->l->data[i], DAT_0055fa58);
        if (arg1 == o->k0 && arg2 == o->k1) {
            res = o;
            break;
        }
    }
    return res;
}

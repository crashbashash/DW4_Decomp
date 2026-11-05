#include "dw4/reflected.h"
int FUN_001da220(void *, int, int);
struct Obj { char pad[20]; unsigned key; };
struct Tbl { char pad[16]; struct Obj **arr; };
extern struct Tbl *DAT_005629f8[4];
struct Pair { int a; int b; };
void FUN_001da6e0(igSorter *arg0) {
    igDataList *h;
    int n;
    struct Obj **arr;
    struct Pair *p;
    int b;
    h = (igDataList *)arg0->_opaquePackageIndices;
    n = h->_count;
    if (n > 2) {
        FUN_001da220(arg0, 0, n - 1);
        return;
    }
    if (n == 2) {
        int m, t;
        p = (struct Pair *)h->_data;
        b = p->b;
        arr = DAT_005629f8[0]->arr;
        if (arr[b]->key < arr[p->a]->key) {
            m = *(volatile int *)&h->_count;
            if (m != 0 && 0 < m && m > 1) {
                t = *(volatile int *)&p->a;
                p->a = b;
                p->b = t;
            }
        }
    }
}

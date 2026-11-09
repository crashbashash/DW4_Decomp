#include "dw4/reflected.h"
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(int *out); };
extern "C" {
int List_Resize(...);
void FUN_004576d0(igContext *arg0, VC *arg1);
}
void FUN_004576d0(igContext *arg0, VC *arg1) {
    volatile int key;
    int s[4];
    igObjectList *l;
    int i;
    int n;
    int cnt;
    int k;
    int r;

    key = 0;
    l = (igObjectList *)arg0->_pExtList;
    k = key;
    cnt = *(int *)&l->_count;
    for (i = 0; i < cnt; i++) {
        if (k == (*(int **)&l->_data)[i]) {
            r = i;
            goto done;
        }
    }
    r = -1;
done:
    if (r < 0) {
        n = *(volatile int *)&l->_count;
        if (n < l->_capacity) {
            l->_count = l->_count + 1;
        } else {
            List_Resize(l, n + 1, 4);
        }
        (*(int **)&l->_data)[n] = (int)arg1;
    } else if (l->_count != 0 && r >= 0 && r < l->_count) {
        (*(int **)&l->_data)[r] = (int)arg1;
    }
    s[0] = 0;
    s[1] = 0;
    s[2] = 0;
    arg1->vX(s);
}

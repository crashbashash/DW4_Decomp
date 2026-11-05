#include "dw4/reflected.h"
extern "C" int FUN_003a82f0(void *, int *, float);
extern int DAT_004e0858[4];
extern int DAT_00589d78[4];
class E {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual int v20();
};
extern "C" void FUN_003a84a0(beBaseInfoRam *t, float f) {
    int n;
    int i;
    int s1;
    int *a1;
    E *e;
    if (t->_dataList != 0) {
        n = ((beBaseInfoDataList *)t->_dataList)->_count;
        i = 0;
        if (0 < n) {
            do {
                s1 = DAT_00589d78[0];
                e = ((E **)((beBaseInfoDataList *)t->_dataList)->_data)[i];
                if (s1 == e->v20()) {
                    a1 = (int *)((beBaseInfoData *)e)->_name;
                    a1 = a1 != 0 ? a1 : &DAT_004e0858[0];
                    FUN_003a82f0(t, a1, f);
                }
                i++;
            } while (i < n);
        }
    }
}

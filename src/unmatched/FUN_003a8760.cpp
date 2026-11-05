#include "dw4/reflected.h"
struct Rc { int vt; int rc; };
extern "C" {
int List_RemoveWordAt(...);
int List_Reserve(...);
int igObject_Destroy(...);
extern int DAT_00589d78[4];
void FUN_003a8760(beBaseInfoRam *arg0);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void FUN_003a8760(beBaseInfoRam *arg0) {
    int temp_s1;
    int var_s3;
    int var_s2;
    igObjectList *temp_s1_2;
    int temp_s0;
    int temp_a1;
    void **temp_a0;
    Rc *temp_a0_2;
    igObjectList *temp_a0_3;
    igObjectList *temp_v1;

    temp_v1 = ((igObjectList *)arg0->_dataList);
    if (temp_v1 != 0) {
        var_s3 = temp_v1->_count;
        var_s2 = 0;
        if (var_s3 > 0) {
            do {
                temp_s0 = var_s2 * 4;
                temp_a0 = (void **)(*(int *)(((igObjectList *)arg0->_dataList)->_data + temp_s0));
                temp_s1 = DAT_00589d78[0];
                if (temp_s1 == ((DW4VC_88_0 *)(temp_a0))->vX()) {
                    temp_s1_2 = ((igObjectList *)arg0->_dataList);
                    temp_a0_2 = (Rc *)*(int *)(temp_s1_2->_data + temp_s0);
                    if (temp_a0_2 != 0) {
                        temp_a0_2->rc = temp_a0_2->rc - 1;
                        if ((temp_a0_2->rc & 0x7FFFFF) == 0) {
                            igObject_Destroy(temp_a0_2);
                        }
                    }
                    List_RemoveWordAt(temp_s1_2, var_s2);
                    var_s3 -= 1;
                    var_s2 -= 1;
                    *(int *)(temp_s1_2->_data + (temp_s1_2->_count * 4)) = 0;
                }
                var_s2 += 1;
            } while (var_s2 < var_s3);
        }
        temp_a0_3 = ((igObjectList *)arg0->_dataList);
        temp_a1 = temp_a0_3->_count;
        if (temp_a1 >= *(volatile int *)&temp_a0_3->_count) {
            List_Reserve(temp_a0_3, temp_a1, 4);
        }
    }
}

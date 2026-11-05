#include "dw4/reflected.h"
extern "C" {
int FUN_00399d90(int, int);
int List_RemoveWordAt(igObjectList *, int);
int igObject_Destroy(igObject *);
void FUN_00399e20(beModelCtrlSubCom *arg0, int arg1);
}

void FUN_00399e20(beModelCtrlSubCom *arg0, int arg1) {
    int var_s3;
    int var_s2;
    igObject *temp_a0;
    igObjectList *temp_s1;

    var_s3 = ((igObjectList *)arg0->_comList)->_count;
    var_s2 = 0;
    if (var_s3 > 0) {
        do {
            if (!(FUN_00399d90(((int *)((igObjectList *)arg0->_comList)->_data)[var_s2], arg1) & 0xFF)) {
                temp_s1 = (igObjectList *)(arg0->_comList);
                temp_a0 = (igObject *)(((int *)temp_s1->_data)[var_s2]);
                if (temp_a0 != 0) {
                    temp_a0->_refCount = temp_a0->_refCount - 1;
                    if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                        igObject_Destroy(temp_a0);
                    }
                }
                List_RemoveWordAt(temp_s1, var_s2);
                var_s2 -= 1;
                var_s3 -= 1;
                ((int *)temp_s1->_data)[temp_s1->_count] = 0;
            }
            var_s2 += 1;
        } while (var_s2 < var_s3);
    }
}

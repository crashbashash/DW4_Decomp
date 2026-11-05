#include "dw4/reflected.h"
int FUN_00304430();
int FUN_00304680();
extern int DAT_004faef0[4];
void Gap__Core__igRawRefArrayMetaField__vfunc_41(igRawRefArrayMetaField *arg0, int arg1, int arg2, int arg3) {
    FUN_00304430(&DAT_004faef0[0], arg3, arg0->_fieldName, *(volatile int *)(arg1 + arg0->_offset));
    FUN_00304680();
}

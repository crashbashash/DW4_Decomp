extern "C" {
typedef struct A6 { int v[6]; } A6;
#include "dw4/reflected.h"
/* The item is a beNDMWItemRevisionPocketBase (weapon / armor): _kindNo selects the table, _revision (+20) and _pocket (+24) add to the record value.
 * Kind 2 (yellow armor) has no _pocket and the code does not read it. */
int beNDMWItemBase_GetRecordInt(beNDMWItemRevisionPocketBase *o, int a, int *s);
int igStrCmp(int a, int *b);
extern A6 DAT_004cfe90;
extern A6 DAT_004cfeb0;
extern int DAT_0051d570[];
extern int DAT_0051d578[];

int FUN_00447ed0(beNDMWItemRevisionPocketBase *arg0, int arg1, int arg2) {
    A6 sp50;
    A6 sp30;
    int var_v0;

    if (igStrCmp(arg2, DAT_0051d570) == 0) {
        var_v0 = beNDMWItemBase_GetRecordInt(arg0, arg1, DAT_0051d570);
        if (arg0->_kindNo == 2) {
            var_v0 += arg0->_revision * 100;
        } else if (arg0->_kindNo == 0 || arg0->_kindNo == 1) {
            var_v0 += arg0->_revision * 100;
            sp50 = DAT_004cfe90;
            var_v0 += sp50.v[arg0->_pocket];
        }
    } else {
        var_v0 = beNDMWItemBase_GetRecordInt(arg0, arg1, DAT_0051d578);
        if (arg0->_kindNo == 2) {
            var_v0 += arg0->_revision * 25;
        } else if (arg0->_kindNo == 0 || arg0->_kindNo == 1) {
            var_v0 += arg0->_revision * 25;
            sp30 = DAT_004cfeb0;
            var_v0 += sp30.v[arg0->_pocket];
        }
    }
    return var_v0;
}
}

#include "dw4/reflected.h"
extern "C" {
struct ListHolder { int pad[3]; igObjectList *list; };
int beNDMWItemBase_GetRecordInt(beNDMWItemBase *, int, int);
char *beNDMWItemBase_GetRecordString(beNDMWItemBase *, int, int *);
struct ListHolder *igProperty_GetRecordFolder(int, int *);
int igStrCmp(char *, int);
extern int DAT_00518ae0[4];
extern int DAT_00518c88[4];
struct beNDMWItemCountView { beNDMWItemBase base; unsigned int _count; };
void FUN_003fa2c0(int arg0, int arg1, int *arg2, int arg3, int arg4) {
    beNDMWItemBase *it; int t;
    if (igProperty_GetRecordFolder(arg1, &DAT_00518ae0[0])->list->_count != 0) {
        it = *(beNDMWItemBase **)igProperty_GetRecordFolder(arg1, &DAT_00518ae0[0])->list->_data;
        if (it != 0) {
            t = beNDMWItemBase_GetRecordInt(it, arg0, arg3); *arg2 += t;
            if (arg4 != 0 && igStrCmp(beNDMWItemBase_GetRecordString(it, arg0, &DAT_00518c88[0]), arg3) == 0) {
                *arg2 += ((beNDMWItemCountView *)it)->_count;
            }
        }
    }
}
}

#include "dw4/reflected.h"
extern "C" {
int beMessenger_SendNamed(int, int *, int *, int, int *);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, int *);
int beMessenger_AppendString(int, const char *);
int beMessenger_DispatchSelected(int, int *);
const char *beDataBase_GetRecordString(int, int, int *);
extern char *DAT_004cf670[12];
extern const char DAT_00519b00[];
extern int DAT_00519b08[4];
extern const char DAT_00519b50[];
extern int DAT_00519c28[4];
extern int DAT_00519f28[4];
extern int DAT_00519f30[4];
extern int DAT_00519f40[4];
extern const char DAT_0051a060[];
extern int DAT_0051a128[4];
extern int DAT_0051a138[4];
extern int DAT_0051a140[4];
void FUN_0041aaa0(beNDMWStatusCtrlFlag *arg0, int arg1, int arg2) {
    int s0;
    int v6;
    igDataList *l;
    int s5;
    int w3;
    char **v4;
    char **w4;
    int v3;
    beMessenger_SendNamed(arg0->_messenger, DAT_0051a128, DAT_0051a138, 0, DAT_0051a140);
    s0 = beMessenger_GetObject(arg0->_messenger, 0);
    if (arg1 != 0) {
        v6 = 0;
        l = (igDataList *)arg0->_impItems;
        if (0 < l->_count) {
            v3 = 0;
            v4 = DAT_004cf670;
            do {
                beMessenger_SelectGroup(arg0->_messenger, DAT_00519c28);
                beMessenger_AppendString(arg0->_messenger, DAT_0051a060);
                beMessenger_AppendString(arg0->_messenger, *v4);
                s5 = arg0->_messenger;
                beMessenger_AppendString(s5, beDataBase_GetRecordString(s0, *(int *)&((unsigned char *)((igDataList *)arg0->_impItems)->_data)[v3], DAT_00519f28));
                beMessenger_DispatchSelected(arg0->_messenger, DAT_00519f30);
                v6++;
                v4++;
                v3 += 4;
            } while (v6 < (l = (igDataList *)arg0->_impItems)->_count);
        }
        w3 = l->_count;
        if (w3 < 12) {
            w4 = &DAT_004cf670[w3];
            do {
                beMessenger_SelectGroup(arg0->_messenger, DAT_00519c28);
                beMessenger_AppendString(arg0->_messenger, DAT_0051a060);
                beMessenger_AppendString(arg0->_messenger, *w4);
                beMessenger_AppendString(arg0->_messenger, DAT_00519b00);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_00519b08);
                w3++;
                w4++;
            } while (w3 < 12);
        }
    }
    if (arg2 != 0 && ((igDataList *)arg0->_impItems)->_count > 0) {
        beMessenger_SelectGroup(arg0->_messenger, DAT_00519c28);
        beMessenger_AppendString(arg0->_messenger, DAT_00519b50);
        beMessenger_AppendString(arg0->_messenger, DAT_004cf670[0]);
        s5 = arg0->_messenger;
        beMessenger_AppendString(s5, beDataBase_GetRecordString(s0, ((int *)((igDataList *)arg0->_impItems)->_data)[arg0->_retCode], DAT_00519f40));
        beMessenger_DispatchSelected(arg0->_messenger, DAT_00519f30);
    }
}
}

#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, const char *);
int beMessenger_DispatchSelected(int, int *);
void *beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, int *);
char *beNDMWItemBase_GetRecordString(beNDMWItemDisk *, int, int *);
char *igProperty_GetRecordFolder(void *, int *);
extern char * DAT_004cf670[4];
extern const char DAT_00519b00[];
extern int DAT_00519b08[4];
extern const char DAT_00519b50[];
extern const char DAT_00519b78[];
extern int DAT_00519ba0[4];
extern int DAT_00519ba8[4];
extern int DAT_00519c28[4];
extern int DAT_00519f28[4];
extern int DAT_00519f30[4];
extern int DAT_00519f40[4];
extern const char DAT_0051a060[];
extern int DAT_0051a150[4];
extern const char DAT_0051a170[];
extern int DAT_0058b028[4];
void FUN_0041d510(beNDMWStatusCtrlDisk *arg0, int arg1, int arg2) {
    char spAC[2];
    int i;
    beNDMWItemDisk *it;
    int s7;
    char *str;
    int off;
    int v1;
    igObjectList *s6;
    char **s0;
    beMessenger_SelectGroup(arg0->_messenger, &DAT_00519ba0[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519ba8[0]);
    s6 = *(igObjectList **)(igProperty_GetRecordFolder(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051a150[0]) + 12);
    s7 = FUN_00236f80(arg0->_insight, DAT_0058b028[0]);
    if (arg1 != 0) {
        spAC[1] = 0;
        i = 0;
        if (0 < s6->_count) {
            off = 0;
            s0 = &DAT_004cf670[0];
            do {
                it = *(beNDMWItemDisk **)((char *)s6->_data + off);
                if (it != 0) {
                    str = beNDMWItemBase_GetRecordString(it, s7, &DAT_00519f28[0]);
                    beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c28[0]);
                    beMessenger_AppendString(arg0->_messenger, &DAT_0051a060[0]);
                    beMessenger_AppendString(arg0->_messenger, *s0);
                    beMessenger_AppendString(arg0->_messenger, str);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519f30[0]);
                    spAC[0] = it->_kazu + 0x30;
                    beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c28[0]);
                    beMessenger_AppendString(arg0->_messenger, &DAT_0051a170[0]);
                    beMessenger_AppendString(arg0->_messenger, *s0);
                    beMessenger_AppendString(arg0->_messenger, spAC);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519f30[0]);
                }
                i++;
                off += 4;
                s0 += 1;
            } while (i < s6->_count);
        }
    }
    if (arg2 != 0) {
        v1 = arg0->_retCode;
        if (v1 != -1) {
            str = beNDMWItemBase_GetRecordString(((beNDMWItemDisk **)s6->_data)[v1], s7, &DAT_00519f40[0]);
            beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c28[0]);
            beMessenger_AppendString(arg0->_messenger, &DAT_00519b50[0]);
            beMessenger_AppendString(arg0->_messenger, DAT_004cf670[0]);
            beMessenger_AppendString(arg0->_messenger, str);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519f30[0]);
            beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c28[0]);
            beMessenger_AppendString(arg0->_messenger, &DAT_00519b50[0]);
            beMessenger_AppendString(arg0->_messenger, DAT_004cf670[0]);
            beMessenger_AppendString(arg0->_messenger, &DAT_00519b78[0]);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519b08[0]);
            return;
        }
        beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c28[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00519b50[0]);
        beMessenger_AppendString(arg0->_messenger, DAT_004cf670[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00519b00[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519b08[0]);
    }
}
}

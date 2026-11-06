#include "dw4/reflected.h"
extern "C" {
int sprintf(char *, int *, int);
int FUN_00236f80(int, int);
int FUN_00447ed0(beNDMWItemDisk *, int, int *);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, char *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, int *);
char *beNDMWItemBase_GetRecordString(beNDMWItemDisk *, int, int *);
void *igProperty_GetRecordFolder(int, int *);
extern char *DAT_004cf8a0[];
extern int DAT_0051b398[];
extern int DAT_0051b3c0[];
extern char DAT_0051b3c8[];
extern int DAT_0051b3e8[];
extern int DAT_0051b468[];
extern char DAT_0051b470[];
extern char DAT_0051b550[];
extern int DAT_0051b558[];
extern int DAT_0051b678[];
extern char DAT_0051b680[];
extern int DAT_0051b6a8[];
extern int DAT_0051b6b0[];
extern char DAT_0051b6b8[];
extern int DAT_0051b6c0[];
extern int DAT_0051bd70[];
extern char DAT_0051bd88[];
extern int DAT_0058b028[];
void FUN_00437ae0(beNDMWShopCtrlDiskSell *arg0, int arg1, int arg2) {
    char spA0[28];
    char spBC[2];
    igObjectList *temp_s6;
    int temp_s7;
    int i;
    beNDMWItemDisk *it;
    char *s;
    int off;
    char **p;

    beMessenger_SelectGroup(arg0->_messenger, DAT_0051b398);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3e8);
    temp_s6 = *(igObjectList **)((char *)igProperty_GetRecordFolder(beMessenger_GetObject(arg0->_messenger, 0), DAT_0051b6c0) + 12);
    temp_s7 = FUN_00236f80(arg0->_insight, DAT_0058b028[0]);
    if (arg1 != 0) {
        i = 0;
        if (i < temp_s6->_count) {
            off = 0;
            p = DAT_004cf8a0;
            do {
                it = *(beNDMWItemDisk **)((char *)temp_s6->_data + off);
                s = beNDMWItemBase_GetRecordString(it, temp_s7, DAT_0051b678);
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b3c8);
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, s);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b6b0);
                spBC[0] = it->_kazu + 0x30;
                spBC[1] = 0;
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051bd88);
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, spBC);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b6b0);
                sprintf(spA0, DAT_0051b468, FUN_00447ed0(it, temp_s7, DAT_0051bd70));
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b680);
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, spA0);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b6b0);
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b3c8);
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b6b8);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b558);
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051bd88);
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b6b8);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b558);
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b680);
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b6b8);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b558);
                i += 1;
                off += 4;
                p += 1;
            } while (i < temp_s6->_count);
        }
    }
    if (arg2 != 0) {
        int idx = arg0->_retCode;
        it = 0;
        if (idx != -1) {
            it = ((beNDMWItemDisk **)temp_s6->_data)[idx];
        }
        if (it != 0) {
            s = beNDMWItemBase_GetRecordString(it, temp_s7, DAT_0051b6a8);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
            beMessenger_AppendString(arg0->_messenger, DAT_0051b470);
            beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[0]);
            beMessenger_AppendString(arg0->_messenger, s);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b6b0);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
            beMessenger_AppendString(arg0->_messenger, DAT_0051b470);
            beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[0]);
            beMessenger_AppendString(arg0->_messenger, DAT_0051b6b8);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b558);
            arg0->_tanka = FUN_00447ed0(it, temp_s7, DAT_0051bd70);
            return;
        }
        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
        beMessenger_AppendString(arg0->_messenger, DAT_0051b470);
        beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[0]);
        beMessenger_AppendString(arg0->_messenger, DAT_0051b550);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b558);
    }
}
}

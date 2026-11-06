#include "dw4/reflected.h"
extern "C" {
struct NamePair { int unused; char *name; };
int sprintf(char *, char *, int);
int beDataBase_GetRecordString(int, int, char *);
int beMessenger_AppendString(int, char *);
int beMessenger_DispatchSelected(int, char *);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, char *);
int beMessenger_SendNamed(int, char *, char *, int, char *);
extern char *DAT_004cf8a0[4];
extern struct NamePair DAT_004cf8d0[16];
extern char DAT_0051b3c0[];
extern char DAT_0051b468[];
extern char DAT_0051b470[];
extern char DAT_0051b550[];
extern char DAT_0051b558[];
extern char DAT_0051b5d8[];
extern char DAT_0051b5e8[];
extern char DAT_0051b6b0[];
extern char DAT_0051b6b8[];
extern char DAT_0051ba48[];
extern char DAT_0051ba80[];
extern char DAT_0051ba90[];
extern char DAT_0051baa0[];
extern char DAT_0051bab0[];
extern char DAT_0051bae8[];
extern char DAT_0051baf0[];
extern char DAT_0051bb20[];
void FUN_00430d20(beNDMWShopCtrlEvolve *ctl, int sendNames, int sendStats) {
    char countBuf[28];
    int statVals[16];
    char valueBuf[16];
    char pageDigits[4];
    beNDMWShinkaObjectList *itemList;
    int slot;
    char *itemName;
    char **labelPtr;
    int statIdx;
    int digitChar;
    int pageBase;
    int cursor;
    int selIndex;
    beNDMWShinkaObjectList *selList;
    int listIndex;
    beNDMWShinkaObject *item;
    beNDMWShinkaObject *selItem;
    char *recordName;
    int *valuePtr;
    struct NamePair *labelPair;
    if (sendNames != 0) {
        itemList = (beNDMWShinkaObjectList *)((beNDMWShinkaCtrl *)ctl->_shinkaCtrl)->_list;
        for (slot = 0, labelPtr = DAT_004cf8a0; slot < 8; slot++, labelPtr++) {
            listIndex = slot + ctl->_nowPage * 8;
            if (itemList->_count - 1 < listIndex) {
                beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(ctl->_messenger, DAT_0051ba80);
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, DAT_0051b550);
                beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b558);
                beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(ctl->_messenger, DAT_0051ba90);
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, DAT_0051b550);
                beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b558);
                beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(ctl->_messenger, DAT_0051baa0);
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, DAT_0051b550);
                beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b558);
            } else {
                item = (beNDMWShinkaObject *)((int *)itemList->_data)[listIndex];
                itemName = (char *)item->_name;
                beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(ctl->_messenger, DAT_0051ba80);
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, itemName);
                beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b6b0);
                beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(ctl->_messenger, DAT_0051ba80);
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, DAT_0051b6b8);
                beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b558);
                beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(ctl->_messenger, DAT_0051ba90);
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, DAT_0051bb20);
                beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b6b0);
                beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(ctl->_messenger, DAT_0051ba90);
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, DAT_0051b6b8);
                beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b558);
                sprintf(countBuf, DAT_0051b468, ((beNDMWShinkaObject *)((int *)itemList->_data)[listIndex])->_level);
                beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(ctl->_messenger, DAT_0051baa0);
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, countBuf);
                beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b6b0);
                beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(ctl->_messenger, DAT_0051baa0);
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, DAT_0051b6b8);
                beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b558);
            }
        }
        if (ctl->_maxPage > 1) {
            pageDigits[1] = 0;
            digitChar = ctl->_nowPage; digitChar += 0x31;
            pageDigits[0] = digitChar;
            beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
            beMessenger_AppendString(ctl->_messenger, DAT_0051ba48);
            beMessenger_AppendString(ctl->_messenger, DAT_004cf8a0[0]);
            beMessenger_AppendString(ctl->_messenger, pageDigits);
            beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b6b0);
            digitChar = ctl->_maxPage; digitChar += 0x30;
            pageDigits[0] = digitChar;
            beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
            beMessenger_AppendString(ctl->_messenger, DAT_0051ba48);
            beMessenger_AppendString(ctl->_messenger, DAT_004cf8a0[1]);
            beMessenger_AppendString(ctl->_messenger, pageDigits);
            beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b6b0);
        }
    }
    if (sendStats != 0) {
        cursor = ctl->_retCode;
        if (cursor != -1) {
            selList = (beNDMWShinkaObjectList *)((beNDMWShinkaCtrl *)ctl->_shinkaCtrl)->_list;
            pageBase = ctl->_nowPage * 8;
            selIndex = pageBase + cursor;
            if (selIndex < selList->_count) {
                selItem = (beNDMWShinkaObject *)((int *)selList->_data)[selIndex];
                statVals[0] = selItem->_hpMax;
                statVals[1] = selItem->_mpMax;
                statVals[2] = selItem->_tsuyosa;
                statVals[3] = selItem->_mamori;
                statVals[4] = selItem->_kashikosa;
                statVals[5] = selItem->_seishin;
                statVals[6] = selItem->_subayasa;
                statVals[7] = selItem->_blunt;
                statVals[8] = selItem->_slash;
                statVals[9] = selItem->_stab;
                statVals[10] = selItem->_bash;
                statVals[11] = selItem->_shot;
                statVals[12] = selItem->_crush;
                statVals[13] = selItem->_blast;
                statVals[14] = selItem->_heal;
                statVals[15] = selItem->_force;
                for (statIdx = 0, valuePtr = statVals, labelPair = DAT_004cf8d0; statIdx < 16; statIdx++, valuePtr++, labelPair++) {
                    sprintf(valueBuf, DAT_0051b468, *valuePtr);
                    beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                    beMessenger_AppendString(ctl->_messenger, DAT_0051bab0);
                    beMessenger_AppendString(ctl->_messenger, labelPair->name);
                    beMessenger_AppendString(ctl->_messenger, valueBuf);
                    beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b6b0);
                }
                beMessenger_SendNamed(ctl->_messenger, DAT_0051b5d8, DAT_0051bae8, 0, DAT_0051b5e8);
                recordName = (char *)beDataBase_GetRecordString(beMessenger_GetObject(ctl->_messenger, 0), selItem->_id, DAT_0051baf0);
                beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(ctl->_messenger, DAT_0051b470);
                beMessenger_AppendString(ctl->_messenger, DAT_004cf8a0[0]);
                beMessenger_AppendString(ctl->_messenger, recordName);
                beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b6b0);
                beMessenger_SelectGroup(ctl->_messenger, DAT_0051b3c0);
                beMessenger_AppendString(ctl->_messenger, DAT_0051b470);
                beMessenger_AppendString(ctl->_messenger, DAT_004cf8a0[0]);
                beMessenger_AppendString(ctl->_messenger, DAT_0051b6b8);
                beMessenger_DispatchSelected(ctl->_messenger, DAT_0051b558);
            }
        }
    }
}
}

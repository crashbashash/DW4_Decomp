#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int memset(int, int, int);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendObject(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetBool(int, int);
int beMessenger_GetInt(int, int);
int beMessenger_SelectReceivers(int, int *, int, int);
int beMessenger_SendNamed(int, int *, int, int, int *);
extern int DAT_00517fd0[4];
extern int DAT_00518000[4];
extern int DAT_00518010[4];
extern int DAT_00518030[4];
extern int DAT_00518048[4];
extern int DAT_00518060[4];
extern int DAT_00518080[4];
extern int DAT_005180a0[4];
extern int DAT_005180c0[4];
extern int DAT_005180e0[4];
extern int DAT_005180f0[4];
extern int DAT_005180f8[4];
beSvDeliver *beMessenger_GetObject(int, int);
void FUN_003f1490(beNDMWMcUtilCtrl *op) {
    if (op->_isRdy == 1) {
        if (op->_isUseUtil == 1) {
            beSvDeliver *r;
            beNDMWMcSlotList *sl;
            int i;
            int off;
            beMessenger_SendNamed(op->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_00518000[0]);
            r = beMessenger_GetObject(op->_messenger, 0);
            sl = (beNDMWMcSlotList *)op->_slot;
            i = 0;
            if (i < sl->_count) {
                off = 0;
                do {
                    if (*(int *)((char *)((igIntList *)r->_actConnect)->_data + off) == 1) {
                        (*(beNDMWMcSlot **)((char *)sl->_data + off))->_isConnect = 1;
                        (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)op->_slot)->_data + off))->_totalSize = *(int *)((char *)((igIntList *)r->_totalSizeList)->_data + off);
                        (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)op->_slot)->_data + off))->_freeSize = *(int *)((char *)((igIntList *)r->_freeSizeList)->_data + off);
                        if (*(int *)((char *)((igIntList *)r->_formatList)->_data + off) == 1) {
                            (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)op->_slot)->_data + off))->_isFormat = 1;
                        } else {
                            (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)op->_slot)->_data + off))->_isFormat = 0;
                        }
                    } else {
                        (*(beNDMWMcSlot **)((char *)sl->_data + off))->_isConnect = 0;
                    }
                    sl = (beNDMWMcSlotList *)op->_slot;
                    i++;
                    off += 4;
                } while (i < sl->_count);
            }
            if (r->_useMtap == 1) {
                op->_isMtap = 1;
            } else {
                op->_isMtap = 0;
            }
        } else {
            int j;
            int off2;
            beNDMWMcSlotList *s2;
            op->_isMtap = 1;
            s2 = (beNDMWMcSlotList *)op->_slot;
            j = 0;
            if (j < s2->_count) {
                off2 = 0;
                do {
                    j++;
                    (*(beNDMWMcSlot **)((char *)s2->_data + off2))->_isConnect = 1;
                    s2 = (beNDMWMcSlotList *)op->_slot;
                    off2 += 4;
                } while (j < s2->_count);
            }
        }
    }
    if (op->_isRun == 1) {
        if (op->_isUseUtil == 1) {
            switch (op->_st0) {
            default:
                break;
            case 0:
                switch (op->_kind) {
                case 0:
                    memset(((beSaveDataDeliver *)op->_svData)->_data, 0, *(volatile int *)&((beSaveDataDeliver *)op->_svData)->_size);
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_AppendObject(op->_messenger, op->_svData);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_00518010[0]);
                    break;
                case 1:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_00518030[0]);
                    break;
                case 2:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_00518048[0]);
                    break;
                case 3:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_00518060[0]);
                    break;
                case 4:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_AppendObject(op->_messenger, op->_svData);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_00518080[0]);
                    break;
                case 5:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_AppendObject(op->_messenger, op->_svData);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_005180a0[0]);
                    break;
                case 6:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_005180c0[0]);
                    break;
                case 7:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_005180e0[0]);
                    break;
                }
                op->_st0 = op->_st0 + 1;
                op->_st3 = 0;
                op->_st2 = 0;
                op->_st1 = 0;
                break;
            case 1:
                beMessenger_SendNamed(op->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_005180f0[0]);
                if ((beMessenger_GetBool(op->_messenger, 0) & 0xFF) == 0) {
                    op->_st0 = op->_st0 + 1;
                    op->_st3 = 0;
                    op->_st2 = 0;
                    op->_st1 = 0;
                }
                break;
            case 2:
                beMessenger_SendNamed(op->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_005180f8[0]);
                op->_result = beMessenger_GetInt(op->_messenger, 0);
                op->_isRun = 0;
                op->_isResult = 1;
                op->_st0 = op->_st0 + 1;
                op->_st3 = 0;
                op->_st2 = 0;
                op->_st1 = 0;
                break;
            case 3:
                break;
            }
        } else {
            op->_result = 2;
            op->_isRun = 0;
            op->_isResult = 1;
        }
    }
}
} /* extern "C" */

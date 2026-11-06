/* The owner pointer is read volatile so the slot list is reloaded on each use. */
#include "dw4/reflected.h"
extern "C" {
int FUN_003f1490(int);
void FUN_003ecc60(beNDMWLoadCtrl2CommonIntf *arg0) {
    int i;
    int j;
    igIntList *il;
    int k;
    FUN_003f1490(arg0->_mcUtilCtrl);
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)arg0->_flagWork)->_data)[0]->_isCutConnect = 0;
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)arg0->_flagWork)->_data)[1]->_isCutConnect = 0;
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)arg0->_flagWork)->_data)[2]->_isCutConnect = 0;
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)arg0->_flagWork)->_data)[3]->_isCutConnect = 0;
    for (i = 0; i < ((beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)*(volatile int *)&arg0->_mcUtilCtrl)->_slot)->_count; i++) {
        if (((beNDMWMcSlotPS2 **)((beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)*(volatile int *)&arg0->_mcUtilCtrl)->_slot)->_data)[i]->_isConnect == 0) {
            for (j = 0; j < ((beNDMWLoadSlotPlayerList *)arg0->_slotSaveData)->_count; j++) {
                if (i == ((beNDMWLoadSlotPlayer **)((beNDMWLoadSlotPlayerList *)arg0->_slotSaveData)->_data)[j]->_connectNO) {
                    il = (igIntList *)((beNDMWLoadSlotPlayer **)((beNDMWLoadSlotPlayerList *)arg0->_slotSaveData)->_data)[j]->_accessPlList;
                    for (k = 0; k < il->_count; k++) {
                        ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)arg0->_flagWork)->_data)[((int *)il->_data)[k]]->_isCutConnect = 1;
                    }
                }
            }
        }
    }
}
}

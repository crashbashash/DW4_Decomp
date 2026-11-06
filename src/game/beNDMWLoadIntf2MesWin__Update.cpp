#include "dw4/reflected.h"
extern "C" {
int TextOrder_ClearFont(...);
int beNDMWLoadIntf2TextOrder_PublishIdLines(...);
int FUN_003eca00(...);
int beNDMWLoadIntf2MesWin__RequestMesErase(...);
int beMessenger_SendNamed(...);
bePadData *bePadManager_GetPadForPlayer(...);
}
extern char DAT_005176a0[], DAT_005176b0[], DAT_00517a48[], DAT_00517a60[], DAT_00517a70[], DAT_00517a80[],
 DAT_00517a90[], DAT_00517aa0[], DAT_00517ab0[], DAT_00517ac0[], DAT_00517ad0[], DAT_00517ae0[], DAT_00517af0[];

extern "C" void beNDMWLoadIntf2MesWin__Update(beNDMWLoadIntf2MesWin *t) {
    int s;
    if (t->_isWinOpen == 1) {
        if (t->_isSystemMes != 1) {
            if (t->_isCtrl == 1) {
                switch (t->_kindCtrl) {
                case 0:
                    switch (t->_statCtrl) {
                    case 0:
                        if (t->_curPoint == 0) {
                            beMessenger_SendNamed(t->_messenger, DAT_00517a48, DAT_00517a60, t->_ramNo, DAT_00517a70);
                        } else {
                            beMessenger_SendNamed(t->_messenger, DAT_00517a48, DAT_00517a60, t->_ramNo, DAT_00517a80);
                        }
                        t->_statCtrl = t->_statCtrl + 1;
                        break;
                    case 1: {
                        bePadData *pad = bePadManager_GetPadForPlayer(t->_padManager, t->_ramNo, 1);
                        int a3 = pad->_trigger;
                        int a2 = pad->_repeat;
                        int a0 = pad->_lTrg | pad->_lRpt;
                        bool a1 = true;
                        if (!(a0 & 1) && !((a3 | a2) & 0x10)) a1 = false;
                        bool a0b = true;
                        if (!(a0 & 4) && !((a3 | a2) & 0x40)) a0b = false;
                        if (a1) {
                            if (t->_curPoint == 1) {
                                t->_curPoint = 0;
                                beMessenger_SendNamed(t->_messenger, DAT_00517a48, DAT_00517a60, t->_ramNo, DAT_00517a90);
                                t->_statCtrl = 2;
                            }
                        } else if (a0b) {
                            if (t->_curPoint == 0) {
                                t->_curPoint = 1;
                                beMessenger_SendNamed(t->_messenger, DAT_00517a48, DAT_00517a60, t->_ramNo, DAT_00517aa0);
                                t->_statCtrl = 3;
                            }
                        } else if (a3 & 0x4000) {
                            if (t->_curPoint == 0) {
                                beMessenger_SendNamed(t->_messenger, DAT_00517a48, DAT_00517a60, t->_ramNo, DAT_00517ab0);
                            } else {
                                beMessenger_SendNamed(t->_messenger, DAT_00517a48, DAT_00517a60, t->_ramNo, DAT_00517ac0);
                            }
                            t->_statCtrl = 4;
                        }
                        break;
                    }
                    case 2:
                        if (!(FUN_003eca00(t, t->_ramNo, DAT_00517a60, DAT_00517a90) & 0xFF)) t->_statCtrl = 1;
                        break;
                    case 3:
                        if (!(FUN_003eca00(t, t->_ramNo, DAT_00517a60, DAT_00517aa0) & 0xFF)) t->_statCtrl = 1;
                        break;
                    case 4:
                        if (t->_curPoint == 0) {
                            if (!(FUN_003eca00(t, t->_ramNo, DAT_00517a60, DAT_00517ab0) & 0xFF)) {
                                beNDMWLoadIntf2MesWin__RequestMesErase(t);
                                t->_isSelect = 1;
                                t->_isCtrl = 0;
                            }
                        } else if (!(FUN_003eca00(t, t->_ramNo, DAT_00517a60, DAT_00517ac0) & 0xFF)) {
                            beNDMWLoadIntf2MesWin__RequestMesErase(t);
                            t->_isSelect = 1;
                            t->_isCtrl = 0;
                        }
                        break;
                    }
                    break;
                case 1:
                    switch (t->_statCtrl) {
                    case 0:
                        beMessenger_SendNamed(t->_messenger, DAT_00517a48, DAT_00517a60, t->_ramNo, DAT_00517ad0);
                        t->_statCtrl = t->_statCtrl + 1;
                        break;
                    case 1:
                        if (bePadManager_GetPadForPlayer(t->_padManager, t->_ramNo, 1)->_trigger & 0x4000) {
                            beMessenger_SendNamed(t->_messenger, DAT_00517a48, DAT_00517a60, t->_ramNo, DAT_00517ae0);
                            t->_statCtrl = t->_statCtrl + 1;
                        }
                        break;
                    case 2:
                        if (!(FUN_003eca00(t, t->_ramNo, DAT_00517a60, DAT_00517ae0) & 0xFF)) {
                            beNDMWLoadIntf2MesWin__RequestMesErase(t);
                            t->_isSelect = 1;
                            t->_isCtrl = 0;
                        }
                        break;
                    }
                    break;
                }
            }
        } else {
            switch (t->_sysStat) {
            case 0:
                beMessenger_SendNamed(t->_messenger, DAT_00517a48, DAT_00517a60, t->_ramNo, DAT_00517af0);
                t->_sysStat = t->_sysStat + 1;
                break;
            case 1:
                break;
            }
        }
        if (t->_isMesCom == 1) {
            if (t->_isSystemMes == 1) {
                beNDMWLoadIntf2TextOrder_PublishIdLines(t->_textOrder, t->_sysMesNo, 1);
            } else if (t->_isMesErase == 0) {
                t->_isDisp = 1;
                beNDMWLoadIntf2TextOrder_PublishIdLines(t->_textOrder, t->_mesNo, 1);
            } else {
                s = 0;
                do {
                    TextOrder_ClearFont(t->_textOrder, DAT_005176a0, t->_ramNo, s);
                    s += 1;
                } while (s < 4);
                s = 4;
                do {
                    TextOrder_ClearFont(t->_textOrder, DAT_005176b0, t->_ramNo, s - 4);
                    s += 1;
                } while (s < 6);
                t->_isMesErase = 0;
                t->_isDisp = 0;
                if (t->_isWinClose == 1) {
                    t->_isWinOpen = 0;
                }
            }
            t->_isMesCom = 0;
        }
    }
}

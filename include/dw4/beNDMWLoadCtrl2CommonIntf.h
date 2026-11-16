#ifndef DW4_BENDMWLOADCTRL2COMMONINTF_H
#define DW4_BENDMWLOADCTRL2COMMONINTF_H

struct beNDMWLoadCtrl2CommonIntf;
struct beNDMWLoadIntf2MesWin;

extern "C" {
beNDMWLoadCtrl2CommonIntf *beNDMWLoadCtrl2CommonIntf_Create(int allocator);
void beNDMWLoadCtrl2CommonIntf__GiveCtrlTo(beNDMWLoadCtrl2CommonIntf *intf, int player);
void beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(beNDMWLoadCtrl2CommonIntf *intf, int player);
void beNDMWLoadCtrl2CommonIntf__StartUtilFor(beNDMWLoadCtrl2CommonIntf *intf, int player, int state);
int beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth);
int beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth);
int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth);
int beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int promptNo, int questionNo, int cursor, int depth);
int beNDMWLoadCtrl2CommonIntf__StepReadMedia(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth);
int beNDMWLoadCtrl2CommonIntf__StepWriteSaveData(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int saveIndex, int depth);
void beNDMWLoadCtrl2CommonIntf__UpdateCutConnect(beNDMWLoadCtrl2CommonIntf *intf);
}

#endif

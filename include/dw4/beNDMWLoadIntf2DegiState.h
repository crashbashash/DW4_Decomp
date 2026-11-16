#ifndef DW4_BENDMWLOADINTF2DEGISTATE_H
#define DW4_BENDMWLOADINTF2DEGISTATE_H

struct beNDMWLoadIntf2DegiState;

extern "C" {
beNDMWLoadIntf2DegiState *beNDMWLoadIntf2DegiState_Create(int allocator);
void beNDMWLoadIntf2DegiState__Init(beNDMWLoadIntf2DegiState *self, int plNo, int commonIntf, int textOrder, int comMdlCtrl, int messenger, int dispPos);
void beNDMWLoadIntf2DegiState__RequestClose(beNDMWLoadIntf2DegiState *self, int closeKind);
void beNDMWLoadIntf2DegiState__RequestConfirmClose(beNDMWLoadIntf2DegiState *self);
void beNDMWLoadIntf2DegiState__RequestOpen(beNDMWLoadIntf2DegiState *self, int kind, int dataNo);
unsigned char beNDMWLoadIntf2DegiState__Update(beNDMWLoadIntf2DegiState *self);
}

#endif

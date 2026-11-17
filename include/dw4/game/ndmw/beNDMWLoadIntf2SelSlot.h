#ifndef DW4_BENDMWLOADINTF2SELSLOT_H
#define DW4_BENDMWLOADINTF2SELSLOT_H

struct beNDMWLoadIntf2SelSlot;

extern "C" {
beNDMWLoadIntf2SelSlot *beNDMWLoadIntf2SelSlot_Create(int allocator);
unsigned char beNDMWLoadIntf2SelSlot__Close(beNDMWLoadIntf2SelSlot *self);
void beNDMWLoadIntf2SelSlot__Init(beNDMWLoadIntf2SelSlot *self);
unsigned char beNDMWLoadIntf2SelSlot__Open(beNDMWLoadIntf2SelSlot *self, int selPoint);
void beNDMWLoadIntf2SelSlot__PublishCursor(beNDMWLoadIntf2SelSlot *self);
void beNDMWLoadIntf2SelSlot__RefreshSlotMarks(beNDMWLoadIntf2SelSlot *self, int lostEntry);
void beNDMWLoadIntf2SelSlot__Reset(beNDMWLoadIntf2SelSlot *self);
unsigned char beNDMWLoadIntf2SelSlot__UpdateSelection(beNDMWLoadIntf2SelSlot *self, unsigned char usePad, unsigned char checkDone);
}

#endif

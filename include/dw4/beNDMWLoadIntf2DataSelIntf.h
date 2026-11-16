#ifndef DW4_BENDMWLOADINTF2DATASELINTF_H
#define DW4_BENDMWLOADINTF2DATASELINTF_H

struct beNDMWLoadIntf2DataSelIntf;

extern "C" {
beNDMWLoadIntf2DataSelIntf *beNDMWLoadIntf2DataSelIntf_Create(int allocator);
void beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(beNDMWLoadIntf2DataSelIntf *self, int level);
unsigned char beNDMWLoadIntf2DataSelIntf__CloseAll(beNDMWLoadIntf2DataSelIntf *self, int level);
unsigned char beNDMWLoadIntf2DataSelIntf__CloseSaveArea(beNDMWLoadIntf2DataSelIntf *self, int level);
unsigned char beNDMWLoadIntf2DataSelIntf__CloseStatusWindows(beNDMWLoadIntf2DataSelIntf *self, int level);
void beNDMWLoadIntf2DataSelIntf__Init(beNDMWLoadIntf2DataSelIntf *self, int player, int kind);
bool beNDMWLoadIntf2DataSelIntf__OpenAreaCursor(beNDMWLoadIntf2DataSelIntf *self, int level);
unsigned char beNDMWLoadIntf2DataSelIntf__OpenSaveArea(beNDMWLoadIntf2DataSelIntf *self, int level);
unsigned char beNDMWLoadIntf2DataSelIntf__OpenSlotSaveArea(beNDMWLoadIntf2DataSelIntf *self, int level);
unsigned char beNDMWLoadIntf2DataSelIntf__RestoreSaveArea(beNDMWLoadIntf2DataSelIntf *self, int level);
int beNDMWLoadIntf2DataSelIntf__ShowAccessPlayers(beNDMWLoadIntf2DataSelIntf *self, int level);
unsigned char beNDMWLoadIntf2DataSelIntf__ShowSelectedStatus(beNDMWLoadIntf2DataSelIntf *self, int level);
unsigned char beNDMWLoadIntf2DataSelIntf__UpdateSelection(beNDMWLoadIntf2DataSelIntf *self, int level);
}

#endif

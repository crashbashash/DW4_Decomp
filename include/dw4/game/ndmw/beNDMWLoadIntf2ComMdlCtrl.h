#ifndef DW4_BENDMWLOADINTF2COMMDLCTRL_H
#define DW4_BENDMWLOADINTF2COMMDLCTRL_H

struct beNDMWLoadIntf2ComMdlCtrl;

extern "C" {
beNDMWLoadIntf2ComMdlCtrl *beNDMWLoadIntf2ComMdlCtrl_Create(int allocator);
void beNDMWLoadIntf2ComMdlCtrl__Close(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSequence, unsigned char trackClose);
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self);
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self);
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsRunning(beNDMWLoadIntf2ComMdlCtrl *self, int slot, const char *name);
void beNDMWLoadIntf2ComMdlCtrl__Play(beNDMWLoadIntf2ComMdlCtrl *self, int slot, const void *modelName, const void *sequenceName, int wait);
void beNDMWLoadIntf2ComMdlCtrl__Poll(beNDMWLoadIntf2ComMdlCtrl *self);
void beNDMWLoadIntf2ComMdlCtrl__Start(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSQ, int recordOpen);
void beNDMWLoadIntf2ComMdlCtrl__StartAt(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSQ, float *position, int recordOpen);
}

#endif

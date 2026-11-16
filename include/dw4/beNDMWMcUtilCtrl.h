#ifndef DW4_BENDMWMCUTILCTRL_H
#define DW4_BENDMWMCUTILCTRL_H

struct beNDMWMcUtilCtrl;

extern "C" {
beNDMWMcUtilCtrl *beNDMWMcUtilCtrl_Create(int allocator);
unsigned char beNDMWMcUtilCtrl__CheckReady(beNDMWMcUtilCtrl *util);
void beNDMWMcUtilCtrl__Generate(beNDMWMcUtilCtrl *util);
void beNDMWMcUtilCtrl__Init(beNDMWMcUtilCtrl *util, int messenger, int kindHard);
bool beNDMWMcUtilCtrl__IsRemoved(beNDMWMcUtilCtrl *util);
void beNDMWMcUtilCtrl__Remove(beNDMWMcUtilCtrl *util);
void beNDMWMcUtilCtrl__Request(beNDMWMcUtilCtrl *util, int kind, int slot);
void beNDMWMcUtilCtrl__Update(beNDMWMcUtilCtrl *util);
}

#endif

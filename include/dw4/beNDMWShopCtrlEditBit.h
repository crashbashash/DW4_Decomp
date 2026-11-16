#ifndef DW4_BENDMWSHOPCTRLEDITBIT_H
#define DW4_BENDMWSHOPCTRLEDITBIT_H

struct beNDMWShopCtrlEditBit;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWShopCtrlEditBit_metaObject;
beNDMWShopCtrlEditBit *beNDMWShopCtrlEditBit_Create(int allocator);
void beNDMWShopCtrlEditBit_ShowValueDigits(beNDMWShopCtrlEditBit *self, int mode, int value);
}

#endif

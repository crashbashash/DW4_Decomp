#ifndef DW4_BENDMWSTATUSTITLE01_H
#define DW4_BENDMWSTATUSTITLE01_H

struct beNDMWStatusTitle01;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWStatusTitle01_metaObject;
beNDMWStatusTitle01 *beNDMWStatusTitle01_Create(int allocator);
void beNDMWStatusTitle01_ShowShopLayout(beNDMWStatusTitle01 *self);
void beNDMWStatusTitle01_ShowStatusLayout(beNDMWStatusTitle01 *self);
}

#endif

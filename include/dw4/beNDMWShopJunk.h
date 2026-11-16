#ifndef DW4_BENDMWSHOPJUNK_H
#define DW4_BENDMWSHOPJUNK_H

struct beNDMWShopJunk;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWShopJunk_metaObject;
beNDMWShopJunk *beNDMWShopJunk_Create(int allocator);
}

#endif

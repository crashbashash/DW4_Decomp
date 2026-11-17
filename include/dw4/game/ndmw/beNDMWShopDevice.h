#ifndef DW4_BENDMWSHOPDEVICE_H
#define DW4_BENDMWSHOPDEVICE_H

struct beNDMWShopDevice;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWShopDevice_metaObject;
beNDMWShopDevice *beNDMWShopDevice_Create(int allocator);
}

#endif

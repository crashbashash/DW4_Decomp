#ifndef DW4_BENDMWITEMDISK_H
#define DW4_BENDMWITEMDISK_H

struct beNDMWItemDisk;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWItemDisk_metaObject;
beNDMWItemDisk *beNDMWItemDisk_Create(int allocator);
void beNDMWItemDisk_Set(beNDMWItemDisk *self, int recNo);
}

#endif

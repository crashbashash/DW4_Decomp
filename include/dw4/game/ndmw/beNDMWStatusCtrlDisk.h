#ifndef DW4_BENDMWSTATUSCTRLDISK_H
#define DW4_BENDMWSTATUSCTRLDISK_H

struct beNDMWStatusCtrlDisk;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWStatusCtrlDisk_metaObject;
beNDMWStatusCtrlDisk *beNDMWStatusCtrlDisk_Create(int allocator);
}

#endif

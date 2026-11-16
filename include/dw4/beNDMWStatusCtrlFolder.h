#ifndef DW4_BENDMWSTATUSCTRLFOLDER_H
#define DW4_BENDMWSTATUSCTRLFOLDER_H

struct beNDMWStatusCtrlFolder;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWStatusCtrlFolder_metaObject;
beNDMWStatusCtrlFolder *beNDMWStatusCtrlFolder_Create(int allocator);
}

#endif

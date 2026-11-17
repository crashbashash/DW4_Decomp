#ifndef DW4_BENDMWSTAGECTL_H
#define DW4_BENDMWSTAGECTL_H

struct beNDMWStageCtl;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWStageCtl_metaObject;
beNDMWStageCtl *beNDMWStageCtl_CreateInstance(int allocator);
}

#endif

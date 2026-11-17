#ifndef DW4_BENDMWSTATUS_H
#define DW4_BENDMWSTATUS_H

struct beNDMWStatus;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWStatus_metaObject;
beNDMWStatus *beNDMWStatus_CreateInstance(int allocator);
}

#endif

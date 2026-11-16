#ifndef DW4_BENDMWSTATUSMAINSLOT_H
#define DW4_BENDMWSTATUSMAINSLOT_H

struct beNDMWStatusMainSlot;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWStatusMainSlot_metaObject;
beNDMWStatusMainSlot *beNDMWStatusMainSlot_Create(int allocator);
}

#endif

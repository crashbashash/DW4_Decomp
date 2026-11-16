#ifndef DW4_BENDMWSTATUSSUBSLOT_H
#define DW4_BENDMWSTATUSSUBSLOT_H

struct beNDMWStatusSubSlot;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWStatusSubSlot_metaObject;
beNDMWStatusSubSlot *beNDMWStatusSubSlot_Create(int allocator);
}

#endif

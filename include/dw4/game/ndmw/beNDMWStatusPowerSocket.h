#ifndef DW4_BENDMWSTATUSPOWERSOCKET_H
#define DW4_BENDMWSTATUSPOWERSOCKET_H

struct beNDMWStatusPowerSocket;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWStatusPowerSocket_metaObject;
beNDMWStatusPowerSocket *beNDMWStatusPowerSocket_Create(int allocator);
}

#endif

#ifndef DW4_BENDMWITEMWAZA_H
#define DW4_BENDMWITEMWAZA_H

struct beNDMWItemWaza;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWItemWaza_metaObject;
beNDMWItemWaza *beNDMWItemWaza_Create(int allocator);
void beNDMWItemWaza_Set(beNDMWItemWaza *self, int recNo, int baseNo);
}

#endif

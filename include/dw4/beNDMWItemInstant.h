#ifndef DW4_BENDMWITEMINSTANT_H
#define DW4_BENDMWITEMINSTANT_H

struct beNDMWItemInstant;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWItemInstant_metaObject;
beNDMWItemInstant *beNDMWItemInstant_Create(int allocator);
void beNDMWItemInstant_Set(beNDMWItemInstant *self, int recNo);
}

#endif

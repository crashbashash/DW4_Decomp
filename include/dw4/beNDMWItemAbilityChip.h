#ifndef DW4_BENDMWITEMABILITYCHIP_H
#define DW4_BENDMWITEMABILITYCHIP_H

struct beNDMWItemAbilityChip;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWItemAbilityChip_metaObject;
beNDMWItemAbilityChip *beNDMWItemAbilityChip_Create(int allocator);
void beNDMWItemAbilityChip_Set(beNDMWItemAbilityChip *self, int recNo);
}

#endif

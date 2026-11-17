#ifndef DW4_BENDMWITEMYELLOWARMOR_H
#define DW4_BENDMWITEMYELLOWARMOR_H

struct beNDMWItemYellowArmor;
struct beNDMWStatus;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWItemYellowArmor_metaObject;
beNDMWItemYellowArmor *beNDMWItemYellowArmor_Create(int allocator);
void beNDMWItemYellowArmor_Set(beNDMWItemYellowArmor *self, int recNo, int revision);
void beNDMWItemYellowArmor_SetRandom(beNDMWItemYellowArmor *self, int recNo, beNDMWStatus *status, int level);
}

#endif

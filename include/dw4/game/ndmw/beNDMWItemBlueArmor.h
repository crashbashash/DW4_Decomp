#ifndef DW4_BENDMWITEMBLUEARMOR_H
#define DW4_BENDMWITEMBLUEARMOR_H

struct beNDMWItemBlueArmor;
struct beNDMWStatus;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWItemBlueArmor_metaObject;
beNDMWItemBlueArmor *beNDMWItemBlueArmor_Create(int allocator);
void beNDMWItemBlueArmor_Set(beNDMWItemBlueArmor *self, int recNo, int pocket, int revision);
void beNDMWItemBlueArmor_SetRandom(beNDMWItemBlueArmor *self, int recNo, beNDMWStatus *status, int level);
}

#endif

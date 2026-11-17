#ifndef DW4_BENDMWITEMWEAPON_H
#define DW4_BENDMWITEMWEAPON_H

struct beNDMWItemWeapon;
struct beNDMWStatus;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWItemWeapon_metaObject;
beNDMWItemWeapon *beNDMWItemWeapon_Create(int allocator);
void beNDMWItemWeapon_Set(beNDMWItemWeapon *self, int recNo, int pocket, int revision);
void beNDMWItemWeapon_SetRandom(beNDMWItemWeapon *self, int recNo, beNDMWStatus *status, int level);
}

#endif

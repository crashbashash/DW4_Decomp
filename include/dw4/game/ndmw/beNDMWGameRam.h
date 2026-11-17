#ifndef DW4_BENDMWGAMERAM_H
#define DW4_BENDMWGAMERAM_H

struct beNDMWGameRam;
struct igMetaEnum;
struct igMetaObject;

extern "C" {
extern igMetaObject *g_beNDMWGameRam_metaObject;
igMetaEnum *FightCom_GetMetaEnum(void);
igMetaEnum *GameRamMessage_GetMetaEnum(void);
int beNDMWGameRam_CalcAttribute(beNDMWGameRam *self, int index, int species, int attribute);
int beNDMWGameRam_CalcMaxPoints(beNDMWGameRam *self, int index, int species, int isHp);
int beNDMWGameRam_ChangeHp(beNDMWGameRam *self, int player_index, int delta, int absolute);
void beNDMWGameRam_ChangeMp(beNDMWGameRam *self, int player_index, int delta);
beNDMWGameRam *beNDMWGameRam_CreateInstance(int allocator);
void beNDMWGameRam_igObjectList_Remove(void *list, int index);
}

#endif

/* The flat field is const: its read is created before the *out reload so the register colouring puts
 * the field in a0 and the running total in v1. */
#include "dw4/reflected.h"
extern "C" {
struct BonusItem { char pad[20]; const int flat; };
struct BonusFolder { char pad[12]; igObjectList *list; };
int beNDMWItemBase_GetRecordInt(beNDMWItemBase *, beNDMWGameRam *, const char *);
struct BonusFolder *igProperty_GetRecordFolder(void *, const char *);
extern int DAT_00518ac0[4];
void FUN_003fa120(beNDMWGameRam *gameram, void *player, int *out, const char *name, int with_flat) {
    beNDMWItemBase *item;
    if (igProperty_GetRecordFolder(player, (const char *)&DAT_00518ac0[0])->list->_count != 0) {
        item = ((beNDMWItemBase **)igProperty_GetRecordFolder(player, (const char *)&DAT_00518ac0[0])->list->_data)[0];
        if (item != 0) {
            *out += beNDMWItemBase_GetRecordInt(item, gameram, name);
            if (with_flat != 0) {
                *out += ((BonusItem *)item)->flat;
            }
        }
    }
}
}

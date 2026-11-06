/* Adds one equipment-style bonus to *out: the first element of the property folder's list gives
 * GetRecordInt(record, gameram, name), and when `with_flat` is set the record's own field at +20
 * is added too. Matching note: the +20 read is volatile -- it is created before the *out reload so
 * the register colouring puts the field in a0 and the running total in v1 (alternate compiler,
 * -O3,p). */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
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
                *out += *(volatile int *)((char *)item + 20);
            }
        }
    }
}
} /* extern "C" */

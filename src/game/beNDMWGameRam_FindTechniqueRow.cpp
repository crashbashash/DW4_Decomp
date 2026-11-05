/* WAZALIST base number -> current database row; 0x003fc6f0, 132 bytes.
 * Declaration order preserves the original loop register allocation.
 * The unused receiver occupies a0. A miss leaves output unchanged.
 */
#include "dw4/reflected.h"

/* Only the property record's reviewed +12 value is projected here. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct TechniqueListProperty {
    char pad[12];
    igObjectList *list;
} TechniqueListProperty;
TechniqueListProperty *igProperty_GetRecordFolder(void *, const char *);
extern const char s_WAZALIST_00518928[16]; /* WAZALIST */

void beNDMWGameRam_FindTechniqueRow(beNDMWGameRam *receiver, void *player,
                                   int base_no, int *output)
{
    igObjectList *list;
    int index;
    beNDMWItemWaza *item;
    int count;

    list = igProperty_GetRecordFolder(player, s_WAZALIST_00518928)->list;
    count = list->_count;
    index = 0;
    for (; index < count; ++index) {
        item = ((beNDMWItemWaza **)list->_data)[index];
        if (base_no == item->_baseNo) {
            *output = item->_recNo;
            return;
        }
    }
}
} /* extern "C" */

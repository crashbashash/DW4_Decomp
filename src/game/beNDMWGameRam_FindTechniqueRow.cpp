/* WAZALIST base number -> current database row. Declaration order preserves the loop register
 * allocation. The unused receiver occupies a0. A miss leaves output unchanged. */
#include "dw4/reflected.h"

/* Only the property record's +12 value is declared here. */
extern "C" {
typedef struct TechniqueListProperty {
    char pad[12];
    igObjectList *list;
} TechniqueListProperty;
TechniqueListProperty *igProperty_GetRecordFolder(void *, const char *);
extern const char WAZALIST[16]; /* WAZALIST */

void beNDMWGameRam_FindTechniqueRow(beNDMWGameRam *receiver, void *player,
                                   int base_no, int *output)
{
    igObjectList *list;
    int index;
    beNDMWItemWaza *item;
    int count;

    list = igProperty_GetRecordFolder(player, WAZALIST)->list;
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
}

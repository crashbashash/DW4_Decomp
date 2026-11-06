/* Current player record -> BASE_* save arrays. Mirror of the post-load BASE -> current mapping:
 * LEVEL and EXP go to the species' slot of BASE_LEVEL / BASE_EXP, SKILL[9] and UPCNT[11] to
 * BASE_SKILL[species * 9 + i] / BASE_UPCNT[species * 11 + i]. Every store is bounds-checked
 * against the destination list's count, like an inlined igIntList set. The declaration order
 * preserves the original register allocation. */
#include "dw4/reflected.h"
/* Property record as returned by igProperty_GetRecord: scalar value at +12. */
extern "C" {
typedef struct PropertyRecord {
    char pad[12];
    int value;
} PropertyRecord;
/* Same record layout for list-valued properties: igIntList pointer at +12. */
typedef struct PropertyIntArray {
    char pad[12];
    igIntList *list;
} PropertyIntArray;
PropertyRecord *igProperty_GetRecord(int, const char *);
PropertyIntArray *FUN_003a9250(int, const char *);
extern const char DIGIMONNO_2[]; /* DIGIMONNO */
extern const char LEVEL_2[]; /* LEVEL */
extern const char SKILL[]; /* SKILL */
extern const char UPCNT[]; /* UPCNT */
extern const char EXP[]; /* EXP */
extern const char BASE_LEVEL[]; /* BASE_LEVEL */
extern const char BASE_EXP[]; /* BASE_EXP */
extern const char BASE_SKILL[]; /* BASE_SKILL */
extern const char BASE_UPCNT[]; /* BASE_UPCNT */

void FUN_003f8760(beNDMWGameRam *self, int player_index)
{
    int upcnt_base;
    igIntList *exp_list;
    int player;
    int upcnt;
    int skill_base;
    int skill_index;
    int skill;
    int upcnt_index;
    int species;
    int value;
    igIntList *level_list;
    igIntList *player_list;
    PropertyIntArray *base_array;

    player_list = (igIntList *)self->_playerDataListList;
    player = ((int *)player_list->_data)[player_index];
    species = igProperty_GetRecord(player, DIGIMONNO_2)->value;
    value = igProperty_GetRecord(player, LEVEL_2)->value;
    level_list = FUN_003a9250(player, BASE_LEVEL)->list;
    if (level_list->_count != 0 && species >= 0 && species < level_list->_count)
        ((int *)level_list->_data)[species] = value;
    value = igProperty_GetRecord(player, EXP)->value;
    exp_list = FUN_003a9250(player, BASE_EXP)->list;
    if (exp_list->_count != 0 && species >= 0 && species < exp_list->_count)
        ((int *)exp_list->_data)[species] = value;
    skill_base = species * 9;
    for (skill_index = 0; skill_index < 9; ++skill_index) {
        skill = ((int *)FUN_003a9250(player, SKILL)->list->_data)[skill_index];
        base_array = FUN_003a9250(player, BASE_SKILL);
        if (base_array->list->_count != 0 && skill_base + skill_index >= 0 &&
            skill_base + skill_index < base_array->list->_count)
            ((int *)base_array->list->_data)[skill_base + skill_index] = skill;
    }
    upcnt_base = species * 11;
    for (upcnt_index = 0; upcnt_index < 11; ++upcnt_index) {
        upcnt = ((int *)FUN_003a9250(player, UPCNT)->list->_data)[upcnt_index];
        base_array = FUN_003a9250(player, BASE_UPCNT);
        if (base_array->list->_count != 0 && upcnt_base + upcnt_index >= 0 &&
            upcnt_base + upcnt_index < base_array->list->_count)
            ((int *)base_array->list->_data)[upcnt_base + upcnt_index] = upcnt;
    }
}
}

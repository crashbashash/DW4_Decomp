/* Cached FightCom metadata enum, 0x003c9be0; 22 command names (table at 0x004cc350, ids at
 * 0x004cc3b0) built once and cached at 0x0058c090. Matching compiler requirement:
 * config/SLUS-20836/unit-compilers.tsv. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
struct Enum;
/* igMetaEnum_Create(name, names[], values[], count): see config/SLUS-20836/names/ObjectModel.tsv */
struct Enum *igMetaEnum_Create(const char *, const char *const *, const int *, int);
extern const char FightCom[];
extern const char *const g_FightCom_commandNames[22];
extern const int g_FightCom_commandIds[22];
extern struct Enum *g_FightCom_metaEnum[4];

struct Enum *FightCom_GetMetaEnum(void)
{
    if (!g_FightCom_metaEnum[0])
        g_FightCom_metaEnum[0] = igMetaEnum_Create(FightCom, g_FightCom_commandNames,
                                          g_FightCom_commandIds, 22);
    return g_FightCom_metaEnum[0];
}
} /* extern "C" */

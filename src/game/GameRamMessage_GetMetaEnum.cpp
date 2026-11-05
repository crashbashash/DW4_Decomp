/* Cached GAMERAM Message metadata enum, 0x003c9c40; 22 command names and ids.
 * Matching compiler requirement: config/SLUS-20836/unit-compilers.tsv.
 */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
struct Enum;
/* igMetaEnum_Create(name, names[], values[], count): see config/SLUS-20836/names/ObjectModel.tsv */
struct Enum *igMetaEnum_Create(const char *, const char *const *, const int *, int);
extern const char s_Message_00510d58[];
extern const char *const g_GameRamMessage_commandNames_004cc410[22];
extern const int g_GameRamMessage_commandIds_004cc470[22];
extern struct Enum *g_GameRamMessage_metaEnum_0058c098[4];

struct Enum *GameRamMessage_GetMetaEnum(void)
{
    if (!g_GameRamMessage_metaEnum_0058c098[0])
        g_GameRamMessage_metaEnum_0058c098[0] = igMetaEnum_Create(s_Message_00510d58, g_GameRamMessage_commandNames_004cc410,
                                          g_GameRamMessage_commandIds_004cc470, 22);
    return g_GameRamMessage_metaEnum_0058c098[0];
}
} /* extern "C" */

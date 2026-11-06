/* Cached FightCom metadata enum: 22 command names built once and cached. */
extern "C" {
struct Enum;
/* igMetaEnum_Create(name, names[], values[], count). */
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
}

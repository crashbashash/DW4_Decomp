/* Cached GAMERAM Message metadata enum: 22 command names and ids. */
extern "C" {
struct Enum;
/* igMetaEnum_Create(name, names[], values[], count). */
struct Enum *igMetaEnum_Create(const char *, const char *const *, const int *, int);
extern const char Message[];
extern const char *const g_GameRamMessage_commandNames[22];
extern const int g_GameRamMessage_commandIds[22];
extern struct Enum *g_GameRamMessage_metaEnum[4];

struct Enum *GameRamMessage_GetMetaEnum(void)
{
    if (!g_GameRamMessage_metaEnum[0])
        g_GameRamMessage_metaEnum[0] = igMetaEnum_Create(Message, g_GameRamMessage_commandNames,
                                          g_GameRamMessage_commandIds, 22);
    return g_GameRamMessage_metaEnum[0];
}
}

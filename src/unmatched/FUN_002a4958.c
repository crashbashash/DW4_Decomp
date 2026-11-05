/* 0x002a4958 — FUN_002a4958 (92 bytes). Returns how far the active source's decode position (FUN_002a5a50 then FUN_002af070) is past its base at +3464, or 0 when inactive. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002a5a50();
void FUN_002af070();

struct Source2a4958 {
    char pad0[36];
    int f36;                              /* +3464 */
    char pad40[44 - 40];
    int active;                           /* +3472 */
    char f48[4];                          /* +3476: read by FUN_002a5a50 */
};
struct Player2a4958 {
    char pad0[3428];
    struct Source2a4958 source;           /* +3428 */
};
struct Desc2a4958 {
    int f0, f4, f8, f12, f16, f20;
    int f24;
    int f28;
};

int FUN_002a4958(struct Player2a4958 *player) {
    struct Source2a4958 *source = &player->source;
    struct Desc2a4958 desc;
    int position;
    int size;

    /* matching construct: manual — active/f48 read through the player, f36 through the source pointer */
    if (player->source.active == 0) {
        return 0;
    }
    FUN_002a5a50(player->source.f48, &desc);
    desc.f24 = 0;
    FUN_002af070(&desc, &position, &size);
    return position - source->f36;
}

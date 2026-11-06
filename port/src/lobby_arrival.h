/* Generated from NDMW 820 Lua 4. Pack SHA256:
 * 4737543c23cfa1b37cd3e4d31e1746755fec1afd5faafad0ea96c5b2bc07d036 */
enum { LOBBY_MALE_WALK_DELAY = 20, LOBBY_RELOCATE_DELAY = 10,
       LOBBY_RESTORE_DELAY = 120, LOBBY_FADE_DELAY = 5,
       LOBBY_PLAYER_ENTRY_DELAY = 180 };
static const char lobby_terminal_cue[] = "mlBEEP01";
static const float lobby_guide_departure_target[3] = { 20, 10, -35 };
static const struct { unsigned actor, tick; int motion; } lobby_opening[] = {
    { 1, 20, 2 },
    { 1, 50, 1 },
    { 0, 60, 2 },
    { 0, 110, 1 },
    { 1, 100, 2 },
    { 1, 160, 1 },
    { 1, 180, 2 },
    { 1, 210, 1 },
    { 0, 190, 2 },
    { 0, 220, 1 },
};

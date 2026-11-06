/* Applies FUN_0029ea28(value) to the player's three streams at +8068, +8064 and +8072. */
void FUN_0029ea28();

struct Params;
/* Block at +8044 in the player (handles shared by FUN_002a2248..FUN_002a2620). */
struct Streams {
    int f0;
    int f4;
    struct Params *params;                /* +8052 */
    int f12;
    int video;                            /* +8060 */
    int f20;                              /* +8064 */
    int f24;                              /* +8068 */
    int f28;                              /* +8072 */
};
struct Player {
    char pad[8044];
    struct Streams streams;               /* +8044 */
};

void FUN_002a2620(struct Player *player, int value) {
    struct Streams *streams = &player->streams;

    FUN_0029ea28(player, streams->f24, value);
    FUN_0029ea28(player, streams->f20, value);
    FUN_0029ea28(player, streams->f28, value);
}

/* Returns the AND of FUN_0029ea88 over the player's three streams at +8068, +8064 and +8072. */
int FUN_0029ea88();

struct Params;
/* Block at +8044 in the player. */
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

int FUN_002a2248(struct Player *player) {
    struct Streams *streams = &player->streams;
    int a;
    int b;
    int c;

    a = FUN_0029ea88(player, streams->f24);
    b = FUN_0029ea88(player, streams->f20);
    c = FUN_0029ea88(player, streams->f28);
    return a & b & c;
}

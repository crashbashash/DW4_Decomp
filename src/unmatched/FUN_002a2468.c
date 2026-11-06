/* When FUN_0029ea88 reports the player's video stream ready (1), runs FUN_002a21d8 with
 * params->f60; reports whether it did through *done. */
int FUN_0029ea88();
void FUN_002a21d8();

struct Params {
    char pad[60];
    int f60;
};
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

void FUN_002a2468(struct Player *player, int *done) {
    struct Streams *streams = &player->streams;
    struct Params *params = streams->params;
    int result;
    int handled;

    result = FUN_0029ea88(player, streams->video);
    if (result == 1) {
        FUN_002a21d8(player, params->f60);
        handled = 1;
    } else {
        handled = 0;
    }
    if (done != 0) {
        *done = handled;
    }
}

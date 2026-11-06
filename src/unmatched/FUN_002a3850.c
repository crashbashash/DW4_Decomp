/* When options 93 and 94 are both set and the context is in state 192, hands them to FUN_0028f360
 * and on success moves the context to state 200 (f116 = 2). */
int FUN_0028f360();
int FUN_002adc40();

struct Context2a3850 {
    void *handle;
    char pad4[116 - 4];
    int f116;
    int state;                            /* +120: 192 -> 200 once FUN_0028f360 accepts the pair */
};
struct Player2a3850 {
    char pad0[8120];
    struct Context2a3850 *context;        /* +8120 */
};

void FUN_002a3850(struct Player2a3850 *player) {
    struct Context2a3850 *context = player->context;
    void *handle = context->handle;
    int pair[2];
    int result[4];

    pair[0] = FUN_002adc40(player, 93);
    pair[1] = FUN_002adc40(player, 94);
    if (pair[0] != 0 && pair[1] != 0 && context->state == 192) {
        if (FUN_0028f360(handle, pair, result) == 0) {
            context->f116 = 2;
            context->state = 200;
        }
    }
}

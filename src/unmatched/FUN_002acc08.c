/* Clears a state block: header words, three sub-blocks, and two FUN_ initialisers. */
int FUN_0029feb8();
int FUN_002ae248();

/* Sub-block at +2208: the two sd stores show 64-bit members at +24 and +32. */
struct Block08A0 {
    int f0, f4, f8, f12, f16, f20;
    long f24;
    long f32;
    int f40, f44;
};

struct Block0AD0 {
    int f0, f4, f8;
};

struct Block0D0C {
    int f0, f4, f8, f12, f16, f20;
};

struct State {
    int f0, f4, f8;
    char f12[2208 - 12];                  /* initialised by FUN_0029feb8 */
    struct Block08A0 b08a0;               /* +2208 */
    char pad[2768 - 2208 - (int)sizeof(struct Block08A0)];
    struct Block0AD0 b0ad0;               /* +2768 */
    char f2780[3340 - 2780];              /* initialised by FUN_002ae248 */
    struct Block0D0C b0d0c;               /* +3340 */
};

void FUN_002acc08(struct State *state) {
    struct Block08A0 *a = &state->b08a0;
    struct Block0D0C *c = &state->b0d0c;
    struct Block0AD0 *b = &state->b0ad0;

    state->f0 = 0;
    state->f4 = 0;
    state->f8 = 0;
    FUN_0029feb8(state->f12);
    a->f0 = 0;
    a->f4 = 0;
    a->f8 = 0;
    a->f12 = 0;
    a->f16 = 0;
    a->f24 = 0;
    a->f32 = 0;
    a->f40 = 0;
    a->f44 = 0;
    b->f0 = 0;
    b->f4 = 0;
    b->f8 = 0;
    FUN_002ae248(state->f2780, 0x7FFFFFFF);
    c->f0 = 0;
    c->f4 = 0;
    c->f12 = 0;
    c->f16 = 0;
    c->f20 = 0;
    c->f8 = 1; /* matching construct: manual — this store written last keeps retail's store order */
}

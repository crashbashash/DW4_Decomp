/* 0x002a0a10 — FUN_002a0a10 (192 bytes). Initialises the global state block at DAT_004be8d8 from the template DAT_004f4ea0 and the config, then starts the DAT_004bea98 sub-system with config->f0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0028b0c0();
void FUN_0028b530();
void FUN_0029d4a0();
void FUN_002a0ad0();
void FUN_002a0b88();
void FUN_002ae010();
int FUN_002afc08();
extern char DAT_004bea98[];
extern char DAT_004f4ea0[];

struct Config2a0a10 {
    int f0;
    int f4;
};
/* Global state block at DAT_004be8d8 (members named by offset). */
struct State2a0a10 {
    char f0[400];                         /* zeroed (137 bytes), then copied from DAT_004f4ea0 */
    char f400[8];                         /* copy of the first 8 bytes of the config */
    int f408;
    char f412[432 - 412];                 /* initialised by FUN_002a0b88 */
    char f432[444 - 432];                 /* initialised by FUN_002ae010 */
    char f444[516 - 444];                 /* initialised by FUN_0029d4a0 */
    int f516[8];
};
extern struct State2a0a10 DAT_004be8d8;

/* matching construct: manual — a long result returned from the int-valued FUN_002afc08 keeps the final call a jal, not a sibling call */
long FUN_002a0a10(struct Config2a0a10 *config) {
    struct State2a0a10 *state = &DAT_004be8d8;
    int i;

    FUN_0028b530(state, 0, 137);
    FUN_0028b0c0(state, DAT_004f4ea0, 400);
    __builtin_memcpy(state->f400, (void *)config, 8);
    state->f408 = 0;
    FUN_002a0b88(state->f412);
    FUN_002ae010(state->f432, config->f4);
    FUN_0029d4a0(state->f444);
    FUN_002a0ad0(state);
    for (i = 7; i >= 0; i--) {
        state->f516[i] = 0;
    }
    return FUN_002afc08(DAT_004bea98, config->f0);
}

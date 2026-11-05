/* 0x002aefe0 — FUN_002aefe0 (124 bytes). Reads the current position/rate through FUN_002aea00 and, when it differs from the pair cached at +0xD28+652/656, notifies FUN_002ae528 and updates the cache; then sets the flag at +68. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct TimingBlock {
    char pad0[652];
    int cached_pos;  /* +652 */
    int cached_rate; /* +656 */
};

struct Handle {
    char pad0[68];
    int stopped; /* +68 */
    char pad72[0xD28 - 72];
    struct TimingBlock timing; /* +0xD28 */
};

int FUN_002aea00(struct Handle *handle, int *pos, int *rate);
void FUN_002ae528(struct Handle *handle, struct TimingBlock *timing);

void FUN_002aefe0(struct Handle *handle) {
    struct TimingBlock *timing = &handle->timing;
    int pos;
    int rate;

    FUN_002aea00(handle, &pos, &rate);
    if (timing->cached_pos != pos || timing->cached_rate != rate) {
        FUN_002ae528(handle, timing);
        timing->cached_pos = pos;
        timing->cached_rate = rate;
    }
    handle->stopped = 1;
}

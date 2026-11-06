/* While the handle is active (+2384), returns whether FUN_00285118 accepts the current position
 * pair (FUN_002ae968) against the base time (+0xD28+636) advanced by the 59.94 Hz frame count at
 * +640; 0 without a base time. */
int FUN_002ae968(void *handle, int *first, int *second);
int FUN_00285118(int time, int frames, int first, int second);

struct TimingBlock {
    char pad0[636];
    int base;   /* +636; -5 = unset */
    int frames; /* +640 */
};

struct Handle {
    char pad0[2384];
    int active; /* +2384 */
    char pad2388[0xD28 - 2388];
    struct TimingBlock timing; /* +0xD28 */
};

int FUN_002afb00(struct Handle *handle) {
    struct TimingBlock *timing = &handle->timing;
    int base = timing->base;
    int frames = timing->frames;
    int first;
    int second;

    if (handle->active == 0) {
        return 1;
    }
    if (base == -5) {
        return 0;
    }
    FUN_002ae968(handle, &first, &second);
    return FUN_00285118(base + frames * 2000 / 59940, frames, first, second) != 0;
}

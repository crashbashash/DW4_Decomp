/* Returns through *out the stream rate (+0xD28+684) scaled by the type context DAT_004f5060[type]
 * over 1000, or -1 without a type; reports error 0xFF000118 when FUN_002a0dd8 refuses. */
int FUN_002a0dd8(void *handle);
int FUN_002a0bb8(void *obj, int code);
int FUN_002916f8(int value, int scale, int divisor);

extern int DAT_004f5060[];

struct TimingBlock {
    char pad0[684];
    int rate; /* +684 */
};

struct Handle {
    char pad0[2336];
    int type; /* +2336 */
    char pad2340[0xD28 - 2340];
    struct TimingBlock timing; /* +0xD28 */
};

int FUN_002af5f8(struct Handle *handle, int *out) {
    struct TimingBlock *timing;
    int type;

    *out = -1;
    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000118);
    }
    type = handle->type;
    timing = &handle->timing;
    if (type == 0) {
        return 0;
    }
    *out = FUN_002916f8(DAT_004f5060[type], timing->rate, 1000);
    return 0;
}

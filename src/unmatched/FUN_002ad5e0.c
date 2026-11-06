/* Stores a divisor/scale pair at +3528/+3532 of the handle's timing record and recomputes it with
 * FUN_002ad870; reports error 0xFF00015A when FUN_002a0dd8 refuses. */
int FUN_002a0dd8(void *handle);
int FUN_002a0bb8(void *obj, int code);
void FUN_002ad870(void *handle);

struct Timing {
    char pad0[3528];
    int divisor; /* +3528 */
    int scale;   /* +3532 */
};

struct Handle {
    char pad0[13864];
    struct Timing *timing; /* +13864 */
};

int FUN_002ad5e0(struct Handle *handle, int divisor, int scale) {
    struct Timing *timing;

    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF00015A);
    }
    timing = handle->timing;
    if (timing == 0) {
        return 0;
    }
    timing->divisor = divisor;
    timing->scale = scale;
    FUN_002ad870(handle);
    return 0;
}

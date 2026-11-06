/* Clears *verdict and, for an enabled block in state 4, asks FUN_002af848 with the limit at
 * +0xA04+180; a disabled block yields verdict 1. Reports error 0xFF000126 when FUN_002a0dd8
 * refuses. */
int FUN_002a0dd8(void *handle);
int FUN_002a0bb8(void *obj, int code);
void FUN_002af848(void *handle, int a, int b, int *verdict, int limit);

struct BlockA04 {
    char pad0[56];
    int enabled; /* +56 */
    char pad60[180 - 60];
    int limit;   /* +180 */
};

struct Handle {
    char pad0[76];
    int state; /* +76 */
    char pad80[0xA04 - 80];
    struct BlockA04 block; /* +0xA04 */
};

int FUN_002af780(struct Handle *handle, int a, int b, int *verdict) {
    int refused;
    struct BlockA04 *block;

    *verdict = 0;
    refused = FUN_002a0dd8(handle);
    block = &handle->block;
    if (refused != 0) {
        return FUN_002a0bb8(0, 0xFF000126);
    }
    if (block->enabled == 0) {
        *verdict = 1;
        return 0;
    }
    if (handle->state != 4) {
        *verdict = 0;
        return 0;
    }
    FUN_002af848(handle, a, b, verdict, block->limit);
    return 0;
}

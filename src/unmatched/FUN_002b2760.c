/* Looks up descriptor `id` (FUN_002b25a8) and, when it exists and its tag (FUN_002b2ea0) is 0xC0,
 * returns the int at +28 through *value; returns 1 then, else 0 with *value = 0. */
struct Descriptor {
    char pad0[28];
    int f28; /* +28 */
};

struct Descriptor *FUN_002b25a8(void *ctx, unsigned char id);
int FUN_002b2ea0(unsigned char id);

int FUN_002b2760(void *ctx, unsigned char id, int *value) {
    struct Descriptor *desc;

    *value = 0;
    desc = FUN_002b25a8(ctx, id);
    if (desc == 0) {
        return 0;
    }
    if (FUN_002b2ea0(id) != 0xC0) {
        return 0;
    }
    *value = desc->f28;
    return 1;
}

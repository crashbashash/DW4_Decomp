/* Looks up descriptor `id` (FUN_002b25a8) and, when FUN_002b2e60 accepts it and the format version
 * (+12) is at least 210, returns the byte at +39 through *value; returns 1 then, else 0 with
 * *value = -1. */
struct Descriptor {
    char pad0[39];
    unsigned char f39; /* +39 */
};

struct Context {
    int f0, f4, f8;
    int version; /* +12 */
};

struct Descriptor *FUN_002b25a8(struct Context *ctx, unsigned char id);
int FUN_002b2e60(unsigned char id, struct Descriptor *desc);

int FUN_002b2d20(struct Context *ctx, unsigned char id, int *value) {
    struct Descriptor *desc;

    *value = -1;
    desc = FUN_002b25a8(ctx, id);
    if (desc == 0) {
        return 0;
    }
    if (FUN_002b2e60(id, desc) == 0) {
        return 0;
    }
    if (ctx->version < 210) {
        return 0;
    }
    *value = desc->f39;
    return 1;
}

/* Looks up descriptor `id` (FUN_002b25a8) and, when it exists and its tag (FUN_002b2ea0) is 0xC0,
 * returns the byte at +27 through *value; returns 1 then, else 0 with *value = 0. */
struct Descriptor {
    char pad0[27];
    unsigned char f27; /* +27 */
};

struct Descriptor *FUN_002b25a8(void *ctx, unsigned char id);
int FUN_002b2ea0(unsigned char id);

int FUN_002b26f0(void *ctx, unsigned char id, int *value) {
    struct Descriptor *desc;

    *value = 0;
    desc = FUN_002b25a8(ctx, id);
    if (desc == 0) {
        return 0;
    }
    if (FUN_002b2ea0(id) != 0xC0) {
        return 0;
    }
    *value = desc->f27;
    return 1;
}

/* Looks up descriptor `id` (FUN_002b25a8) and, when it exists and its tag (FUN_002b2ea0) is 0xE0,
 * returns FUN_002b2db0 of the byte at +31 through *value; returns 1 then, else 0 with *value = 0. */
struct Descriptor {
    char pad0[31];
    unsigned char f31; /* +31 */
};

struct Descriptor *FUN_002b25a8(void *ctx, unsigned char id);
int FUN_002b2ea0(unsigned char id);
int FUN_002b2db0(int code);

int FUN_002b2968(void *ctx, unsigned char id, int *value) {
    struct Descriptor *desc;

    *value = 0;
    desc = FUN_002b25a8(ctx, id);
    if (desc == 0) {
        return 0;
    }
    if (FUN_002b2ea0(id) != 0xE0) {
        return 0;
    }
    *value = FUN_002b2db0(desc->f31);
    return 1;
}

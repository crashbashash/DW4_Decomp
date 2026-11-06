/* Looks up descriptor `id` (FUN_002b25a8) and, when it exists, its tag (FUN_002b2ea0) is 0xC0 and
 * the byte at +25 is 1, returns the byte at +26 through *value; returns 1 then, else 0 with *value
 * = 0. */
struct Descriptor {
    char pad0[25];
    unsigned char f25; /* +25 */
    unsigned char f26; /* +26 */
};

struct Descriptor *FUN_002b25a8(void *ctx, unsigned char id);
int FUN_002b2ea0(unsigned char id);

int FUN_002b2670(void *ctx, unsigned char id, int *value) {
    struct Descriptor *desc;

    *value = 0;
    desc = FUN_002b25a8(ctx, id);
    if (desc == 0) {
        return 0;
    }
    if (FUN_002b2ea0(id) != 0xC0) {
        return 0;
    }
    if (desc->f25 != 1) {
        return 0;
    }
    *value = desc->f26;
    return 1;
}

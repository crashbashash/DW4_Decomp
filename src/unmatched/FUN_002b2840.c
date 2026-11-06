/* Looks up descriptor `id` (FUN_002b25a8) and, when it exists and its tag (FUN_002b2ea0) is 0xE0,
 * returns the halfword at +26 (0xFFFF read as 0) through *value; returns 1 then, else 0 with
 * *value = 0. */
struct Descriptor {
    char pad0[26];
    unsigned short f26; /* +26 */
};

struct Descriptor *FUN_002b25a8(void *ctx, unsigned char id);
int FUN_002b2ea0(unsigned char id);

int FUN_002b2840(void *ctx, unsigned char id, int *value) {
    struct Descriptor *desc;
    unsigned short raw;

    *value = 0;
    desc = FUN_002b25a8(ctx, id);
    if (desc == 0) {
        return 0;
    }
    if (FUN_002b2ea0(id) != 0xE0) {
        return 0;
    }
    raw = desc->f26;
    *value = raw == 0xFFFF ? 0 : raw;
    return 1;
}

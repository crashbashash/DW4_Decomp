/* 0x002b27d0 — FUN_002b27d0 (112 bytes). Looks up descriptor `id` (FUN_002b25a8) and, when it exists and its tag (FUN_002b2ea0) is 0xE0, returns the byte at +25 through *value; returns 1 then, else 0 with *value = -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Descriptor {
    char pad0[25];
    unsigned char f25; /* +25 */
};

struct Descriptor *FUN_002b25a8(void *ctx, unsigned char id);
int FUN_002b2ea0(unsigned char id);

int FUN_002b27d0(void *ctx, unsigned char id, int *value) {
    struct Descriptor *desc;

    *value = -1;
    desc = FUN_002b25a8(ctx, id);
    if (desc == 0) {
        return 0;
    }
    if (FUN_002b2ea0(id) != 0xE0) {
        return 0;
    }
    *value = desc->f25;
    return 1;
}

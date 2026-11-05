/* 0x002b2ab8 — FUN_002b2ab8 (112 bytes). Looks up descriptor `id` (FUN_002b25a8) and, when it exists and FUN_002b2e60 accepts it, returns bit 0 of the byte at +35 through *value; returns 1 then, else 0 with *value = 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Descriptor {
    char pad0[35];
    unsigned char f35; /* +35 */
};

struct Descriptor *FUN_002b25a8(void *ctx, unsigned char id);
int FUN_002b2e60(unsigned char id, struct Descriptor *desc);

int FUN_002b2ab8(void *ctx, unsigned char id, int *value) {
    struct Descriptor *desc;

    *value = 0;
    desc = FUN_002b25a8(ctx, id);
    if (desc == 0) {
        return 0;
    }
    if (FUN_002b2e60(id, desc) == 0) {
        return 0;
    }
    *value = desc->f35 & 1;
    return 1;
}

/* 0x002b2c10 — FUN_002b2c10 (132 bytes). Looks up descriptor `id` (FUN_002b25a8) and, when it exists and FUN_002b2e60 accepts it, returns the byte at +37 (values of 64 and up read as -1) through *value; returns 1 then, else 0 with *value = -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Descriptor {
    char pad0[37];
    unsigned char f37; /* +37 */
};

struct Descriptor *FUN_002b25a8(void *ctx, unsigned char id);
int FUN_002b2e60(unsigned char id, struct Descriptor *desc);

int FUN_002b2c10(void *ctx, unsigned char id, int *value) {
    struct Descriptor *desc;
    int raw;

    *value = -1;
    desc = FUN_002b25a8(ctx, id);
    if (desc == 0) {
        return 0;
    }
    if (FUN_002b2e60(id, desc) == 0) {
        return 0;
    }
    raw = desc->f37;
    *value = raw;
    if (raw >= 64) {
        *value = -1;
    }
    return 1;
}

/* Looks up descriptor `id` (FUN_002b25a8) and, when it exists and FUN_002b2e60 accepts it, returns
 * the byte at +33 through *value; returns 1 then, else 0 with *value = -1. */
struct Descriptor {
    char pad0[33];
    unsigned char f33; /* +33 */
};

struct Descriptor *FUN_002b25a8(void *ctx, unsigned char id);
int FUN_002b2e60(unsigned char id, struct Descriptor *desc);

int sfd_GetHdrStmInfo(void *ctx, unsigned char id, int *value) {
    struct Descriptor *desc;

    *value = -1;
    desc = FUN_002b25a8(ctx, id);
    if (desc == 0) {
        return 0;
    }
    if (FUN_002b2e60(id, desc) == 0) {
        return 0;
    }
    *value = desc->f33;
    return 1;
}

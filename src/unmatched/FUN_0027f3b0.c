typedef struct EnbayaSlot { unsigned char data[32]; } EnbayaSlot;
typedef struct EnbayaSlotGroup { EnbayaSlot slots[3]; } EnbayaSlotGroup;

typedef struct EnbayaContext {
    char pad0[16];
    EnbayaSlotGroup *groups;     /* +16 */
    char pad20[149];
    unsigned char slot;          /* +169 */
    unsigned char pad170;
    unsigned char external;      /* +171 */
    char pad172[4];
    EnbayaSlotGroup local[1];    /* +176 */
} EnbayaContext;

EnbayaSlot *FUN_0027f3b0(EnbayaContext *ctx, int group) {
    if (ctx->external) {
        return &ctx->groups[group].slots[ctx->slot ^ 1];
    }
    return &ctx->local[group].slots[ctx->slot ^ 1];
}

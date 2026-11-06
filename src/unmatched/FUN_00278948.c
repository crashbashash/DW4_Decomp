/* Clears the two 96-entry word tables a context points at (+8 and +12), zeroes its count at +20
 * and sets +24 to 64. */
typedef struct Ctx_278948 {
    int pad0[2];
    int *table_a;   /* 0x08 */
    int *table_b;   /* 0x0c */
    int pad16;
    int count;      /* 0x14 */
    int limit;      /* 0x18 */
} Ctx_278948;

void FUN_00278948(Ctx_278948 *ctx) {
    int i;

    for (i = 0; i < 96; i++) {
        ctx->table_a[i] = 0;
        ctx->table_b[i] = 0;
    }
    ctx->count = 0;
    ctx->limit = 64;
}

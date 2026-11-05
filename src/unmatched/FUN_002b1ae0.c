/* 0x002b1ae0 — FUN_002b1ae0 (108 bytes). Sets *present to whether stream `id` exists in the context's stream table (FUN_002b1c20 on the object at +4), once FUN_002b1980 reports the table valid; otherwise leaves it 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b1980(void *ctx);
int FUN_002b1c20(void *table, unsigned char id);

struct Context {
    int f0;
    void *table; /* +4 */
};

void FUN_002b1ae0(struct Context *ctx, unsigned char id, int *present) {
    void *table;

    *present = 0;
    table = ctx->table;
    if (FUN_002b1980(ctx) == 0) {
        return;
    }
    if (FUN_002b1c20(table, id) != 0) {
        *present = 1;
    } else {
        *present = 0;
    }
}

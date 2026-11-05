/* 0x002b2358 — FUN_002b2358 (76 bytes). Reads the int at +8 of the stream-info block (+176 of the object at +4) into *value once FUN_002b1980 reports the info valid; returns 1 then, else 0 with *value = 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b1980(void *ctx);

struct Info176 {
    char pad0[8];
    int value; /* +8 */
};

struct Stream {
    char pad0[176];
    struct Info176 info; /* +176 */
};

struct Context {
    int f0;
    struct Stream *stream; /* +4 */
};

int FUN_002b2358(struct Context *ctx, int *value) {
    struct Info176 *info;

    *value = 0;
    info = &ctx->stream->info;
    if (FUN_002b1980(ctx) == 0) {
        return 0;
    }
    *value = info->value;
    return 1;
}

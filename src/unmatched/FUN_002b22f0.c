/* 0x002b22f0 — FUN_002b22f0 (104 bytes). Reads the int at +4 of the stream-info block (+176 of the object at +4) into *value when FUN_002b1980 reports the info valid and the format version (+12) is at least 110; returns 1 then, else 0 with *value = 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b1980(void *ctx);

struct Info176 {
    int f0;
    int value; /* +4 */
};

struct Stream {
    char pad0[176];
    struct Info176 info; /* +176 */
};

struct Context {
    int f0;
    struct Stream *stream; /* +4 */
    int f8;
    int version;           /* +12 */
};

int FUN_002b22f0(struct Context *ctx, int *value) {
    struct Info176 *info;

    *value = 0;
    info = &ctx->stream->info;
    if (FUN_002b1980(ctx) == 0) {
        return 0;
    }
    if (ctx->version < 110) {
        return 0;
    }
    *value = info->value;
    return 1;
}

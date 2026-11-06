/* Reads the int at +0 of the stream-info block (+128 of the object at +4) into *value once
 * FUN_002b1980 reports the info valid; returns 1 then, else 0 with *value = 0. */
int FUN_002b1980(void *ctx);

struct Info128 {
    int value; /* +0 */
};

struct Stream {
    char pad0[128];
    struct Info128 info; /* +128 */
};

struct Context {
    int f0;
    struct Stream *stream; /* +4 */
};

int FUN_002b1f88(struct Context *ctx, int *value) {
    struct Info128 *info;

    *value = 0;
    info = &ctx->stream->info;
    if (FUN_002b1980(ctx) == 0) {
        return 0;
    }
    *value = info->value;
    return 1;
}

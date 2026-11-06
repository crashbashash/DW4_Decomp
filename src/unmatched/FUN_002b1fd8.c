/* Reads the unsigned char at +4 of the stream-info block (+128 of the object at +4) into *value
 * once FUN_002b1980 reports the info valid; returns 1 then, else 0 with *value = -1. */
int FUN_002b1980(void *ctx);

struct Info128 {
    char pad0[4];
    unsigned char value; /* +4 */
};

struct Stream {
    char pad0[128];
    struct Info128 info; /* +128 */
};

struct Context {
    int f0;
    struct Stream *stream; /* +4 */
};

int FUN_002b1fd8(struct Context *ctx, int *value) {
    struct Info128 *info;

    *value = -1;
    info = &ctx->stream->info;
    if (FUN_002b1980(ctx) == 0) {
        return 0;
    }
    *value = info->value;
    return 1;
}

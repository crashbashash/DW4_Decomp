/* Reads the unsigned char at +3 of the stream-info block (+176 of the object at +4) into *value
 * once FUN_002b1980 reports the info valid; returns 1 then, else 0 with *value = 0. */
int FUN_002b1980(void *ctx);

struct Info176 {
    char pad0[3];
    unsigned char value; /* +3 */
};

struct Stream {
    char pad0[176];
    struct Info176 info; /* +176 */
};

struct Context {
    int f0;
    struct Stream *stream; /* +4 */
};

int FUN_002b22a0(struct Context *ctx, int *value) {
    struct Info176 *info;

    *value = 0;
    info = &ctx->stream->info;
    if (FUN_002b1980(ctx) == 0) {
        return 0;
    }
    *value = info->value;
    return 1;
}

/* 0x002b1d48 — FUN_002b1d48 (148 bytes). Copies the 32-character name block (+96 of the object at +4) into `out` as a NUL-terminated string once FUN_002b19c8 reports it valid; returns 1 then, else 0 with an empty string. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void *memset(void *dst, int value, unsigned int size);
int FUN_002b19c8(void *ctx);

struct Name32 {
    char text[32];
};

struct Stream {
    char pad0[96];
    struct Name32 name; /* +96 */
};

struct Context {
    int f0;
    struct Stream *stream; /* +4 */
};

int FUN_002b1d48(struct Context *ctx, char *out) {
    struct Name32 *name;

    *out = '\0';
    name = &ctx->stream->name;
    if (FUN_002b19c8(ctx) == 0) {
        return 0;
    }
    memset(out, 0, sizeof(struct Name32) + 1);
    *(struct Name32 *)out = *name;
    return 1;
}

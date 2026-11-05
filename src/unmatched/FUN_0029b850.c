/* 0x0029b850 — FUN_0029b850 (136 bytes). Passes a chunk to the sink: whole through slot 28 when length is 0, otherwise split at length by FUN_0027d470, head through slot 32 and remainder through slot 28. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0027d470();

/* A data chunk as split by FUN_0027d470: start pointer and length. */
struct Chunk {
    char *data;
    int size;
};
struct Sink;
struct SinkVtbl {
    char pad[28];
    void (*fn28)(struct Sink *, int, struct Chunk *);
    void (*fn32)(struct Sink *, int, struct Chunk *);
};
struct Sink {
    struct SinkVtbl *vt;
};

void FUN_0029b850(struct Sink *sink, int length, struct Chunk *chunk) {
    struct Chunk rest;

    if (length == 0) {
        sink->vt->fn28(sink, 0, chunk);
        return;
    }
    FUN_0027d470(chunk, length, chunk, &rest);
    sink->vt->fn32(sink, 1, chunk);
    sink->vt->fn28(sink, 0, &rest);
}

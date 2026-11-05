/* 0x002a9ba0 — FUN_002a9ba0 (36 bytes). Runs FUN_002a9310 on the play state's buffer at +4376; returns 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdPlayState {
    char pad0[4376];
    char buf[4];            /* +4376 */
} SfdPlayState;

typedef struct SfdHandle {
    char pad0[8120];
    SfdPlayState *play;     /* +8120 */
} SfdHandle;

extern void FUN_002a9310(void *buf);

int FUN_002a9ba0(int unused0, int unused1, SfdHandle *handle) {
    FUN_002a9310(handle->play->buf);
    return 1;
}

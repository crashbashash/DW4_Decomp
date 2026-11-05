/* 0x002970b0 — FUN_002970b0 (52 bytes). Sets stream parameter 37 of a non-NULL handle through FUN_002ad950. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_002ad950(int stream, int param, int value);

typedef struct {
    char pad0[64];
    int stream;   /* 64 */
} Ply2970b0;

void FUN_002970b0(Ply2970b0 *ply, int value) {
    /* matching construct: manual — retail reads +64 before the NULL test (load in the
     * branch delay slot); testing first and loading inside the branch does not match. */
    int stream = ply->stream;

    if (ply != 0) {
        FUN_002ad950(stream, 37, value);
    }
}

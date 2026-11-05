/* 0x00295438 — FUN_00295438 (44 bytes). Passes the handle's stream (+64) to FUN_002ac418 unless `index` is negative. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_002ac418(int stream, int index);

typedef struct {
    char pad0[64];
    int stream;   /* 64 */
} Sfd295438;

void FUN_00295438(Sfd295438 *sfd, int index) {
    int stream = sfd->stream;

    if (index >= 0) {
        FUN_002ac418(stream, index);
    }
}

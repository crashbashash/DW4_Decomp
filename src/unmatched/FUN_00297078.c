extern void FUN_002ad950(int stream, int param, int value);

typedef struct {
    char pad0[64];
    int stream;   /* 64 */
} Ply297078;

void FUN_00297078(Ply297078 *ply, int value) {
    int stream = ply->stream;

    if (ply != 0) {
        FUN_002ad950(stream, 36, value);
    }
}

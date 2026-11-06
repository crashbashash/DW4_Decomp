/* Returns word +52 of the handle's record at +8052, or -1 without a handle. */
typedef struct SfdRecord8052 {
    char pad0[52];
    int f52;
} SfdRecord8052;

typedef struct SfdHandle {
    char pad0[8052];
    SfdRecord8052 *record;  /* +8052 */
} SfdHandle;

int FUN_002a1048(SfdHandle *handle) {
    if (handle == 0) {
        return -1;
    }
    return handle->record->f52;
}

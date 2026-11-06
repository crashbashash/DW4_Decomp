/* Resets a record: three zeroed words, then -1, -1, 0 and -1 in the block at +16. */
typedef struct SfdBlock16 {
    long f0;                /* one 64-bit store of -1 covers +16..+23 */
    int f8;
    int f12;
} SfdBlock16;

typedef struct SfdRecord {
    int f0;
    int f4;
    int f8;
    int f12;
    SfdBlock16 block;       /* +16 */
} SfdRecord;

void FUN_002a5060(SfdRecord *record) {
    SfdBlock16 *block = &record->block;

    record->f0 = 0;
    record->f4 = 0;
    record->f8 = 0;
    block->f0 = -1;
    block->f12 = -1;
    block->f8 = 0;
}

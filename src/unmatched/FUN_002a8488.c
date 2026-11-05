/* 0x002a8488 — FUN_002a8488 (72 bytes). Finds the 136-byte record (at +5800) paired with a given 232-byte slot of the play state; NULL if none. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdPlaySlot {
    char pad0[232];
} SfdPlaySlot;

typedef struct SfdPlayState {
    char pad0[376];
    int slotCount;          /* +376 */
    int pad380;
    SfdPlaySlot slots[1];   /* +384 */
} SfdPlayState;

typedef struct SfdPlayRecord {
    char pad0[136];
} SfdPlayRecord;

typedef struct SfdHandle {
    char pad0[5800];
    SfdPlayRecord records[1]; /* +5800 */
    char pad5936[2184];
    SfdPlayState *play;     /* +8120 */
} SfdHandle;

SfdPlayRecord *FUN_002a8488(SfdHandle *handle, SfdPlaySlot *target) {
    SfdPlayState *play = handle->play;
    int i = 0;
    int count = play->slotCount;
    SfdPlaySlot *slot = play->slots;
    SfdPlayRecord *record;

    if (count > 0) {
        record = handle->records;
        do {
            /* matching construct: hand — the candidate is taken before the
               advance, so the compare sits in the copy's delay slot */
            SfdPlayRecord *found = record;
            record++;
            if (slot == target) {
                return found;
            }
            i++;
            slot++;
        } while (i < count);
    }
    return 0;
}

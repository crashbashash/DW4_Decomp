/* Returns the context slot whose 136-byte record (at +5800) has the given body pointer, or 0. */
/* One 232-byte decode slot. */
struct Slot {
    int state;                            /* 2/4 = holding a picture */
    char pad4[232 - 4];
};
struct Context {
    char pad0[124];
    int f124;
    char pad128[376 - 128];
    int slotCount;                        /* +376 */
    int pad380;
    struct Slot slots[16];                /* +384 */
};
/* One 136-byte record per slot; +8 holds the slot's id. */
struct Record {
    int f0;
    int f4;
    char body[136 - 8];                   /* +8: identifies the slot */
};
struct Player2a8440 {
    char pad0[5800];
    struct Record records[16];            /* +5800 */
    char pad7976[8120 - 5800 - 16 * 136];
    struct Context *context;              /* +8120 */
};

/* Returns the slot whose record body is `body`, or 0. */
struct Slot *FUN_002a8440(struct Player2a8440 *player, char *body) {
    struct Record *record = player->records;
    struct Slot *slot = player->context->slots;
    int i;

    for (i = 0; i < 16; i++) {
        if (record->body == body) {
            return slot;
        }
        record++;
        slot++;
    }
    return 0;
}

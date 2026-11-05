/* 0x00281d80 — FUN_00281d80 (108 bytes). Copies a 4-word message, passes words 1 and 2 to the context's notification callback when both it and word 2 are set, clears the in-handler flag and re-enables interrupts. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Message00281d80 {
    int word[4];
};

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx00281d80 {
    char pad0[5024];
    void (*notify)(int a, int b); /* +5024 */
};

extern struct Ctx00281d80 *DAT_004bb114;
extern int DAT_00571700; /* cleared before interrupts are re-enabled */

void FUN_00281d80(struct Message00281d80 *message) {
    struct Message00281d80 copy;
    int *src = message->word;
    int *dst = copy.word;
    int i;

    for (i = 0; i < 4; i++) {
        *dst++ = *src++;
    }
    if (DAT_004bb114->notify != 0 && copy.word[2] != 0) {
        DAT_004bb114->notify(copy.word[1], copy.word[2]);
    }
    DAT_00571700 = 0;
    /* asm-body: reason=EE sync/ei have no C spelling tried=n/a (two privileged instructions only) */
    __asm__ volatile ("sync");
    __asm__ volatile ("ei");
}

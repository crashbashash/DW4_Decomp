/* 0x002aac38 — FUN_002aac38 (136 bytes). Issues FUN_002ada78(obj, 15, n) for whichever pending request at +0xA18/+0xA1C is clear while the mode at +0xA40 asks for it. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002ada78(int obj, int code, int channel);

struct PendingPair {
    char pad0[20];
    int request1; /* +20 */
    int request2; /* +24 */
    char pad28[60 - 28];
    int mode;     /* +60 */
};

void FUN_002aac38(int obj) {
    struct PendingPair *pending = (struct PendingPair *)(obj + 0xA04);

    if (pending->request2 == 0 && pending->mode == 2) {
        FUN_002ada78(obj, 15, 1);
    }
    if (pending->request1 == 0 && pending->mode == 1) {
        FUN_002ada78(obj, 15, 2);
    }
}

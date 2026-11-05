/* 0x0027a8b0 — FUN_0027a8b0 (44 bytes). Stores a byte into +80 of an object while the library is active (not mode 1
   with no entries). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Object27a {
    char pad0[80];
    signed char flag80;   /* +80 */
};

extern int DAT_004b1dc0;
extern int DAT_004b1dc8;

void FUN_0027a8b0(struct Object27a *object, int value) {
    if (DAT_004b1dc8 != 1 || DAT_004b1dc0 > 0) {
        object->flag80 = value;
    }
}

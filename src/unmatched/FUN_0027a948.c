/* 0x0027a948 — FUN_0027a948 (44 bytes). Stores a byte into +91 of an object while the library is active (not mode 1
   with no entries). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Object27a {
    char pad0[91];
    signed char flag91;   /* +91 */
};

extern int DAT_004b1dc0;
extern int DAT_004b1dc8;

void FUN_0027a948(struct Object27a *object, int value) {
    if (DAT_004b1dc8 != 1 || DAT_004b1dc0 > 0) {
        object->flag91 = value;
    }
}

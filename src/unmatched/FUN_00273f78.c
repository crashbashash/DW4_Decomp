/* 0x00273f78 — FUN_00273f78 (88 bytes). Shuts an object down: when its state byte (+2) is 2 or more it is
   stopped through FUN_00274248 first, then the in-use byte (+0) is cleared and FUN_00273de0 releases it.
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Object273 {
    unsigned char used;   /* +0 */
    unsigned char f1;
    unsigned char state;  /* +2 */
};

extern void FUN_00274248(struct Object273 *object);
extern void FUN_00273de0(struct Object273 *object);

void FUN_00273f78(struct Object273 *object) {
    if (object != 0) {
        if (object->state >= 2) {
            FUN_00274248(object);
        }
        object->used = 0;
        FUN_00273de0(object);
    }
}

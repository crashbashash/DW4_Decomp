/* 0x00269498 — FUN_00269498 (104 bytes). Between FUN_0025f2d0 and FUN_0025f2e8, releases the two resources at offsets 128 and 132 with FUN_00267da0 and clears the in-use word. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Object_269498 {
    int used;           /* 0x00 */
    char pad4[124];
    void *first;        /* 0x80 */
    void *second;       /* 0x84 */
} Object_269498;

void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void FUN_00267da0(void *resource);

void FUN_00269498(Object_269498 *object) {
    if (object == 0) {
        return;
    }
    FUN_0025f2d0();
    if (object->first != 0) {
        FUN_00267da0(object->first);
    }
    if (object->second != 0) {
        FUN_00267da0(object->second);
    }
    object->used = 0;
    FUN_0025f2e8();
}

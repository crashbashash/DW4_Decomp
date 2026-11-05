/* 0x002960e8 — FUN_002960e8 (100 bytes). Gets object 8 from FUN_00102df0, stores `owner` at its +128 and passes `data` with size/16 to FUN_001032c0; returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Object002960e8 {
    char pad0[128];
    int owner; /* +128 */
};

struct Object002960e8 *FUN_00102df0(int id);
void FUN_001032c0(struct Object002960e8 *object, void *data, int count);

int FUN_002960e8(int owner, int size, void *data) {
    struct Object002960e8 *object = FUN_00102df0(8);

    object->owner = owner;
    FUN_001032c0(object, data, size / 16);
    return 0;
}

/* 0x002961c0 — FUN_002961c0 (100 bytes). Gets object 9 from FUN_00102df0, stores `owner` at its +128 and passes `data` with size/16 to FUN_00103188; returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Object002961c0 {
    char pad0[128];
    int owner; /* +128 */
};

struct Object002961c0 *FUN_00102df0(int id);
void FUN_00103188(struct Object002961c0 *object, void *data, int count);

int FUN_002961c0(void *data, int size, int owner) {
    struct Object002961c0 *object = FUN_00102df0(9);

    object->owner = owner;
    FUN_00103188(object, data, size / 16);
    return 0;
}

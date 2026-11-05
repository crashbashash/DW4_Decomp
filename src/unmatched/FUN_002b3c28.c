/* 0x002b3c28 — FUN_002b3c28 (76 bytes). Calls FUN_002b3c88(obj, 100), then stores value into word `index` of the array at +64. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b3c88();

struct Obj0040 {
    char pad[64];
    int values[1];                        /* +64; length not shown here */
};

void FUN_002b3c28(struct Obj0040 *obj, int index, int value) {
    FUN_002b3c88(obj, 100);
    obj->values[index] = value;
}

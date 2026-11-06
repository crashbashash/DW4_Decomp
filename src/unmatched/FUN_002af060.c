/* Stores value into word slot `index` of the array at +3368. */

struct Obj0D28 {
    char pad[3368];
    int slot0;                            /* +3368 (0xD28): first of an int array; length not shown here */
};

void FUN_002af060(struct Obj0D28 *obj, int value, int index) {
    /* matching construct: manual — stepping the object pointer by `index` words (a0 += index*4) is retail's address order */
    obj = (struct Obj0D28 *)((int *)obj + index);
    obj->slot0 = value;
}

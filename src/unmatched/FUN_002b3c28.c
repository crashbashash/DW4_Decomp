/* Calls FUN_002b3c88(obj, 100), then stores value into word `index` of the array at +64. */
int FUN_002b3c88();

struct Obj0040 {
    char pad[64];
    int values[1];                        /* +64; length not shown here */
};

void FUN_002b3c28(struct Obj0040 *obj, int index, int value) {
    FUN_002b3c88(obj, 100);
    obj->values[index] = value;
}

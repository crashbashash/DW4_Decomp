/* Returns FUN_002977d8 of the object's +8/+12 pair, plus 0x20000 when FUN_00298260 reports 1. */
extern int FUN_002977d8(int a, int b);
extern int FUN_00298260(void *obj);

typedef struct {
    char pad0[8];
    int f8;
    int f12;
} Obj291c28;

int FUN_00291c28(Obj291c28 *obj) {
    int size = FUN_002977d8(obj->f8, obj->f12);

    if (FUN_00298260(obj) == 1) {
        size += 0x20000;
    }
    return size;
}

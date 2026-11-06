/* Clears the three words at +184 and the eight 20-byte entries at +196 (last word 17), then calls
 * FUN_00297f18(obj, 0). */
extern void FUN_00297f18(void *obj, int arg);

typedef struct {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
} Entry2945c8;

typedef struct {
    char pad0[184];
    int f184;
    int f188;
    int f192;
    Entry2945c8 entries[8]; /* 196 */
} Obj2945c8;

void FUN_002945c8(Obj2945c8 *obj) {
    int i;

    obj->f184 = 0;
    obj->f188 = 0;
    obj->f192 = 0;
    for (i = 0; i < 8; i++) {
        obj->entries[i].f0 = 0;
        obj->entries[i].f4 = 0;
        obj->entries[i].f8 = 0;
        obj->entries[i].f12 = 0;
        obj->entries[i].f16 = 17;
    }
    FUN_00297f18(obj, 0);
}

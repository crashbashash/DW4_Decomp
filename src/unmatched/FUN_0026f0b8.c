/* Unless the object is busy, stores four arguments and kind 1; returns 1, or 0 when busy. */
typedef struct Object_26f058 {
    char pad0[12];
    int busy;           /* 0x0c: the call is refused while non-zero */
    char pad16[4];
    int kind;           /* 0x14 */
    int f24;            /* 0x18 */
    int f28;            /* 0x1c */
    int f32;            /* 0x20 */
    int f36;            /* 0x24 */
} Object_26f058;

int FUN_0026f0b8(Object_26f058 *object, int f24, int f28, int f32, int f36) {
    if (object->busy == 0) {
        object->f36 = f36;
        object->f24 = f24;
        object->f28 = f28;
        object->f32 = f32;
        object->kind = 1;
        return 1;
    }
    return 0;
}

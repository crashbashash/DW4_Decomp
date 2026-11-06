/* Stores b at offset 24 and a at offset 28 of an object; returns 1. */
typedef struct Object_26a9d8 {
    char pad0[24];
    int f24;            /* 0x18 */
    int f28;            /* 0x1c */
} Object_26a9d8;

int FUN_0026a9d8(Object_26a9d8 *object, int a, int b) {
    object->f28 = a;
    object->f24 = b;
    return 1;
}

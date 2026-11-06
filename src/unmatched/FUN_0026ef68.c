/* Calls FUN_0025f300(c, b, &object->f48, &object->f50). */
typedef struct Object_26ef68 {
    char pad0[48];
    short f48;          /* 0x30 */
    short f50;          /* 0x32 */
} Object_26ef68;

void FUN_0025f300(int a, int b, short *first, short *second);

void FUN_0026ef68(Object_26ef68 *object, int b, int a) {
    FUN_0025f300(a, b, &object->f48, &object->f50);
}

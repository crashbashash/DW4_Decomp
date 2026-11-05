/* 0x00267378 — FUN_00267378 (88 bytes). Returns FUN_0025db78 of the object handle when FUN_0025db70 reports a positive value and the state is 2 or 3, else 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* Object layout shared by FUN_00265fb0, FUN_00266298, FUN_002662c8 and FUN_00266be0 (offsets from their accesses). */
typedef struct Object_265fb0 {
    char f0;
    char state;         /* 0x01: 1 after FUN_00266298, 0 after FUN_002662c8, 2 in FUN_00266d20 */
    char f2;
    char f3;            /* 0x03 */
    void *handle;       /* 0x04 */
    char pad8[36];
    int f44;            /* 0x2c */
    int f48;            /* 0x30 */
    int f52;            /* 0x34 */
    int f56;            /* 0x38: reset to 0x7FFFFFFF */
    int f60;            /* 0x3c: reset to -1 */
    int f64;            /* 0x40 */
    int f68;            /* 0x44 */
    char pad72[80];
    int f152;           /* 0x98 */
    int f156;
    int f160;           /* 0xa0 */
    int f164;           /* 0xa4 */
} Object_265fb0;
int FUN_0025db70(void *handle);    /* 0x25db70: returns the word at offset 204 */
short FUN_0025db78(void *handle);  /* 0x25db78: returns the halfword at offset 224 */

int FUN_00267378(Object_265fb0 *object) {
    if (FUN_0025db70(object->handle) > 0 && (object->state == 2 || object->state == 3)) {
        return FUN_0025db78(object->handle);
    }
    return 0;
}

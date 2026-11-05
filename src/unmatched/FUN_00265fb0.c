/* 0x00265fb0 — FUN_00265fb0 (60 bytes). Resets the counters of an object: field 60 to -1, field 56 to 0x7FFFFFFF, the rest to 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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

void FUN_00265fb0(Object_265fb0 *object) {
    object->f60 = -1;
    object->f56 = 0x7FFFFFFF;
    object->f164 = 0;
    object->f152 = 0;
    object->f44 = 0;
    object->f48 = 0;
    object->f52 = 0;
    object->f64 = 0;
    object->f68 = 0;
    /* matching construct: permuter — the do/while(0) keeps ee-gcc from scheduling the f160 store above this byte store */
    do {
        object->f3 = 0;
    } while (0);
    object->f160 = 0;
}

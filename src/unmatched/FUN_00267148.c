/* 0x00267148 — FUN_00267148 (96 bytes). Between FUN_0025f2d0 and FUN_0025f2e8, adds a positive amount to field 160 or subtracts a non-positive one from field 164; returns the amount. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);

int FUN_00267148(Object_265fb0 *object, int amount) {
    FUN_0025f2d0();
    if (amount > 0) {
        object->f160 += amount;
    } else {
        object->f164 -= amount;
    }
    FUN_0025f2e8();
    return amount;
}

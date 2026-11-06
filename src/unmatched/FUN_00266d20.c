/* Per-update step: runs FUN_00266dc8 while field 160 is positive, dispatches on the state (2:
 * FUN_00266c70, 1: FUN_002662f8), then runs FUN_00266f18 while field 164 is positive; each guarded
 * call sits between FUN_0025f2d0 and FUN_0025f2e8. */
/* Object layout shared by FUN_00265fb0, FUN_00266298, FUN_002662c8 and FUN_00266be0. */
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
void FUN_00266dc8(Object_265fb0 *object);
void FUN_00266c70(Object_265fb0 *object);
void FUN_002662f8(Object_265fb0 *object);
void FUN_00266f18(Object_265fb0 *object);

void FUN_00266d20(Object_265fb0 *object) {
    if (object->f160 > 0) {
        FUN_0025f2d0();
        FUN_00266dc8(object);
        FUN_0025f2e8();
    }
    if (object->state == 2) {
        FUN_00266c70(object);
    } else if (object->state == 1) {
        FUN_002662f8(object);
    }
    if (object->f164 > 0) {
        FUN_0025f2d0();
        FUN_00266f18(object);
        FUN_0025f2e8();
    }
}

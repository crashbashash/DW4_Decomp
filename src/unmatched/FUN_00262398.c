/* Between FUN_0025f2d0 and FUN_0025f2e8, runs FUN_002622d0 on each of the 16 68-byte records in
 * DAT_00499de8 whose first byte is 1. */
typedef struct Object_262398 {
    char used; /* 0x00 */
    char rest[67];
} Object_262398;

extern Object_262398 DAT_00499de8[16];
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void FUN_002622d0(Object_262398 *object);

void FUN_00262398(void) {
    int remaining;
    Object_262398 *object;

    remaining = 15;
    FUN_0025f2d0();
    object = DAT_00499de8;
    do {
        if (object->used == 1) {
            FUN_002622d0(object);
        }
        remaining--;
        object++;
    } while (remaining >= 0);
    FUN_0025f2e8();
}

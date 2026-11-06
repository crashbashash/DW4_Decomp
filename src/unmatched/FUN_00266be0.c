/* Advances an object by the smaller of FUN_0025def8 and the remaining FUN_0025db20 - field 52
 * (adding it to fields 52 and 44) and adds FUN_0025def0 to field 48. */
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
int FUN_0025db20(void *handle);
int FUN_0025def0(void *handle);
int FUN_0025def8(void *handle);

void FUN_00266be0(Object_265fb0 *object) {
    void *handle = object->handle;
    int total = FUN_0025db20(handle);
    int added = FUN_0025def0(handle);
    int step = FUN_0025def8(handle);
    int remaining = total - object->f52;

    if (step < remaining) {
        remaining = step;
    }
    /* matching construct: permuter — the three updates moved from f52, f44, f48 order to this one */
    object->f44 += remaining;
    object->f48 += added;
    object->f52 += remaining;
}

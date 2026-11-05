/* 0x0025da78 — FUN_0025da78 (44 bytes). Reports the object's state byte (+14), except that state 1 reads as 2
 * once the word at +232 is set. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Obj25da78 {
    char pad0[14];
    signed char state;      /* +14 */
    char pad15[217];
    int f232;               /* +232 */
} Obj25da78;

int FUN_0025da78(Obj25da78 *obj) {
    if (obj->state == 1 && obj->f232 != 0) {
        return 2;
    }
    return obj->state;
}

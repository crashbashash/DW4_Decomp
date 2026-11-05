/* 0x00293958 — FUN_00293958 (80 bytes). Takes the +44 value of `src` into the object's +420 word, first calling FUN_00298420 when it grows. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00298420(void *obj);

typedef struct {
    char pad0[420];
    int f420;
} Obj293958;

typedef struct {
    char pad0[44];
    int f44;
} Src293958;

void FUN_00293958(Obj293958 *obj, Src293958 *src) {
    if (obj->f420 < src->f44) {
        FUN_00298420(obj);
    }
    obj->f420 = src->f44;
}

/* 0x0028f0d8 — FUN_0028f0d8 (40 bytes). Copies the first and third words of the record at +1000 out through the optional pointers. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct {
    int f0;
    int f4;
    int f8;
} Rec28f0d8;

typedef struct {
    char pad0[1000];
    Rec28f0d8 rec; /* 1000 */
} Obj28f0d8;

void FUN_0028f0d8(Obj28f0d8 *obj, int *out0, int *out8) {
    Rec28f0d8 *rec = &obj->rec;

    if (out0 != 0) {
        *out0 = rec->f0;
    }
    if (out8 != 0) {
        *out8 = rec->f8;
    }
}

/* 0x00298378 — FUN_00298378 (28 bytes). Sets the +420 word to -1 and clears the three words at +424. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct {
    int f0;
    int f4;
    int f8;
} Rec298378;

typedef struct {
    char pad0[420];
    int f420;
    Rec298378 rec; /* 424 */
} Obj298378;

void FUN_00298378(Obj298378 *obj) {
    Rec298378 *rec = &obj->rec;

    rec->f0 = 0;
    rec->f4 = 0;
    rec->f8 = 0;
    obj->f420 = -1;
}

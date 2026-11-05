/* 0x00267de8 — FUN_00267de8 (88 bytes). Converts (id, arg) into a pair of shorts through FUN_0025f300 and applies the pair to the object (FUN_00267dd8) and to its resource at +136 (FUN_00267c50). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Obj_267de8 {
    char pad0[136];
    int resource;   /* 0x88 */
} Obj_267de8;

int FUN_0025f300(short id, int arg, short *first, short *second);
int FUN_00267dd8(Obj_267de8 *obj, short first, short second);
int FUN_00267c50(int resource, short first, short second);

void FUN_00267de8(Obj_267de8 *obj, short id, int arg) {
    short first;
    short second;

    FUN_0025f300(id, arg, &first, &second);
    FUN_00267dd8(obj, first, second);
    FUN_00267c50(obj->resource, first, second);
}

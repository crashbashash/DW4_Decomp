/* 0x0027bfd0 — FUN_0027bfd0 (76 bytes). Returns the word at +12 for query 1 or at +16 for query 0; any other query is reported to the error callback (+56, with its object +60 and code -3) and returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Obj_27bfd0 {
    char pad0[12];
    int value1;                                 /* 0x0c */
    int value0;                                 /* 0x10 */
    char pad20[36];
    void (*error)(int object, int code);        /* 0x38 */
    int error_object;                           /* 0x3c */
} Obj_27bfd0;

int FUN_0027bfd0(Obj_27bfd0 *obj, int query) {
    if (query == 1) {
        return obj->value1;
    }
    if (query == 0) {
        return obj->value0;
    }
    if (obj->error != 0) {
        obj->error(obj->error_object, -3);
    }
    return 0;
}


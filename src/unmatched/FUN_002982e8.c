/* 0x002982e8 — FUN_002982e8 (48 bytes). Calls vtable slot +12 of the stream joint held at +400, if any. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SjObj SjObj;
typedef struct {
    char pad0[12];
    void (*fn12)(SjObj *sj); /* 12 */
} SjVtbl;
struct SjObj {
    SjVtbl *vtbl;
};

typedef struct {
    char pad0[400];
    SjObj *sj;    /* 400 */
} Obj2982e8;

void FUN_002982e8(Obj2982e8 *obj) {
    SjObj *sj = obj->sj;

    if (sj != 0) {
        sj->vtbl->fn12(sj);
    }
}

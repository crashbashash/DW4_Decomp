/* 0x00298398 — FUN_00298398 (48 bytes). Calls vtable slot +20 of the stream joint held at +400, if any. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SjObj SjObj;
typedef struct {
    char pad0[20];
    void (*fn20)(SjObj *sj); /* 20 */
} SjVtbl;
struct SjObj {
    SjVtbl *vtbl;
};

typedef struct {
    char pad0[400];
    SjObj *sj;    /* 400 */
} Obj298398;

void FUN_00298398(Obj298398 *obj) {
    SjObj *sj = obj->sj;

    if (sj != 0) {
        sj->vtbl->fn20(sj);
    }
}
